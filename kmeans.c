# include <stdio.h>
# include <stdlib.h>
#include <math.h>

struct cord
{
    double value;
    struct cord *next;
};
struct vector
{
    struct vector *next;
    struct cord *cords;
};

// Function to calculate the Euclidean distance between two vectors
double calc_distance(struct vector *vector1, struct vector *vector2){
    double sum = 0,temp = 0;
    struct cord *vec1_cords = vector1->cords;
    struct cord *vec2_cords = vector2->cords;

     while (vec1_cords != NULL) {
            temp = vec1_cords->value - vec2_cords->value;
            sum = sum + temp*temp;

            vec1_cords = vec1_cords->next;
            vec2_cords = vec2_cords->next;
        }

        return sqrt(sum);
}

// Function to find the index of the closest centroid for a given point
int argmin(struct vector *point, struct vector **centroids, int k){
    double min = MAXFLOAT,dist = 0;;
    int index = -1;
    for (int i = 0; i < k; i++)
    {
           dist = calc_distance(point,centroids[i]);
           if (dist < min)
           {
                min = dist;
                index = i;
           }  
    }
    return index;
}
    

struct vector *calculate_new_centroid(struct vector *cluster_head, int cords_num){
    struct vector *new_centroid = malloc(sizeof(struct vector));
    struct cord *new_cord, *head_cord;
    int i = 0;
    head_cord = NULL;
    while (i < cords_num) {
        new_cord = malloc(sizeof(struct cord));
        new_cord->value = 0;
        new_cord->next = head_cord;
        head_cord = new_cord;
        i++;
    }
    new_centroid->cords = head_cord;

    struct cord *curr_cord_of_cluster = cluster_head->cords;
    struct cord *curr_cord_of_new_centroid = new_centroid->cords;

    int count = 0;

    while (cluster_head != NULL)
    {
        while (curr_cord_of_cluster != NULL)
        {
            curr_cord_of_new_centroid->value += curr_cord_of_cluster->value;
            curr_cord_of_cluster = curr_cord_of_cluster->next;
            curr_cord_of_new_centroid = curr_cord_of_new_centroid->next;
        }
        
        count++;
        cluster_head = cluster_head->next;
        curr_cord_of_cluster = cluster_head->cords;
        curr_cord_of_new_centroid = new_centroid->cords;
    }

    if (count > 0) {
        curr_cord_of_new_centroid = new_centroid->cords;
        while (curr_cord_of_new_centroid != NULL) {
            curr_cord_of_new_centroid->value /= count; // Divide by the number of vectors
            curr_cord_of_new_centroid = curr_cord_of_new_centroid->next;
        }
    }

    // Step 5: Return the newly calculated centroid
    return new_centroid;
    
}

// k-means algorithm
struct vector **kmeans(int k, int iterations, int cords_num, struct vector *points_head, double epsilon);

// Function to initialize the centroids for k-means
struct vector **initialize_centroids(struct vector *points_head, int k);

int main(int argc, char **argv)
{
     if (argc != 3) {
        printf("Usage: ./kmeans <K> <iterations>\n");
        return 1;
    }

    int k = atoi(argv[1]);
    int iterations = atoi(argv[2]);
    int cords_num = 0, vectors_num = 0;

    struct vector *head_vec, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    double n;
    char c; 

    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;


    while (scanf("%lf%c", &n, &c) == 2)
    {

        if (c == '\n')
        {
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            curr_vec->next = malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;

            head_cord = malloc(sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            vectors_num++;
            continue;
        }

        curr_cord->value = n;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }

    curr_cord = head_vec->cords;
    while (curr_cord != NULL) {
        cords_num++;
        curr_cord = curr_cord->next;
    }

    struct vector **clusters = kmeans(k, iterations, cords_num, head_vec, 0.001);

    // print points
    curr_vec = head_vec;
    int vector_index = 0;
    while (curr_vec->next != NULL) { // Stop before the last empty vector
        printf("Vector %d:\n", vector_index++);
        curr_cord = curr_vec->cords;
        while (curr_cord != NULL) {
            printf("%.4f ", curr_cord->value);
            curr_cord = curr_cord->next;
        }
        printf("\n");
        curr_vec = curr_vec->next;
    }
    return 0;
}