#include "objects.hpp"
#include "score.hpp"
#include "mino.hpp"
#include "field.hpp"
#include "DxLib/DxLib.h"

// ゲーム画面描画
void disp(t_mino mino){
    // フィールドの描画
    disp_field();
    // ミノの描画
    disp_t_mino(&mino);
    // スコアの描画
    disp_score();
}

// ゲームオーバー画面
void disp_game_over(){
    TCHAR gameover_str[] = _T("GAME OVER"); // ゲームオーバーの文字列
    int Green = GetColor( 0, 255, 0 ); // 文字色
    
    DrawString( SCREEN_X/2-40, SCREEN_Y/2, gameover_str, Green); // ゲームオーバー文字の表示
}
