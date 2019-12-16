#ifndef   FIELD_HPP
#define   FILED_HPP

#include "objects.hpp"

void init_field();

bool is_field_over(t_mino mino);

bool is_field_over_y(t_mino mino);

bool is_field_over_x(t_mino mino);

bool is_side_hit(t_mino mino);

bool is_down_hit(t_mino mino);

void row_check();

void pack_block(int row);

void row_clear(int row);

void stack_block(t_mino mino);

void disp_field();

#endif   // DISPLAY_HPP