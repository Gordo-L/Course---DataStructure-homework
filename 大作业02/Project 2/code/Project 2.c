#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#define MaxNv 2000
#define INF 1e9

int dist[MaxNv], sequence[MaxNv], G[MaxNv][MaxNv];
bool visit[MaxNv];

int main() {
	int Nv, Ne, K, x, y, z;
	//Enter the total number of vertices(Nv) and edges(Ne).
	scanf("%d %d", &Nv, &Ne);
	//Initialize adjacency matrix(G).
	for (int i = 0; i < MaxNv; i++) {
		for (int j = 0; j < MaxNv; j++) {
			G[i][j] = INF;  //Each edge is initialized to infinity.
		}
	}
	//Store edge information in adjacency matrix(G).
	for (int i = 0; i < Ne; i++) {
		scanf("%d %d %d", &x, &y, &z);
		G[x][y] = G[y][x] = z;
	}
	//Enter the number of queries(K).
	scanf("%d", &K);
	//Judge each case.
	while (K--) {
		//Enter the sequence to be judged.
		for (int i = 1; i <= Nv; i++) {
			scanf("%d", &sequence[i]);
		}
		//flag to judge whether it is a Dijkstra sequence.
		bool flag = true;
		//Initialize the matrix(visit) to indicate whether the vertex has been accessed.
		for (int i = 0; i < MaxNv; i++) {
			visit[i] = false;  //Each vertex is initialized as not accessed.
		}
		//Initialize the matrix(dist) to indicate the shortest 
		//path length between one particular source vertex to  
		//all the other vertices of the given graph.
		for (int i = 0; i < MaxNv; i++) {
			dist[i] = INF;  //Each path length is initialized to INF.
		}
		//The shortest path length from oneself to oneself is initialized to 0.
		dist[sequence[1]] = 0;
		/*
		* According to the input order,judge whether the distance
		* of the input vertex is the shortest path length currently.
		* If no,return false;if yes,update the matrix(dist).
		*/

		for (int i = 1; i <= Nv; i++) {
			int minN = -1, minDist = INF;
			/*
			* Find the minimum path length(minDist) and the corresponding vertex(minN)
			* in the currently non-visited vertices.
			*/
			for (int j = 1; j <= Nv; j++) {
				if (!visit[j] && dist[j] < minDist) {
					minN = j;
					minDist = dist[j];
				}
			}
			/*
			* If the minimum path is not found or the distance
			* of the input vertex is not equal to the current
			* shortest path length,then failed.
			*/
			if (minN == -1 || dist[minN] != dist[sequence[i]]) {
				flag = false;
				continue;
			}
			//Update the information.
			minN = sequence[i];
			visit[minN] = true;
			/*
			* For each of its adjacent vertix,if the shortest path
			* length becomes shorter after adding minN, update it.
			*/
			for (int j = 1; j <= Nv; j++) {
				if (!visit[j] && G[minN][j] != INF && G[minN][j] + dist[minN] < dist[j]) {
					dist[j] = G[minN][j] + dist[minN];
				}
			}
		}
		//Judge according to the flag.
		if (flag)printf("Yes\n");
		else printf("No\n");
	}
	getchar();
	getchar();
}