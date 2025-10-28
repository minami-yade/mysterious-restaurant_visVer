#include "DxPlus/DxPlus.h"
#include "Title.h"
#include "WinMain.h"
#include "Back.h"
#include"vol.h"

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


int mouseX, mouseY;
int mouseInput;

//音
int vol_button;
int vol_title_BGM;


//---------------------------------------------------------------------- 
// 初期設定 
//----------------------------------------------------------------------
void Title_Init() {

	vol_button = DxLib::LoadSoundMem(L"./Data/Sounds/shush.mp3");
	if (vol_button == -1)
	{
		DxPlus::Utils::FatalError(L"ss./Data/Sounds/shush.mp3");
	}
	 vol_title_BGM = DxLib::LoadSoundMem(L"./Data/Sounds/Push.mp3");
	if (vol_title_BGM == -1)
	{
		DxPlus::Utils::FatalError(L"kk./Data/Sounds/Push.mp3");

	}
	ChangeVolumeSoundMem((int)GetVolume, vol_button);
	
	ChangeVolumeSoundMem((int)GetVolume, vol_title_BGM);


	TitleBackImage();

	Title_Reset();
}

//---------------------------------------------------------------------- 
// リセット
//----------------------------------------------------------------------
void Title_Reset() {

	frameCount = 0;

	TitleBackReset();
	gamePlay = false;
	titleState = 0;
	titleFadeTimer = 1.0f;

}
//---------------------------------------------------------------------- 
// 更新処理
//----------------------------------------------------------------------
void Title_Update() {

	Title_Fade();

	//if ((mouseInput & MOUSE_INPUT_LEFT) &&startbutton)
	//	titleState = 2;
	//if ((mouseInput & MOUSE_INPUT_LEFT) && settingbutton)
	//	titleState = 3;
	//if ((mouseInput & MOUSE_INPUT_LEFT) && finbutton)
	//	titleState = 4;

	if (mouseInput & MOUSE_INPUT_LEFT)
	{
		if (startbutton || settingbutton || finbutton)
		{
			PlaySoundMem(vol_button, DX_PLAYTYPE_BACK);
		}

		if (startbutton)titleState = 2;
		if (settingbutton)titleState = 3;
		if (finbutton)titleState = 4;

	}

	mouseInput = DxLib::GetMouseInput();
	DxLib::GetMousePoint(&mouseX, &mouseY);
	


	startbutton = ButtonPosition({ startButtonPos }, { (float)mouseX,(float)mouseY });
	settingbutton = ButtonPosition({ settingButtonPos }, { (float)mouseX,(float)mouseY });
	finbutton = ButtonPosition({ finButtonPos }, { (float)mouseX,(float)mouseY });




}




//---------------------------------------------------------------------- 
// 更新処理
//----------------------------------------------------------------------
void Title_Render() {

	TitleBackDraw({ 362.0f,473.0f },{1.0f,1.0f},{362.0f,473.0f},startbutton,settingbutton,finbutton, &gamePlay);

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
		/*titleFadeTimer -= 1 / 60.0f;
		if (titleFadeTimer < 0.0f) {
			titleFadeTimer = 0.0f;
			titleState++;
		}*/
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
		}
		break;
	}
	case 3: // フェードアウト中
	{
		titleFadeTimer += 1 / 60.0f;
		if (titleFadeTimer > 1.0f) {
			titleFadeTimer = 1.0f;
			nextScene = SceneSetting;
		}
		break;
	}
	case 4: // フェードアウト中
	{
			PostQuitMessage(0);
		
		break;
	}
	}
	frameCount++;

}
void Title_End() {
	TitleBackDelete();
}