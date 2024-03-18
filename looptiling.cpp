#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <ctime>
#include <cstdlib>

const int MATRIX_SIZE = 84; // Matrix size for CNN.

// Function to initialize a matrix with random values
void initializeMatrix(int matrix[MATRIX_SIZE][MATRIX_SIZE]) {
    for (int i = 0; i < MATRIX_SIZE; i++) {
        for (int j = 0; j < MATRIX_SIZE; j++) {
            matrix[i][j] = rand() % 10; // Fill with random values (0 to 9)
        }
    }
}

// Function to multiply two matrices using loop tiling
void multiplyMatricesWithTiling(int A[MATRIX_SIZE][MATRIX_SIZE], int B[MATRIX_SIZE][MATRIX_SIZE], int result[MATRIX_SIZE][MATRIX_SIZE], int TILE_SIZE) {
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
    // Check next tile size in CSV
    std::ifstream inputFile("looptilingdata.csv");
    int next_tile_size = 5;
    if (inputFile.is_open()) {
        std::vector<int> tile_sizes;
        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, ',');
            tile_sizes.push_back(std::stoi(token));
        }
        inputFile.close();

        if (!tile_sizes.empty()) {
            next_tile_size = tile_sizes.back() + 1;
        }
    }

    // Append the new tile size to CSV
    std::ofstream outputFile("looptilingdata.csv", std::ios::app);
    if (outputFile.is_open()) {
        outputFile << next_tile_size << ",0\n";
        outputFile.close();
    } else {
        std::cerr << "Error: Cannot open file." << std::endl;
        return 1;
    }

    int matrixA[MATRIX_SIZE][MATRIX_SIZE];
    int matrixB[MATRIX_SIZE][MATRIX_SIZE];
    int resultMatrix[MATRIX_SIZE][MATRIX_SIZE];

    srand(time(nullptr));

    initializeMatrix(matrixA);
    initializeMatrix(matrixB);

    clock_t start_time = clock();

    // Multiply the matrices using loop tiling
    multiplyMatricesWithTiling(matrixA, matrixB, resultMatrix, next_tile_size);

    clock_t end_time = clock();
    double processing_time = static_cast<double>(end_time - start_time) / CLOCKS_PER_SEC;

    // Update time in CSV file
    inputFile.open("looptilingdata.csv");
    if (inputFile.is_open()) {
        std::string tempFileName = "temp.csv";
        std::ofstream tempFile(tempFileName);

        std::string line;
        while (std::getline(inputFile, line)) {
            std::istringstream iss(line);
            std::string token;
            std::getline(iss, token, ',');
            int tileSize = std::stoi(token);
            if (tileSize == next_tile_size) {
                // Overwrite the processing time
                tempFile << next_tile_size << "," << processing_time << "\n";
            } else {
                tempFile << line << "\n";
            }
        }
        inputFile.close();
        tempFile.close();

        // Replace the original file with temporary file
        if (std::rename(tempFileName.c_str(), "looptilingdata.csv") != 0) {
            std::cerr << "Error: Cannot update file." << std::endl;
            return 1;
        }
    } else {
        std::cerr << "Error: Cannot open file." << std::endl;
        return 1;
    }

    std::cout << "Tile Size: " << next_tile_size << ", Time: " << processing_time << " seconds" << std::endl;

    return 0;
}
