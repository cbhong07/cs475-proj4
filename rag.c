#define NLOCK 10
#define NPROC 20

#include <stdlib.h>
int rag[NLOCK+NPROC][NLOCK+NPROC];

void rag_request(int pid, int lockid)
{
    rag[pid][lockid] = 1;
}

void rag_alloc(int pid, int lockid)
{
    rag[lockid][pid] = 1;
    rag[pid][lockid] = 0;
}

void rag_dealloc(int pid, int lockid)
{
    rag[lockid][pid] = 0;
    rag[pid][lockid] = 0;
}

void rag_print()
{
    for(int i = 0; i < (NPROC+NLOCK); i++)
    {
        for(int j = 0; j < (NLOCK+NPROC); j++)
        {
            kprintf("%d ", rag[i][j]);
        }
        kprintf("\n");
    }
}

void deadlock_detect()
{
    //char* visited[NLOCK*NPROC];
    //int visitCounter = 0;
    for(int i = 0; i < (NLOCK+NPROC); i++) {
        for(int j = 0; j < (NLOCK+NPROC); j++) {
            if(rag[i][j] > 1) {
                kprintf("DEADLOCK");
                deadlockHelper();
                break;
            }
            else if(rag[i][j] == 1) {
                rag[i][j] += 1;
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
                    krpintf("pid=%d ", i-NLOCK); //proc
                else
                    kprintf("lockID=%d ", i);
                i = j;
                j = 0;
            }
        }
    }
}

