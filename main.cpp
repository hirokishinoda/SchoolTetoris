#include <stdlib.h>
#include <time.h>
#include "DxLib\DxLib.h"
#include "field.hpp"
#include "mino.hpp"
#include "objects.hpp"
#include "define.hpp"
#include "score.hpp"
#include "game_screen.hpp"

void initialize(t_mino *mino){
    srand((unsigned)time(NULL));

    init_field();
    make_t_mino(mino);
    init_score();
}

// プログラムは WinMain から
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    t_mino mino;
    clock_t key_time = clock();
    clock_t drop_time = clock();
    double time = 0;
    char key[256];

    ChangeWindowMode(TRUE); // 非全画面モードに
    SetGraphMode(SCREEN_X, SCREEN_Y, 32); // 画面サイズ指定
    SetOutApplicationLogValidFlag(FALSE); // Log.txtを生成しないように設定
    if( DxLib_Init() == -1 ){return -1 ;} // エラーが起きたら直ちに終了

    // 初期化
    initialize(&mino);

    // mainループ
    while(ProcessMessage() == 0){
        ClearDrawScreen(); // 裏画面の消去
        SetDrawScreen(DX_SCREEN_BACK); // 描画先を裏画面に

        // キー入力
        GetHitKeyStateAll(key);
        time = (double)(clock() - key_time) / CLOCKS_PER_SEC;
        if(time >= 0.175){
            key_time = clock();
            move_block(&mino, key);
        }
        // 自動落下判定
        time = (double)(clock() - drop_time) / CLOCKS_PER_SEC;
        if(time >= 1.0){
            drop_time = clock();
            move_down(&mino);
        }

        // 表示
        if(!gameover){
            disp(mino);
        }else{
            disp_game_over();
            ScreenFlip();
            exit;
        }
                
        ScreenFlip(); // 裏画面を表画面に描画
    }

    WaitKey();

    DxLib_End() ; // DXライブラリ使用の終了処理
    return 0 ; // ソフトの終了 
}

