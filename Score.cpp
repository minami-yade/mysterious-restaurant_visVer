#include "Score.h"
#include <cwchar> // swprintf�p

extern int fontID1;
Entity2D Scores;

// �O���[�o���ϐ�
int scoreSub = 0; // �O��̃X�R�A��ۑ�
int value = 0;    // �X�R�A�̍�����ۑ�

// SubScore�p�̍\����
struct SubScore {
    DxPlus::Vec2 position;   // �ʒu
    float alpha;             // �����x
    int lifetime;            // �\�����ԁi�t���[�����j
} subScore;

// --- �摜�ǂݍ��݊֌W ---
void ScoreImage()
{
    Scores.spriteID = LoadGraph(L"./Data/images/score_number.png");
    if (Scores.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/score_number.png");
    }
}

// --- ���Z�b�g�֐� ---
void ScoreReset()
{
    scoreSub = 0;
    Scores.position = { 20.0f, 20.0f };
    Scores.scale = { 0.5f, 0.5f };
    Scores.center = { 0.0f, 0.0f };
    subScore = { {0.0f, 0.0f}, 0.0f, 0 }; // SubScore�̏�����
}

// --- �X�V�֐� ---
void ScoreUpdate(int score)
{
    bool isMoveScore;
    if (score - scoreSub != 0) {
        value = score - scoreSub; // �X�R�A�̍������v�Z
        isMoveScore = true;
    }
    else isMoveScore = false;

    if (isMoveScore) {
		int ofsX = 450;
		int ofsY = 300;
        int randomX = ofsX + rand() % (1280 - ofsX * 2); 
        int randomY = ofsY + rand() % (720 -  48 - ofsY);  

        subScore.position = { static_cast<float>(randomX), static_cast<float>(randomY) }; // �����_���Ȉʒu��ݒ�
        subScore.alpha = 1.0f; // �s����
        subScore.lifetime = 120; // �\�����ԁi�t���[�����j
    }

    // SubScore�̍X�V
    if (subScore.lifetime > 0) {
        subScore.position.y -= 1.0f; // ��Ɉړ�
        subScore.alpha -= 1.0f / 60.0f; // �t�F�[�h�A�E�g
        subScore.lifetime--;
    }

    // ���̃X�R�A���L�^
    scoreSub = score;
}

// --- �`��֐� ---
void ScoreDraw(int score)
{
    // �X�R�A�̕`��
    DxPlus::Sprite::Draw(Scores.spriteID,
        Scores.position,
        Scores.scale,
        Scores.center,
        0.0f,
        GetColor(255, 255, 255));
    DxPlus::Text::DrawString(
        L"Score: ",
        { Scores.position.x + 120, Scores.position.y + 75.0f },
        GetColor(160, 82, 45),
        DxPlus::Text::TextAlign::MIDDLE_LEFT,
        { 0.8f, 0.8f },
        0.0,
        fontID1
    );

    wchar_t scoreText[16];
    swprintf(scoreText, sizeof(scoreText) / sizeof(wchar_t), L"%d", scoreSub);
    DxPlus::Text::DrawString(
        scoreText,
        { Scores.position.x + 450, Scores.position.y + 75.0f },
        GetColor(160, 82, 45),
        DxPlus::Text::TextAlign::MIDDLE_RIGHT,
        { 1.0f, 1.0f },
        0.0,
        fontID1
    );

 
    if (subScore.lifetime > 0) {
        wchar_t subScoreText[16];
        swprintf(subScoreText, sizeof(subScoreText) / sizeof(wchar_t), L"+%d", value); // �����X�R�A���e�L�X�g�ɕϊ�

        int alphaColor = DxLib::GetColor(128, 0, 0) | (static_cast<int>(subScore.alpha * 255) << 24); // �A���t�@�l��K�p
        DxPlus::Text::DrawString(
            subScoreText, // �e�L�X�g
            subScore.position, // �\���ʒu
            alphaColor, // �F�i�����x���܂ށj
            DxPlus::Text::TextAlign::MIDDLE_center, // ��������
            { 1.4f, 1.4f }, // �X�P�[��
            0.0, // ��]�p�x
            fontID1 // �t�H���g�n���h��
        );
    }
}

// --- ����֐� ---
void ScoreDelete()
{
    if (Scores.spriteID != -1)
    {
        DxLib::DeleteGraph(Scores.spriteID);
        Scores.spriteID = -1;
    }
}
