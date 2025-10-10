#include "DxPlus/DxPlus.h"
#include "Clear.h"
#include "WinMain.h"

/*
memo

*/

//----------------------------------------------------------------------
// �萔
//----------------------------------------------------------------------


//----------------------------------------------------------------------
// �ϐ�
//----------------------------------------------------------------------

int clearState;
float clearFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// �����ݒ�
//----------------------------------------------------------------------
void Clear_Init()
{
    SetBackgroundColor(120, 123, 74);

    Clear_Reset();
}

//----------------------------------------------------------------------
// ���Z�b�g
//----------------------------------------------------------------------
void Clear_Reset()
{
    clearState = 0;
    clearFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// �X�V����
//----------------------------------------------------------------------
void Clear_Update()
{

    Clear_Fade();

}

//----------------------------------------------------------------------
// �`�揈��
//----------------------------------------------------------------------
void Clear_Render()
{

    DxPlus::Text::DrawString(L"���肠",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.33f },
        DxLib::GetColor(255, 255, 255), DxPlus::Text::TextAlign::MIDDLE_CENTER, { 3.0f, 3.0f });



    // �t�F�[�h�C�� / �t�F�[�h�A�E�g�p 
    if (clearFadeTimer > 0.0f) {
        //���
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * clearFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Clear_Fade()
{
    switch (clearState) {
    case 0: // �t�F�[�h�C���� 
    {
        clearFadeTimer -= 1 / 60.0f;
        if (clearFadeTimer < 0.0f) {
            clearFadeTimer = 0.0f;
            clearState++;
        }
        break;
    }
    case 1: // �ʏ펞
    {
        // BackSpace �L�[�������ꂽ��^�C�g���ɖ߂� 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            clearState++;
        }
        break;
    }
    case 2: // �t�F�[�h�A�E�g��
    {
        clearFadeTimer += 1 / 60.0f;
        if (clearFadeTimer > 1.0f) {
            clearFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    
    //�Q�[���I�[�o�[
    case 3:
    {
        clearFadeTimer += 1 / 60.0f;
        if (clearFadeTimer > 1.0f) {
            clearFadeTimer = 1.0f;
            nextScene = SceneResult;
        }
        break;
    }
    //Game
    case 4:
    {
        clearFadeTimer += 1 / 60.0f;
        if (clearFadeTimer > 1.0f) {
            clearFadeTimer = 1.0f;
            nextScene = SceneGame;
        }
        break;
    }
    //�o�g��
    case 5:
    {
        clearFadeTimer += 1 / 60.0f;
        if (clearFadeTimer > 1.0f) {
            clearFadeTimer = 1.0f;
            nextScene = SceneClear;
        }
        break;
    }
    }
  

}


//----------------------------------------------------------------------
void Clear_End()
{

}
