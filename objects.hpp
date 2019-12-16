#ifndef   OBJECTS_HPP
#define   OBJECTS_HPP

#include "define.hpp"

typedef struct{
    int mino[MINO_SIZE][MINO_SIZE];
    int x,y;
} t_mino;

extern int field[FIELD_Y][FIELD_X];

extern int score;

extern bool gameover;

extern int t_mino_buff[T_MINO_TYPE][MINO_SIZE][MINO_SIZE];

#endif