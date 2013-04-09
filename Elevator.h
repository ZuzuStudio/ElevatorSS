#ifndef ELEVATOR_H
#define ELEVATOR_H

const int unit=50000;
const char empty='e', full='f';

void draw(Queue *a, char *b, short c);
void move(Queue *a, char *b, short start, short finish, short &main_time, const char ch, short stages, short &av, short &avn);
void inctime(Queue *a, short &main_time, short stages);

#endif

