#ifndef QUEUELIB_H
#define QUEUELIB_H

using namespace std;

struct Men
{
    short finish;
    short time;
};

template <typename T>
struct Node
{
    T content;
    Node<T> *link;
};

template <typename T>
struct Queue
{
    Node<Men> *head;
    Node<Men> *tail;
    short hmp, maxhmp;
    bool *h;
};

#endif

template <typename T>
bool is_empty (Queue<T> a)
{
    return (a.tail==NULL)&&(a.head==NULL);
}

template <typename T>
void enqueue (Queue<T> &a, T dt)
{
    Node<T> *temp=NULL;
    temp=new Node<T>;
    temp->content=dt;
    temp->link=NULL;
    is_empty(a)?a.head=temp: a.tail->link=temp;
    a.tail=temp;
    temp=NULL;
}

template <typename T>
bool dequeue (Queue<T> &a)
{
    if (is_empty(a))
        return false;
    Node<T> *temp;
    temp=a.head;
    a.head=temp->link;
    temp->content.finish=0;
    temp->content.time=0;
    temp->link=NULL;
    delete temp;
    temp=NULL;
    if(a.head==NULL){
        a.tail=NULL;
    }
    return true;
}

template <typename T>
bool on_head(Queue<T> a, T &dt)
{
    if (a.head)
    {
        dt=a.head->content;
        return true;
    }
    return false;
}

template <typename T>
bool on_tail( Queue<T> a, T &dt)
{
    if (a.tail)
    {
        dt=a.tail->content;
        return true;
    }
    return false;
}
template <typename T>
void clear (Queue<T> &a)
{
    while(!is_empty(a))
    {
        Node<T> *temp;
        temp=a.tail;
        a.tail=temp->link;
        temp->content.finish=0;
        temp->content.time=0;
        temp->link=NULL;
        delete temp;
        temp=NULL;
    }
    if (!a.tail)
        a.head=NULL;
}
