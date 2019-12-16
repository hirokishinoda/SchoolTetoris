
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "objects.hpp"
#include "field.hpp"
#include "DxLib\DxLib.h"
#include "mino.hpp"
#include "game_screen.hpp"

void move_block(t_mino *mino,char key[256]){
    if(key[KEY_INPUT_LEFT]){
        move_left(mino);
    }
    if(key[KEY_INPUT_RIGHT]){
        move_right(mino);
    }
    if(key[KEY_INPUT_DOWN]){
        move_down(mino);
    }
    if(key[KEY_INPUT_UP]){
        rotate_block(mino);
    }
}

void rotate_block(t_mino *mino){
    t_mino tmp_mino;
    int i,j;

    tmp_mino.x = mino->x;
    tmp_mino.y = mino->y;
    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            tmp_mino.mino[j][MINO_SIZE - i - 1] = mino->mino[i][j];
        }
    }

    if(!is_field_over(tmp_mino) && !is_side_hit(tmp_mino)){
        for(i = 0;i < MINO_SIZE;i++){
            for(j = 0;j < MINO_SIZE;j++){
                mino->mino[i][j] = tmp_mino.mino[i][j];
            }
        }
    }

}

void make_t_mino(t_mino *mino){
    int type = rand() % T_MINO_TYPE;
    int x,y;

    for(y = 0;y < MINO_SIZE;y++){
        for(x = 0;x < MINO_SIZE;x++){
            mino->mino[y][x] = t_mino_buff[type][y][x];
        }
    }

    mino->y = 0;
    mino->x = 3;

    if(is_down_hit(*mino)){
        gameover = true;
    }
}

void move_right(t_mino *mino){
    mino->x++;
    if(is_field_over(*mino) || is_side_hit(*mino)) mino->x--;
}

void move_left(t_mino *mino){
    mino->x--;
    if(is_field_over(*mino) || is_side_hit(*mino)) mino->x++;
}

void move_down(t_mino *mino){
    mino->y++;
    if(is_down_hit(*mino) || is_field_over_y(*mino)){ 
        mino->y--;
        // 次のブロックへ
        stack_block(*mino);
        row_check();
        make_t_mino(mino);
        Sleep(400);
    }
}

void disp_t_mino(t_mino *mino){
    int x,y;
    int plot_x,plot_y;
    unsigned int Color = GetColor(100,255,100);

    for(y = 0; y < MINO_SIZE;y++){
        for(x = 0; x < MINO_SIZE;x++){
            if(mino->mino[y][x] == 1){
                plot_x = x + mino->x;
                plot_y = y + mino->y;
                DrawBox(plot_x*BLOCK_SIZE+OFFSET_X,plot_y*BLOCK_SIZE+OFFSET_Y,(plot_x+1)*BLOCK_SIZE+OFFSET_X,(plot_y+1)*BLOCK_SIZE+OFFSET_Y,Color,true);
            }
        }
    }
}