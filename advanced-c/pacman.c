#include <stdio.h>
#include <stdlib.h>
#include "pacman.h"
#include "map.h"
#include "ui.h"
#include <time.h>

MAP m;
POSITION hero;
int haspill = 0;

int ghostmovement(int xcurrent, int ycurrent,
                  int* xdestiny, int* ydestiny){

    int options[4][2] = {
        {xcurrent, ycurrent + 1},
        {xcurrent + 1, ycurrent},
        {xcurrent, ycurrent -1 },
        {xcurrent -1 , ycurrent}

    };
    srand(time(0));
    for(int i = 0; i < 10; i++){
        int position = rand() % 4;
        
        if(canwalk(&m, GHOST,options[position][0], options[position][1])){
            *xdestiny = options[position][0];
            *ydestiny = options[position][1];

            return 1;
        }
    }
    return 0;
}

void ghosts(){
    MAP copy;
    copymap(&copy, &m);

    for(int i = 0; i < m.lines; i++){
    for(int j = 0; j < m.columns; j++){
            if(copy.map[i][j] == GHOST){

                int xdestiny;
                int ydestiny;
                
                int found = ghostmovement(i, j , &xdestiny, &ydestiny);
                if (found){
                    setposition(&m, i, j, xdestiny , ydestiny);
                }
            }
        }
    }
    freemap(&copy);
}

int isdirection(char direction){
    return direction == LEFT ||
        direction == DOWN ||
        direction == RIGHT ||
        direction == UP;

}

void move(char direction)
{
    if(!isdirection(direction))
        return;

    int nextx = hero.x;
    int nexty = hero.y;

    switch (direction){
        case LEFT:
            nexty--;
            break;
        case UP:
            nextx--;
            break;
        case DOWN:
            nextx++;
            break;
        case RIGHT:
            nexty++;
            break;
    }
    if(!canwalk(&m,HERO, nextx, nexty))
        return;

    if(ishero(&m, PILL, nextx, nexty)){
        haspill = 1;
    }
    setposition(&m, hero.x, hero.y, nextx, nexty);
    hero.x = nextx;
    hero.y = nexty;
}

int over(){
    POSITION pos;
    int heroposition = findmap(&m, &pos, HERO);
    return !heroposition;
}

void pill(){
    powerup(hero.x, hero.y, 0, 1, 3);
    powerup(hero.x, hero.y, 0, -1, 3);
    powerup(hero.x, hero.y, 1, 0, 3);
    powerup(hero.x, hero.y, -1, 0, 3);
}

void powerup(int x, int y, int sumx, int sumy, int ammount){

    if(ammount == 0) return;

    int newx = x + sumx;
    int newy = y + sumy;

    if(!isvalid(&m, newx, newy)) return;
    if(iswall(&m, newx, newy)) return;

    m.map[newx][newy] = EMPTY;
        
    powerup(newx, newy, sumx, sumy, ammount -1);
}

int main()
{
    readmap(&m);
    findmap(&m,&hero, HERO);

    do {

        printf("Has pill: %s\n", (haspill ? "YES" : "NO"));
        printmap(&m);
        char input;
        scanf(" %c", &input);
        move(input);
        if(input == BOMB) pill();
        ghosts();

    } while(!over());

    freemap(&m);
}
