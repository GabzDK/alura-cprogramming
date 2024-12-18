#include <stdlib.h>
#include <stdio.h>
#include "map.h"
#include <string.h>

void copymap(MAP* destiny, MAP* origin){
    destiny->lines = origin->lines;
    destiny->columns = origin->columns;
    mapalloc(destiny);
    for(int i = 0; i < destiny->lines;i++){
        strcpy(destiny->map[i], origin->map[i]);
    }
}
int canwalk(MAP* m, char character,int x ,int y){
    return 
        isvalid(m, x, y) &&
        !iswall(m,x,y) &&
        !ishero(m,character,x,y);
}

int isvalid(MAP* m, int x, int y){
    if(x >= m->lines)
        return 0;
    if(y >= m->columns)
        return 0 ;
    return 1;
}

int isempty(MAP* m, int x, int y){
   return m->map[x][y] == EMPTY;
}

void setposition(MAP* m, int xorigin, int yorigin,
                 int xdestination, int ydestination){
    char character = m->map[xorigin][yorigin];
    m->map[xdestination][ydestination] = character;
    m->map[xorigin][yorigin] = EMPTY;
    
}

int findmap(MAP* m,POSITION* p, char c){
    for(int i = 0; i < m->lines; i++) {
        for(int j = 0; j < m->columns; j++){
            if(m->map[i][j] == c){
                p->x = i;
                p->y = j;
                return 1;
            }
        }
    }
    return 0;
};
int iswall(MAP* m, int x, int y){
    return m->map[x][y] == VERTICAL_WALL ||
        m->map[x][y] == HORIZONTAL_WALL; 
}

int ishero(MAP* m, char character, int x, int y){
    return m->map[x][y] == character;
}

void freemap(MAP* m)
{
    for(int i = 0; i < m->lines; i++){
        free(m->map[i]);
    }
    free(m->map);
}

void mapalloc(MAP* m)
{
    m->map = malloc(sizeof(char*) * m->lines);

    for(int i = 0; i < m->lines; i++) {
        m->map[i] = malloc(sizeof(char) * (m->columns + 1));
    }
}

void readmap(MAP* m)
{
    FILE* f;

    f = fopen("map.txt", "r");
    if(f == 0){
        printf("Failed to open file");
        exit(1);
    }

    fscanf(f,"%d %d", &m->lines, &m->columns);

    mapalloc(m);

    for(int i = 0; i < m->lines; i++) {
        fscanf(f, "%s", m->map[i]);
    }
    fclose(f);
}
