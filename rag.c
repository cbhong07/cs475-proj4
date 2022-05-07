#define NLOCK 10
#define NPROC 20

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int rag[NLOCK+NPROC][NLOCK+NPROC];

void rag_request(int pid, int lockid)
{
	printf("%d requests %d\n", pid, lockid);
	rag[pid][lockid+NPROC] = 1;
}

void rag_alloc(int pid, int lockid)
{
	printf("%d allocs %d\n", lockid, pid);
	rag[lockid+NPROC][pid] = 1;
	rag[pid][lockid+NPROC] = 0;
}

void rag_dealloc(int pid, int lockid)
{
	printf("%d deallocs %d\n", pid, lockid);
	rag[lockid+NPROC][pid] = 0;
	rag[pid][lockid+NPROC] = 0;
}

void rag_print()
{
	for(int i = 0; i < (NPROC+NLOCK); i++)
	{
		printf("[%d] ", i);
		for(int j = 0; j < (NLOCK+NPROC); j++)
		{
			printf("%d ", rag[i][j]);
		}
		printf("\n");
	}
}

void deadlock_detect()
{
	//char* visited[NLOCK*NPROC];
	//int visitCounter = 0;
	for(int i = 0; i < (NLOCK+NPROC); i++) {
		for(int j = 0; j < (NLOCK+NPROC); j++) {
			if(rag[i][j] > 1) {
				rag_print();
				printf("DEADLOCK ");
				deadlockHelper();
				return;
			}
			else if(rag[i][j] == 1) {
				rag[i][j] += 1;
				printf("Rag[%d][%d] increased\n", i, j);
				/**
				visited[visitCounter] = i + "->" + j;
				visitCounter += 1;
				**/
				i = j;
				j = 0;
			}
		}
	}
}

void deadlockHelper()
{
	for(int i = 0; i < (NLOCK+NPROC); i++)
	{
		for(int j = 0; j < (NLOCK+NPROC); j++)
		{
			if(rag[i][j] == 2) {
				if(i > NLOCK)
					printf("pid=%d ", i-NLOCK); //proc :)
				else
					printf("lockID=%d ", i); //lock :)
				rag[i][j] += -1;
				i = j;
				j = 0;
			}
		}
	}
}

int main(int arg, int **argv)
{
	char input[] = "1   R   1\n1    A   1\n0    R   1\n0    R   2\n0    A   2\n1    R   2";
	char* token = strtok(input, "\t\n   ");
	char* ids[3];
	int i = 0;

	while(token != NULL)
	{
		//printf("%s\n", token);
		ids[i] = token;
		if(i == 2)
		{
			if(*ids[1] == 'R')
				rag_request(atoi(ids[0]), atoi(ids[2]));
			else if(*ids[1] == 'A')
				rag_alloc(atoi(ids[0]), atoi(ids[2]));
			else if(*ids[1] == 'D')
				rag_dealloc(atoi(ids[0]), atoi(ids[2]));
			else {
				printf("Error: unexpected ID[1]: ");
				printf("%s\n", *ids);
			}
			i = 0;
		}
		else {
			i++;
		}
		token = strtok(NULL, "\t\n   ");
	}

	rag_print();
	deadlock_detect();
	rag_print();
}