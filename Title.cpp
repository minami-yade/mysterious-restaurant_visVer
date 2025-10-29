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
int creditButtons;
const DxPlus::Vec2 creditButtonPos     = { buttonBase.x - 700.0f ,  buttonBase.y + 4 * 140.0f + 10 };

Entity2D creditButton;


int mouseX, mouseY;
int mouseInput;


//---------------------------------------------------------------------- 
// �����ݒ� 
//----------------------------------------------------------------------
void Title_Init() {

	TitleBackImage();
	creditButton.spriteID = LoadGraph(L"./Data/images/creditbutton .png");
	if(creditButton.spriteID == -1){
		DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/creditbutton .png");
	}

	Title_Reset();
}

//---------------------------------------------------------------------- 
// ���Z�b�g
//----------------------------------------------------------------------
void Title_Reset() {

	frameCount = 0;
	mouseInput = -1;
	mouseX = 0;
	mouseY = 0;
	creditButton.position = creditButtonPos;
	creditButton.scale = { 1.0f, 1.0f };
	creditButton.center = { 0.0f, 30.0f };
	creditButton.angle = 0.2f;


	TitleBackReset();
	gamePlay = false;
	titleState = 0;
	titleFadeTimer = 1.0f;

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

    // �{�^���̃N���b�N����
    if ((mouseInput & MOUSE_INPUT_LEFT) && startbutton)
        titleState = 2;
    if ((mouseInput & MOUSE_INPUT_LEFT) && settingbutton)
        titleState = 3; // �ݒ��ʂɑJ�ڂ����ԂɕύX
    if ((mouseInput & MOUSE_INPUT_LEFT) && finbutton)
        titleState = 4;


	// �N���W�b�g�{�^���̏���



}




//---------------------------------------------------------------------- 
// �X�V����
//----------------------------------------------------------------------
void Title_Render() {

	TitleBackDraw({ 362.0f,473.0f },{1.0f,1.0f},{362.0f,473.0f},startbutton,settingbutton,finbutton, &gamePlay);


	bool wasMousePressed = false;
	// �}�E�X�̈ʒu���擾
	DxPlus::Vec2 mousePos = { static_cast<float>(mouseX), static_cast<float>(mouseY) };

	DxPlus::Vec2 pos = creditButton.position;
	DxPlus::Vec2 length = { creditButton.scale.x * 200.0f, creditButton.scale.y * 100.0f };
	// �����蔻��
	creditButtons = (mousePos.x > pos.x && mousePos.x < pos.x + length.x &&
		mousePos.y > pos.y && mousePos.y < pos.y + length.y);

#if _DEBUG
	// �f�o�b�O�\��: �{�^���̋�`���E��`��
	int color = creditButtons ? GetColor(255, 255, 255) : GetColor(255, 0, 0);
	DrawBox(static_cast<int>(pos.x), static_cast<int>(pos.y),
		static_cast<int>(pos.x + length.x), static_cast<int>(pos.y + length.y),
		color, FALSE);
#endif

	// �}�E�X�N���b�N��Ԃ��擾
	wasMousePressed = false; // �O��̃N���b�N��Ԃ�ێ�
	int mouseInput = GetMouseInput();
	bool isMouseClicked = (mouseInput & MOUSE_INPUT_LEFT) != 0;

	// �X�P�[���ύX
	creditButton.angle = creditButtons ? creditButton.angle = 0.0f : creditButton.angle = 0.2f;

	// �����蔻�肪�������A���N���b�N�������ꂽ�u�Ԃ̂ݏ��������s
	if (creditButtons && isMouseClicked && !wasMousePressed && titleState == 1) {
		titleState = 5; // TitleState��ύX
	}

	// ���݂̃N���b�N��Ԃ�ۑ�
	wasMousePressed = isMouseClicked;

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
	DxPlus::Sprite::Draw(creditButton.spriteID, creditButton.position, creditButton.scale, creditButton.center,creditButton.angle);


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

	case 5: // �t�F�[�h�A�E�g��
	{
		if (creditButtons) {

			nextScene = SceneCredit; // �N���W�b�g�V�[���ɕύX
		}
		break;
	}
	default:
		DxPlus::Utils::FatalError(L"Invalid titleState value.");
		break;
	}

	frameCount++;

}
void Title_End() {
	TitleBackDelete();
}