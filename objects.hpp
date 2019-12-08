#ifndef   OBJECTS_HPP
#define   OBJECTS_HPP

#include "define.hpp"

typedef struct{
    int mino[MINO_SIZE][MINO_SIZE];
    int x,y;
} t_mino;

extern int field[FIELD_X][FIELD_Y];

extern int score;

#endif