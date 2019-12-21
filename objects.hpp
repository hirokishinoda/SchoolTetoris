#ifndef   OBJECTS_HPP
#define   OBJECTS_HPP

#include "define.hpp"

// テトリミノの構造体
typedef struct{
    int mino[MINO_SIZE][MINO_SIZE]; // ミノ本体
    int x,y; // テトリミノの座標
} t_mino;

// フィールド
extern int field[FIELD_Y][FIELD_X];
// スコア
extern int score;
// ゲームオーバーフラグ
extern bool gameover;
// テトリミノの種類
extern int t_mino_buff[T_MINO_TYPE][MINO_SIZE][MINO_SIZE];

#endif