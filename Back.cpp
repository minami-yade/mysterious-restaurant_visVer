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

// アニメーション用
float titleBackAnimTimer = 0.0f;
int titleBackAnimFrame = 0;
float titleBackAnimSpeed = 0.03f; // 秒（小さいほど）
bool gamePlay;

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
        titleBack[j].spriteID = LoadGraph(BacksPaths[j]);
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


 
   


void GameBackImage() {
    gameBack.spriteID = LoadGraph(L"./Data/images/haikei.png");
    if (gameBack.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/haikei.png");
    }
    gameFloor.spriteID = LoadGraph(L"./Data/images/front_lane.png");
    if (gameFloor.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/front_lane.png");
    }

}

void TitleBackReset() {
    gamePlay = false;
}

void GameBackReset() {

}

void TitleBackUpdate() 
{

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

void TitleBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center, bool start, bool set, bool fin) {
    // タイトル背景アニメーション描画
    if (gamePlay) {
        // タイトルプレイアニメーション描画
        int playFrame = titleBackAnimFrame % TITLE_BACKPLAY_NUM;
        if (TitlePlay[playFrame].spriteID != -1) {
            DxPlus::Sprite::Draw(TitlePlay[playFrame].spriteID, position, scale, center);
        }
    }
    else {
        int frame = titleBackAnimFrame % TITLE_BACK_NUM;
        if (titleBack[frame].spriteID != -1) {

            DxPlus::Sprite::Draw(titleBack[frame].spriteID, position, scale, center);
        }
    }

    // ボタン描画


    for (int i = 0; i < TITLE_BUTTON_NUM; ++i) {
        if (Button[i].spriteID != -1) {
            DxPlus::Vec2 offset;
            DxPlus::Vec2 scale;

            if (i == 0) { // タイトルロゴ
                offset = { -50.0f, 50.0f };
                scale = { 0.5f, 0.5f };
            }
            else { // その他のボタン
                offset = { 100.0f, 80.0f + i * 144.0f };
                scale = { 0.9f, 0.9f };
            }
           
\
            float alpha = 255.0f;
            float crick = 100.0f;
            if (start && i == 1) { 
                alpha = crick; // 暗く
            }
            if (set && i == 2) {
                alpha = crick;
            }
            if(fin && i == 3) {
                alpha = crick;
			}

            DxPlus::Sprite::Draw(Button[i].spriteID, buttonBase + offset, scale, { 0.0f, 0.0f },0.0f, GetColor(alpha,alpha,alpha));
        }
    }


    // アニメーション更新
    titleBackAnimTimer += titleBackAnimSpeed; 
    if (titleBackAnimTimer >= 1.0f) { 
        titleBackAnimTimer -= 1.0f;
        titleBackAnimFrame = (titleBackAnimFrame + 1) % TITLE_BACK_NUM;
    }
}

void GameBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center) {
    DxPlus::Sprite::Draw(gameBack.spriteID,position, scale, center);
}

void GameFloorDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center) {
    DxPlus::Sprite::Draw(gameFloor.spriteID, position, scale, center);
}

void TitleBackDelete() {
    
}

void GameBackDelete() {
    if (gameBack.spriteID != -1) {
        DxPlus::Sprite::Delete(gameBack.spriteID);
    }
}
