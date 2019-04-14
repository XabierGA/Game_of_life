#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

  const int N = 4;
  const int M = 5;
  double * flat = (double*)malloc(N*N*sizeof(double));
  double ** matrix = (double**)malloc(N*sizeof(double*));
  for (int i = 0; i< N ; i++){
    matrix[i] = (double*)malloc(M*sizeof(double));
  }

  for (int i = 0; i < N ; i++){
    for (int j = 0; j < M ; j++){
      matrix[i][j] = i+j;
    //  flat[i + N*j] = i + j;
    }
  }

  for (int i = 0; i < N ; i++){
    for (int j = 0; j < M ; j++){
      printf("%lf " , matrix[i][j]);
    }
    printf("\n");
  }
  printf("\n");
/*
  for (int i = 0; i < N ; i++){
    for (int j = 0; j < N ; j++){
      printf("%lf " , flat[i + N*j]);
    }
    printf("\n");
  }
*/
printf("\n");
/*
  for (int i =  ; i < (N-1) ;i++){
    printf("Up neighbour : %lf: " , matrix[i-1][0]);
    printf("Right up Neighbour: %lf: \n", matrix[i-1][1] );
    printf("Particle: %lf: ", matrix[i][0] );
    printf("Right Neighbour: %lf: \n" ,matrix[i][1] );
    printf("Down Neighbour: %lf: " ,matrix[i+1][0] );
    printf("Right Down Neighbour: %lf: \n" ,matrix[i+1][1] );
  }
  */
/*
  for (int i = 0 ; i<(N) ; i++){
    for (int j = 0; j < N ; j++){
      printf("%d \n ", (i-1)%N);
      printf("%d \n ", (j-1)%N);
      printf("Left up Neighbour: %lf: ", matrix[(i-1)%N][(j-1)%N] );
      printf("Up Neighbour: %lf: " ,matrix[(i-1)%N][j%N] );
      printf("Right up Neighbour: %lf: \n", matrix[(i-1)%N][(j+1)%N] );
      printf("Left Neighbour: %lf: ", matrix[i%N][(j-1)%N] );
      printf("Particle: %lf: ", matrix[i%N][j%N] );
      printf("Right Neighbour: %lf: \n" ,matrix[i%N][(j+1)%N] );
      printf("Left Down Neighbour: %lf: ", matrix[(i+1)%N][(j-1)%N] );
      printf("Down Neighbour: %lf: " ,matrix[(i+1)%N][j%N] );
      printf("Right Down Neighbour: %lf: \n" ,matrix[(i+1)%N][(j+1)%N] );
    }
  }*/

for (int i = 0 ; i < 10 ; i++){
  int new = rand() % 15;
  printf("%d \n" , new);
}
/*  printf("%lf \n" , flat[N]);
  printf("%lf \n" , flat[2]);
  printf("%lf \n" , flat[N*(N-1)]);
  printf("%lf \n" , flat[N*1 + (N-1)]);
  printf("%lf \n" , flat[N*2 + (N-1)]);
  printf("%lf \n" , flat[N*3 + (N-1)]);

*/

  free(flat);
  for (int i = 0; i< N;i++){
    free(matrix[i]);
  }
  free(matrix);
  int coef = 32%45;
  int coef2 = 47%45;
  printf("%d \n", coef);
  printf("%d \n" , coef2);
}
