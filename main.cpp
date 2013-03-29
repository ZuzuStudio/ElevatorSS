#include <iostream>
#include <fstream>
#include "Queuelib.h"

using namespace std;

int main()
{
    short stages, people;
    fstream fin;
    fin.open("Script");
    fin>>stages;
    fin>>people;
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
        short temps=current_stage, tempo=order;
        while (true){
            if (!is_empty(Queue_fl[temps]))
                if ((Queue_fl[temps].head->content.time<=main_time)&&((Queue_fl[temps].head->content.finish-current_stage)*tempo>=0)){
                    current_stage=temps;
                    order=tempo;
                    break;
                }
            temps+=tempo;
            if(temps==stages){
                tempo=-1;
                temps+=tempo;
            }
            if(temps==-1){
                tempo=1;
                temps+=tempo;
            }
            if(temps==current_stage-order&&tempo==order)
                main_time++;
        }
        Data x;
        x.time=0;
        x.finish=0;
        on_head(Queue_fl[current_stage], x);
        dequeue(Queue_fl[current_stage]);
        cout<<current_stage+1<<" "<<x.finish+1<<endl;
        current_stage=x.finish;
        people--;
    }
    delete [] Queue_fl;
    return 0;
}
