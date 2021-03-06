#include <iostream>
#include <fstream>
#include <cstring>
#include "Queuelib.h"
#include "Elevator.h"

using namespace std;

int main()
{

    short stages, people, scr=100, fund=1000, av=0, avn=0;
    char *script=new char[scr];
    for (short i=0; i<scr; ++i)
        script[i]=0;
    cout<<"Сценарий: ";
    cin>>script;
    ifstream fin;
    fin.open(script);
    delete [] script;
    script=NULL;
    fin>>stages;
    fin>>people;
    Queue<Men> *Queue_fl=new Queue<Men>[stages];
    for (short i=0; i<stages; ++i)
    {
        Queue_fl[i].head=NULL;
        Queue_fl[i].tail=NULL;
        Queue_fl[i].hmp=0;
        Queue_fl[i].maxhmp=0;
        Queue_fl[i].h=new bool[fund];
        for (short j=0; j<fund;++j)
            Queue_fl[i].h[j]=false;
    }
    for (short i=0; i<people&&(!fin.eof()); ++i)
    {
        Men man;
        short start;
        fin>>start;
        fin>>man.finish;
        start--;
        man.finish--;
        fin>>man.time;
        Queue_fl[start].h[man.time]=true;
        enqueue(Queue_fl[start], man);
    }
    short main_time=0, current_stage=0, order=1;
    char *elevator=new char[stages];
    for (short i=1; i<stages; ++i)
        elevator[i]=' ';
    elevator[0]=empty;
    for (short i=0; i<stages; ++i){
        Queue_fl[i].hmp+=Queue_fl[i].h[main_time];
        if(Queue_fl[i].hmp>Queue_fl[i].maxhmp)
            Queue_fl[i].maxhmp=Queue_fl[i].hmp;
    }
    draw(Queue_fl, elevator, stages);
    float pause=0;
    while(people)
    {
        short temps=current_stage, tempo=order, check=0;
        while (true)
        {
            check++;
            if (!is_empty(Queue_fl[temps]))
                if ((Queue_fl[temps].head->content.time<=main_time)
                        &&((Queue_fl[temps].head->content.finish-temps)*tempo>=0))
                {
                    move(Queue_fl, elevator, current_stage, temps,
                         main_time, empty, stages, av, avn);
                    current_stage=temps;
                    move(Queue_fl, elevator, current_stage, Queue_fl[temps].head->content.finish,
                         main_time, full, stages, av, avn);
                    order=tempo;
                    break;
                }
            temps+=tempo;
            if(temps==stages||temps==-1)
            {
                tempo-=2*tempo;
                temps+=tempo;
            }
            if(check==2*stages)
            {
                pause++;
                inctime(Queue_fl, main_time, stages);
                draw(Queue_fl, elevator, stages);
                check=0;
            }
        }
        Men temp;
        on_head(Queue_fl[current_stage], temp);
        dequeue(Queue_fl[current_stage]);
        current_stage=temp.finish;
        people--;
    }
    fin.close();
    short max=0, averp=0;
    for (short i=0;i<stages; ++i){
        if(max<Queue_fl[i].maxhmp)
            max=Queue_fl[i].maxhmp;
        averp+=Queue_fl[i].maxhmp;
    }
    cout<<"\nСтатистика (1 единица времени = "<<(double)unit/1000000<<" секунды):\n";
    cout<<"Общее время: "<<main_time<<" единиц времени\n";
    cout<<"Максимальная длина очереди: "<<max<<" человек\n";
    cout<<"Среднее количество пассажиров в очереди: "<<(float)averp/stages<<" человек\n";
    cout<<"Время простоя лифта: "<<pause<<" единиц времени\n";
    cout<<"Среднее число этажей одной поездки лифта: ";
    av&&avn?cout<<av/avn:cout<<0;
    cout<<" этажей\n";
    delete [] elevator;
    elevator=NULL;
    delete [] Queue_fl;
    for (short i=0; i<fund;++i)
        Queue_fl[i].h=NULL;
    Queue_fl=NULL;
    return 0;
}
