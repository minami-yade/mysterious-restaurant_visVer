#include "DxPlus/DxPlus.h"
#include "Title.h"
#include "WinMain.h"
#include "Back.h"

//---------------------------------------------------------------------- 
// �萔 
// ---------------------------------------------------------------------- 

//---------------------------------------------------------------------- 
// �ϐ� 
//----------------------------------------------------------------------

int frameCount;

extern int nextScene;
unsigned int semiTransparentWhite = GetColor(255, 255, 255) | (128 << 24);  // 128 �͓����x
int BlackGreen = GetColor(0, 100, 0);


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


//---------------------------------------------------------------------- 
// �����ݒ� 
//----------------------------------------------------------------------
void Title_Init() {

	TitleBackImage();

	Title_Reset();
}

//---------------------------------------------------------------------- 
// ���Z�b�g
//----------------------------------------------------------------------
void Title_Reset() {

	frameCount = 0;

	TitleBackReset();
	
	titleState = 0;
	titleFadeTimer = 1.0f;

}
//---------------------------------------------------------------------- 
// �X�V����
//----------------------------------------------------------------------
void Title_Update() {

	TitleBackUpdate();
	Title_Fade();

	if ((mouseInput & MOUSE_INPUT_LEFT) &&startbutton)
		titleState = 2;
	if ((mouseInput & MOUSE_INPUT_LEFT) && settingbutton)
		titleState = 3;
	if ((mouseInput & MOUSE_INPUT_LEFT) && finbutton)
		titleState = 4;

	mouseInput = DxLib::GetMouseInput();
	DxLib::GetMousePoint(&mouseX, &mouseY);
	


	startbutton = ButtonPosition({ startButtonPos }, { (float)mouseX,(float)mouseY });
	settingbutton = ButtonPosition({ settingButtonPos }, { (float)mouseX,(float)mouseY });
	finbutton = ButtonPosition({ finButtonPos }, { (float)mouseX,(float)mouseY });




}




//---------------------------------------------------------------------- 
// �X�V����
//----------------------------------------------------------------------
void Title_Render() {

	TitleBackDraw({0,0},{1.0f,1.0f},{0.0f,0.0f},startbutton,settingbutton,finbutton);

#if _DEBUG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // ���������[�h���Z�b�g
	DxPlus::Primitive2D::DrawRect(
		{ startButtonPos },
		{ 370, 90 },
		DxLib::GetColor(255, 255, 255), startbutton);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // ���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // ���������[�h���Z�b�g
	DxPlus::Primitive2D::DrawRect(
		{ settingButtonPos },
		{ 370, 90 },
		DxLib::GetColor(255, 255, 255), settingbutton);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // ���ɖ߂�
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // ���������[�h���Z�b�g
	DxPlus::Primitive2D::DrawRect(
		{ finButtonPos },
		{ 370, 90 },
		DxLib::GetColor(255, 255, 255), finbutton);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // ���ɖ߂�

#endif


	FadeDrawTitle();
}

void FadeDrawTitle()
{
	if (titleFadeTimer > 0.0f) {
		DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * titleFadeTimer));
		DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
			DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void Title_Fade() {

	switch (titleState) {
	case 0:// �t�F�[�h�C���� 
	{
		titleFadeTimer -= 1 / 60.0f;
		if (titleFadeTimer < 0.0f) {
			titleFadeTimer = 0.0f;
			titleState++;
		} break;
	}
	case 1: // �ʏ펞 
	{
		
		break;
	}
	case 2: // �t�F�[�h�A�E�g��
	{
		titleFadeTimer += 1 / 60.0f;
		if (titleFadeTimer > 1.0f) {
			titleFadeTimer = 1.0f;
			nextScene = SceneGame;
		}
		break;
	}
	case 3: // �t�F�[�h�A�E�g��
	{
		titleFadeTimer += 1 / 60.0f;
		if (titleFadeTimer > 1.0f) {
			titleFadeTimer = 1.0f;
			nextScene = SceneSetting;
		}
		break;
	}
	case 4: // �t�F�[�h�A�E�g��
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