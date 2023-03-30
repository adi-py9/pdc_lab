#include <stdio.h> 
#include <stdlib.h> 
#include <mpi.h> 
#include <math.h> 


int main(argc,argv) 
int argc; 
char *argv[]; 

{ 

    int i,id, numprocs; 
    int source,count; 
    int buffer[4]; 
    MPI_Status status; 
    MPI_Request request; 

    MPI_Init(&argc,&argv); 
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs); 
    MPI_Comm_rank(MPI_COMM_WORLD,&id); 

    source=0; 
    count=4; 

    if(id == source){ 
      for(i=0;i<count;i++) 
        buffer[i]=i; 
    } 

    MPI_Bcast(buffer,count,MPI_INT,source,MPI_COMM_WORLD); 

    for(i=0;i<count;i++) 
      printf("%d ",buffer[i]); 

    printf("\n"); 
    MPI_Finalize(); 

} 