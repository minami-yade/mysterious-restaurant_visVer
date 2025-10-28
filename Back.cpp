#include "Back.h"

Entity2D titleBack[TITLE_BACK_NUM];
Entity2D Button[TITLE_BUTTON_NUM];
Entity2D TitlePlay[TITLE_BACKPLAY_NUM];
enum ButtonType {
    Title,
    Start,
    Settings,
    Fin
};
Entity2D gameBack;
Entity2D gameFloor;
DxPlus::Vec2 buttonBase = { 700.0f, 0.0f };

DxPlus::Vec2 karipos{};
Entity2D kari[ANI_SOMESHING_NUM];

// アニメーション用
float titleBackAnimTimer = 0.0f;
int titleBackAnimFrame = 0;
float titleBackAnimSpeed = 0.05f; // 秒（小さいほど）

//AniSomething用
//アニメーション
float aniSomeTimer = 0.0f;     
int aniSomeFrame = 0;          
float aniSomeSpeed = 0.2f;    
bool aniSomePlayOnce = false;  

// スケール補間用変数
DxPlus::Vec2 currentScale = { 1.0f, 1.0f }; // 初期スケール
const DxPlus::Vec2 targetScale = { 3.5f, 3.5f }; // 目標スケール
const float scaleSpeed = 0.3f; // スケール補間速度（小さいほどゆっくり）


//リザルト--------------------------
int ResultAnimation[RESULT_ANIM_COUNT];
int ResultStar0Animation[RESULT_ANIM_COUNT];
int ResultStar1Animation[RESULT_ANIM_COUNT];
int ResultStar2Animation[RESULT_ANIM_COUNT];
int ResultStar3Animation[RESULT_ANIM_COUNT];
// アニメーション用の変数
int currentFrame = 0; // 現在のフレーム
float animTimer = 0.0f; // アニメーションタイマー
const float animSpeed = 0.1f; // アニメーション速度（秒）
// アニメーション用の変数
int TitleToFrame = 0; // 現在のフレーム(GOTITLE)
float animTitleToTimer = 0.0f; // アニメーションタイマー
const float animTitleToSpeed = 0.1f; // アニメーション速度（秒）

extern int fontID1;


void TitleBackImage() {
    const wchar_t* BacksPaths[TITLE_BACK_NUM] = {
        L"./Data/images/b1 (1).png",
        L"./Data/images/b2 (1).png",
        L"./Data/images/b3 (1).png",
        L"./Data/images/b4 (1).png",
        L"./Data/images/b5 (1).png"
    };
    const wchar_t* ButtonPaths[TITLE_BUTTON_NUM] = {
		L"./Data/images/title_logo1.png", // Title
		L"./Data/images/start.png",      // Start
		L"./Data/images/setting.png",    // Settings   
		L"./Data/images/quit_game.png",  // Fin
    };
    const wchar_t* titlePlayPaths[TITLE_BACKPLAY_NUM] = {
        L"./Data/images/b1.png",
        L"./Data/images/b2.png",
        L"./Data/images/b3.png",
        L"./Data/images/b4.png",
        L"./Data/images/b5.png",
        L"./Data/images/b6.png",
        L"./Data/images/b7.png",
        L"./Data/images/b8.png",
    };
    for (int j = 0; j < TITLE_BACK_NUM; ++j)
    {
        titleBack[j].spriteID = LoadGraph(BacksPaths[j]);//
        if (titleBack[j].spriteID == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + BacksPaths[j]).c_str());
        }
    }
    for (int j = 0; j < TITLE_BUTTON_NUM; ++j)
    {
        Button[j].spriteID = LoadGraph(ButtonPaths[j]);
        if (Button[j].spriteID == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + ButtonPaths[j]).c_str());
        }
    }
    for(int i=0;i<TITLE_BACKPLAY_NUM;++i){
        TitlePlay[i].spriteID = LoadGraph(titlePlayPaths[i]);
        if (TitlePlay[i].spriteID == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + titlePlayPaths[i]).c_str());
        }
	}
}

void TitleBackReset() {
    // アニメーション用変数のリセット
    titleBackAnimTimer = 0.0f;
    titleBackAnimFrame = 0;
    // スケール補間用変数のリセット
    currentScale = { 1.0f, 1.0f };

    
}


 
   


void GameBackImage() {
    gameBack.spriteID = LoadGraph(L"./Data/images/h1.png");
    if (gameBack.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/h1.png");
    }
    gameFloor.spriteID = LoadGraph(L"./Data/images/front_lane.png");
    if (gameFloor.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/front_lane.png");
    }

}


int ButtonPosition(DxPlus::Vec2 pos, DxPlus::Vec2 mousePos)
{
    int width = 370;  // 幅（X方向）
    int height = 90;  // 高さ（Y方向）

    DxPlus::Vec2 leftTop = pos;
    DxPlus::Vec2 rightBottom = { pos.x + width, pos.y + height };

    DrawBox(
        leftTop.x,
        leftTop.y,
        rightBottom.x,
        rightBottom.y,
        DxLib::GetColor(255, 0, 0),
        true
    );

    return (leftTop.x < mousePos.x && leftTop.y < mousePos.y &&
        rightBottom.x > mousePos.x && rightBottom.y > mousePos.y);
}

void GameBackUpdate() {
}

void TitleBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center, bool start, bool set, bool fin, bool* gamePlay) {
    // タイトル背景アニメーション描画
    if (*gamePlay) {
        // スケールを補間して徐々に大きくする
        currentScale.x += (targetScale.x - currentScale.x) * scaleSpeed * titleBackAnimSpeed;
        currentScale.y += (targetScale.y - currentScale.y) * scaleSpeed * titleBackAnimSpeed;

        // タイトルプレイアニメーション描画（1回だけ再生）
        int playFrame = titleBackAnimFrame;
        if (playFrame >= TITLE_BACKPLAY_NUM) {
            playFrame = TITLE_BACKPLAY_NUM - 1; // 最後のフレームで止める
        }
        if (TitlePlay[playFrame].spriteID != -1) {
            DxPlus::Sprite::Draw(TitlePlay[playFrame].spriteID, position, currentScale, center); // 拡大のみ
        }
    } else {
        // 通常のタイトル背景アニメーション（繰り返し）
        int frame = titleBackAnimFrame % TITLE_BACK_NUM;
        if (titleBack[frame].spriteID != -1) {
            DxPlus::Sprite::Draw(titleBack[frame].spriteID, position, scale, center);
        }
    }

    // ボタン描画
    for (int i = 0; i < TITLE_BUTTON_NUM; ++i) {
        if (Button[i].spriteID != -1) {
            DxPlus::Vec2 offset;
            DxPlus::Vec2 buttonScale;

            if (i == 0) { // タイトルロゴ
                offset = { -50.0f, 50.0f };
                buttonScale = { 0.5f, 0.5f };
            } else { // その他のボタン
                offset = { 100.0f, 80.0f + i * 144.0f };
                buttonScale = { 0.9f, 0.9f };
            }

            float alpha = 255.0f;
            float crick = 100.0f;
            if (start && i == 1) {
                alpha = crick; // 暗く
            }
            if (set && i == 2) {
                alpha = crick;
            }
            if (fin && i == 3) {
                alpha = crick;
            }

            DxPlus::Sprite::Draw(Button[i].spriteID, buttonBase + offset, buttonScale, { 0.0f, 0.0f }, 0.0f, GetColor(alpha, alpha, alpha));
        }
    }

    // アニメーション更新
    if (*gamePlay) {
        // TitlePlay のアニメーションは一回だけ再生
        if (titleBackAnimFrame < TITLE_BACKPLAY_NUM - 1) {
            titleBackAnimTimer += titleBackAnimSpeed * 3; // 描画速度
            if (titleBackAnimTimer >= 1.0f) {
                titleBackAnimTimer -= 1.0f;
                titleBackAnimFrame++;
            }
        }
    } else {
        // 通常のタイトル背景アニメーションは繰り返し
        titleBackAnimTimer += titleBackAnimSpeed;
        if (titleBackAnimTimer >= 1.0f) {
            titleBackAnimTimer -= 1.0f;
            titleBackAnimFrame = (titleBackAnimFrame + 1) % TITLE_BACK_NUM;
        }
    }
}

void GameBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center) {
    DxPlus::Sprite::Draw(gameBack.spriteID,position, scale, center);
}

void GameFloorDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center) {
    DxPlus::Sprite::Draw(gameFloor.spriteID, position, scale, center);
}

void TitleBackDelete() {
    // titleBack 配列のスプライトを削除
    for (int i = 0; i < TITLE_BACK_NUM; ++i) {
        if (titleBack[i].spriteID != -1) {
            DxPlus::Sprite::Delete(titleBack[i].spriteID);
            titleBack[i].spriteID = -1; // 解放後に初期化
        }
    }

    // Button 配列のスプライトを削除
    for (int i = 0; i < TITLE_BUTTON_NUM; ++i) {
        if (Button[i].spriteID != -1) {
            DxPlus::Sprite::Delete(Button[i].spriteID);
            Button[i].spriteID = -1; // 解放後に初期化
        }
    }

    // TitlePlay 配列のスプライトを削除
    for (int i = 0; i < TITLE_BACKPLAY_NUM; ++i) {
        if (TitlePlay[i].spriteID != -1) {
            DxPlus::Sprite::Delete(TitlePlay[i].spriteID);
            TitlePlay[i].spriteID = -1; // 解放後に初期化
        }
    }
}

void GameBackDelete() {
    if (gameBack.spriteID != -1) {
        DxPlus::Sprite::Delete(gameBack.spriteID);
    }
}

struct Rank {

	int spriteID = -1;
	DxPlus::Vec2 BasePos = { 340.0f, 350.0f };
	DxPlus::Vec2 pos = { BasePos };
	DxPlus::Vec2 scale = { 0.8f, 0.8f };
	DxPlus::Vec2 center = { 0.0f, 0.0f };

};  
enum RankType {
    Star0,
    Star1,
    Star2,
    Star3,
};
Rank ResultRank[5];
Rank TitleTo;

const int MIN_SCORE_FOR_1_STAR  = 100;    // 1つ星を獲得するための最小スコア
const int MIN_SCORE_FOR_2_STARS = 200;  // 2つ星を獲得するための最小スコア
const int MIN_SCORE_FOR_3_STARS = 300;  // 3つ星を獲得するための最小スコア


bool TitleToClicked = false;

// Result関連--------------------------
void ResultBackImage() {
    const wchar_t* animPaths[RESULT_ANIM_COUNT] = {
        L"./Data/images/Result1.png",
        L"./Data/images/Result2.png",
        L"./Data/images/Result3.png",
        L"./Data/images/Result4.png",
        L"./Data/images/Result5.png",
        L"./Data/images/Result6.png",
        L"./Data/images/Result7.png"
    };

    for (int i = 0; i < RESULT_ANIM_COUNT; ++i) {
        ResultAnimation[i] = LoadGraph(animPaths[i]);
        if (ResultAnimation[i] == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"Failed to load sprite: ") + animPaths[i]).c_str());
        }
    }
    const wchar_t* animStar0Paths[RESULT_ANIM_COUNT] = {
        L"./Data/images/star0/1.png",
        L"./Data/images/star0/2.png",
        L"./Data/images/star0/3.png",
        L"./Data/images/star0/4.png",
        L"./Data/images/star0/5.png",
        L"./Data/images/star0/6.png",
        L"./Data/images/star0/7.png"
    };

    for (int i = 0; i < RESULT_ANIM_COUNT; ++i) {
        ResultStar0Animation[i] = LoadGraph(animStar0Paths[i]);
        if (ResultStar0Animation[i] == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"Failed to load sprite: ") + animStar0Paths[i]).c_str());
        }
    }
    const wchar_t* animStar1Paths[RESULT_ANIM_COUNT] = {
        L"./Data/images/star1/1.png",
        L"./Data/images/star1/2.png",
        L"./Data/images/star1/3.png",
        L"./Data/images/star1/4.png",
        L"./Data/images/star1/5.png",
        L"./Data/images/star1/6.png",
        L"./Data/images/star1/7.png"
	};
    for (int i = 0; i < RESULT_ANIM_COUNT; ++i) {
        ResultStar1Animation[i] = LoadGraph(animStar1Paths[i]);
        if (ResultStar1Animation[i] == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"Failed to load sprite: ") + animStar1Paths[i]).c_str());
        }
	}
    const wchar_t* animStar2Paths[RESULT_ANIM_COUNT] = {
        L"./Data/images/star2/1.png",
        L"./Data/images/star2/2.png",
        L"./Data/images/star2/3.png",
        L"./Data/images/star2/4.png",
        L"./Data/images/star2/5.png",
        L"./Data/images/star2/6.png",
        L"./Data/images/star2/7.png"
	};
    for (int i = 0; i < RESULT_ANIM_COUNT; ++i) {
        ResultStar2Animation[i] = LoadGraph(animStar2Paths[i]);
        if (ResultStar2Animation[i] == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"Failed to load sprite: ") + animStar2Paths[i]).c_str());
		}
	}
    const wchar_t* animStar3Paths[RESULT_ANIM_COUNT] = {
        L"./Data/images/star3/1.png",
        L"./Data/images/star3/2.png",
        L"./Data/images/star3/3.png",
        L"./Data/images/star3/4.png",
        L"./Data/images/star3/5.png",
        L"./Data/images/star3/6.png",
		L"./Data/images/star3/7.png"
	};
    for (int i = 0; i < RESULT_ANIM_COUNT; ++i) {
        ResultStar3Animation[i] = LoadGraph(animStar3Paths[i]);
        if (ResultStar3Animation[i] == -1) {
			DxPlus::Utils::FatalError((std::wstring(L"Failed to load sprite: ") + animStar3Paths[i]).c_str());
		}
	}

    //結果
    //星０
	ResultRank[Star0].spriteID = LoadGraph(L"./Data/images/star0.png");
    if(ResultRank[Star0].spriteID == -1){
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/star0.png");
	}
	//星１
	ResultRank[Star1].spriteID = LoadGraph(L"./Data/images/star1.png");
    if(ResultRank[Star1].spriteID == -1){
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/star1.png");
	}
	//星２
	ResultRank[Star2].spriteID = LoadGraph(L"./Data/images/star2.png");
    if(ResultRank[Star2].spriteID == -1){
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/star2.png");
	}
	//星３
	ResultRank[Star3].spriteID = LoadGraph(L"./Data/images/star3.png");
    if (ResultRank[Star3].spriteID == -1) {
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/star3.png");
    }
    //タイトルへ
	TitleTo.spriteID = LoadGraph(L"./Data/images/back_title.png");
    if (TitleTo.spriteID == -1) {
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/back_title.png");
    }
	TitleTo.pos = { TitleTo.BasePos.x + 0.0f, TitleTo.BasePos.y + 230.0f };// 初期位置	
    ResultRank[Star0].center = { 269.5f, 330.0f };
	ResultRank[Star1].center = { 269.5f, 330.0f };
	ResultRank[Star2].center = { 269.5f, 330.0f };
	ResultRank[Star3].center = { 269.5f, 330.0f };

	TitleTo.center = { 89.5f, 11.0f };

    
}

void ResultBackReset() {
    currentFrame = 0;
    animTimer = 0.0f;

    TitleToFrame = 0;
    animTitleToTimer = 0.0f;

	TitleTo.scale = { 1.0f,1.0f };
	TitleToClicked = false;
}

void ResultBackUpdate(int mouX,int mouY,int *resultState) {
    animTimer += animSpeed;
	if (TitleToClicked)
	animTitleToTimer += animTitleToSpeed;

        static int prevMouseInput = 0;
        int currentMouseInput = GetMouseInput();
    // フレームを進める
    if (animTimer >= 1.0f) {
        animTimer -= 1.0f;
        currentFrame = (currentFrame + 1) % RESULT_ANIM_COUNT; // ループ
    }
    // フレームを進める
    if (animTitleToTimer >= 1.0f) {
        animTitleToTimer -= 1.0f;
        TitleToFrame = (TitleToFrame + 1) % RESULT_ANIM_COUNT; // ループ
    }
	int titletoWidth = 179 * TitleTo.scale.x; // タイトルへボタンの幅
    int titletoHeight = 22 * TitleTo.scale.y; // タイトルへボタンの高さ
    if (mouX > TitleTo.pos.x - titletoWidth/2 && mouX < TitleTo.pos.x + titletoWidth/2 &&
        mouY > TitleTo.pos.y - titletoHeight/2 && mouY < TitleTo.pos.y + titletoHeight/2)
    {


        if ((currentMouseInput & MOUSE_INPUT_LEFT) && !(prevMouseInput & MOUSE_INPUT_LEFT)) {
            TitleToClicked = true; 
            *resultState = 2;

        }

 

        TitleTo.scale = { 1.2f,1.2f };
        
    }
    else {
        TitleTo.scale = { 1.0f,1.0f };
    }
    prevMouseInput = currentMouseInput;
}

void ResultBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center,int score) {
    if (ResultAnimation[currentFrame] != -1) {
		DxPlus::Sprite::Draw(ResultAnimation[currentFrame], position, scale, center);
    }




    //スコアによって表示を変える
    if (score >= MIN_SCORE_FOR_3_STARS) {

        if (TitleToClicked) {
            DxPlus::Sprite::Draw(ResultStar3Animation[TitleToFrame], position, scale, center);
        }
        else
            DxPlus::Sprite::Draw(ResultRank[Star3].spriteID, ResultRank[Star3].pos, ResultRank[Star3].scale, ResultRank[Star3].center);
    }
    else if (score >= MIN_SCORE_FOR_2_STARS) {

        if (TitleToClicked) {
            DxPlus::Sprite::Draw(ResultStar2Animation[TitleToFrame], position, scale, center);
        }
        else
            DxPlus::Sprite::Draw(ResultRank[Star2].spriteID, ResultRank[Star2].pos, ResultRank[Star2].scale, ResultRank[Star2].center);
    }
    else if (score >= MIN_SCORE_FOR_1_STAR) {
     
        if (TitleToClicked) {
            DxPlus::Sprite::Draw(ResultStar1Animation[TitleToFrame], position, scale, center);
        }  
        else
            DxPlus::Sprite::Draw(ResultRank[Star1].spriteID, ResultRank[Star1].pos, ResultRank[Star1].scale, ResultRank[Star1].center);
    }
    else {
    
        if (TitleToClicked) {
            DxPlus::Sprite::Draw(ResultStar0Animation[TitleToFrame], position, scale, center);
        }   
        else
            DxPlus::Sprite::Draw(ResultRank[Star0].spriteID, ResultRank[Star0].pos, ResultRank[Star0].scale, ResultRank[Star0].center);
	}

	DxPlus::Sprite::Draw(TitleTo.spriteID, TitleTo.pos, TitleTo.scale, TitleTo.center);

    if (!TitleToClicked) {
        // スコアの描画
        wchar_t scoreText[16];
        swprintf(scoreText, sizeof(scoreText) / sizeof(wchar_t), L"%d", score);
        DxPlus::Text::DrawString(
            scoreText,
            { 450.0f,240.0f },
            GetColor(160, 82, 45),
            DxPlus::Text::TextAlign::MIDDLE_RIGHT,
            { 1.0f, 1.0f },
            0.0,
            fontID1
        );
    }

}

void AnimeSomething()
{
    const wchar_t* AniSome[ANI_SOMESHING_NUM] =
    {
        L"./Data/Images/re1.png",
        L"./Data/Images/re2.png",
        L"./Data/Images/re3.png",
        L"./Data/Images/re4.png",
        L"./Data/Images/re5.png",
    };

    for (int i = 0;i < ANI_SOMESHING_NUM;++i)
    {
        kari[i].spriteID = LoadGraph(AniSome[i]);
        if (kari[i].spriteID == -1)
        {
            DxPlus::Utils::FatalError((std::wstring(L"failed to laod sprite :")+AniSome[i]).c_str());
        }
    }
}


void AniSomethingUpdate(bool *gameplay)
{
    if (*gameplay)
    {
        int AniFrame = aniSomeFrame;
        if (aniSomeFrame < ANI_SOMESHING_NUM - 1)
        {
            aniSomeTimer += animSpeed * 3;
            if (aniSomeTimer >= 1.0f)
            {
                aniSomeTimer -= 1.0f;
                aniSomeFrame++;
            }
        }

        if (kari[AniFrame].spriteID != -1)
        {
            DxPlus::Sprite::Draw(kari[AniFrame].spriteID, { 640.0f, 360.0f },{ 0.5f, 0.5f },{ 0.0f, 0.0f });
        }
    }
    else
    {
        aniSomeTimer += aniSomeSpeed;
        if (aniSomeTimer >= 1.0f)
        {
            aniSomeTimer -= 1.0f;
            aniSomeFrame = (aniSomeFrame + 1) % ANI_SOMESHING_NUM;
        }
    }
    DrawFormatString(0, 0, GetColor(255, 255, 255), L"Frame: %d", aniSomeFrame);
}



void ResultBackDelete() {
    for (int i = 0; i < RESULT_ANIM_COUNT; ++i) {
        if (ResultAnimation[i] != -1) {
            DxPlus::Sprite::Delete(ResultAnimation[i]);
            ResultAnimation[i] = -1;
        }
    }
    for (int i = 0; i < RESULT_ANIM_COUNT; ++i) {
        if (ResultStar0Animation[i] != -1) {
            DxPlus::Sprite::Delete(ResultStar0Animation[i]);
            ResultStar0Animation[i] = -1;
        }
        if (ResultStar1Animation[i] != -1) {
            DxPlus::Sprite::Delete(ResultStar1Animation[i]);
            ResultStar1Animation[i] = -1;
        }
        if (ResultStar2Animation[i] != -1) {
            DxPlus::Sprite::Delete(ResultStar2Animation[i]);
            ResultStar2Animation[i] = -1;
        }
        if (ResultStar3Animation[i] != -1) {
            DxPlus::Sprite::Delete(ResultStar3Animation[i]);
            ResultStar3Animation[i] = -1;
        }
    }
}

