#include <stddef.h>

const int matrix1[3][3] = {{-2, -1, 2}, {2, 1, 4}, {-3, 3, -1}};
const int matrix2[3][3] = {{102, 18, 36}, {1, 3, 4}, {17, 3, 6}};
const int matrix3[3][3] = {{2, 3, 1}, {1, 0, 5}, {2, 3, 1}};
const int matrix4[3][3] = {{3, 3, 0}, {2, 1, 1}, {5, 0, 1}};

int determinant(const int matrix[3][3]) {
    int determinant = 0;
    for (int i = 0; i < 3; ++i) {
        int diag1 = 1;
        int diag2 = 1;
        for (int j = 0; j < 3; ++j) {
            diag1 *= matrix[j][(3 + j + i) % 3];
            diag2 *= matrix[j][(3 - j + i) % 3];
        }
        determinant += diag1 - diag2;
    }
    return determinant;
}

int main() {
    if (determinant(matrix1) != 54)
        return 1;
    else if (determinant(matrix2) != 0)
        return 2;
    else if (determinant(matrix3) != 0)
        return 3;
    else if (determinant(matrix4) != 12)
        return 4;
    return 0;
}