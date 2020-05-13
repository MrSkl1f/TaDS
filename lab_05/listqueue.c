#include "main.h"

void InitForList(struct QueueForList *queue)
{
    queue->ptr_push = NULL;
    queue->ptr_pop = NULL;
    queue->len = 0;
}

void FreeList(struct QueueForList *queue)
{
    struct node_t *cur = queue->ptr_pop, *buf = NULL;
    while (cur)
    {
        buf = cur->last;
        free(cur);
        cur = buf;
    }
    queue->ptr_push = NULL;
    queue->ptr_pop = NULL;
    queue->len = 0;
}

int PushList(struct QueueForList *queue, int elem)
{
    int result = 1;
    struct node_t *new = (struct node_t *) malloc(sizeof(struct node_t));
    if (new)
    {
        new->last = NULL;
        new->value = elem;
        if (queue->len)
            queue->ptr_push->last = new;
        else
            queue->ptr_pop = new;
        queue->ptr_push = new;
        queue->len += 1;
    }
    else
        result = 0;
    
    return result;
}

void PopList(struct QueueForList *queue)
{
    int elem;
    int result = 1;
    if (queue->len)
    {
        elem = queue->ptr_pop->value;
        struct node_t *buf = queue->ptr_pop;
        queue->ptr_pop = queue->ptr_pop->last;
        free(buf);
        queue->len -= 1;
    }
    else
        result = 0;
}
