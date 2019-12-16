#include "objects.hpp"
#include "score.hpp"
#include "mino.hpp"
#include "field.hpp"
#include "DxLib/DxLib.h"

void disp(t_mino mino){
    disp_field();
    disp_t_mino(&mino);
    disp_score();
}

void disp_game_over(){
    TCHAR gameover_str[] = _T("GAME OVER");
    int Green = GetColor( 0, 255, 0 );
    
    DrawString( SCREEN_X/2-40, SCREEN_Y/2, gameover_str, Green);
}
