#include <stdio.h>
#include "map.h"

char walldraw[4][7] = {
    {"......" },
    {"......" },
    {"......" },
    {"......" }
};

char ghostdraw[4][7] = {
    {" .-.  " },
    {"| OO| " },
    {"|   | " },
    {"'^^^' " }
};

char herodraw[4][7] = {
    {" .--. "  },
    {"/ _.-'"  },
    {"\\  '-." },
    {" '--' "  }
};

char pilldraw[4][7] = {
    {"      "},
    {" .-.  "},
    {" '-'  "},
    {"      "}
};

char emptydraw[4][7] = {
    {"      "},
    {"      "},
    {"      "},
    {"      "}
};

void printpart(char draw[4][7], int part){
    printf("%s", draw[part]);
}

void printmap(MAP* m){
    for(int i = 0; i < m->lines; i++) {

        for(int part = 0; part < 4; part++ ){

            for(int j = 0; j < m->columns; j++) {

                switch(m->map[i][j]) {
                    case GHOST:
                        printpart(ghostdraw, part);
                        break;
                    case HERO:
                        printpart(herodraw, part);
                        break;
                    case PILL:
                        printpart(pilldraw, part);
                        break;
                    case VERTICAL_WALL:
                    case HORIZONTAL_WALL:
                        printpart(walldraw, part);
                        break;
                    case EMPTY:
                        printpart(emptydraw, part);
                        break;
                }
            }
            printf("\n");
        }
    }

}
