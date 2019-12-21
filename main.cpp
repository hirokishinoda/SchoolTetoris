#include <stdlib.h>
#include <time.h>
#include "DxLib\DxLib.h"
#include "field.hpp"
#include "mino.hpp"
#include "objects.hpp"
#include "define.hpp"
#include "score.hpp"
#include "game_screen.hpp"

// 初期化処理
void initialize(t_mino *mino){
    // seed値の設定
    srand((unsigned)time(NULL));

    // フィールドの初期化
    init_field();
    // ミノを作成
    make_t_mino(mino);
    // スコアの初期化
    init_score();
}

// プログラムは WinMain から
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    t_mino mino; // 操作対象のテトリミノ
    clock_t key_time = clock(); // キー操作の時間計測用
    clock_t drop_time = clock(); // 自動落下の時間計測用
    double time = 0; // 現在の時間計算用
    char key[256]; // キー取得用

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
        if(time >= KEY_CHECK_TIME){ // 一定の時間間隔でキーをチェック
            key_time = clock();
            move_block(&mino, key); // キーの方向にブロックを移動
        }
        // 自動落下判定
        time = (double)(clock() - drop_time) / CLOCKS_PER_SEC;
        if(time >= DROP_CHECK_TIME){ // 一定の時間間隔で自動落下を行う
            drop_time = clock();
            move_down(&mino); // 1つ下にブロックを移動
        }

        // 表示
        // ゲームオーバーになったらゲームオーバー画面を表示しループを抜ける
        if(!gameover){
            disp(mino); // ミノやフィールドを表示
        }else{
            disp_game_over(); // ゲームオーバー画面を表示
            ScreenFlip(); // 裏画面を表画面に
            exit;
        }
                
        ScreenFlip(); // 裏画面を表画面に描画
    }

    WaitKey(); // キーが押されるまで待機

    DxLib_End() ; // DXライブラリ使用の終了処理
    return 0 ; // ソフトの終了 
}