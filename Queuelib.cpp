#include "Queuelib.h"
#define NULL 0

using namespace std;

void enqueue (Queue &a, Data dt)
{
    Node *temp=NULL;
    temp=new Node;
    temp->content=dt;
    temp->link=NULL;
    if(!is_empty(a)){
        a.tail->link=temp;
        a.tail=temp;
    }
    else{
        a.tail=temp;
        a.head=a.tail;
    }
    temp=NULL;
}

bool dequeue (Queue &a)
{
    if (is_empty(a))
        return false;
    Node *temp;
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

bool on_head(Queue a, Data &dt)
{
    if (a.head)
    {
        dt=a.head->content;
        return true;
    }
    return false;
}

bool on_tail( Queue a, Data &dt)
{
    if (a.tail)
    {
        dt=a.tail->content;
        return true;
    }
    return false;
}

bool is_empty (Queue a)
{
    return (a.tail==NULL)&&(a.head==NULL);
}

void clear (Queue &a)
{
    while(!is_empty(a))
    {
        Node *temp;
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
