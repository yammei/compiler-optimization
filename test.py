import time
import random

def mmm1(A, B, ts):

    # Dimensions of the matrices
    M = len(A)  # Number of rows in A
    N = len(B[0])  # Number of columns in B
    K = len(B)  # Number of columns in A (should match rows in B)

    # Tile dimensions
    tile_size = ts


    # Result matrix
    C = [[0 for _ in range(N)] for _ in range(M)]

    startTime = time.time()

    for i0 in range(0, M, tile_size):
        for j0 in range(0, N, tile_size):
            for k0 in range(0, K, tile_size):
                for i in range(i0, min(i0 + tile_size, M)):
                    for j in range(j0, min(j0 + tile_size, N)):
                        for k in range(k0, min(k0 + tile_size, K)):
                            # print(f"i: {i}, k: {k}, j: {j}")
                            C[i][j] += A[i][k] * B[k][j]

    endTime = time.time()
    totalTime = endTime - startTime
    print(f"Loop Tiling: {str(totalTime)[:4]} seconds. Tile Size: {tile_size}.")

    # Print the result
    # for row in C:
    #     print(row)

    return(totalTime)


def mmm2(A, B):
    # Check if the matrices can be multiplied
    if len(A[0]) != len(B):
        raise ValueError("Matrix dimensions are not compatible for multiplication.")

    # Initialize the result matrix with zeros
    result = [[0 for _ in range(len(B[0]))] for _ in range(len(A))]

    startTime = time.time()

    # Perform matrix multiplication using nested loops
    for i in range(len(A)):
        for j in range(len(B[0])):
            for k in range(len(B)):
                result[i][j] += A[i][k] * B[k][j]

    endTime = time.time()
    totalTime = endTime - startTime
    print(f"Non-Loop Tiling: {str(totalTime)[:4]} seconds. \n")

    return(totalTime)
    # for row in result:
    #     print(row)

def compare(tile_size, ms):
    # Input matrices
    matrix_size = ms 
    A = [[random.randint(1, 10) for _ in range(matrix_size)] for _ in range(matrix_size)]
    B = [[random.randint(1, 10) for _ in range(matrix_size)] for _ in range(matrix_size)]

    loop_tiling_avg = []
    non_loop_tiling_avg = []
    trials = 3

    for i in range(trials):
        print(f"\nTrial {i+1}")
        loop_tiling_avg.append(mmm1(A, B, tile_size))
        non_loop_tiling_avg.append(mmm2(A, B))


    loop_tiling_avg = sum(loop_tiling_avg)/trials
    non_loop_tiling_avg = sum(non_loop_tiling_avg)/trials

    print("Results")
    print(f"Loop Tiling ({trials}-Trial Average): {str(loop_tiling_avg)[:4]} seconds.")
    print(f"Non-Loop Tiling ({trials}-Trial Average): {str(non_loop_tiling_avg)[:4]} seconds.\n")

    return loop_tiling_avg

def optimize_tile_size(ms):
    trials = 10
    most_efficient_tile = 1
    matrix_size = ms
    interval = matrix_size/trials
    timers = []

    for i in range(trials):
        timers.append([compare(int(i*interval+1), matrix_size), i*interval, i])
    print(f"Timers 1: {timers}")

    most_efficient_tile = sorted(timers)[0][1]
    index_of_fastest = sorted(timers)[0][2]
    timers2 = []
    ts_start = most_efficient_tile - (matrix_size/trials)
    interval = matrix_size * .01

    for i in range(trials*2):
        timers2.append([compare(int(ts_start+(i*interval)), matrix_size), ts_start+(i*interval), i])
    print(f"Timers 2: {timers2}")
    print(interval)

    most_efficient_tile = sorted(timers2)[0][1]
    index_of_fastest = sorted(timers2)[0][2]

    print(int(most_efficient_tile))
    return most_efficient_tile

# tile_size = 50
matrix_size = 100
A = [[random.randint(1, 10) for _ in range(matrix_size)] for _ in range(matrix_size)]
B = [[random.randint(1, 10) for _ in range(matrix_size)] for _ in range(matrix_size)]
best_ts = int(optimize_tile_size(matrix_size))
compare(best_ts, matrix_size)