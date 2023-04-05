#include<mpi.h>


#include <stdio.h>
#include <stdlib.h>
 int main ( ) { 
    int arr [ 10 ] = { 1 , 6 , 4 , 2 , 3 , 7 , 9 , 4 , 2 , 10 } ;
     int i ; 
     int r [ 2 ] , j = 0 ; r [ 0 ] = 0 ; r [ 1 ] = 0 ; 
     int tid ; 
     omp_set_num_threads ( 1 ) ; 
     #pragma omp parallel 
     { 
        tid = omp_get_num_threads ( ) ; 
        if ( tid == 1 )
         { 
            for ( i = 0 ; i < 10 ; i ++ )
             { 
                if( arr [ i ] >= 0 && arr [ i ] <= 5 ) 
                {
                     r[ 0 ]++; 
                     }
                      if ( arr [ i ] >= 6 && arr [ i ] <= 10 ) {
                         r [ 1 ] ++ ; }
                         }
                         }
                         } printf ( " In range [ 0-5 ]: %d\n " , r [ 0 ] ) ; 
                         printf ( " In range [ 6-10 ] : %d\n " , r [ 1 ] ) ; 
                         return 0 ; }