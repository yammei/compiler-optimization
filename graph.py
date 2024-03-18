import csv
import matplotlib.pyplot as plt

# Read loop tiling CSV file
tile_sizes = []
average_times = []
with open('looptilingdata.csv', 'r') as file:
    csv_reader = csv.reader(file)
    for row in csv_reader:
        tile_size = int(row[0])
        average_time = float(row[1])
        if average_time != 0:  # Exclude data points with average time equal to 0
            tile_sizes.append(tile_size)
            average_times.append(average_time)

# Read non-loop tiling CSV file and calculate average time
nonloop_average_time = None
with open('nonlooptilingdata.csv', 'r') as file:
    csv_reader = csv.reader(file)
    next(csv_reader)  # Skip header row
    nonloop_average_time = float(next(csv_reader)[0])

# Plot loop tiling data without connecting the points
plt.scatter(tile_sizes, average_times, marker='o', label='Loop Tiling')

# Plot straight line for non-loop tiling average performance
plt.axhline(y=nonloop_average_time, color='r', linestyle='--', label='Non-Loop Tiling (Average)')

# Customize plot
plt.title('Average Run Time vs. Tile Size')
plt.xlabel('Tile Size')
plt.ylabel('Average Run Time (seconds)')
plt.legend()
plt.grid(True)
plt.show()
