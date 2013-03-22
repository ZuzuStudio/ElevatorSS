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

void enqueue (Node *&head, Node *&tail, Data dt);
bool dequeue (Node *&head, Node *&tail, Data &dt);
bool is_empty (Node *head, Node *tail);
bool on_tail(Node *tail, Data &dt);
bool on_head(Node *head, Data &dt);
void clear (Node *&head, Node *&tail);

#endif
