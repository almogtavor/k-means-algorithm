import math
import sys
from typing import List
import pandas as pd
import numpy as np
import random  # Importing the random module


np.random.seed(1234)

Vector = List[float]
DEF_EPSILON = 0.001
DEF_ITERATION = 300

def calc_distance(vector1: Vector, vector2: Vector):
    sum = 0
    for i in range(len(vector1)):
        sum += (vector1[i] - vector2[i]) ** 2
    return math.sqrt(sum)

def choose_centroids(all_points, centroids ,k):
    if k==1:
        return centroids
    
    for _ in range(1, k): 
        min_distances = []
        for index, row in all_points.iterrows():
            point = row.tolist()
            distances = [calc_distance(point[1:], centroid.tolist()[1:]) for _, centroid in centroids.iterrows()]
            min_distances.append(min(distances))
        
        all_points['min_distance'] = min_distances

        # Normalize the distances into probabilities
        total_distance = all_points['min_distance'].sum()
        all_points['probability'] = all_points['min_distance'] / total_distance

        # Choose the next centroid based on probabilities
        probabilities = all_points['probability'].to_numpy()
        chosen_index = np.random.choice(all_points.index, p=probabilities)
        new_centroid = all_points.drop(columns=['min_distance', 'probability']).loc[chosen_index]
        centroids = pd.concat([centroids, new_centroid.to_frame().T], ignore_index=True)

        all_points = all_points.drop(columns=['min_distance', 'probability'])

    return centroids


def main():
    file1 = pd.read_csv("k-means-algorithm/data/input_1.txt", header=None)
    file2 = pd.read_csv("k-means-algorithm/data/input_2.txt", header=None)
    all_points = pd.merge(file1, file2, how="inner", on=0)
    all_points = all_points.sort_values(by=0)

    centroids = pd.DataFrame(columns=all_points.columns)
    random_index = np.random.choice(all_points.index)
    first_centroid = all_points.loc[[random_index]]
    centroids = pd.concat([centroids, first_centroid], ignore_index=True)

    print(centroids)

    centroids=choose_centroids(all_points,centroids,7)

    print(centroids)

if __name__ == "__main__":
    main()