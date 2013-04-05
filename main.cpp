#include <iostream>
#include <fstream>
#include "Queuelib.h"

using namespace std;

const int unit=500000;

//void move (char *a, short start, short finish, short main_time)
int main()
{

    short stages, people, next;
    fstream fin;
    fin.open("Script");
    fin>>stages;
    fin>>people;
    next=2*stages-3;
    Queue *Queue_fl;
    Queue_fl = new Queue[stages];
    for (short i=0; i<stages; ++i)
    {
        Queue_fl[i].head=NULL;
        Queue_fl[i].tail=NULL;
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
        enqueue(Queue_fl[start], man);
    }
    short main_time=0, current_stage=0, order=1;
    while(people)
    {
        short temps=current_stage, tempo=order, check=0;
        while (true)
        {
            check++;
            if (!is_empty(Queue_fl[temps]))
                if ((Queue_fl[temps].head->content.time<=main_time)
                        &&((Queue_fl[temps].head->content.finish==current_stage)||((Queue_fl[temps].head->content.finish-temps)*tempo>=0)))
                {
                    current_stage=temps;
                    order=tempo;
                    break;
                }
            temps+=tempo;
            if(temps==stages||temps==-1)
            {
                tempo-=2*tempo;
                temps+=tempo;
            }
            if(check==next)//(temps==current_stage-order&&tempo==order)
                main_time++;
        }
        Data x;
        on_head(Queue_fl[current_stage], x);
        dequeue(Queue_fl[current_stage]);
        cout<<main_time<<" "<<current_stage+1<<" "<<x.finish+1<<endl;
        current_stage=x.finish;
        people--;
    }
    delete [] Queue_fl;
    return 0;
}
