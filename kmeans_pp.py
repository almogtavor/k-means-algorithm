import math
import sys
import pandas as pd
import numpy as np
import random
# import mykmeanssp

np.random.seed(1234)

Vector = list
DEF_EPSILON = 0.001
DEF_ITERATION = 300

def calc_distance(vector1: Vector, vector2: Vector):
    return math.sqrt(sum((vector1[i] - vector2[i]) ** 2 for i in range(len(vector1))))

def choose_centroids(all_points, centroids, k):
    if k == 1:
        return centroids

    for _ in range(1, k):
        min_distances = []
        for _, row in all_points.iterrows():
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
    # Parse command-line arguments (Usage example: python3 kmeans_pp.py 3 100 0.01 data/input_1.txt data/input_2.tx)
    if len(sys.argv) not in [5, 6]:
        print("Invalid number of arguments!")
        return

    try:
        k = int(sys.argv[1])
        if k <= 1:
            raise ValueError("Invalid number of clusters!")
        max_iter = int(sys.argv[2]) if len(sys.argv) == 6 else DEF_ITERATION
        if not (1 < max_iter < 1000):
            raise ValueError("Invalid maximum iteration!")
        eps = float(sys.argv[3])
        if eps < 0:
            raise ValueError("Invalid epsilon!")
        file1_name = sys.argv[4]
        file2_name = sys.argv[5]
    except ValueError as e:
        print(e)
        return

    try:
        file1 = pd.read_csv(file1_name, header=None)
        file2 = pd.read_csv(file2_name, header=None)
    except Exception as e:
        print(f"Error reading input files: {e}")
        return

    all_points = pd.merge(file1, file2, how="inner", on=0)
    all_points = all_points.sort_values(by=0)

    # Initialize centroids using k-means++
    centroids = pd.DataFrame(columns=all_points.columns)
    random_index = np.random.choice(all_points.index)
    first_centroid = all_points.loc[[random_index]]
    centroids = pd.concat([centroids, first_centroid], ignore_index=True, copy=False)

    centroids = choose_centroids(all_points, centroids, k)

    # Call the C extension's fit function
    data_points = all_points.iloc[:, 1:].to_numpy()
    initial_centroids = centroids.iloc[:, 1:].to_numpy()
    # final_centroids = mykmeanssp.fit(initial_centroids, data_points, k, max_iter, eps)

    # Output results
    initial_indices = centroids[0].astype(int).tolist()
    print(",".join(map(str, initial_indices)))

    # for centroid in final_centroids:
    for centroid in initial_centroids:
        print(",".join(map(lambda x: f"{x:.4f}", centroid)))

if __name__ == "__main__":
    main()
