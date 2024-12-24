#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct vector {
    double *cords; // array to hold coordinates
    int cords_num; // number of coordinates
};

// Function to calculate the Euclidean distance between two vectors
double calc_distance(struct vector *vector1, struct vector *vector2) {
    double sum = 0, temp = 0;
    
    // Ensure both vectors have the same number of coordinates
    if (vector1->cords_num != vector2->cords_num) {
        return -1; // error if dimensions do not match
    }

    for (int i = 0; i < vector1->cords_num; i++) {
        temp = vector1->cords[i] - vector2->cords[i];
        sum += temp * temp;
    }

    return sqrt(sum);
}

// Function to find the index of the closest centroid for a given point
int argmin(struct vector *point, struct vector **centroids, int k) {
    double min = MAXFLOAT, dist = 0;
    int index = -1;

    for (int i = 0; i < k; i++) {
        dist = calc_distance(point, centroids[i]);
        if (dist < min) {
            min = dist;
            index = i;
        }
    }
    return index;
}

// Function to calculate the new centroid by averaging the points in the cluster
struct vector *calculate_new_centroid(struct vector **cluster, int cluster_size, int cords_num) {
    struct vector *new_centroid = malloc(sizeof(struct vector));
    new_centroid->cords = malloc(sizeof(double) * cords_num);
    new_centroid->cords_num = cords_num;

    for (int i = 0; i < cords_num; i++) {
        new_centroid->cords[i] = 0;
    }

    for (int i = 0; i < cluster_size; i++) {
        for (int j = 0; j < cords_num; j++) {
            new_centroid->cords[j] += cluster[i]->cords[j];
        }
    }

    for (int i = 0; i < cords_num; i++) {
        new_centroid->cords[i] /= cluster_size; // Average the coordinates
    }

    return new_centroid;
}

// // k-means algorithm
struct vector **kmeans(int k, int iterations, int cords_num, struct vector *points, double epsilon);

// // Function to initialize the centroids for k-means
struct vector **initialize_centroids(struct double *points, int k, int cords_num)
{
    poi
}


    
int main(int argc, char **argv) {

int k = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    int cords_num = 0, vectors_num = 0;
    double n;
    int is_first_line = 0;
    // First pass: Read input to count the number of vectors and coordinates
    while (scanf("%lf,", &n) == 1) {
        if (is_first_line == 0)
        {
            cords_num++;  // Count the number of coordinates per vector

        }
        if (getchar() == '\n') {
            is_first_line = 1;
            vectors_num++;  // Count the number of vectors (lines)
            
        }
    }


    printf("num of cordinates is %d", cords_num);
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


    // kmeans()

    // Free the allocated memory
    for (int i = 0; i < vectors_num; i++) {
        free(all_points[i]);
    }
    free(all_points);

    return 0;
}