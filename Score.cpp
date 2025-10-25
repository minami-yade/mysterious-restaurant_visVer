#include "Score.h"
#include <cwchar> // swprintf用

extern int fontID1;
Entity2D Scores;

// グローバル変数
int scoreSub = 0; // 前回のスコアを保存
int value = 0;    // スコアの差分を保存

// SubScore用の構造体
struct SubScore {
    DxPlus::Vec2 position;   // 位置
    float alpha;             // 透明度
    int lifetime;            // 表示時間（フレーム数）
} subScore;

// --- 画像読み込み関係 ---
void ScoreImage()
{
    Scores.spriteID = LoadGraph(L"./Data/images/score_number.png");
    if (Scores.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/score_number.png");
    }
}

// --- リセット関数 ---
void ScoreReset()
{
    scoreSub = 0;
    Scores.position = { 20.0f, 20.0f };
    Scores.scale = { 0.5f, 0.5f };
    Scores.center = { 0.0f, 0.0f };
    subScore = { {0.0f, 0.0f}, 0.0f, 0 }; // SubScoreの初期化
}

// --- 更新関数 ---
void ScoreUpdate(int score)
{
    bool isMoveScore;
    if (score - scoreSub != 0) {
        value = score - scoreSub; // スコアの差分を計算
        isMoveScore = true;
    }
    else isMoveScore = false;

    if (isMoveScore) {
		int ofsX = 450;
		int ofsY = 300;
        int randomX = ofsX + rand() % (1280 - ofsX * 2); 
        int randomY = ofsY + rand() % (720 -  48 - ofsY);  

        subScore.position = { static_cast<float>(randomX), static_cast<float>(randomY) }; // ランダムな位置を設定
        subScore.alpha = 1.0f; // 不透明
        subScore.lifetime = 120; // 表示時間（フレーム数）
    }

    // SubScoreの更新
    if (subScore.lifetime > 0) {
        subScore.position.y -= 1.0f; // 上に移動
        subScore.alpha -= 1.0f / 60.0f; // フェードアウト
        subScore.lifetime--;
    }

    // 今のスコアを記録
    scoreSub = score;
}

// --- 描画関数 ---
void ScoreDraw(int score)
{
    // スコアの描画
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
        swprintf(subScoreText, sizeof(subScoreText) / sizeof(wchar_t), L"+%d", value); // 差分スコアをテキストに変換

        int alphaColor = DxLib::GetColor(128, 0, 0) | (static_cast<int>(subScore.alpha * 255) << 24); // アルファ値を適用
        DxPlus::Text::DrawString(
            subScoreText, // テキスト
            subScore.position, // 表示位置
            alphaColor, // 色（透明度を含む）
            DxPlus::Text::TextAlign::MIDDLE_center, // 中央揃え
            { 1.4f, 1.4f }, // スケール
            0.0, // 回転角度
            fontID1 // フォントハンドル
        );
    }
}

// --- 解放関数 ---
void ScoreDelete()
{
    if (Scores.spriteID != -1)
    {
        DxLib::DeleteGraph(Scores.spriteID);
        Scores.spriteID = -1;
    }
}
