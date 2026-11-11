#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int empty(struct queue_t *q)
{
        if (q == NULL)
                return 1;
        return (q->size == 0);
}

void enqueue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: put a new process to queue [q] */
        if(q == NULL || proc == NULL)
                return; 

        if(q->size >= MAX_QUEUE_SIZE)
                return;

        q->proc[q->size] = proc;
        q->size++;
}

struct pcb_t *dequeue(struct queue_t *q)
{
        /* TODO: return a pcb whose prioprity is the highest
         * in the queue [q] and remember to remove it from q
         * */
        if(empty(q))
                return NULL;

        struct pcb_t *curr_proc = q->proc[0];

        #ifndef MLQ_SCHED

        for(int i = 1;i<q->size;i++)
        {
                if(curr_proc->priority > q->proc[i]->priority)
                        curr_proc = q->proc[i];
        }

        #endif

        return purgequeue(q, curr_proc);
}

struct pcb_t *purgequeue(struct queue_t *q, struct pcb_t *proc)
{
        /* TODO: remove a specific item from queue
         * */
        if(empty(q) || proc == NULL)
                return NULL;

        for(int i = 0;i < q->size; i++)
        {       
                if(q->proc[i] == proc)
                        return removeFromQueue(q, i);
        }

        return NULL;
}

// Student's functions
struct pcb_t *removeFromQueue(struct queue_t * q, int index)
{
        if(empty(q) || (index < 0) || index >= q->size)
                return NULL;

        struct pcb_t * proc = q->proc[index];

        for(int i = index; i < q->size - 1; i++)
                q->proc[i] = q->proc[i+1];

        q->size--;
        return proc;
}