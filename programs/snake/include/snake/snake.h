#pragma once
#include <inttypes.h>
#include <stdbool.h>

#define DIM_X 20
#define DIM_Y 20

#define BUF_X (DIM_X + 3)
#define BUF_Y (DIM_Y + 2)

#define MAX_SNAKE_LENGTH (DIM_X * DIM_Y)

typedef struct {
    uint16_t command;
    uint8_t field[BUF_Y][BUF_X];
    uint8_t terminator;
} buffer_t;

typedef enum {
    Up,
    Down,
    Left,
    Right,
} direction_t;

typedef struct {
    int8_t x;
    int8_t y;
} snake_section_t;

typedef struct {
    snake_section_t* parts;
    direction_t direction;
    uint16_t length;
} snake_t;

typedef struct {
    int8_t x;
    int8_t y;
} apple_t;

typedef struct {
    uint32_t score;
    uint32_t apple_count;
    snake_t snake;
    apple_t apple;
    bool game_over;
    bool game_paused;
    buffer_t* buffer;
} game_t;

void initialize(game_t* game);
void reset_game(game_t* game);
void update_snake(game_t* game);
void process_input(game_t* game, uint8_t chr);
void* draw(game_t* game);