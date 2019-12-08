#include "DxLib\DxLib.h"

// プログラムは WinMain から
int WINAPI WinMain( HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow )
{
    ChangeWindowMode(TRUE); // 非全画面モードに
    SetGraphMode(300, 600, 32); // 画面サイズ指定
    SetOutApplicationLogValidFlag(FALSE); // Log.txtを生成しないように設定
    if( DxLib_Init() == -1 ){return -1 ;} // エラーが起きたら直ちに終了

    // mainループ
    while(ProcessMessage() == 0){
        ClearDrawScreen(); // 裏画面の消去
        SetDrawScreen(DX_SCREEN_BACK); // 描画先を裏画面に


        ScreenFlip(); // 裏画面を表画面に描画
    }

    DxLib_End() ; // DXライブラリ使用の終了処理
    return 0 ; // ソフトの終了 
}

