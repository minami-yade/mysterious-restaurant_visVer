#include "DxPlus/DxPlus.h"
#include "Title.h"
#include "WinMain.h"

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
bool isMouseOver;
int startbutton;
int mouseX, mouseY;
int mouseInput;


//---------------------------------------------------------------------- 
// �����ݒ� 
//----------------------------------------------------------------------
void Title_Init() {

	// Game �Ƌ�ʂ��邽�߂ɔw�i�̐F��ς���
	DxLib::SetBackgroundColor(0, 0, 0);

	Title_Reset();
}

//---------------------------------------------------------------------- 
// ���Z�b�g
//----------------------------------------------------------------------
void Title_Reset() {

	frameCount = 0;

	titleState = 0;
	titleFadeTimer = 1.0f;

}
//---------------------------------------------------------------------- 
// �X�V����
//----------------------------------------------------------------------
void Title_Update() {

	Title_Fade();

	startbutton = mouseX >= DxPlus::CLIENT_WIDTH * 0.5f - 150 && mouseX <= DxPlus::CLIENT_WIDTH * 0.5f + 150 &&
		mouseY >= DxPlus::CLIENT_HEIGHT * 0.7f - 40 && mouseY <= DxPlus::CLIENT_HEIGHT * 0.7f + 40;
	mouseInput = DxLib::GetMouseInput();
	DxLib::GetMousePoint(&mouseX, &mouseY);


	if (startbutton) {
		isMouseOver = true;
	}
	else isMouseOver = false;




}




//---------------------------------------------------------------------- 
// �X�V����
//----------------------------------------------------------------------
void Title_Render() {




	// �X�^�[�g�{�^���̕`��
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);  // ���������[�h���Z�b�g
	DxPlus::Primitive2D::DrawRect(
		{ DxPlus::CLIENT_WIDTH * 0.5f - 150, DxPlus::CLIENT_HEIGHT * 0.7f - 40 }, // ������ɏC��
		{ 300, 80 },
		DxLib::GetColor(255, 255, 255), isMouseOver);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);  // ���ɖ߂�


	// �^�C�g���̕`�� 
	DxPlus::Text::DrawString(L"2D GameProgramming I",
		{ DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.33f },
		BlackGreen, DxPlus::Text::TextAlign::MIDDLE_center, { 3.0f, 3.0f });

	DxPlus::Text::DrawString(L"Start Game",
		{ DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.7f },
		BlackGreen,
		DxPlus::Text::TextAlign::MIDDLE_center,
		{ 2.0f, 2.0f });


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
		if ((mouseInput & MOUSE_INPUT_LEFT) &&
			startbutton && titleState == 1) titleState++;
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
	}
	frameCount++;

}
void Title_End() {

}