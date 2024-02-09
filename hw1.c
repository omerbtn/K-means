#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define     ITER_DEFAULT    200
#define     epsilon         0.001

// Assisting methods
void    insertPointsFromStdin(double**, int, int);
int     checkLegal(int, int, int, int);
int     findClosestCentroid(double*, double**, int, int);
void    updatePoints(double**, double**, int*, int, int, int);
double  dist(double*, double*, int);


int main(int argc, char *argv[])
{
    // consts
    int k, n, d, iter; // consts
    double **points; // A list of vectors
    double **centroids; // A list of vectors
    int *cluster_index; // A list of clusters
    int i, j; // for the for loops

    // initializing and checking legality
    if (argc > 5 || argc < 4){
        printf("\nToo little/many arguments in command line!");
        return 0;
    }
    if (argc == 4){
        iter = ITER_DEFAULT;
    } else {
        iter = atoi(argv[4]);
    }
    k = atoi(argv[1]);
    n = atoi(argv[2]);
    d = atoi(argv[3]);
    if (checkLegal(k, n, d, iter) == 0){
        return 0;
    }

    // Allocate memory for empty array of points
    // (represented as 'n' d-sized arrays)
    // NEED ASSERT OF ENOUGH SPACE

    points = calloc(n, sizeof(double*));
    for (i = 0; i < n ; i++) {
        points[i] = calloc(d, sizeof(double));
    }
    
    // Allocate memory for empty array of centroids
    // (represented as 'k' d-sized arrays)
    // NEED ASSERT OF ENOUGH SPACE

    centroids = calloc(k, sizeof(double*));
    for (i = 0 ; i < k ; i++) {
        centroids[i] = calloc(d, sizeof(double));
    }

    insertPointsFromStdin(points, n, d);

    // Insert first k points as centroids
    for (i = 0 ; i < k ; i++){
        memcpy(centroids[i], points[i], sizeof(double) * d);
    }

    cluster_index = calloc(n, sizeof(int));

    
    // go over k- for each cluster(0 - k-1) calculate new centroid and compare
    for (i = 0 ; i < iter ; i++){
        updatePoints(points, centroids, cluster_index, n, k, d);

        if (updateCentroids(centroids, cluster_index, points, n, k, d) == 1){
            break;
            // leave because of epsilon or something
        }   
    }

    // STILL HAVE TO PRINT THE CENTROIDS

    // FREE TWO DIMENSION ARRAYS PROPERLY WITH FOR
    free(points);
    free(centroids);
    free(cluster_index);
    return 0;
}


// return 1 if converged, 0 else
int updateCentroids(
    double** centroids, int* cluster_index, double** points, 
    int n, int k, int d){

    double* new_centroid;
    int converged, i, j, x, cnt;
    

    new_centroid = calloc(d, sizeof(double));
    converged = 1;

    for (i = 0 ; i < k ; i++){
        // initalize new_centroid = [0, ... , 0]
        for (x = 0; x < d; x++){
            new_centroid[x] = 0;
        }
        
        cnt = 0;
        for (j = 0 ; j < n ; j++){
            if (cluster_index[j] == i){
                for (x = 0 ; x < d ; x++){
                    new_centroid[x] += points[j][x];
                }
                cnt++;
            }
        }

        for (x = 0 ; x < d ; x++){
            new_centroid[x] /= cnt; // WORKS?
        }

        if (dist(centroids[i], new_centroid, d) >= epsilon){
            converged = 0;
        }

        centroids[i] = new_centroid;
    }

    free(new_centroid);

    return converged;
}


int findClosestCentroid(double* point, double** centroids, int k, int d){
    double minDist, currDist;
    int minDistIndex;
    int i;

    minDist = dist(point, centroids[0], d);
    minDistIndex = 0;
    for (i = 1; i < k; i++){
        currDist = dist(point, centroids[i], d);
        if (currDist < minDist){
            minDist = currDist;
            minDistIndex = i;
        }
    }
    return minDistIndex;
}

// assign every point- an index of closest cluster
void updatePoints(
    double** points, double** centroids, int* cluster_index, int n, int k, int d){
    
    int j;
    for (j = 0 ; j < n ; j++){
        cluster_index[j] = findClosestCentroid(points[j], centroids, k, d);
    }
}

// find euclidian distance between 2 d-dimension points
double dist(double* p1, double* p2, int d){
    double diff, sum = 0;
    int i;

    for (i = 0; i < d; i++){
        diff = p1[i] - p2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

// Gets the points array and fills it according to input
void insertPointsFromStdin(double **points, int n, int d){
    int i, j; // for loops
    double double_val;
    for (i = 0 ; i < n ; i++){
        for (j = 0 ; j < d - 1 ; j++){
            scanf("%lf,", &double_val);
            points[i][j] = double_val;
        }
        scanf("%lf", &double_val);
        points[i][d - 1] = double_val;
    }
}

// Done
int checkLegal(int k, int n, int d, int iter){
    // Return 1 if legal, else 0
    // Function will print the error (if any)
    if (k <= 1 || k >= n){
        printf ("Invalid number of clusters!");
        return 0;
    }
    if (n <= 1){
        printf ("Invalid number of points!");
        return 0;
    }
    if (d < 1){
        printf ("Invalid dimension of point!");
        return 0;
    }
    if (iter <= 1 || iter >= 1000){
        printf ("Invalid maximum iteration!");
        return 0;
    }
    return 1;
}