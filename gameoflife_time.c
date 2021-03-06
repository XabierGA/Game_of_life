#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct _cell{
  struct _cell** neighbours;
  int current;
  int next;
}cell;

void seed_cells(cell**, int , int );
void obtain_neighbours(cell**, int , int , cell*);
void free_neighbours(cell**, int , int  );
void print_cell(cell** , int , int);
void generation_update(cell*);
void evolution(cell*);



int main(int argc, char *argv[]) {
  struct timespec start, finish;
  double elapsed;

  clock_gettime(CLOCK_MONOTONIC, &start);
  if (argc != 4){
    printf("Introduce only one argument \n");
  }

  int N = atoi(argv[1]);
  int M = atoi(argv[2]);
  int n_steps = atoi(argv[3]);



  cell ** cells_grid = (cell**)malloc(N*sizeof(cell*));
  for (int i = 0 ; i < N; i++){
    cells_grid[i] = (cell*)malloc(M*sizeof(cell));
  }


  seed_cells(cells_grid , N, M);
//  print_cell(cells_grid , N , M);

  //printf(" %c" , rand() & 1 );
  cell *b = (cell*)malloc(sizeof(cell));
  b->neighbours = NULL;
  b->current = 0;
  b->next = 0;
  obtain_neighbours(cells_grid , N , M , b);
  //free(b);


  for (int k = 0 ; k < n_steps ; k++){
    for (int i = 0 ; i < N ; i++){
      for (int j = 0 ; j < M ; j++){
          cell* pointer = &cells_grid[i][j];
          evolution(pointer);
      }
    }
    for (int i = 0 ; i < N ; i++){
      for (int j = 0 ; j < M ; j++){
          generation_update(&cells_grid[i][j]);
      }
    }

  }

  free_neighbours(cells_grid,N , M);

  for (int i = 0 ; i < N ; i++){
    free(cells_grid[i]);
  }
  free(cells_grid);

  free(b);

  clock_gettime(CLOCK_MONOTONIC, &finish);

  elapsed = (finish.tv_sec - start.tv_sec);
  elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;
  FILE *file3;
  file3 = fopen("time.txt" , "a+");
  fprintf(file3 , "%lf \n" , elapsed);
  fclose(file3);

}
void seed_cells(cell** cells_grid , int N , int M){

  for (int i = 0 ; i<N ; i++){
    for (int j = 0 ; j<M ; j++){
      int cur = rand()%2;
      cells_grid[i][j].current = cur;
      cells_grid[i][j].next = cur;
    }
  }
}

void print_cell(cell** cells_grid , int N , int M){
  for (int i = 0 ; i < N ; i++){
    for (int j = 0 ; j < M ; j++){
      printf(" %d " , cells_grid[i][j].current);
    }
    printf(" \n");
  }
}

void obtain_neighbours(cell**cells_grid , int N , int M , cell* b ){
  //obtain neighbours for [0][0]

  cells_grid[0][0].neighbours = (cell**)malloc(8*sizeof(cell*));
  cells_grid[N-1][0].neighbours = (cell**)malloc(8*sizeof(cell*));
  cells_grid[0][M-1].neighbours = (cell**)malloc(8*sizeof(cell*));
  cells_grid[N-1][M-1].neighbours = (cell**)malloc(8*sizeof(cell*));
  /*for (int t = 0 ; t < 8 ; t++){
    cells_grid[0][0].neighbours[t] = (cell*)malloc(sizeof(cell));
    cells_grid[N-1][0].neighbours[t] = (cell*)malloc(sizeof(cell));
    cells_grid[0][M-1].neighbours[t] = (cell*)malloc(sizeof(cell));
    cells_grid[N-1][M-1].neighbours[t] = (cell*)malloc(sizeof(cell));
  }*/
  cells_grid[0][0].neighbours[0] = b;
  cells_grid[0][0].neighbours[1] = b;
  cells_grid[0][0].neighbours[2] = b;
  cells_grid[0][0].neighbours[3] = b;
  cells_grid[0][0].neighbours[4] = &cells_grid[0][1];
  cells_grid[0][0].neighbours[5] = b;
  cells_grid[0][0].neighbours[6] = &cells_grid[1][0];
  cells_grid[0][0].neighbours[7] = &cells_grid[1][1];


  cells_grid[N-1][0].neighbours[0] = b;
  cells_grid[N-1][0].neighbours[1] = &cells_grid[N-2][0];
  cells_grid[N-1][0].neighbours[2] = &cells_grid[N-2][1];
  cells_grid[N-1][0].neighbours[3] = b;
  cells_grid[N-1][0].neighbours[4] = &cells_grid[N-1][1];
  cells_grid[N-1][0].neighbours[5] = b;
  cells_grid[N-1][0].neighbours[6] = b;
  cells_grid[N-1][0].neighbours[7] = b;


  cells_grid[0][M-1].neighbours[0] = b;
  cells_grid[0][M-1].neighbours[1] = b;
  cells_grid[0][M-1].neighbours[2] = b;
  cells_grid[0][M-1].neighbours[3] = &cells_grid[0][M-2];
  cells_grid[0][M-1].neighbours[4] = b;
  cells_grid[0][M-1].neighbours[5] = &cells_grid[1][M-2];
  cells_grid[0][M-1].neighbours[6] = &cells_grid[1][M-1];
  cells_grid[0][M-1].neighbours[7] = b;


  cells_grid[N-1][M-1].neighbours[0] = &cells_grid[N-2][M-2];
  cells_grid[N-1][M-1].neighbours[1] = &cells_grid[N-2][M-1];
  cells_grid[N-1][M-1].neighbours[2] = b;
  cells_grid[N-1][M-1].neighbours[3] = &cells_grid[N-1][M-2];
  cells_grid[N-1][M-1].neighbours[4] = b;
  cells_grid[N-1][M-1].neighbours[5] = b;
  cells_grid[N-1][M-1].neighbours[6] = b;
  cells_grid[N-1][M-1].neighbours[7] = b;

  for (int i = 1 ; i< (M-1) ; i++){
    cells_grid[0][i].neighbours = (cell**)malloc(8*sizeof(cell*));
    cells_grid[N-1][i].neighbours = (cell**)malloc(8*sizeof(cell*));
    /*
    for (int t = 0 ; t < 8 ; t++){
      cells_grid[0][i].neighbours[t] = (cell*)malloc(sizeof(cell));
      cells_grid[N-1][i].neighbours[t] = (cell*)malloc(sizeof(cell));
    }*/

    cells_grid[0][i].neighbours[0] = b;
    cells_grid[0][i].neighbours[1] = b;
    cells_grid[0][i].neighbours[2] = b;
    cells_grid[0][i].neighbours[3] = &cells_grid[0][i-1];
    cells_grid[0][i].neighbours[4] = &cells_grid[0][i+1];
    cells_grid[0][i].neighbours[5] = &cells_grid[1][i-1];
    cells_grid[0][i].neighbours[6] = &cells_grid[1][i];
    cells_grid[0][i].neighbours[7] = &cells_grid[1][i+1];


    cells_grid[N-1][i].neighbours[0] = &cells_grid[N-2][i-1];
    cells_grid[N-1][i].neighbours[1] = &cells_grid[N-2][i];
    cells_grid[N-1][i].neighbours[2] = &cells_grid[N-2][i+1];
    cells_grid[N-1][i].neighbours[3] = &cells_grid[N-1][i-1];
    cells_grid[N-1][i].neighbours[4] = &cells_grid[N-1][i+1];
    cells_grid[N-1][i].neighbours[5] = b;
    cells_grid[N-1][i].neighbours[6] = b;
    cells_grid[N-1][i].neighbours[7] = b;
  }
  for (int i = 1 ; i < (M-1) ; i++){
      cells_grid[i][0].neighbours = (cell**)malloc(8*sizeof(cell*));
      cells_grid[i][M-1].neighbours = (cell**)malloc(8*sizeof(cell*));
      /*
      for (int t = 0 ; t < 8 ; t++){
        cells_grid[i][0].neighbours[t] = (cell*)malloc(sizeof(cell));
        cells_grid[i][M-1].neighbours[t] = (cell*)malloc(sizeof(cell));
      }*/

      cells_grid[i][0].neighbours[0] = b;
      cells_grid[i][0].neighbours[1] = &cells_grid[i-1][0];
      cells_grid[i][0].neighbours[2] = &cells_grid[i-1][1];
      cells_grid[i][0].neighbours[3] = b;
      cells_grid[i][0].neighbours[4] = &cells_grid[i][1];
      cells_grid[i][0].neighbours[5] = b;
      cells_grid[i][0].neighbours[6] = &cells_grid[i+1][0];
      cells_grid[i][0].neighbours[7] = &cells_grid[i+1][1];

      cells_grid[i][M-1].neighbours[0] = &cells_grid[i-1][M-2];
      cells_grid[i][M-1].neighbours[1] = &cells_grid[i-1][M-1];
      cells_grid[i][M-1].neighbours[2] = b;
      cells_grid[i][M-1].neighbours[3] = &cells_grid[i][M-2];
      cells_grid[i][M-1].neighbours[4] = b;
      cells_grid[i][M-1].neighbours[5] = &cells_grid[i+1][M-2];
      cells_grid[i][M-1].neighbours[6] = &cells_grid[i+1][M-1];
      cells_grid[i][M-1].neighbours[7] = b;


    }
    const int blockSz = 100;
    int nBlocks = (N-1) /blockSz;
    int i, j, block_i, block_j;
    for (block_i = 1 ; block_i < nBlocks; block_i ++){
      int iStart = (block_i-1)*blockSz;
      for(block_j = 1 ; block_j < nBlocks ; block_j++){
        int jStart = (block_j-1)*blockSz;
        for (int k =)

        cells_grid[iStart][jStart].neighbours = (cell**)malloc(8*sizeof(cell*));
      /*  for (int t = 0 ; t < 8 ; t++){
          cells_grid[i][j].neighbours[t] = (cell*)malloc(sizeof(cell));
        }*/

        cells_grid[iStart][jStart].neighbours[0] = &cells_grid[iStart-1][jStart-1];
        cells_grid[iStart][jStart].neighbours[1] = &cells_grid[iStart-1][jStart];
        cells_grid[iStart][jStart].neighbours[2] = &cells_grid[iStart-1][jStart+1];
        cells_grid[iStart][jStart].neighbours[3] = &cells_grid[iStart][jStart-1];
        cells_grid[iStart][jStart].neighbours[4] = &cells_grid[iStart][jStart+1];
        cells_grid[iStart][jStart].neighbours[5] = &cells_grid[iStart+1][jStart-1];
        cells_grid[iStart][jStart].neighbours[6] = &cells_grid[iStart+1][jStart];
        cells_grid[iStart][jStart].neighbours[7] = &cells_grid[iStart+1][jStart+1];
      }
    }

}


void free_neighbours(cell** cells_grid , int N , int M){

  for (int i = 0 ; i < N ; i++){
    for (int j = 0 ; j < M ; j++){
      for (int k = 0 ; k < 8 ; k++){
      //  free(cells_grid[i][j].neighbours[k]);
      }
      free(cells_grid[i][j].neighbours);
    }
  }
}



inline void generation_update(cell * cell){
  cell->current = cell->next;
}
