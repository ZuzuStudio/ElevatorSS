#include <iostream>
#include <fstream>
#include <cstdlib>
#include <unistd.h>
#include "Queuelib.h"

using namespace std;

const int unit=1000000;
const char empty='e', full='f';

void draw(Queue *a, char *b, short c)
{
    system("clear");
    for (short i=c-1; i>=0; --i)
    {
        cout.width(4);
        if(a[i].hmp)
        {
            cout.width(4-(a[i].hmp/10+1));
            cout<<a[i].hmp;
        }
        cout<<' '<<'|'<<b[i]<<'|'<<endl;
    }
}

void move (Queue *a, char *b, short start, short finish, short &main_time, const char ch, short stages)
{
    short order;
    finish>=start?order=1:order=-1;
    if (start==finish)
    {
        system("clear");
        for (short i=stages-1; i>=0; --i)
        {
            cout.width(4);
            if(a[i].hmp)
            {
                cout.width(4-(a[i].hmp/10+1));
                cout<<a[i].hmp;
            }
            cout<<' '<<'|'<<b[i]<<'|';
            if(ch==full)
            {
                if (i==finish)
                {
                    cout<<'>';
                    b[i]=empty;
                }
            }
            else
            {
                if (i==finish)
                {
                    b[i]=full;
                    a[i].hmp--;

                }
            }
            cout<<endl;
        }
    }


    else
    {
        while(start!=finish)
        {
            usleep(unit);
            main_time++;
            b[start+order]=ch;
            b[start]=' ';
            system("clear");
            for (short i=stages-1; i>=0; --i)
            {
                cout.width(4);
                if(a[i].hmp)
                {
                    cout.width(4-(a[i].hmp/10+1));
                    cout<<a[i].hmp;
                }
                cout<<' '<<'|'<<b[i]<<'|';
                if((start+order==finish)&&(ch==full))
                    if (i==finish)
                    {
                        cout<<'>';
                        b[i]=empty;
                    }
                if((start+order==finish)&&(ch==empty))
                    if (i==finish)
                    {
                        b[i]=full;
                        a[i].hmp--;
                    }
                cout<<endl;
            }
            start+=order;
        }
    }
    usleep(unit);
    main_time++;
    draw(a, b, stages);
}

int main()
{

    short stages, people, next;
    ifstream fin;
    fin.open("Script");
    fin>>stages;
    fin>>people;
    next=2*stages-3;
    Queue *Queue_fl=new Queue[stages];
    for (short i=0; i<stages; ++i)
    {
        Queue_fl[i].head=NULL;
        Queue_fl[i].tail=NULL;
        Queue_fl[i].hmp=0;
    }
    for (short i=0; i<people&&(!fin.eof()); ++i)
    {
        Data man;
        short start;
        fin>>start;
        fin>>man.finish;
        start--;
        man.finish--;
        fin>>man.time;
        Queue_fl[start].hmp++;
        enqueue(Queue_fl[start], man);
    }
    short main_time=0, current_stage=0, order=1;
    char *elevator=new char[stages];
    for (short i=1; i<stages; ++i)
        elevator[i]=' ';
    elevator[0]=empty;
    draw(Queue_fl, elevator, stages);
    while(people)
    {
        short temps=current_stage, tempo=order, check=0;
        while (true)
        {
            check++;
            if (!is_empty(Queue_fl[temps]))
                if ((Queue_fl[temps].head->content.time<=main_time)
                        &&((Queue_fl[temps].head->content.finish==current_stage)
                           ||((Queue_fl[temps].head->content.finish-temps)*tempo>=0)))
                {
                    move(Queue_fl, elevator, current_stage, temps, main_time, empty, stages);
                    current_stage=temps;
                    move(Queue_fl, elevator, current_stage, Queue_fl[temps].head->content.finish, main_time, full, stages);
                    order=tempo;
                    break;
                }
            temps+=tempo;
            if(temps==stages||temps==-1)
            {
                tempo-=2*tempo;
                temps+=tempo;
            }
            if(check==next)
            {
                usleep(unit);
                main_time++;
                draw(Queue_fl, elevator, stages);
            }
        }
        Data x;
        on_head(Queue_fl[current_stage], x);
        dequeue(Queue_fl[current_stage]);
        current_stage=x.finish;
        people--;
    }
    fin.close();
    delete [] elevator;
    delete [] Queue_fl;
    return 0;
}
