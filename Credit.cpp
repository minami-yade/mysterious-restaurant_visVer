#include "DxPlus/DxPlus.h"
#include "Credit.h"
#include "WinMain.h"
#include "Entity2D.h"
/*
memo

*/


//----------------------------------------------------------------------
// �萔
//----------------------------------------------------------------------
Entity2D creditBack[2];
Entity2D creditButtonda;
//----------------------------------------------------------------------
// �ϐ�
//----------------------------------------------------------------------



int CreditState;
float CreditFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// �����ݒ�
//----------------------------------------------------------------------
void Credit_Init()
{

	creditBack[0].spriteID = DxPlus::Sprite::Load(L"./Data/images/b1 (1).png");
    if(creditBack[0].spriteID == -1) {
        DxPlus::Utils::FatalError(L"data/Tex/credit_jpn.png�̓ǂݍ��݂Ɏ��s���܂���");
	}

	creditBack[1].spriteID = DxPlus::Sprite::Load(L"./Data/images/credit_ita.png");
    if(creditBack[1].spriteID == -1) {
        DxPlus::Utils::FatalError(L"data/Tex/credit_ita.png�̓ǂݍ��݂Ɏ��s���܂���");
	}

	creditButtonda.spriteID = DxPlus::Sprite::Load(L"./Data/images/back_titleto.png");
    if (creditButtonda.spriteID == -1) {
        DxPlus::Utils::FatalError(L"data/Tex/creditbutton.png�̓ǂݍ��݂Ɏ��s���܂���");
    }

    Credit_Reset();
}

//----------------------------------------------------------------------
// ���Z�b�g
//----------------------------------------------------------------------
void Credit_Reset()
{
    creditButtonda.position = { 525.0f, 626.0f };
    creditButtonda.scale = { 1.0f, 1.0f }; // �X�P�[����������
    creditButtonda.center = { 0.0f, 0.0f }; // ���S�_��������

    CreditState = 0;
    CreditFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// �X�V����
//----------------------------------------------------------------------
void Credit_Update()
{


    Credit_Fade();

}

//----------------------------------------------------------------------
// �`�揈��
//----------------------------------------------------------------------
void Credit_Render()
{
	static bool isHits = false;

    for (int i = 0; i < 2; ++i) {
        DxPlus::Sprite::Draw(creditBack[i].spriteID, { 0,0 });
    }
    float alpha = 255.0f;
    float crick = 100.0f;
    if (isHits) {
        alpha = crick; // �Â�
    }

	DxPlus::Sprite::Draw(creditButtonda.spriteID, creditButtonda.position, creditButtonda.scale, creditButtonda.center, creditButtonda.angle,GetColor(alpha,alpha,alpha));

	int mouseX, mouseY;
	GetMousePoint(&mouseX, &mouseY);
	DxPlus::Text::DrawString(L"Back to Title",
        40,
        15,
        GetColor(255, 255, 255),
        DxPlus::Text::BOTTOM_center,
        0,
        -1
    );


    bool wasMousePressed = false;
    // �}�E�X�̈ʒu���擾
    DxPlus::Vec2 mousePos = { static_cast<float>(mouseX), static_cast<float>(mouseY) };

    DxPlus::Vec2 pos = creditButtonda.position ;
    DxPlus::Vec2 length = { creditButtonda.scale.x * 220.0f, creditButtonda.scale.y * 55.0f };
    // �����蔻��
    isHits = (mousePos.x > pos.x && mousePos.x < pos.x + length.x &&
        mousePos.y > pos.y && mousePos.y < pos.y + length.y);

#if _DEBUG
    // �f�o�b�O�\��: �{�^���̋�`���E��`��
    int color = isHits ? GetColor(255, 255, 255) : GetColor(255, 0, 0);
    DrawBox(static_cast<int>(pos.x), static_cast<int>(pos.y),
        static_cast<int>(pos.x + length.x), static_cast<int>(pos.y + length.y),
        color, FALSE);
#endif

    // �}�E�X�N���b�N��Ԃ��擾
    wasMousePressed = false; // �O��̃N���b�N��Ԃ�ێ�
    int mouseInput = GetMouseInput();
    bool isMouseClicked = (mouseInput & MOUSE_INPUT_LEFT) != 0;

    // �X�P�[���ύX
    //creditButtonda.angle = creditButtondas ? creditButtonda.angle = 0.0f : creditButtonda.angle = 0.2f;

    // �����蔻�肪�������A���N���b�N�������ꂽ�u�Ԃ̂ݏ��������s
    if (isHits && isMouseClicked && !wasMousePressed && CreditState == 1) {
        CreditState = 2;
    }

    // ���݂̃N���b�N��Ԃ�ۑ�
    wasMousePressed = isMouseClicked;

    // �t�F�[�h�C�� / �t�F�[�h�A�E�g�p 
    if (CreditFadeTimer > 0.0f) {
        //���
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * CreditFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Credit_Fade()
{
    switch (CreditState) {
    case 0: // �t�F�[�h�C���� 
    {
        CreditFadeTimer -= 1 / 60.0f;
        if (CreditFadeTimer < 0.0f) {
            CreditFadeTimer = 0.0f;
            CreditState++;
        }
        break;
    }
    case 1: // �ʏ펞
    {
        // BackSpace �L�[�������ꂽ��^�C�g���ɖ߂� 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            CreditState++;
        }
        break;
    }
    case 2: // �t�F�[�h�A�E�g��
    {
        CreditFadeTimer += 1 / 60.0f;
        if (CreditFadeTimer > 1.0f) {
            CreditFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    //�Q�[���I�[�o�[
    case 3:
    {
        CreditFadeTimer += 1 / 60.0f;
        if (CreditFadeTimer > 1.0f) {
            CreditFadeTimer = 1.0f;
            nextScene = SceneResult;
        }
        break;
    }
    //�N���A
    case 4:
    {
        CreditFadeTimer += 1 / 60.0f;
        if (CreditFadeTimer > 1.0f) {
            CreditFadeTimer = 1.0f;
            nextScene = SceneCredit;
        }
        break;
    }
    //Game
    case 5:
    {
        CreditFadeTimer += 1 / 60.0f;
        if (CreditFadeTimer > 1.0f) {
            CreditFadeTimer = 1.0f;
            nextScene = SceneGame;
        }
        break;
    }
    }

}


//----------------------------------------------------------------------
void Credit_End()
{

}
