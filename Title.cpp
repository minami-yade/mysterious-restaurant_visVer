#include "DxPlus/DxPlus.h"
#include "Title.h"
#include "WinMain.h"
#include "Back.h"
#include"vol.h"
#include <algorithm>

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

int vol_title_button;
extern int vol_title_BGM;


int vol_kachi;

bool vol_prevStartHover = false;
bool vol_prevSettingHover = false;
bool vol_prevFinHover = false;

//---------------------------------------------------------------------- 
// �����ݒ� 
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
	TitleBackImage();

	Title_Reset();

	ChangeVolumeSoundMem((int)GetVolume(), vol_title_button);
	ChangeVolumeSoundMem((int)GetVolume(), vol_title_BGM);
	ChangeVolumeSoundMem((int)GetVolume(), vol_kachi);
}

//---------------------------------------------------------------------- 
// ���Z�b�g
//----------------------------------------------------------------------
void Title_Reset() {

	frameCount = 0;
	mouseInput = -1;
	mouseX = 0;
	mouseY = 0;


	TitleBackReset();
	gamePlay = false;
	titleState = 0;
	titleFadeTimer = 1.0f;


	StopSoundMem(vol_title_BGM);
	PlaySoundMem(vol_title_BGM, DX_PLAYTYPE_LOOP);

}
//---------------------------------------------------------------------- 
// �X�V����
//----------------------------------------------------------------------
void Title_Update() {



    Title_Fade();

    // �}�E�X���͂̎擾
    mouseInput = DxLib::GetMouseInput();
    DxLib::GetMousePoint(&mouseX, &mouseY);

    // �{�^���̈ʒu����
    startbutton = ButtonPosition({ startButtonPos }, { (float)mouseX,(float)mouseY });
    settingbutton = ButtonPosition({ settingButtonPos }, { (float)mouseX,(float)mouseY });
    finbutton = ButtonPosition({ finButtonPos }, { (float)mouseX,(float)mouseY });

    
	if (startbutton && !vol_prevStartHover)
	{
		PlaySoundMem(vol_kachi, DX_PLAYTYPE_BACK); // �z�o�[���i�J�[�\����������u�ԁj
	}
	if (settingbutton && !vol_prevSettingHover)
	{
		PlaySoundMem(vol_kachi, DX_PLAYTYPE_BACK);
	}
	if (finbutton && !vol_prevFinHover)
	{
		PlaySoundMem(vol_kachi, DX_PLAYTYPE_BACK);
	}

	// --- ���݂̏�Ԃ����̃t���[���p�ɕۑ� ---
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
		StopSoundMem(vol_title_BGM);  // �� �����Ń^�C�g��BGM���~�߂�I
	}


}




//---------------------------------------------------------------------- 
// �X�V����
//----------------------------------------------------------------------
void Title_Render() {

	TitleBackDraw({ 362.0f,473.0f },{1.0f,1.0f},{362.0f,473.0f},startbutton,settingbutton,finbutton, &gamePlay);

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
			DxLib::GetColor(125, 125, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void Title_Fade() {

	switch (titleState) {
	case 0:// �t�F�[�h�C���� 
	{
		titleFadeTimer = 0.0f;
		titleState++;

		break;
	}
	case 1: // �ʏ펞 
	{
		//	gamePlay = false;
		break;
	}
	case 2: // �t�F�[�h�A�E�g��
	{
		titleFadeTimer += 1 / 100.0f;
		gamePlay = true;
		if (titleFadeTimer > 0.5f) {
			titleFadeTimer = 0.5f;
			nextScene = SceneGame;
		}
		break;
	}
	case 3: // �t�F�[�h�A�E�g��
	{
		
		if (settingbutton) {
		

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
	StopSoundMem(vol_title_BGM);
	TitleBackDelete();
}