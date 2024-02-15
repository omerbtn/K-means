#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define     ITER_DEFAULT    200
#define     epsilon         0.001

void    insertPointsFromStdin(double**, int, int);
int     checkLegal(int, int, int, int);
int     findClosestCentroid(double*, double**, int, int);
void    updatePoints(double**, double**, int*, int, int, int);
int     updateCentroids(double**, int*, double**, int, int, int);
double  dist(double*, double*, int);
void    printCentroids(double**, int, int);


int main(int argc, char *argv[])
{
    int k, n, d, iter;
    double **points;
    double **centroids;
    int *cluster_index;
    int i, j; 

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

    points = calloc(n, sizeof(double*));
    if (points == NULL){
            printf("An Error Has Occurred");
            return 1;
        }
    for (i = 0; i < n ; i++) {
        points[i] = calloc(d, sizeof(double));
        if (points[i] == NULL){
            printf("An Error Has Occurred");
            return 1;
        }
    }

    centroids = calloc(k, sizeof(double*));
    if (centroids == NULL){
        printf("An Error Has Occurred");
        return 1;
    }
    for (i = 0 ; i < k ; i++) {
        centroids[i] = calloc(d, sizeof(double));
        if (centroids[i] == NULL){
            printf("An Error Has Occurred");
            return 1;
        }
    }

    insertPointsFromStdin(points, n, d);
    for (i = 0 ; i < k ; i++){
        memcpy(centroids[i], points[i], sizeof(double) * d);
    }

    cluster_index = calloc(n, sizeof(int));

    for (i = 0 ; i < iter ; i++){
        updatePoints(points, centroids, cluster_index, n, k, d);

        if (updateCentroids(centroids, cluster_index, points, n, k, d) == 1){
            break;
        }   
    }
    printCentroids(centroids, k, d);
    for (i = 0 ; i < n ; i++){
        free(points[i]);
    }
    free(points);
    for (i = 0 ; i < k ; i++){
        free(centroids[i]);
    }
    free(centroids);
    free(cluster_index);
    return 0;
}


int updateCentroids(
    double** centroids, int* cluster_index, double** points, 
    int n, int k, int d){

    double* new_centroid;
    int converged, i, j, x, cnt;
    

    new_centroid = calloc(d, sizeof(double));
    converged = 1;

    for (i = 0 ; i < k ; i++){
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
            new_centroid[x] /= cnt; 
        }

        if (dist(centroids[i], new_centroid, d) >= epsilon){
            converged = 0;
        }

        memcpy(centroids[i], new_centroid, sizeof(double) * d);
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

void updatePoints(
    double** points, double** centroids, int* cluster_index, int n, int k, int d){
    
    int j;
    for (j = 0 ; j < n ; j++){
        cluster_index[j] = findClosestCentroid(points[j], centroids, k, d);
    }
}

double dist(double* p1, double* p2, int d){
    double diff, sum = 0;
    int i;

    for (i = 0; i < d; i++){
        diff = p1[i] - p2[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}

void insertPointsFromStdin(double **points, int n, int d){
    int i, j;
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

int checkLegal(int k, int n, int d, int iter){
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

void printCentroids(double** centroids, int k, int d){
    int i, j;
    
    for (i = 0 ; i < k ; i++){
        for (j = 0 ; j < d-1 ; j++){
            printf("%.4lf,", centroids[i][j]);
        }
        printf("%.4lf\n", centroids[i][d-1]);
    }
}