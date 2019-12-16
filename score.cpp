#include "score.hpp"
#include "objects.hpp"
#include "Dxlib/DxLib.h"

void init_score(){
    score = 0;
}

void add_score(int lines){
    score += ADD_SCORE * (1 + SCORE_BIAS*lines);
}

void disp_score(){
    int color = GetColor(100,255,255);
    DrawFormatString(0,0,color,_T("SCORE : %d"),score);
}
