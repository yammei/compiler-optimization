#include <iostream>
#include <ctime>
#include <cstdlib>

const int MATRIX_SIZE = 500; // Change this value to increase matrix A and B
const int TILE_SIZE = 25; // Change this value to adjust tile size (Use 1, 25, 100).

// Function to initialize a matrix with random values
void initializeMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = rand() % 10; // Fill with random values (0 to 9)
        }
    }
}

// Function to multiply two matrices using loop tiling
void multiplyMatricesWithTiling(int A[MATRIX_SIZE][MATRIX_SIZE], int B[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i0 = 0; i0 < MATRIX_SIZE; i0 += TILE_SIZE) {
        for (int j0 = 0; j0 < MATRIX_SIZE; j0 += TILE_SIZE) {
            for (int k0 = 0; k0 < MATRIX_SIZE; k0 += TILE_SIZE) {
                for (int i = i0; i < i0 + TILE_SIZE; i++) {
                    for (int j = j0; j < j0 + TILE_SIZE; j++) {
                        for (int k = k0; k < k0 + TILE_SIZE; k++) {
                            result[i][j] += A[i][k] * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    int matrixA[MATRIX_SIZE][MATRIX_SIZE];
    int matrixB[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

    // Seed the random number generator
    srand(time(nullptr));

    double average_time = 0.0;
    int num_trials = 3;

    for (int trial = 0; trial < num_trials; trial++) {
        // Initialize the matrices with random values
        initializeMatrix(matrixA);
        initializeMatrix(matrixB);

        clock_t start_time = clock();

        // Multiply the matrices using loop tiling
        multiplyMatricesWithTiling(matrixA, matrixB, resultMatrix);

        clock_t end_time = clock();
        double processing_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

        std::cout << "Matrix multiplication time with loop tiling (Trial " << trial + 1 << "): " << processing_time << " seconds" << std::endl;

        average_time += processing_time;
    }

    average_time /= num_trials;

    std::cout << "Average time over " << num_trials << " trials: " << average_time << " seconds" << std::endl;

    return 0;
}
