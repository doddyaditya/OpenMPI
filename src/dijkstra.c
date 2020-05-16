#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>
#include <assert.h>

int minDistance(int dist[], int sptSet[], int V)
{
	// Initialize min value
	int min = INT_MAX, min_index;
	for (int v = 0; v < V; v++)
		if (sptSet[v] == 0 && dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}

int *dijkstra(int **graph, int src, int V)
{
	int dist[V]; // The output array. dist[i] will hold the shortest
	// distance from src to i

	int sptSet[V]; // sptSet[i] will be true if vertex i is included in shortest
	// path tree or shortest distance from src to i is finalized

	// Initialize all distances as INFINITE and stpSet[] as false
	for (int i = 0; i < V; i++)
		dist[i] = INT_MAX, sptSet[i] = 0;

	// Distance of source vertex from itself is always 0
	dist[src] = 0;

	// Find shortest path for all vertices
	for (int count = 0; count < V - 1; count++)
	{
		// Pick the minimum distance vertex from the set of vertices not
		// yet processed. u is always equal to src in the first iteration.

		int u = minDistance(dist, sptSet, V);

		// Mark the picked vertex as processed
		sptSet[u] = 1;

		// Update dist value of the adjacent vertices of the picked vertex.
		for (int v = 0; v < V; v++)

			// Update dist[v] only if is not in sptSet, there is an edge from
			// u to v, and total weight of path from src to v through u is
			// smaller than current value of dist[v]
			if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
				dist[v] = dist[u] + graph[u][v];
	}

	int *ansArray;
	ansArray = (int *)malloc(V * sizeof(int));
	for (int i = 0; i < V; i++)
	{
		ansArray[i] = dist[i];
	}
	return ansArray;
}
int initGraf2(int ***array, int n)
{

	/* allocate the n*m contiguous items */
	int *p = (int *)malloc(n * n * sizeof(int));
	if (!p)
		return -1;

	/* allocate the row pointers into the memory */
	(*array) = (int **)malloc(n * sizeof(int *));
	if (!(*array))
	{
		free(p);
		return -1;
	}

	/* set up the pointers into the contiguous memory */
	for (int i = 0; i < n; i++)
		(*array)[i] = &(p[i * n]);

	return 0;
}
int **initGraf3(int n)
{
	int random;
	int *data = (int *)malloc(n * n * sizeof(int));
	int **array = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; i++)
		array[i] = &(data[n * i]);
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			random = rand() % 100;
			if (i == j)
			{
				array[i][i] = 0;
			}
			else
			{
				array[i][j] = random;
				array[j][i] = random;
			}
		}
	}
	return array;
}
int **initGraf(int n)
{
	srand(13517143);
	int random, **graf;

	graf = (int **)malloc(n * sizeof(int *));
	for (int i = 0; i < n; ++i)
		graf[i] = (int *)malloc(n * sizeof(int));
	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			random = rand() % 100;
			if (i == j)
			{
				graf[i][i] = 0;
			}
			else
			{
				graf[i][j] = random;
				graf[j][i] = random;
			}
		}
	}
	return graf;
}
void printGraf(int **graf, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			printf("%d\t", graf[i][j]);
		}
		printf("\n");
	}
}
int randomNumber(int ***graf, int n)
{
	int random;
	srand(13517143);

	for (int i = 0; i < n; i++)
	{
		for (int j = i; j < n; j++)
		{
			random = rand() % 100;
			if (i == j)
			{
				(*graf)[i][i] = 0;
			}
			else
			{
				(*graf)[i][j] = random;
				(*graf)[j][i] = random;
			}
		}
	}
}
int free2dint(int ***array)
{
	/* free the memory - the first element of the array is at the start */
	free(&((*array)[0][0]));

	/* free the pointers into the memory */
	free(*array);

	return 0;
}
int main(int argc, char *argv[])
{

	clock_t start, end;
	double cpu_time_used;
	int rank, size;
	int n, random;
	int numnode = atoi(argv[1]);
	MPI_Status Stat;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int **graf, *arr;
	int localdata[numnode];
	int sendbuf[numnode];
	int i;
	int length = numnode / size;
	int **recvbuf;
	initGraf2(&graf, numnode);
	initGraf2(&recvbuf, numnode);
	if (rank == 0)
	{
		for (i = 0; i < numnode; i++)
		{
			sendbuf[i] = i;
		}

		randomNumber(&graf, numnode);
		start = clock();
	}
	MPI_Bcast(&graf[0][0], numnode * numnode, MPI_INT, 0, MPI_COMM_WORLD);

	MPI_Scatter(sendbuf, length, MPI_INT, &localdata, length, MPI_INT, 0, MPI_COMM_WORLD);
	int **matrixtemp;
	initGraf2(&matrixtemp, numnode);

	for (int j = 0; j < length; j++)
	{
		arr = dijkstra(graf, localdata[j], numnode);
		for (int i = 0; i < numnode; i++)
		{
			matrixtemp[j][i] = arr[i];
		}
	}
	MPI_Gather(&matrixtemp[0][0], length * numnode, MPI_INT, &recvbuf[0][0], length * numnode, MPI_INT, 0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		for (int j = 0; j < numnode; j++)
		{
			for (int i = 0; i < numnode; i++)
				printf("%d\t", recvbuf[j][i]);
			printf("\n");
		}
		end = clock();
		cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

		printf("waktu yang dibutuhkan %f", cpu_time_used);
	}
	free2dint(&graf);
	free2dint(&matrixtemp);
	free2dint(&recvbuf);
	free(arr);
	MPI_Finalize();
}
