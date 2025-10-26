#include "DxPlus/DxPlus.h"
#include "Setting.h"
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

int SettingState;
float SettingFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// �����ݒ�
//----------------------------------------------------------------------
void Setting_Init()
{
    SetBackgroundColor(120, 123, 74);

    Setting_Reset();
}

//----------------------------------------------------------------------
// ���Z�b�g
//----------------------------------------------------------------------
void Setting_Reset()
{
    SettingState = 0;
    SettingFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// �X�V����
//----------------------------------------------------------------------
void Setting_Update()
{
 
    Setting_Fade();

}

//----------------------------------------------------------------------
// �`�揈��
//----------------------------------------------------------------------
void Setting_Render()
{

    DxPlus::Text::DrawString(L"�����Ă����",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.33f },
        DxLib::GetColor(255, 255, 255), DxPlus::Text::TextAlign::MIDDLE_center, { 3.0f, 3.0f });

    if (DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1) & DxPlus::Input::BUTTON_TRIGGER1) {


        SettingState = 2;
    }
    else
    {
        DxPlus::Text::DrawString(L"SPACE�ł����ǂ��",
            { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.66f },
            DxLib::GetColor(255, 255, 0), DxPlus::Text::TextAlign::MIDDLE_center, { 2.0f, 2.0f });
	}

    // �t�F�[�h�C�� / �t�F�[�h�A�E�g�p 
    if (SettingFadeTimer > 0.0f) {
        //���
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * SettingFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Setting_Fade()
{
    switch (SettingState) {
    case 0: // �t�F�[�h�C���� 
    {
        SettingFadeTimer -= 1 / 60.0f;
        if (SettingFadeTimer < 0.0f) {
            SettingFadeTimer = 0.0f;
            SettingState++;
        }
        break;
    }
    case 1: // �ʏ펞
    {
        // BackSpace �L�[�������ꂽ��^�C�g���ɖ߂� 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            SettingState++;
        }
        break;
    }
    case 2: // �t�F�[�h�A�E�g��
    {
        SettingFadeTimer += 1 / 60.0f;
        if (SettingFadeTimer > 1.0f) {
            SettingFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    
    //�Q�[���I�[�o�[
    case 3:
    {
        SettingFadeTimer += 1 / 60.0f;
        if (SettingFadeTimer > 1.0f) {
            SettingFadeTimer = 1.0f;
            nextScene = SceneResult;
        }
        break;
    }
    //Game
    case 4:
    {
        SettingFadeTimer += 1 / 60.0f;
        if (SettingFadeTimer > 1.0f) {
            SettingFadeTimer = 1.0f;
            nextScene = SceneGame;
        }
        break;
    }
    //�o�g��
    case 5:
    {
        SettingFadeTimer += 1 / 60.0f;
        if (SettingFadeTimer > 1.0f) {
            SettingFadeTimer = 1.0f;
            nextScene = SceneSetting;
        }
        break;
    }
    }
  

}


//----------------------------------------------------------------------
void Setting_End()
{

}
