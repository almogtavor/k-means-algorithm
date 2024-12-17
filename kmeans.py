import sys
from typing import List

from django.template.defaultfilters import random

Vector = List[float]

def calc_distance(vector1:Vector,vector2:Vector):
    pass

def argmin():
    pass

def argmin(vector:Vector, centroid:Vector):
    for i in range(len(vector)):
        pass


def calculate_new_centroid(cluster: list[Vector], cords_num: int) -> Vector:
    pass


def kmeans(k:int,iterations:int,cords_num:int,vectors:List[Vector],epsilon:float=0.001):
    centroids = initialize_centroids(vectors, k)
    clusters: list[list[Vector]] = [[] for _ in range(k)]
    curr_i = 0
    converged = False
    while (curr_i < iterations and not converged):
        previous_centroid = []

        # Check convergence
        for centroid in centroids:
            if (calc_distance(centroid, previous_centroid) < epsilon):
                converged = True
            else:
                converged = False
                break


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
    kmeans(k,int(iterations),cords_num,all_dots)


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