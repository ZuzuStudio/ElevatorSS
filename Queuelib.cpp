#include <iostream>
#include <fstream>
#include <cstdlib>
#include "Queuelib.h"

using namespace std;

void enqueue (Node *&head, Node *&tail, Data dt)
{
    Node *temp=NULL;
    temp=new Node;
    temp->content=dt;
    temp->link=NULL;
    if(!is_empty(head, tail)){
        tail->link=temp;
        tail=temp;
    }
    else{
        tail=temp;
        head=tail;
    }
    temp=NULL;
}

bool dequeue (Node *&head, Node *&tail)
{
    if (is_empty(head, tail))
        return false;
    Node *temp=NULL;
    temp=head ;
    head=head->link;
    temp->content.finish=0;
    temp->content.time=0;
    temp->link=NULL;
    delete temp;
    temp=NULL;
    return true;
}

bool on_head(Node *head, Data &dt)
{
    if (head)
    {
        dt=head->content;
        return true;
    }
    return false;
}

bool on_tail( Node *tail, Data &dt)
{
    if (tail)
    {
        dt=tail->content;
        return true;
    }
    return false;
}

bool is_empty (Node *head, Node *tail)
{
    if(head&&tail)
        return false;
    return true;
}

void clear (Node *&head, Node *&tail)
{
    while(!is_empty(head, tail))
    {
        Node *temp;
        temp=tail;
        tail=temp->link;
        temp->content.finish=0;
        temp->content.time=0;
        temp->link=NULL;
        delete temp;
        temp=NULL;
    }
}

