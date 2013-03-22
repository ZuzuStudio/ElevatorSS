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
    for (short i=0; i<people||(!fin.eof()); ++i)
    {
        Data man;
        short start;
        fin>>start;
        fin>>man.finish;
        fin>>man.time;
        enqueue(Queue_fl[start-1].head, Queue_fl[start-1].tail, man);
    }
    fin.close();
    delete [] Queue_fl;
    return 0;
}
