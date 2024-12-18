#ifndef _PAC_H_

#define _PAC_H_
#define UP 'w'
#define LEFT 'a'
#define DOWN 's'
#define RIGHT 'd'
#define BOMB 'b'

int over();
void move(char direction);
int isdirection(char direction);
void ghosts();
int ghostmovement(int xcurrent, int ycurrent,
                  int* xdestiny, int* ydestiny);
void pill();
void powerup(int x, int y, int sumx, int sumy, int ammount);

#endif
