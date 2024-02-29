#include <iostream>
#include <ctime>
#include <cstdlib>

const int MATRIX_SIZE = 500; // Change this value to increase matrix A and B

// Function to initialize a matrix with random values
void initializeMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = rand() % 10; // Fill with random values (0 to 9)
        }
    }
}

// Function to multiply two matrices without loop tiling
void multiplyMatrices(int A[MATRIX_SIZE][MATRIX_SIZE], int B[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            for (int k = 0; k < MATRIX_SIZE; k++) {
                result[i][j] += A[i][k] * B[k][j];
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

        // Multiply the matrices without loop tiling
        multiplyMatrices(matrixA, matrixB, resultMatrix);

        clock_t end_time = clock();
        double processing_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

        std::cout << "Matrix multiplication time without loop tiling (Trial " << trial + 1 << "): " << processing_time << " seconds" << std::endl;

        average_time += processing_time;
    }

    average_time /= num_trials;

    std::cout << "Average time over " << num_trials << " trials: " << average_time << " seconds" << std::endl;

    return 0;
}
