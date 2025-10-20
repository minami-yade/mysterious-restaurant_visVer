#include "Score.h"

extern int fontID1;
Entity2D Scores;
// --- �摜�ǂݍ��݊֌W ---
void ScoreImage()
{
    Scores.spriteID = LoadGraph(L"./Data/images/score_number.png");
    if (Scores.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/score_number.png");
    }


}

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void ScoreReset()
{
	Scores.position = { 20.0f, 20.0f };
    Scores.scale = { 0.5f,0.5f };
	Scores.center = { 0.0f, 0.0f };
}

// --- �����̍X�V�i�P���ȎO�p�g�ŏ㉺�j ---
void UpdateScore(float deltaTime)
{

}

// --- �`��֐� ---
void ScoreDraw(int score)
{
    DxPlus::Sprite::Draw(Scores.spriteID,
        Scores.position,
        Scores.scale,
        Scores.center,
        0.0f,
		GetColor(255, 255, 255));
    DxPlus::Text::DrawString(
		(L"Score: "),
        { Scores.position.x + 120, Scores.position.y + 75.0f },
        GetColor(160, 82, 45),
        DxPlus::Text::TextAlign::MIDDLE_LEFT,
        { 0.8f, 0.8f },
        0.0,               // angle�i��]�p�x�j���w��B0.0�ŉ�]�Ȃ�
        fontID1                 // fontHandle
    );


    DxPlus::Text::DrawString(
        std::to_wstring(score).c_str(), // const wchar_t* �ɕϊ�
        { Scores.position.x + 450, Scores.position.y + 75.0f },
        GetColor(160, 82, 45),
        DxPlus::Text::TextAlign::MIDDLE_RIGHT,
        { 1.0f, 1.0f },
        0.0,               // angle�i��]�p�x�j���w��B0.0�ŉ�]�Ȃ�
        fontID1                 // fontHandle
    );

}

// --- ����֐� ---
void ScoreDelete()
{
    if( Scores.spriteID != -1 )
    {
        DxLib::DeleteGraph( Scores.spriteID );
        Scores.spriteID = -1;
	}
}
