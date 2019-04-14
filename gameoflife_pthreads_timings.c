#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
//declare variables that will be read as arguments in main function
int N_ROWS, M_COLS , N_STEPS  ,NUM_THREADS;

//set counters and initialize mutex and conditions that will be used in barriers
int counter_update = 0;
int counter_evolve = 0;

//declaring mutex and conditions that will be used for barriers
pthread_mutex_t lock_update;
pthread_cond_t signal_update;

pthread_mutex_t lock_evolve;
pthread_cond_t signal_evolve;

typedef struct _cell{
  struct _cell** neighbours;
  int current;
  int next;
} cell;

//struct to pass arguments to pthread_create
struct parameters{
  int min;
  int max;
};


cell** world;

void seed_cells(cell**, int , int );
void obtain_neighbours(cell**, int , int , cell*);
void free_neighbours(cell**, int , int  );
void print_cell(cell** , int , int);
void generation_update(int , int);
void evolve(int  , int );
void* evolution_threads(void*);
void barrier_evolving();
void barrier_update();


int main(int argc , char* argv[]){
  if (argc != 5){
    printf("Wrong Number of Arguments\n");
  }
  N_ROWS = atoi(argv[1]);
  M_COLS = atoi(argv[2]);
  N_STEPS = atoi(argv[3]);
  NUM_THREADS = atoi(argv[4]);


  //Declaring block size to parallelize over columns
  int size_block = M_COLS/NUM_THREADS;

  world = (cell**)malloc(N_ROWS*sizeof(cell*));
  for (int i = 0 ; i < N_ROWS ; i++){
    world[i] = (cell*)malloc(M_COLS*sizeof(cell));
  }

  //Applying the initial conditions
  seed_cells(world, N_ROWS, M_COLS);

  //Auxiliary pointer
  cell *b = (cell*)malloc(sizeof(cell));
  b->neighbours = NULL;
  b->current = 0;
  b->next = 0;


  obtain_neighbours(world, N_ROWS , M_COLS , b);


  struct parameters *arguments;
  arguments = malloc(sizeof(struct parameters)*NUM_THREADS);


  pthread_t* thread_handles = (pthread_t*)malloc(NUM_THREADS*sizeof(pthread_t));


  printf("Size block : %d \n" , size_block);

  //Playing Game of life for n_steps Generations
  for (int t = 0 ; t < N_STEPS ; t++){
    for (int i = 0 ; i < NUM_THREADS ; i++){
      arguments[i].min = i*size_block;
      arguments[i].max = i*size_block + size_block;
      pthread_create((void*)&thread_handles[i] , NULL , (void*)evolution_threads , (void*)&arguments[i]);
    }
    for (int i = 0 ; i < NUM_THREADS ; i++){
      pthread_join(thread_handles[i] , NULL);
    }
  }
  free(arguments);
  free(thread_handles);
  free_neighbours(world, N_ROWS, M_COLS);
  for (int i = 0 ; i < M_COLS ; i++){
    free(world[i]);
  }
  free(world);
  free(b);

  return 0;
}

void* evolution_threads(void*arg){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   evolution_threads
   # Purpose:    Enables our previous evolve function to be
                compatible with pthread, it iterates
                over the global variable using evolve
                and update function with its respective barriers.
   # In args:
   # @param arg ---->Struct that contain the boundaries for
                      the parallelization
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  struct parameters *par = (struct parameters*)arg;
    for (int i = par->min ;  i < par->max ; i++){
      for (int j = 0 ; j < N_ROWS ; j++){
        evolve(i , j);
      }
    }
    barrier_evolving();
    for (int i = par->min ;  i < par->max ; i++){
      for (int j = 0 ; j < N_ROWS ; j++){
        generation_update(i , j);
      }
    }
    barrier_update();
    return NULL;
}

void barrier_evolving(){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   barrier_evolving
   # Purpose:    Sets a barrier to ensure thread synchronization after using
                  function evolve over different threads
   # In args:
                Void
   #
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  pthread_mutex_lock(&lock_evolve);

  counter_evolve++;
  if (counter_evolve == NUM_THREADS){
    pthread_cond_broadcast(&signal_evolve);
    counter_evolve = 0;
  }
  else{
    pthread_cond_wait(&signal_evolve , &lock_evolve);

  }
  pthread_mutex_unlock(&lock_evolve);
  return;
}

void barrier_update(){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   barrier_update
   # Purpose:    Sets a barrier to ensure thread synchronization after using
                  function update over different threads
   # In args:
                Void
   #
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  pthread_mutex_lock(&lock_update);

  counter_update++;

  if (counter_update == NUM_THREADS){
    pthread_cond_broadcast(&signal_update);
    counter_update = 0;

  }
  else{
    pthread_cond_wait(&signal_update , &lock_update);
  }
  pthread_mutex_unlock(&lock_update);
  return;
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
  for (int i = 0 ; i<N ; i++){
    for (int j = 0 ; j<M ; j++){
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

void evolve(int i , int j){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   Evolution
   # Purpose:    Applies the transition rule of COnways Game of life
   # In args:    title
   #              cell: we will iterate over all cells again, it takes a pointer to each cell so td
   #              that its value can be changed
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
     int counter = 0;
     for (int k = 0 ; k < 8 ; k++){
       counter+=(world[i][j]).neighbours[k]->current;
     }
     if ((world[i][j]).current == 1){
       if (counter<2){
         (world[i][j]).next = 0;
       }
       else if(counter == 2 || counter == 3){
         (world[i][j]).next = 1;
       }
       else{
         (world[i][j]).next = 0;
       }
     }
     else{
       if (counter ==3){
         (world[i][j]).next = 1;
         }
      else{
         (world[i][j].next = 0);
      }
       }
     }

void generation_update(int i , int j){
  /*$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$
   # Function:   generation_update
   # Purpose:    Updates the cell to its state in the next generation
   # In args:    title
   # @param cell: we will iterate over all cells again, it takes a pointer to each cell so td
   # @param that its value can be changed
   $$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$*/
  world[i][j].current = world[i][j].next;
}
