#include "Back.h"
#include "Entity2D.h"

Entity2D titleBack;
Entity2D gameBack;
Entity2D gameFloor;

void TitleBackImage() {
    titleBack.spriteID = LoadGraph(L"./Data/images/Title.png");
    if (titleBack.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/Title.png");
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

void TitleBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center) {
    DxPlus::Sprite::Draw(titleBack.spriteID, position, scale, center);
}

void GameBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center) {
    DxPlus::Sprite::Draw(gameBack.spriteID,position, scale, center);
}

void GameFloorDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center) {
    DxPlus::Sprite::Draw(gameFloor.spriteID, position, scale, center);
}

void TitleBackDelete() {
    DxPlus::Sprite::Delete(titleBack.spriteID);
}

void GameBackDelete() {
    DxPlus::Sprite::Delete(gameBack.spriteID);
}
