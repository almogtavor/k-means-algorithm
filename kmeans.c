#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define def_epsilon 0.001
#define def_iteration 200



double **initialize_centroids(double **points, int k, int cords_num);

// Function to check if a string is a positive integer
int is_positive_integer(const char *str) {
    if (str == NULL || *str == '\0') return 0; // Empty string or NULL is invalid
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') return 0; // Non-digit character found
    }
    return 1; // All characters are digits
}

double calc_distance(double *point1, double *point2, int cords_num) {
    double sum = 0, temp = 0;
    for (int i = 0; i < cords_num; i++) {
        sum += (point1[i] - point2[i]) * (point1[i] - point2[i]);
    }
    return sqrt(sum);
}

int argmin(double *point, double **centroids, int k, int cords_num) {
    double min_dist = calc_distance(point, centroids[0], cords_num);
    double dist = 0.0;
    int closest_index = 0;

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
    double *new_centroid = malloc(sizeof(double) * cords_num);
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

double **kmeans(int k, int iterations, int cords_num, double **points, int vectors_num, double epsilon, int *cluster_sizes) {
    double **centroids = initialize_centroids(points, k, cords_num);
    double **prev_centroids = initialize_centroids(points, k, cords_num);
    double ***clusters = malloc(sizeof(double**) * k); // Pointer of the array of clusters

    // Allocate memory for clusters
    for (int i = 0; i < k; i++) {
        clusters[i] = malloc(sizeof(double *) * vectors_num); // Allocate memory for each cluster
        for (int j = 0; j < vectors_num; j++) {
            clusters[i][j] = malloc(sizeof(double) * cords_num); // Allocate for each point in cluster
        }
        cluster_sizes[i] = 0;
    }
    int curr_i = 0;
    int converged = 0;
    while (curr_i < k && converged == 0) {
        for (int i = 0; i < k; i++) {
            cluster_sizes[i] = 0;
            for (int j = 0; j < vectors_num; j++) {
                for (int l = 0; l < cords_num; l++) {
                    clusters[i][j][l] = 0.0; // Reset cluster values to 0
                }
            }
        }
        for (int i = 0; i < vectors_num; i++) {
            int cluster_index = argmin(points[i], centroids, k, cords_num);
            int size = cluster_sizes[cluster_index];        
            for (int l = 0; l < cords_num; l++) {
                clusters[cluster_index][size][l] = points[i][l];
            }
            cluster_sizes[cluster_index]++;
        }
        for (int i = 0; i < k; i++) {
            double *new_centroid = calculate_new_centroid(clusters[i], cluster_sizes[i], cords_num);
            for (int j = 0; j < cords_num; j++) {
                prev_centroids[i][j] = centroids[i][j];
                centroids[i][j] = new_centroid[j];
            }
            free(new_centroid); // Free the temp new centroid
        }
        converged = 1;
        for (int i = 0; i < k; i++) {
            if (calc_distance(centroids[i], prev_centroids[i], cords_num) >= epsilon) {
                converged = 0;
                break;
            }
        }
        curr_i++;
    }    
    for (int i = 0; i < k; i++) {
        free(prev_centroids[i]);
        for (int j = 0; j < vectors_num; j++) {
            free(clusters[i][j]);
        }
        free(clusters[i]);
    }
    free(prev_centroids);
    free(clusters);

    return centroids; // Return the centroids instead of clusters
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
    if (argc < 2 || argc >4)
    {
        printf("An Error Has Occurred");
        return 1;
    }
    

    if (!is_positive_integer(argv[1])) {
        printf("Invalid number of clusters!");
        return 1;
    }

    int k = atoi(argv[1]);
    int iterations = def_iteration; // Default value

    if (argc >= 3) {
        if (!is_positive_integer(argv[2])) {
            printf("Invalid maximum iteration!\n");
            return 1;
        }
        iterations = atoi(argv[2]);
    }

    if (iterations >= 1000 || iterations < 1) {
        printf("Invalid maximum iteration!");
        return 1;
    }

    if (k < 1) {
        printf("Invalid number of clusters!");
        return 1;
    }

    int cords_num = 0, vectors_num = 0;
    double n;
    int is_first_line = 0;
    while (scanf("%lf,", &n) == 1) {
        if (is_first_line == 0) {
            cords_num++; // Count the number of coordinates per vector
        }
        if (getchar() == '\n') {
            is_first_line = 1;
            vectors_num++; // Count the number of vectors (lines)
        }
    }

    if (k > vectors_num)
    {
        printf("Invalid number of clusters!");
        return 1;
    }
    

    if (cords_num == 0 && vectors_num > 0) {
        cords_num = 1;
    }

    double **all_points = malloc(sizeof(double *) * vectors_num);
    for (int i = 0; i < vectors_num; i++) {
        all_points[i] = malloc(sizeof(double) * cords_num);
    }

    rewind(stdin); // Rewind the input to the beginning
    int vector_index = 0;
    char c;
    while (vector_index < vectors_num) {
        for (int i = 0; i < cords_num; i++) {
            if (scanf("%lf%c", &all_points[vector_index][i], &c) != 2) {
                printf("Error reading data.\n");
                return 1;
            }
            if (c == '\n') {
                break; // End of the current vector
            }
        }
        vector_index++;
    }

    int *cluster_sizes = malloc(sizeof(int) * k); // Array to store the size of each cluster
    for (int i = 0; i < k; i++) {
        cluster_sizes[i] = 0;
    }


    double **centroids = kmeans(k, iterations, cords_num, all_points, vectors_num, def_epsilon, cluster_sizes);

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < cords_num; j++) {
            printf("%.4f ", centroids[i][j]);
        }
        printf("\n");
    }

    free(cluster_sizes);

    for (int i = 0; i < k; i++) {
        free(centroids[i]);
    }
    free(centroids);

    for (int i = 0; i < vectors_num; i++) {
        free(all_points[i]);
    }
    free(all_points);

    return 0;
}
