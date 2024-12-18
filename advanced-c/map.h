#ifndef _MAP_H_
#define _MAP_H_
#define HERO '@'
#define GHOST 'F'
#define PILL 'P'
#define EMPTY '.'
#define VERTICAL_WALL '|'
#define HORIZONTAL_WALL '-'

struct map{
    char** map;
    int lines;
    int columns;
};

typedef struct map MAP;

struct position{
    int x;
    int y;
};

typedef struct position POSITION;

void freemap(MAP* m);
void mapalloc(MAP* m);
void readmap(MAP* m);
int findmap(MAP* m,POSITION* p, char c);
int isvalid(MAP*m, int x, int y);
int isempty(MAP* m, int x, int y);
void setposition(MAP* m, int xorigin, int yorigin,
                 int xdestination, int ydestination);
void copymap(MAP* destiny, MAP* origin);
int canwalk(MAP* m, char character, int x ,int y);
int iswall(MAP* m, int x, int y);
int ishero(MAP* m, char character, int x, int y);

#endif
