#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include "Queuelib.h"
#include "Elevator.h"

using namespace std;

void draw(Queue *a, char *b, short c)
{
    system("clear");
    for (short i=c-1; i>=0; --i)
    {
        cout.width(5);
        if(a[i].hmp)
        {
            cout.width(5-(a[i].hmp/10+1));
            cout<<a[i].hmp;
        }
        cout<<' '<<'|'<<b[i]<<'|'<<endl;
    }
}

void move(Queue *a, char *b, short start, short finish, short &main_time, const char ch, short stages, short &av, short &avn)
{
    short order;
    if (start==finish)
    {
        system("clear");
        for (short i=stages-1; i>=0; --i)
        {
            cout.width(5);
            if(a[i].hmp)
            {
                cout.width(5-(a[i].hmp/10+1));
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
                    cout<<'\a';

                }
            }
            cout<<endl;
        }
    }


    else
    {
        finish>start?order=1:order=-1;
        while(start!=finish)
        {
            av++;
            inctime(a, main_time, stages);
            b[start+order]=ch;
            b[start]=' ';
            system("clear");
            for (short i=stages-1; i>=0; --i)
            {
                cout.width(5);
                if(a[i].hmp)
                {
                    cout.width(5-(a[i].hmp/10+1));
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
        avn++;
    }
    inctime(a, main_time, stages);
    draw(a, b, stages);
}

void inctime(Queue *a, short &main_time, short stages)
{
    usleep(unit);
    main_time++;
}
