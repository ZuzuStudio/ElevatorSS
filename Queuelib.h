#ifndef QUEUELIB_H
#define QUEUELIB_H

struct Men
{
    short finish;
    short time;
};

typedef Men Data;

struct Node
{
    Data content;
    Node *link;
};

struct Queue
{
    Node *head;
    Node *tail;
};

void enqueue (Queue &a, Data dt);
bool dequeue (Queue &a, Data &dt);
bool is_empty (Queue a);
bool on_tail(Queue a, Data &dt);
bool on_head(Queue a, Data &dt);
void clear (Queue &a);

#endif
