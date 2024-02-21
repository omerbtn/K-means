import sys
import math

ITER_DEFAULT = 200
EPSILON = 0.001


def main():
    argv = sys.argv
    if not check_legal(argv):
        return

    k = int(argv[1])
    n = int(argv[2])
    d = int(argv[3])
    iter = int(argv[4]) if len(argv) == 6 else ITER_DEFAULT
    input_file = argv[5] if len(argv) == 6 else argv[4]

    points = []
    with open(input_file) as input:
        for line in input:
            temp = line[:-1].split(',')
            points.append([float(temp[i]) for i in range(d)])

    centroids = []
    for i in range(k):
        centroids.append(points[i])

    for i in range(iter):
        clusters = [[] for i in range(k)]
        converged = True
        for p in points:
            clusters[find_closest_centroid(p, centroids)].append(p)
        for j in range(k):
            new_centroid = find_cluster_mean(clusters[j], d)
            if mydist(centroids[j], new_centroid) >= EPSILON:
                converged = False
            centroids[j] = new_centroid
        if converged:
            break
    printCentroids(centroids, k, d)

def check_legal(argv):
    if len(argv) < 5 or len(argv) > 6:
        print("An Error Has Occurred")
        return False
    for i in range(1, len(argv) - 1):
        try:
            argv[i] = int(argv[i])
        except:
            print("An Error Has Occurred")
            return False
    if argv[1] <= 1 or argv[1] >= argv[2]:
        print("Invalid number of clusters!")
        return False
    if argv[2] <= 1:
        print("Invalid number of points!")
        return False
    if argv[3] < 1:
        print("Invalid dimension of point!")
        return False
    if len(argv) == 6 and (argv[4] <= 1 or argv[4] >= 1000):
        print("Invalid maximum iteration!")
        return False
    return True


def find_closest_centroid(p, centroids):
    min_dist = mydist(p, centroids[0])
    min_dist_index = 0
    for i in range(1, len(centroids)):
        dist = mydist(p, centroids[i])
        if dist < min_dist:
            min_dist_index = i
            min_dist = dist
    return min_dist_index


def find_cluster_mean(points, d):
    mean = []
    num_of_points = len(points)
    for i in range(d):
        dim_sum = 0
        for p in points:
            dim_sum += p[i]
        mean.append(dim_sum / num_of_points)
    return mean


def printCentroids(centroids, k, d):
    res = ""
    for i in range(k):
        for j in range(d-1):
            res += "{:.4f}".format(centroids[i][j]) + ","
        print(res + "{:.4f}".format(centroids[i][d-1]), end="\r\n")
        res = ""

def mydist(point1, point2):
    if len(point1) != len(point2):
        print("An Error Has Occurred")
        exit()

    squared_distances = [(p1 - p2) ** 2 for p1, p2 in zip(point1, point2)]
    sum_of_squared_distances = sum(squared_distances)
    distance = math.sqrt(sum_of_squared_distances)
    return distance

if __name__ == "__main__":
    main()
