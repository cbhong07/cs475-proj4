#define NLOCK 10
#define NPROC 20

#include <stdlib.h>

void rag_request(int pid, int lockid)
{

}

void rag_alloc(int pid, int lockid)
{

}

void rag_dealloc(int pid, int lockid)
{

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

}

