#ifndef   MINO_HPP
#define   MINO_HPP

#include "objects.hpp"

void move_block(t_mino mino, int direction);

void rotate_block(t_mino mino);

void make_t_mino(t_mino mino);

void move_right(t_mino mino);

void move_left(t_mino mino);

void move_down(t_mino mino);

void disp_t_mino();

#endif    // CONTROL_MINO_HPP