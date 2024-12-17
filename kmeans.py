import math
import sys
from typing import List

Vector = List[float]

def calc_distance(vector1:Vector,vector2:Vector):
    sum=0
    for i in range(len(vector1)):
        sum += (vector1[i]-vector2[i])**2
    return math.sqrt(sum)


def argmin(point:Vector, centroids:List[Vector]):
    min_dist = sys.maxsize
    index = -1
    for i in range(len(centroids)):
        dist = calc_distance(point,centroids[i])
        if dist < min_dist:
            min_dist = dist
            index=i
    return index
        


def calculate_new_centroid(cluster: list[Vector], cords_num: int) -> Vector:
    new_cent: Vector = [0.0] * cords_num
    sum=0
    for i in range(len(cluster)):
        for j in range(cords_num):
            new_cent[j] += cluster[i][j]
    for i in range(len(new_cent)):
        new_cent[i]=round(new_cent[i]/len(cluster),4)
    return new_cent


def kmeans(k:int,iterations:int,cords_num:int,points:List[Vector],epsilon:float=0.001):
    centroids = initialize_centroids(points, k)
    clusters: list[list[Vector]] = [[] for _ in range(k)]
    curr_i = 0
    converged = False
    while (curr_i < iterations and not converged):
        previous_centroids = centroids
        for i in range(len(points)):
            cluster_index = argmin(points[i],centroids)
            clusters[cluster_index].append(points[i])

        for i in range(len(clusters)):
            centroids[i] = calculate_new_centroid(clusters[i],cords_num)
        curr_i += 1
        for i in range(len(centroids)):
            if (calc_distance(centroids[i], previous_centroids[i]) < epsilon):
                converged = True
            else:
                converged = False
                break
        return clusters
        


def initialize_centroids(vectors: List[Vector], k:int) -> List[Vector]:
    if k > len(vectors):
        raise ValueError('k must be less than/ equal to the number of vectors')
    return vectors[:k]


def main():
    if len(sys.argv) !=4:
        print("Usage: python kmeans.py <K> <iterations> <data_path>")
        return
    all_dots, cords_num, k, iterations, vectors_num = load_dots()

    print("\nmatrix:")
    for i in range(vectors_num):
        for j in range(cords_num):
            print (f"{all_dots[i][j]} ", end="")
        print()


    k = int(k)
    clusters = kmeans(k,int(iterations),cords_num,all_dots)
    for i, cluster in enumerate(clusters):
        print(f"Cluster {i}:")
        for vector in cluster:
            print(vector)




def load_dots():
    _, k, iterations, data_path = sys.argv
    print(k, iterations, data_path)
    with open(data_path, "r") as file:
        lines = file.readlines()
        vectors_num = len(lines)

        cords_num = len(lines[0].strip().split(","))

        print("\nFile Contents:")
        for line in lines:
            print(line.strip())

        all_dots = [[0.0 for _ in range(cords_num)] for _ in range(vectors_num)]
    with open(data_path, "r") as file:

        for j, line in enumerate(file):
            line_arr = line.split(",")

            for i in range(len(line_arr)):
                all_dots[j][i] = round(float(line_arr[i]), 4)
    return all_dots, cords_num, k, iterations, vectors_num


if __name__ == "__main__":
    main()