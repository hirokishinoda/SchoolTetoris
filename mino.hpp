#ifndef   MINO_HPP
#define   MINO_HPP

#include "objects.hpp"

// 指定方向にミノを移動
void move_block(t_mino *mino,char key[256]);

// ミノを回転する
void rotate_block(t_mino *mino);

// ミノを新しく作成する
void make_t_mino(t_mino *mino);

// ミノを右方向に移動する
void move_right(t_mino *mino);

// ミノを左方向に移動する
void move_left(t_mino *mino);

// ミノを下に移動する
void move_down(t_mino *mino);

// ミノを描画する
void disp_t_mino(t_mino *mino);

#endif    // CONTROL_MINO_HPP