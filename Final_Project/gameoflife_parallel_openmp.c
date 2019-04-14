#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include <time.h>

typedef struct _cell{
  struct _cell** neighbours;
  int current;
  int next;
} cell;

cell ** cells_grid ;
cell *b ;


void seed_cells(cell**, int , int );
void obtain_neighbours(cell**, int , int , cell*);
void free_neighbours(cell**, int , int );
void print_cell(cell** , int , int);
void generation_update(cell*);
void evolution(cell*);

//cell** cells_grid;
//cell* b;

int main(int argc, char *argv[]) {

  if (argc != 4){
    printf("Introduce only one argument \n");
    return -1;
  }

  const int N = atoi(argv[1]);
  const int M = atoi(argv[2]);
  const int n_steps = atoi(argv[3]);



  cells_grid = (cell**)malloc(N*sizeof(cell*));
  for (int i = 0 ; i < N; i++){
    cells_grid[i] = (cell*)malloc(M*sizeof(cell));
  }

  //Applying the initial conditions
  seed_cells(cells_grid , N, M);

  b = (cell*)malloc(sizeof(cell));
  b->neighbours = NULL;
  b->current = 0;
  b->next = 0;
  obtain_neighbours(cells_grid , N , M , b);

  int j,i;
  //Playing Game of life for n_steps generations
  for (int k = 0 ; k < n_steps ; k++){
    #pragma omp parallel for private(j) schedule(static,1)
    for ( i = 0 ; i < M ; i++){
      for (j = 0 ; j < N ; j++){
          evolution(&cells_grid[i][j]);
      }
    }
   #pragma omp parallel for private(j) schedule(static, 1)
    for (i = 0 ; i < M ; i++){
      for ( j = 0 ; j < N ; j++){
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

 return 0;

}
void seed_cells(cell** cells_grid , int N , int M){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   Seed_Cell
   # Purpose:    Fills the cells of the with alive and dead cells (0 or 1)
   # In args:
   # @param cells_grid : uninitialized world
   # @param M:  number of rows in world
   # @param N:  number of cols in world
   #
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  int j;
  #pragma omp parallel for private(j)
  for (int i = 0 ; i<N ; i++){
    for (j = 0 ; j<M ; j++){
      int cur = rand()%2;
      cells_grid[i][j].current = cur;
      cells_grid[i][j].next = cur;
    }
  }
}

void print_cell(cell** cells_grid , int N , int M){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   Print_cell
   # Purpose:    Print the current generation
   # In args:
   # @param cells_grid : whole world
   # @param M:  number of rows in world
   # @param N:  number of cols in world
   #
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  for (int i = 0 ; i < N ; i++){
    for (int j = 0 ; j < M ; j++){
      printf(" %d " , cells_grid[i][j].current);
    }
    printf(" \n");
  }
}

void obtain_neighbours(cell** cells_grid , int N , int M , cell* b ){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   Obtain Neighbours
   # Purpose:    Loads pointers to the neighbours of each cell in the array member of cell struct
   # In args:
   # @param cells_grid : cell from which we will find the neighbours
   # @param  M:  number of rows in world
   # @param N:  number of cols in world
   # @param b: auxiliary pointer for cells in the corners
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/



  cells_grid[0][0].neighbours = (cell**)malloc(8*sizeof(cell*));
  cells_grid[N-1][0].neighbours = (cell**)malloc(8*sizeof(cell*));
  cells_grid[0][M-1].neighbours = (cell**)malloc(8*sizeof(cell*));
  cells_grid[N-1][M-1].neighbours = (cell**)malloc(8*sizeof(cell*));

    //obtain neighbours for [0][0]
  cells_grid[0][0].neighbours[0] = b;
  cells_grid[0][0].neighbours[1] = b;
  cells_grid[0][0].neighbours[2] = b;
  cells_grid[0][0].neighbours[3] = b;
  cells_grid[0][0].neighbours[4] = &cells_grid[0][1];
  cells_grid[0][0].neighbours[5] = b;
  cells_grid[0][0].neighbours[6] = &cells_grid[1][0];
  cells_grid[0][0].neighbours[7] = &cells_grid[1][1];

  //obtain neighbours for [N-1][0]
  cells_grid[N-1][0].neighbours[0] = b;
  cells_grid[N-1][0].neighbours[1] = &cells_grid[N-2][0];
  cells_grid[N-1][0].neighbours[2] = &cells_grid[N-2][1];
  cells_grid[N-1][0].neighbours[3] = b;
  cells_grid[N-1][0].neighbours[4] = &cells_grid[N-1][1];
  cells_grid[N-1][0].neighbours[5] = b;
  cells_grid[N-1][0].neighbours[6] = b;
  cells_grid[N-1][0].neighbours[7] = b;

  //obtain neighbours for [0][M-1]
  cells_grid[0][M-1].neighbours[0] = b;
  cells_grid[0][M-1].neighbours[1] = b;
  cells_grid[0][M-1].neighbours[2] = b;
  cells_grid[0][M-1].neighbours[3] = &cells_grid[0][M-2];
  cells_grid[0][M-1].neighbours[4] = b;
  cells_grid[0][M-1].neighbours[5] = &cells_grid[1][M-2];
  cells_grid[0][M-1].neighbours[6] = &cells_grid[1][M-1];
  cells_grid[0][M-1].neighbours[7] = b;

  //obtain neighbours for [N-1][M-1]
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

    //obtain neighbours for first column
    cells_grid[0][i].neighbours[0] = b;
    cells_grid[0][i].neighbours[1] = b;
    cells_grid[0][i].neighbours[2] = b;
    cells_grid[0][i].neighbours[3] = &cells_grid[0][i-1];
    cells_grid[0][i].neighbours[4] = &cells_grid[0][i+1];
    cells_grid[0][i].neighbours[5] = &cells_grid[1][i-1];
    cells_grid[0][i].neighbours[6] = &cells_grid[1][i];
    cells_grid[0][i].neighbours[7] = &cells_grid[1][i+1];

    //obtain neighbours for last column
    cells_grid[N-1][i].neighbours[0] = &cells_grid[N-2][i-1];
    cells_grid[N-1][i].neighbours[1] = &cells_grid[N-2][i];
    cells_grid[N-1][i].neighbours[2] = &cells_grid[N-2][i+1];
    cells_grid[N-1][i].neighbours[3] = &cells_grid[N-1][i-1];
    cells_grid[N-1][i].neighbours[4] = &cells_grid[N-1][i+1];
    cells_grid[N-1][i].neighbours[5] = b;
    cells_grid[N-1][i].neighbours[6] = b;
    cells_grid[N-1][i].neighbours[7] = b;
  }
  for (int i = 1 ; i < (N-1) ; i++){
    cells_grid[i][0].neighbours = (cell**)malloc(8*sizeof(cell*));
    cells_grid[i][M-1].neighbours = (cell**)malloc(8*sizeof(cell*));

    //obtain neighbours for first row
    cells_grid[i][0].neighbours[0] = b;
    cells_grid[i][0].neighbours[1] = &cells_grid[i-1][0];
    cells_grid[i][0].neighbours[2] = &cells_grid[i-1][1];
    cells_grid[i][0].neighbours[3] = b;
    cells_grid[i][0].neighbours[4] = &cells_grid[i][1];
    cells_grid[i][0].neighbours[5] = b;
    cells_grid[i][0].neighbours[6] = &cells_grid[i+1][0];
    cells_grid[i][0].neighbours[7] = &cells_grid[i+1][1];

    //obtain neighbours for last row
    cells_grid[i][M-1].neighbours[0] = &cells_grid[i-1][M-2];
    cells_grid[i][M-1].neighbours[1] = &cells_grid[i-1][M-1];
    cells_grid[i][M-1].neighbours[2] = b;
    cells_grid[i][M-1].neighbours[3] = &cells_grid[i][M-2];
    cells_grid[i][M-1].neighbours[4] = b;
    cells_grid[i][M-1].neighbours[5] = &cells_grid[i+1][M-2];
    cells_grid[i][M-1].neighbours[6] = &cells_grid[i+1][M-1];
    cells_grid[i][M-1].neighbours[7] = b;



    for (int j = 1 ; j < (M-1) ; j++){
      cells_grid[i][j].neighbours = (cell**)malloc(8*sizeof(cell*));

      //obtain neighbours for cells that are not in the borders
      cells_grid[i][j].neighbours[0] = &cells_grid[i-1][j-1];
      cells_grid[i][j].neighbours[1] = &cells_grid[i-1][j];
      cells_grid[i][j].neighbours[2] = &cells_grid[i-1][j+1];
      cells_grid[i][j].neighbours[3] = &cells_grid[i][j-1];
      cells_grid[i][j].neighbours[4] = &cells_grid[i][j+1];
      cells_grid[i][j].neighbours[5] = &cells_grid[i+1][j-1];
      cells_grid[i][j].neighbours[6] = &cells_grid[i+1][j];
      cells_grid[i][j].neighbours[7] = &cells_grid[i+1][j+1];

    }
  }
}


void free_neighbours(cell** cells_grid , int N , int M){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   Free_Neighbours
   # Purpose:    Auxiliary function that frees the neighbour array
   # In args:    title
   # @param cells_grid : we will iterate over each cell
   # @param M:  number of rows in world
   # @param N:  number of cols in world
   #
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  for (int i = 0 ; i < N ; i++){
    for (int j = 0 ; j < M ; j++){
      free(cells_grid[i][j].neighbours);
    }
  }
}

void evolution(cell* cell){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   Evolution
   # Purpose:    Applies the transition rule of COnways Game of life
   # In args:    title
   # @param cell: we will iterate over all cells again, it takes a pointer to each cell so td
   # @param that its value can be changed
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  int counter = 0;
  for (int i = 0 ; i < 8 ; i++){
    counter+=(*cell).neighbours[i]->current;
  }
  if ((*cell).current == 1){
    if (counter<2){
      (*cell).next = 0;
    }
    else if(counter == 2 || counter == 3){
      (*cell).next = 1;
    }
    else{
      (*cell).next = 0;
    }
  }
  else{
    if (counter ==3){
      (*cell).next = 1;
      }
    }
  }

void generation_update(cell* cell){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   generation_update
   # Purpose:    Updates the cell to its state in the next generation
   # In args:    title
   # @param cell: we will iterate over all cells again, it takes a pointer to each cell so td
   # @param that its value can be changed
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  cell->current = cell->next;
}
