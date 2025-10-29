#include "DxPlus/DxPlus.h"
#include "Title.h"
#include "WinMain.h"
#include "Back.h"
#include"vol.h"
#include <algorithm>

//---------------------------------------------------------------------- 
// 定数 
// ---------------------------------------------------------------------- 

//---------------------------------------------------------------------- 
// 変数 
//----------------------------------------------------------------------

int frameCount;

extern int nextScene;
unsigned int semiTransparentWhite = GetColor(255, 255, 255) | (128 << 24);  // 128 は透明度
int BlackGreen = GetColor(0, 100, 0);

bool gamePlay  = false;
int titleState;

float titleFadeTimer;

extern DxPlus::Vec2 buttonBase;

int startbutton;
const DxPlus::Vec2 startButtonPos   = { buttonBase.x + 100.0f ,	 buttonBase.y + 2 * 140.0f };
int settingbutton;
const DxPlus::Vec2 settingButtonPos = { buttonBase.x + 100.0f ,	 buttonBase.y + 3 * 140.0f + 5 };
int finbutton;
const DxPlus::Vec2 finButtonPos     = { buttonBase.x + 100.0f ,  buttonBase.y + 4 * 140.0f + 10 };
int CreditButton;
const DxPlus::Vec2 CreditButtonPos = { 0.0f ,  650.0f };


int mouseX, mouseY;
int mouseInput;

int vol_title_button;
extern int vol_title_BGM;

Entity2D creditButton;

int vol_kachi;

bool vol_prevStartHover = false;
bool vol_prevSettingHover = false;
bool vol_prevFinHover = false;

bool wasMousePresseds = false;

int vol_door;
//---------------------------------------------------------------------- 
// 初期設定 
//----------------------------------------------------------------------
void Title_Init() {

	//vol_title_button = DxLib::LoadSoundMem(L"./Data/Sounds/shush.mp3");
	//if (vol_title_button == -1)
	//{
	//	DxPlus::Utils::FatalError(L"./Data/Sounds/shush.mp3");
	//}

	//vol_title_BGM = DxLib::LoadSoundMem(L"./Data/Sounds/BGMtitle.wav");
	//if (vol_title_BGM == -1)
	//{
	//	DxPlus::Utils::FatalError(L"./Data/Sounds/BGMtitle.wav");
	//}
	vol_kachi = DxLib::LoadSoundMem(L"./Data/Sounds/shush.mp3");
	if (vol_kachi == -1)
	{
		DxPlus::Utils::FatalError(L"./Data/Sounds/shush.mp3");
	}	
	vol_door = DxLib::LoadSoundMem(L"./Data/Sounds/door.mp3");
	if (vol_door == -1)
	{
		DxPlus::Utils::FatalError(L"./Data/Sounds/door.mp3");
	}

	creditButton.spriteID = LoadGraph(L"./Data/images/credit.png");
	if (creditButton.spriteID == -1) {
		DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/creditbutton.png");
	}

	TitleBackImage();

	Title_Reset();

	ChangeVolumeSoundMem((int)GetVolume(), vol_title_button);
	ChangeVolumeSoundMem((int)GetVolume(), vol_title_BGM);
	ChangeVolumeSoundMem((int)GetVolume(), vol_kachi);
	ChangeVolumeSoundMem((int)GetVolume(), vol_door);
}

//---------------------------------------------------------------------- 
// リセット
//----------------------------------------------------------------------
void Title_Reset() {

	frameCount = 0;
	mouseInput = -1;
	mouseX = 0;
	mouseY = 0;

	creditButton.position = CreditButtonPos;
	creditButton.scale = { 1.0f, 1.0f };
	creditButton.center = { 0.0f, 0.0f };

	TitleBackReset();
	gamePlay = false;
	titleState = 0;
	titleFadeTimer = 1.0f;


	StopSoundMem(vol_title_BGM);
	PlaySoundMem(vol_title_BGM, DX_PLAYTYPE_LOOP);

}
//---------------------------------------------------------------------- 
// 更新処理
//----------------------------------------------------------------------
void Title_Update() {



    Title_Fade();

    // マウス入力の取得
    mouseInput = DxLib::GetMouseInput();
    DxLib::GetMousePoint(&mouseX, &mouseY);

    // ボタンの位置判定
    startbutton = ButtonPosition({ startButtonPos }, { (float)mouseX,(float)mouseY });
    settingbutton = ButtonPosition({ settingButtonPos }, { (float)mouseX,(float)mouseY });
    finbutton = ButtonPosition({ finButtonPos }, { (float)mouseX,(float)mouseY });

    
	if (startbutton && !vol_prevStartHover)
	{
		PlaySoundMem(vol_kachi, DX_PLAYTYPE_BACK); // ホバー音（カーソルが乗った瞬間）
	}
	if (settingbutton && !vol_prevSettingHover)
	{
		PlaySoundMem(vol_kachi, DX_PLAYTYPE_BACK);
	}
	if (finbutton && !vol_prevFinHover)
	{
		PlaySoundMem(vol_kachi, DX_PLAYTYPE_BACK);
	}

	// --- 現在の状態を次のフレーム用に保存 ---
	vol_prevStartHover = startbutton;
	vol_prevSettingHover = settingbutton;
	vol_prevFinHover = finbutton;




	if (mouseInput & MOUSE_INPUT_LEFT)
	{
		if (startbutton)      titleState = 2;
		else if (settingbutton) titleState = 3;
		else if (finbutton)     titleState = 4;
	}


	if ( nextScene == SceneGame)
	{
		StopSoundMem(vol_title_BGM);  // ← ここでタイトルBGMを止める！
	}


}




//---------------------------------------------------------------------- 
// 更新処理
//----------------------------------------------------------------------
void Title_Render() {

	TitleBackDraw({ 362.0f,473.0f },{1.0f,1.0f},{362.0f,473.0f},startbutton,settingbutton,finbutton, &gamePlay);

	bool isHit = false;
	// マウスの位置を取得
	DxPlus::Vec2 mousePos = { static_cast<float>(mouseX), static_cast<float>(mouseY) };
	DxPlus::Vec2 pos = CreditButtonPos;
	DxPlus::Vec2 length = { 220.0f,55.0f };
	// 当たり判定
	isHit = (mousePos.x > pos.x && mousePos.x < pos.x + length.x &&
		mousePos.y > pos.y && mousePos.y < pos.y + length.y);
#if _DEBUG
	// デバッグ表示: ボタンの矩形境界を描画
	int color = isHit ? GetColor(255, 255, 255) : GetColor(255, 0, 0);
	DrawBox(static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(pos.x + length.x), static_cast<int>(pos.y + length.y),
		color, FALSE);
#endif
	// マウスクリック状態を取得
	wasMousePresseds = false; // 前回のクリック状態を保持
	int mouseInput = GetMouseInput();
	bool isMouseClicked = (mouseInput & MOUSE_INPUT_LEFT) != 0;

	//if (isHit && !prevHit[mode]) {
	//	PlaySoundMem(vol_kachi2, DX_PLAYTYPE_BACK);
	//}

	
	// 当たり判定が成立し、かつクリックが押された瞬間のみ処理を実行
	if (isHit && isMouseClicked && !wasMousePresseds && titleState == 1) {
		titleState = 5;
	}

	// 現在のクリック状態を保存
	wasMousePresseds = isMouseClicked;

	//prevHit[mode] = isHit;

#if _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // 半透明モードをセット
	DxPlus::Primitive2D::DrawRect(
		{ startButtonPos },
		{ 370, 90 },
		DxLib::GetColor(255, 255, 255), startbutton);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // 元に戻す
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // 半透明モードをセット
	DxPlus::Primitive2D::DrawRect(
		{ settingButtonPos },
		{ 370, 90 },
		DxLib::GetColor(255, 255, 255), settingbutton);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // 元に戻す
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // 半透明モードをセット
	DxPlus::Primitive2D::DrawRect(
		{ finButtonPos },
		{ 370, 90 },
		DxLib::GetColor(255, 255, 255), finbutton);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // 元に戻す

#endif
	int alpha = 255.0f;
	int crick = 100.0f;
	if (isHit) {
		alpha = crick; // 暗く
	}
	DxPlus::Sprite::Draw(
		creditButton.spriteID,
		creditButton.position,
		creditButton.scale,
		creditButton.center,
		creditButton.angle,
		GetColor(alpha,alpha,alpha)
	);

	FadeDrawTitle();
}

void FadeDrawTitle()
{
	if (titleFadeTimer > 0.0f) {
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * titleFadeTimer));
		DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
			DxLib::GetColor(125, 125, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void Title_Fade() {

	switch (titleState) {
	case 0:// フェードイン中 
	{
		titleFadeTimer = 0.0f;
		titleState++;


		break;
	}
	case 1: // 通常時 
	{
		//	gamePlay = false;
		break;
	}
	case 2: // フェードアウト中
	{
		titleFadeTimer += 1 / 100.0f;
		gamePlay = true;
		if (titleFadeTimer > 0.5f) {
			titleFadeTimer = 0.5f;
			nextScene = SceneGame;
			PlaySoundMem(vol_door, DX_PLAYTYPE_BACK);
		}
		break;
	}
	case 3: // フェードアウト中
	{

		if (settingbutton) {


			nextScene = SceneSetting;
		}
		break;
	}
	case 4: // フェードアウト中
	{
		PostQuitMessage(0);

		break;
	}

	case 5: // フェードアウト中
	{
		nextScene = SceneCredit;
		break;
	}
	default:
		DxPlus::Utils::FatalError(L"Invalid TitleState value.");
		break;
	}
	frameCount++;

}
void Title_End() {
	StopSoundMem(vol_title_BGM);
	TitleBackDelete();
}