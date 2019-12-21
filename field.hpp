#ifndef   FIELD_HPP
#define   FILED_HPP

#include "objects.hpp"

// フィールド初期化
void init_field();

// ミノがフィールド内か確認
bool is_field_over(t_mino mino);

// ミノがy軸でフィールド内か確認
bool is_field_over_y(t_mino mino);

// ミノがx軸でフィールド内か確認
bool is_field_over_x(t_mino mino);

// x軸でミノがフィールドのブロックと被ってないか確認
bool is_side_hit(t_mino mino);

// y軸でミノがフィールドのブロックと被ってないか確認
bool is_down_hit(t_mino mino);

// 列がそろっているのかの確認
void row_check();

// 列を1段下に詰める
void pack_block(int row);

// 指定された列を消去する
void row_clear(int row);

// ブロックを固定化する
void stack_block(t_mino mino);

// フィールドを表示する
void disp_field();

#endif   // DISPLAY_HPP