#include "DxPlus/DxPlus.h"
#include "WinMain.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "Clear.h"
#include "Battle.h"
#include "Mouse.h"
#include "AllManager.h"


int currentScene = SceneNone;
int nextScene = SceneTitle;
 
int fontID1 = -1;
int fontID2 = -1;


float deltaTime = 0.0f;
static unsigned int g_prevMs = 0;

int sizeX = 1920;
int sizeY = 1080;
bool f11PressedLastFrame = false;

//カスタムウィンドウプロシージャのプロトタイプ宣言
static LRESULT CALLBACK CustomWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
	bool WINDOWED = TRUE; //ウィンドウモード

	SetWindowStyleMode(7); // スタイルを「サイズ変更可能」にする
	SetMainWindowText(L"野菜収穫ゲーム"); // ウィンドウのタイトルを変更する


	// DxPIus()X ライプラリ)の初期化
	if (DxPlus::Initialize(DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT, WINDOWED) == -1)
	{
		return -1;//初期化失敗
	}

	//ウィンドウプロシージャを設定
	DxLib::SetHookWinProc(CustomWinProc);

	//Game_Init();
	if (AddFontResourceExW(L"./Data/Fonts/Yusei_Magic/YuseiMagic-Regular.ttf", FR_PRIVATE, 0) == 0)
	{
		DxPlus::Utils::FatalError(L"Failed to add font: ./Data/Fonts/Yusei_Magic/YuseiMagic-Regular.ttf");
	}
	fontID2 = DxPlus::Text::InitializeFont(L"Yusei Magic", 30, 5);
	if (fontID2== -1)
	{
		DxPlus::Utils::FatalError(L"Failed to init font: Yusei Magic");
	}
	if (AddFontResourceExW(L"./Data/Fonts/New/001Shirokuma-Regular.otf", FR_PRIVATE, 0) == 0)
	{
		DxPlus::Utils::FatalError(L"Failed to add font: ./Data/Fonts/New/001Shirokuma-Regular (1).otf");
	}
	fontID1 = DxPlus::Text::InitializeFont(L"001Shirokuma-Regular", 40, 5);
	if (fontID1 == -1)
	{
		DxPlus::Utils::FatalError(L"Failed to init font: font");
	}
	Mouse_Image();
	Mouse_Reset();

	//ゲ ー ムル ー プ
	while (DxPlus::GameLoop())
	{
		//Mouseを消す
			SetMouseDispFlag(FALSE); 

		//今の時間を取得
		deltaTime = GetDeltaTime_DxLib(g_prevMs);
		Mouse_Update(deltaTime);

		//画面の大きさ
		SetWindowSize(sizeX, sizeY);
	
		//画面切り替え
		HandleScreenToggle();
	
		//シ-ンが切り替わるなら 
		if (nextScene != SceneNone) {
			//今のシ ー ンの終了関数を呼ぶ
			switch (currentScene) {

			case SceneTitle:
				Title_End();
				break;

			case SceneGame:
				Game_End();
				break;

			case SceneResult:
				Result_End();
				break;
			case SceneBattle:
				Battle_End();
				break;
			case SceneClear:
				Clear_End();
				break;
			}

			//次のシーンの初期設定関数を呼ぶ
			switch (nextScene) {

			case SceneTitle:
				Title_Init();
				break;

			case SceneGame:
				Game_Init();
				break;

			case SceneResult:
				Result_Init();
				break;

			case SceneBattle:
				Battle_Init();
				break;

			case SceneClear:
				Clear_Init();
				break;

			}

			//シーンの切り替えを反映させ、次のシーン指定をクリアしておく 
			currentScene = nextScene;
			nextScene = SceneNone;
		}

		DxPlus::Input::Update();

		//今のシーンの更新処理と描画処理を呼ぶ 
		switch (currentScene) {

		case SceneTitle:
			Title_Update();
			Title_Render();
			break;

		case SceneGame:
			Game_Update();
			Game_Render();
			break;

		case SceneResult:
			Result_Update();
			Result_Render();
			break;

		case SceneClear:
			Clear_Update();
			Clear_Render();
			break;

		case SceneBattle:
			Battle_Update();
			Battle_Render();
			break;
		}

		//DxPlus::Debug::Draw();
		Mouse_Draw();

		//画面をクリアする
		DxLib::ScreenFlip();
		DxLib::ClearDrawScreen();
	}
	//Game_End();
	//終了処理関数を呼ぶ 
	switch (currentScene) {

	case SceneTitle:
		Title_End();
		break;

	case SceneGame:
		Game_End();
		break;

	case SceneResult:
		Result_End();
		break;

	case SceneClear:
		Clear_End();
		break;

	case SceneBattle:
		Battle_End();
		break;
	
	}


	// DxPIus の終了処理
	DxPlus::ShutDown();

	//戻り値は 0 でよい
	return 0;
}
void HandleScreenToggle()
{
	bool f11Now = DxLib::CheckHitKey(KEY_INPUT_F11);

	if (f11Now && !f11PressedLastFrame)
	{
		// 押した瞬間だけ反応する
		sizeX = (sizeX == 1920) ? 1880 : 1920;
		sizeY = (sizeY == 1080) ? 1040 : 1080;

		// 必要なら画面モード切り替え処理をここに
	}

	f11PressedLastFrame = f11Now; // 状態を保存
		}

//ウインドウブロシ ー ジャ
LRESULT CALLBACK CustomWinProc(HWND, UINT msg, WPARAM wParam, LPARAM)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		break;
	}
	return 0;
}