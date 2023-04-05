#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>

#define MAX_QUERY_LENGTH 1000
#define MAX_RESULT_LENGTH 10000

typedef struct {
    char* data;
    int size;
} SearchData;

void search(SearchData data, char* query, char* result) {
    // Perform a simple search on the data
    int num_matches = 0;
    char* match = strstr(data.data, query);
    while (match != NULL) {
        num_matches++;
        match = strstr(match + 1, query);
    }

    // Format the result string
    sprintf(result, "%d matches in %d bytes", num_matches, data.size);
}

int main(int argc, char** argv) {
    int rank, size;
    int i, j;
    char query[MAX_QUERY_LENGTH];
    char result[MAX_RESULT_LENGTH];
    MPI_Status status;
    SearchData* data;
    int num_data;

    // Initialize MPI
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    if (rank == 0) {
        // Master process: handle queries from clients
        while (1) {
            // Get a query from the client
            printf("Enter a query: ");
            fflush(stdout);
            fgets(query, MAX_QUERY_LENGTH, stdin);
            int len = strlen(query);
            if (len > 0 && query[len-1] == '\n') {
                query[len-1] = '\0';
            }

            // Distribute the query to worker processes
            for (i = 1; i < size; i++) {
                MPI_Send(query, MAX_QUERY_LENGTH, MPI_CHAR, i, 0, MPI_COMM_WORLD);
            }

            // Receive the results from worker processes
            for (i = 1; i < size; i++) {
                MPI_Recv(result, MAX_RESULT_LENGTH, MPI_CHAR, i, 0, MPI_COMM_WORLD, &status);
                printf("Result from server %d: %s\n", i, result);
            }
        }
    } else {
        // Worker process: handle search requests from the master
        while (1) {
            // Receive a query from the master
            MPI_Recv(query, MAX_QUERY_LENGTH, MPI_CHAR, 0, 0, MPI_COMM_WORLD, &status);

            // Perform the search on the local data
            sprintf(result, "No matches");
            for (i = 0; i < num_data; i++) {
                search(data[i], query, result);
                if (strstr(result, "matches") != NULL) {
                    break;
                }
            }

            // Send the result back to the master
            MPI_Send(result, MAX_RESULT_LENGTH, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
        }
    }

    MPI_Finalize();
    return 0;
}
