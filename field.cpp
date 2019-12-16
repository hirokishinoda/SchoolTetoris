#include "score.hpp"
#include "field.hpp"
#include "define.hpp"
#include "objects.hpp"
#include "DxLib\DxLib.h"

void init_field(){
    int x,y;

    for(y = 0;y < FIELD_Y;y++){
        for(x = 0;x < FIELD_X;x++){
            field[y][x] = EMPTY;
        }        
    }
}

bool is_field_over(t_mino mino){

    if(is_field_over_x(mino)) return true;
    if(is_field_over_y(mino)) return true;

    return false;
}

bool is_field_over_y(t_mino mino){
    int i,j;

    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            if(mino.mino[i][j] == EXIST){
                if(mino.y + i < 0 || mino.y + i >= FIELD_Y) return true;
            }
        }
    }

    return false;
}

bool is_field_over_x(t_mino mino){
    int i,j;

    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            if(mino.mino[i][j] == EXIST){
                if(mino.x + j < 0 || mino.x + j >= FIELD_X) return true;
            }
        }
    }

    return false;
}

bool is_side_hit(t_mino mino){
    int i,j;

    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            if(mino.mino[i][j] == EXIST){
                if(field[mino.y + i][mino.x + j] == EXIST) return true;
            }
        }
    }

    return false;
}

bool is_down_hit(t_mino mino){
    int i,j;

    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            if(mino.mino[i][j] == EXIST){
                if(field[mino.y + i][mino.x + j] == EXIST) return true;
            }
        }
    }
    return false;
}

void stack_block(t_mino mino){
    int i,j;

    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            if(mino.mino[i][j] == EXIST){
                field[mino.y + i][mino.x + j] = EXIST;
            }       
        }
    }
}

void row_check(){
    int i,j;
    int count_lines = 0;

    for(i = FIELD_Y-1;i >= 0;){
        for(j = 0;j < FIELD_X;j++){
            if (field[i][j] == EMPTY) break;
        }
        if(j == FIELD_X){
            row_clear(i);
            pack_block(i);
            count_lines++;
        }else{
            i--;
        }
    }

    if(count_lines != 0){
        add_score(count_lines);
    }
}

void pack_block(int row){
    int i,j;

    for(i = row-1;i >= 0;i--){
        for(j = 0;j < FIELD_X;j++){
            field[i+1][j] = field[i][j];
        }
    }
}

void row_clear(int row){
    int i;

    for(i = 0;i < FIELD_X;i++){
        field[row][i] = EMPTY;
    }
}

void disp_field(){
    int x,y;
    unsigned int Color = GetColor(255,255,255);

    for(y = 0;y < FIELD_Y;y++){
        for(x = 0;x < FIELD_X;x++){
            if(field[y][x] == EMPTY){
                DrawBox(x*BLOCK_SIZE+OFFSET_X,y*BLOCK_SIZE+OFFSET_Y,(x+1)*BLOCK_SIZE+OFFSET_X,(y+1)*BLOCK_SIZE+OFFSET_Y,Color,false);
            }else{
                DrawBox(x*BLOCK_SIZE+OFFSET_X,y*BLOCK_SIZE+OFFSET_Y,(x+1)*BLOCK_SIZE+OFFSET_X,(y+1)*BLOCK_SIZE+OFFSET_Y,Color,true);
            }         
        }
    }

}