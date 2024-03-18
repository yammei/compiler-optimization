#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

const int MATRIX_SIZE = 128; // Matrix size for CNN.

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

    int num_trials = 100; // Change the number of trials to 20
    double total_time = 0.0;

    for (int trial = 0; trial < num_trials; trial++) {
        // Initialize the matrices with random values
        initializeMatrix(matrixA);
        initializeMatrix(matrixB);
        clock_t start_time = clock();

        // Multiply the matrices without loop tiling
        multiplyMatrices(matrixA, matrixB, resultMatrix);

        clock_t end_time = clock();
        double processing_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;
        std::cout << processing_time << std::endl;

        total_time += processing_time;
    }

    // Calculate the average time
    double average_time = total_time / num_trials;

    // Write data to CSV file
    std::ofstream outfile("nonlooptilingdata.csv");
    if (outfile.is_open()) {
        outfile << "Average Time\n";
        outfile << average_time << "\n";
        outfile.close();
        std::cout << "Data written to nonlooptilingdata.csv successfully." << std::endl;
    } else {
        std::cerr << "Unable to open file." << std::endl;
        return 1;
    }

    return 0;
}
