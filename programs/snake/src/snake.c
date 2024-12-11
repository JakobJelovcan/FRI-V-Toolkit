#include <snake/snake.h>
#include <stdlib.h>
#include <unistd.h>

const char game_over_str[] = "\033cGame over";
const char game_paused_str[] = "\033cGame paused";

bool valid_position(snake_t* snake) {
    if (snake->parts[0].x < 0 || snake->parts[0].x >= DIM_X || snake->parts[0].y < 0 || snake->parts[0].y >= DIM_Y)
        return false;

    for (uint16_t i = 1; i < snake->length; ++i) {
        if ((snake->parts[0].x == snake->parts[i].x) && (snake->parts[0].y == snake->parts[i].y))
            return false;
    }

    return true;
}

apple_t generate_apple(snake_t* snake) {
    apple_t apple;
    apple.x = ((uint8_t) rand()) % DIM_X;
    apple.y = ((uint8_t) rand()) % DIM_Y;
    return apple;
}

void initialize(game_t* game) {
    game->snake.parts = (snake_section_t*) malloc(MAX_SNAKE_LENGTH * sizeof(snake_section_t));
    game->buffer = (buffer_t*) malloc(sizeof(buffer_t));
    reset_game(game);
}

void reset_game(game_t* game) {
    game->snake.direction = Right;
    game->snake.length = 1;
    game->snake.parts[0].x = 0;
    game->snake.parts[0].y = 0;
    game->buffer->command = 0x631b;
    game->buffer->terminator = 0;

    game->score = 0;
    game->apple_count = 0;
    game->apple = generate_apple(&(game->snake));
    game->game_over = false;
}

void update_snake(game_t* game) {
    if (game->game_over || game->game_paused)
        return;

    snake_section_t head = game->snake.parts[0];
    switch (game->snake.direction) {
        case Up:
            --head.y;
            break;
        case Down:
            ++head.y;
            break;
        case Left:
            --head.x;
            break;
        case Right:
            ++head.x;
            break;
    }

    if (head.x == game->apple.x && head.y == game->apple.y) {
        ++game->snake.length;
        ++game->apple_count;
        game->apple = generate_apple(&(game->snake));
    }

    for (uint16_t i = game->snake.length - 1; i > 0; --i) {
        game->snake.parts[i] = game->snake.parts[i - 1];
    }

    game->snake.parts[0] = head;

    game->game_over = !valid_position(&(game->snake));
}

void process_input(game_t* game, uint8_t chr) {
    switch (chr) {
        case 'A':
        case 'a':
            game->snake.direction = Left;
            break;
        case 'W':
        case 'w':
            game->snake.direction = Up;
            break;
        case 'S':
        case 's':
            game->snake.direction = Down;
            break;
        case 'D':
        case 'd':
            game->snake.direction = Right;
            break;
        case 'P':
        case 'p':
            game->game_paused = !game->game_paused;
            break;
        case 'R':
        case 'r':
            reset_game(game);
            break;
    }
}

void draw_field(game_t* game) {
    for (uint32_t y = 0; y < BUF_Y; ++y) {
        for (uint32_t x = 0; x < BUF_X; ++x) {
            if (y == 0 && x == 0 || y == 0 && x == BUF_X - 2 || y == BUF_Y - 1 && x == 0 || y == BUF_Y - 1 && x == BUF_X - 2)
                game->buffer->field[y][x] = '+';
            else if (x == BUF_X - 1)
                game->buffer->field[y][x] = '\n';
            else if (x == 0 || x == BUF_X - 2)
                game->buffer->field[y][x] = '|';
            else if (y == 0 || y == BUF_Y - 1)
                game->buffer->field[y][x] = '-';
            else
                game->buffer->field[y][x] = ' ';
        }
    }
}

void draw_snake(game_t* game) {
    for (uint32_t i = 0; i < game->snake.length; ++i) {
        const snake_section_t part = game->snake.parts[i];
        game->buffer->field[part.y + 1][part.x + 1] = 'S';
    }
}

void draw_apple(game_t* game) {
    const apple_t apple = game->apple;
    game->buffer->field[apple.y + 1][apple.x + 1] = 'A';
}

void* draw(game_t* game) {
    if (game->game_over)
        return (void*) game_over_str;
    else if (game->game_paused)
        return (void*) game_paused_str;

    draw_field(game);
    draw_snake(game);
    draw_apple(game);
    return (void*) game->buffer;
}
