#include "score.hpp"
#include "field.hpp"
#include "define.hpp"
#include "objects.hpp"
#include "DxLib\DxLib.h"

// フィールドの初期化
void init_field(){
    int x,y;

    // フィールドを全て空にする
    for(y = 0;y < FIELD_Y;y++){
        for(x = 0;x < FIELD_X;x++){
            field[y][x] = EMPTY;
        }        
    }
}

/*
    ミノがフィールドを超えていないか確認する
*/
bool is_field_over(t_mino mino){

    if(is_field_over_x(mino)) return true;
    if(is_field_over_y(mino)) return true;

    return false;
}

/*
    y軸(縦)に対してミノが範囲を超えていないか確認する
*/
bool is_field_over_y(t_mino mino){
    int i,j;

    // ミノを全て調べる
    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            if(mino.mino[i][j] == EXIST){ // ミノが存在するところ
                if(mino.y + i < 0 || mino.y + i >= FIELD_Y) return true; // 範囲を超えていないか確認
            }
        }
    }

    return false;
}

/*
    x軸(横)に対してミノが範囲を超えていないか確認する
*/
bool is_field_over_x(t_mino mino){
    int i,j;

    // ミノを全て調べる
    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            if(mino.mino[i][j] == EXIST){ // ミノが存在するところ
                if(mino.x + j < 0 || mino.x + j >= FIELD_X) return true; // 範囲を超えていないか
            }
        }
    }

    return false;
}

/*
    x軸でミノとフィールドのブロックが被っていないか確認する
*/
bool is_side_hit(t_mino mino){
    int i,j;

    // ミノの全てを調査
    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            if(mino.mino[i][j] == EXIST){ // ミノが存在するところ
                if(field[mino.y + i][mino.x + j] == EXIST) return true; // フィールドと被っていたら
            }
        }
    }

    return false;
}

/*
    y軸でミノとフィールドのブロックが被っていないか確認する
*/
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

/*
    ブロックを固定する
*/
void stack_block(t_mino mino){
    int i,j;

    // ミノ全てに対して調査
    for(i = 0;i < MINO_SIZE;i++){
        for(j = 0;j < MINO_SIZE;j++){
            if(mino.mino[i][j] == EXIST){ // ミノが存在していたら
                field[mino.y + i][mino.x + j] = EXIST; // ミノをフィールドに固定
            }       
        }
    }
}

/*
    列がそろっているかの確認を全ての列に対して行う
*/
void row_check(){
    int i,j;
    int count_lines = 0; // そろった列をカウントする用

    for(i = FIELD_Y-1;i >= 0;){
        for(j = 0;j < FIELD_X;j++){
            if (field[i][j] == EMPTY) break; // 1つでも空があったら抜ける
        }
        if(j == FIELD_X){ // 1列全てが埋まっていたら
            row_clear(i); // 列を削除
            pack_block(i); // 列を詰める
            count_lines++; // そろった列のカウントを進める
        }else{
            i--;
        }
    }

    if(count_lines != 0){
        add_score(count_lines);
    }
}

/*
    空になった列を詰める
*/
void pack_block(int row){
    int i,j;

    // 現在の列よりも上の列を1つ落とす
    for(i = row-1;i >= 0;i--){
        for(j = 0;j < FIELD_X;j++){
            field[i+1][j] = field[i][j];
        }
    }
}

/*
    そろった列を消す
*/
void row_clear(int row){
    int i;

    // 指定された列を空にする
    for(i = 0;i < FIELD_X;i++){
        field[row][i] = EMPTY;
    }
}

/*
    フィールド表示用
*/
void disp_field(){
    int x,y;
    unsigned int Color = GetColor(255,255,255); // フィールドの色

    for(y = 0;y < FIELD_Y;y++){
        for(x = 0;x < FIELD_X;x++){
            if(field[y][x] == EMPTY){ // フィールドが空だったら塗りつぶさない
                // 指定座標にブロックを描画
                DrawBox(x*BLOCK_SIZE+OFFSET_X,y*BLOCK_SIZE+OFFSET_Y,
                (x+1)*BLOCK_SIZE+OFFSET_X,(y+1)*BLOCK_SIZE+OFFSET_Y,Color,false);
            }else{ // フィールドが空でなかったら塗りつぶす
                // 指定座標にブロックを描画
                DrawBox(x*BLOCK_SIZE+OFFSET_X,y*BLOCK_SIZE+OFFSET_Y,
                (x+1)*BLOCK_SIZE+OFFSET_X,(y+1)*BLOCK_SIZE+OFFSET_Y,Color,true);
            }         
        }
    }
}