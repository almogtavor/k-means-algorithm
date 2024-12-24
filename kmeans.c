#include <stdio.h>
#include <stdlib.h>
#include <math.h>


double calc_distance(double *point1, double *point2, int cords_num) {
    double sum = 0, temp = 0;
    for (int i = 0; i < cords_num; i++) {
        sum += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    }
    return sqrt(sum);
}

int argmin(double *point, double **centroids, int k, int cords_num) {
    // todo: convert to maxfloat
    double min_dist = calc_distance(point, centroids[0], cords_num);
    double dist = 0.0;
    int closest_index = -1;

    for (int i = 1; i < k; i++) {
        dist = calc_distance(point, centroids[i], cords_num);
        if (dist < min_dist) {
            min_dist = dist;
            closest_index = i;
        }
    }
    return closest_index;
}

// A function to calculate the new centroid by averaging the points in the cluster
double *calculate_new_centroid(double **cluster, int cluster_size, int cords_num) {
    double *new_centroid = malloc(sizeof(double *));
    new_centroid = malloc(sizeof(double) * cords_num);
    new_centroid = cords_num;
    for (int i = 0; i < cords_num; i++) {
        new_centroid[i] = 0.0;
    }
    for (int i = 0; i < cluster_size; i++) {
        for (int j = 0; j < cords_num; j++) {
            new_centroid[j] += cluster[i][j];
        }
    }
    for (int i = 0; i < cords_num; i++) {
        new_centroid[i] /= cluster_size; // Average the coordinates
    }
    return new_centroid;
}

double **kmeans(int k, int iterations, int cords_num, double **points, int vectors_num, double epsilon) {
    double **centroids = initialize_centroids(points, k, cords_num);
    double ***clusters = malloc(sizeof(double **) * k); // Array of clusters
    int *cluster_sizes = malloc(sizeof(int) * k); // Array to store the size of each cluster



    // Free centroids memory
    for (int i = 0; i < k; i++) {
        free(centroids[i]);
    }
    free(centroids);
    free(cluster_sizes);
}

// Function to initialize the centroids for k-means
double **initialize_centroids(double **points, int k, int cords_num) {
    double **centroids = malloc(sizeof(double*) * k);
    for (int i = 0; i < k; i++) {
        centroids[i] = malloc(sizeof(double) * cords_num);
        for (int j = 0; j < cords_num; j++) {
            centroids[i][j] = points[i][j];
        }
    }
    return centroids;
}
    
int main(int argc, char **argv) {
    int k = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    int cords_num = 0, vectors_num = 0;
    double n;
    int is_first_line = 0;
    // First pass: Read input to count the number of vectors and coordinates
    while (scanf("%lf,", &n) == 1) {
        if (is_first_line == 0) {
            cords_num++;  // Count the number of coordinates per vector
        }
        if (getchar() == '\n') {
            is_first_line = 1;
            vectors_num++;  // Count the number of vectors (lines)
        }
    }

    printf("Num of cordinates is %d and num of vectors is %d", cords_num, vectors_num);
    // If no coordinates were found, assume at least one coordinate per vector
    if (cords_num == 0 && vectors_num > 0) {
        cords_num = 1;
    }

    // Now we know how many vectors and coordinates exist, we need to allocate memory for them
    double **all_points = malloc(sizeof(double *) * vectors_num);
    for (int i = 0; i < vectors_num; i++) {
        all_points[i] = malloc(sizeof(double) * cords_num);
    }

    // Second pass: Read the actual data into the 2D array `all_points`
    rewind(stdin);  // Rewind the input to the beginning
    int vector_index = 0;
    char c;
    while (vector_index < vectors_num) {
        for (int i = 0; i < cords_num; i++) {
            if (scanf("%lf%c", &all_points[vector_index][i], &c) != 2) {
                printf("Error reading data.\n");
                return 1;
            }
            if (c == '\n') {
                break; // end of the current vector
            }
        }
        vector_index++;
    }

    // Print the matrix (all points)
    printf("\nMatrix of points:\n");
    for (int i = 0; i < vectors_num; i++) {
        for (int j = 0; j < cords_num; j++) {
            printf("%.4f ", all_points[i][j]);
        }
        printf("\n");
    }

    double epsilon = 0.001; // Convergence threshold
    double ***clusters = kmeans(k, iterations, cords_num, all_points, vectors_num, epsilon);

    printf("\nClusters:\n");
    for (int i = 0; i < k; i++) {
        printf("Cluster %d:\n", i + 1);
        for (int j = 0; clusters[i][j] != NULL; j++) {
            for (int c = 0; c < cords_num; c++) {
                printf("%.4f ", clusters[i][j][c]); // the .4 is because we want to round the float and take only 4 numbers
            }
            printf("\n");
        }
        printf("\n");
    }

    for (int i = 0; i < k; i++) {
        free(clusters[i]);
    }
    free(clusters);

    // Free the allocated memory
    for (int i = 0; i < vectors_num; i++) {
        free(all_points[i]);
    }
    free(all_points);

    return 0;
}