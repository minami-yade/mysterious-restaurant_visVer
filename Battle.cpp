#include "DxPlus/DxPlus.h"
#include "Battle.h"
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

int battleState;
float battleFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// �����ݒ�
//----------------------------------------------------------------------
void Battle_Init()
{
    SetBackgroundColor(0,0, 255);

    Battle_Reset();
}

//----------------------------------------------------------------------
// ���Z�b�g
//----------------------------------------------------------------------
void Battle_Reset()
{
    battleState = 0;
    battleFadeTimer = 1.0f;

}
//----------------------------------------------------------------------
// �X�V����
//----------------------------------------------------------------------
void Battle_Update()
{
   
   
    Battle_Fade();

}

//----------------------------------------------------------------------
// �`�揈��
//----------------------------------------------------------------------
void Battle_Render()
{
    DxPlus::Text::DrawString(L"�΂Ƃ�",
        { DxPlus::CLIENT_WIDTH * 0.5f, DxPlus::CLIENT_HEIGHT * 0.33f },
        DxLib::GetColor(255, 255, 255), DxPlus::Text::TextAlign::MIDDLE_center, { 3.0f, 3.0f });

    // �t�F�[�h�C�� / �t�F�[�h�A�E�g�p 
    if (battleFadeTimer > 0.0f) {
        //���
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * battleFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Battle_Fade()
{
    switch (battleState) {
    case 0: // �t�F�[�h�C���� 
    {
        battleFadeTimer -= 1 / 60.0f;
        if (battleFadeTimer < 0.0f) {
            battleFadeTimer = 0.0f;
            battleState++;
        }
        break;
    }
    case 1: // �ʏ펞
    {
        // BackSpace �L�[�������ꂽ��^�C�g���ɖ߂� 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            battleState++;
        }
        break;
    }
    case 2: // �t�F�[�h�A�E�g��
    {
        battleFadeTimer += 1 / 60.0f;
        if (battleFadeTimer > 1.0f) {
            battleFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    //�Q�[���I�[�o�[
    case 3:
    {
        battleFadeTimer += 1 / 60.0f;
        if (battleFadeTimer > 1.0f) {
            battleFadeTimer = 1.0f;
            nextScene = SceneResult;
        }
        break;
    }
    //�N���A
    case 4:
    {
        battleFadeTimer += 1 / 60.0f;
        if (battleFadeTimer > 1.0f) {
            battleFadeTimer = 1.0f;
            nextScene = SceneSetting;
        }
        break;
    }
    //Game
    case 5:
    {
        battleFadeTimer += 1 / 60.0f;
        if (battleFadeTimer > 1.0f) {
            battleFadeTimer = 1.0f;
            nextScene = SceneGame;
        }
        break;
    }
    }

}


//----------------------------------------------------------------------
void Battle_End()
{

}
