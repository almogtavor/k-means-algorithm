#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct vector {
    double *cords; // array to hold coordinates
    int cords_num; // number of coordinates
};

// // Function to calculate the Euclidean distance between two vectors
// double calc_distance(struct vector *vector1, struct vector *vector2) {
//     double sum = 0, temp = 0;
    
//     // Ensure both vectors have the same number of coordinates
//     if (vector1->cords_num != vector2->cords_num) {
//         return -1; // error if dimensions do not match
//     }

//     for (int i = 0; i < vector1->cords_num; i++) {
//         temp = vector1->cords[i] - vector2->cords[i];
//         sum += temp * temp;
//     }

//     return sqrt(sum);
// }

// // Function to find the index of the closest centroid for a given point
// int argmin(struct vector *point, struct vector **centroids, int k) {
//     double min = MAXFLOAT, dist = 0;
//     int index = -1;

//     for (int i = 0; i < k; i++) {
//         dist = calc_distance(point, centroids[i]);
//         if (dist < min) {
//             min = dist;
//             index = i;
//         }
//     }
//     return index;
// }

// // Function to calculate the new centroid by averaging the points in the cluster
// struct vector *calculate_new_centroid(struct vector **cluster, int cluster_size, int cords_num) {
//     struct vector *new_centroid = malloc(sizeof(struct vector));
//     new_centroid->cords = malloc(sizeof(double) * cords_num);
//     new_centroid->cords_num = cords_num;

//     for (int i = 0; i < cords_num; i++) {
//         new_centroid->cords[i] = 0;
//     }

//     for (int i = 0; i < cluster_size; i++) {
//         for (int j = 0; j < cords_num; j++) {
//             new_centroid->cords[j] += cluster[i]->cords[j];
//         }
//     }

//     for (int i = 0; i < cords_num; i++) {
//         new_centroid->cords[i] /= cluster_size; // Average the coordinates
//     }

//     return new_centroid;
// }

// // k-means algorithm
// struct vector **kmeans(int k, int iterations, int cords_num, struct vector *points, double epsilon);

// // Function to initialize the centroids for k-means
// struct vector **initialize_centroids(struct vector *points, int k, int cords_num);

int main(int argc, char **argv) {
    

    int k = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    int cords_num = 0, vectors_num = 0;

    printf("bla");
    struct vector *points = malloc(sizeof(struct vector));
    struct vector *curr_vec = points;

    double n;
    char c;

    while (scanf("%lf%c", &n, &c) == 2) {
        if (c == '\n') {
            curr_vec->cords = malloc(sizeof(double) * cords_num);
            curr_vec->cords[cords_num - 1] = n;
            curr_vec->cords_num = cords_num;

            vectors_num++;
            continue;
        }

        curr_vec->cords[cords_num] = n;
        cords_num++;
    }

    // // struct vector **clusters = kmeans(k, iterations, cords_num, points, 0.001);

    // // Print points
    // curr_vec = points;
    // int vector_index = 0;
    // printf("Vector %d:\n", vector_index++);
    // for (int i = 0; i < curr_vec->cords_num; i++) {
    //     printf("%.4f ", curr_vec->cords[i]);
    // }
    // printf("\n");

    return 0;
}

