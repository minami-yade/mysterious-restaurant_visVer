#include "DxPlus/DxPlus.h"
#include "Credit.h"
#include "WinMain.h"

/*
memo

*/
extern int fontID1;

//----------------------------------------------------------------------
// �萔
//----------------------------------------------------------------------

float textPos = -1200.0f;
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


    Credit_Reset();
}

//----------------------------------------------------------------------
// ���Z�b�g
//----------------------------------------------------------------------
void Credit_Reset()
{
    CreditState = 0;
    CreditFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// �X�V����
//----------------------------------------------------------------------
void Credit_Update()
{
    textPos += 1;

    Credit_Fade();

}

//----------------------------------------------------------------------
// �`�揈��
//----------------------------------------------------------------------
void Credit_Render()
{
    const float lineSpacing = 250.0f; // �s�Ԋu��ݒ�
    for (int i = 0; i < 6; i++) {
        float yPos = textPos + i * lineSpacing; // �e�s��Y���W���v�Z
        switch (i)
        {
        case 0:
            DxPlus::Text::DrawString(
                L"0",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
            break;
        case 1:
            DxPlus::Text::DrawString(
                L"Producer: Your Name",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
            break;
        case 2:
            DxPlus::Text::DrawString(
                L"Thanks for playing!",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
            break;
        case 3:
            DxPlus::Text::DrawString(
                L"Press SELECT to return to Title",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
            break;
        case 4:
            DxPlus::Text::DrawString(
                L"Game Development Team",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
			);
			break;
            case 5:
            DxPlus::Text::DrawString(
                L"Special Thanks to Our Supporters",
                { DxPlus::CLIENT_WIDTH * 0.5f, yPos },
                GetColor(255, 255, 255),
                DxPlus::Text::TextAlign::MIDDLE_center,
                { 1.0f, 1.0f },
                0.0f,
                fontID1
            );
			break;


        default:
			DxPlus::Utils::FatalError(L"Invalid credit line index.");
            break;
        }
   
    }
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
            nextScene = SceneSetting;
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
