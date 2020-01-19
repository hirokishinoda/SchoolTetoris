#include "score.hpp"
#include "objects.hpp"
#include "Dxlib/DxLib.h"

// スコアの初期化
void init_score(){
    score = 0;
}

// スコアの加算
void add_score(int lines){
    score += ADD_SCORE * (1 + (lines-1) * SCORE_BIAS);
}

// スコアの表示
void disp_score(){
    int color = GetColor(100,255,255);
    DrawFormatString(0,0,color,_T("SCORE : %d"),score);
}
