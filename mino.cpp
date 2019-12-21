#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "objects.hpp"
#include "field.hpp"
#include "DxLib\DxLib.h"
#include "mino.hpp"
#include "game_screen.hpp"

/* 
    ブロックを指定の方向に動かす
*/
void move_block(t_mino *mino,char key[256]){
    if(key[KEY_INPUT_LEFT]){ // 左方向に移動
        move_left(mino);
    }
    if(key[KEY_INPUT_RIGHT]){ // 右方向に移動
        move_right(mino);
    }
    if(key[KEY_INPUT_DOWN]){ // 下方向に移動
        move_down(mino);
    }
    if(key[KEY_INPUT_UP]){ // ブロックの回転
        rotate_block(mino);
    }
}

/*
    ブロックの回転
*/
void rotate_block(t_mino *mino){
    t_mino tmp_mino;
    int i,j;

    // 仮のミノを作成
    tmp_mino.x = mino->x;
    tmp_mino.y = mino->y;
    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            tmp_mino.mino[j][MINO_SIZE - i - 1] = mino->mino[i][j];
        }
    }

    //　他のブロックに当たらず，範囲外でないなら90度回転
    if(!is_field_over(tmp_mino) && !is_side_hit(tmp_mino)){
        for(i = 0;i < MINO_SIZE;i++){
            for(j = 0;j < MINO_SIZE;j++){
                mino->mino[i][j] = tmp_mino.mino[i][j];
            }
        }
    }

}

/*
    ミノを作成
*/
void make_t_mino(t_mino *mino){
    int type = rand() % T_MINO_TYPE; // ランダムにミノを選択
    int x,y;

    // あらかじめ決めた形から読み込み
    for(y = 0;y < MINO_SIZE;y++){
        for(x = 0;x < MINO_SIZE;x++){
            mino->mino[y][x] = t_mino_buff[type][y][x];
        }
    }
    mino->y = 0; // y座標の設定
    mino->x = 3; // x座標の設定

    // 作った直後にブロックがあったらゲームオーバー
    if(is_down_hit(*mino)){
        gameover = true;
    }
}

/*
    ミノを右に移動させる
*/
void move_right(t_mino *mino){
    mino->x++;
    if(is_field_over(*mino) || is_side_hit(*mino)) mino->x--;
}

/*
    ミノを左に移動させる
*/
void move_left(t_mino *mino){
    mino->x--;
    if(is_field_over(*mino) || is_side_hit(*mino)) mino->x++;
}

/*
    ミノを1つ下に移動させる
*/
void move_down(t_mino *mino){
    mino->y++;
    if(is_down_hit(*mino) || is_field_over_y(*mino)){ 
        mino->y--;
        // 次のブロックへ
        stack_block(*mino); // ミノを固定化
        row_check();        // そろった列の確認
        make_t_mino(mino);  // 新しくミノを作る
        Sleep(400);
    }
}

/*
    ミノを表示する
*/
void disp_t_mino(t_mino *mino){
    int x,y;
    int plot_x,plot_y; // ミノの座標
    unsigned int Color = GetColor(100,255,100); // ミノの色

    // ミノを表示する
    for(y = 0; y < MINO_SIZE;y++){
        for(x = 0; x < MINO_SIZE;x++){
            if(mino->mino[y][x] == EXIST){ // ミノが存在していたら描画
                plot_x = x + mino->x;
                plot_y = y + mino->y;
                DrawBox(plot_x*BLOCK_SIZE+OFFSET_X,plot_y*BLOCK_SIZE+OFFSET_Y,
                (plot_x+1)*BLOCK_SIZE+OFFSET_X,(plot_y+1)*BLOCK_SIZE+OFFSET_Y,Color,true);
            }
        }
    }
}