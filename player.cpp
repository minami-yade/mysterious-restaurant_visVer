#include "player.h"


Entity2D player[PLAYER_NUM];

const int PART_BODY            = 0;
const int PART_RIGHT_ARM       = 1;
const int PART_RIGHT_ARM_LONG  = 2;
const int PART_RIGHT_HAND      = 3;
const int PART_LEFT_ARM        = 4;
const int PART_LEFT_ARM_LONG   = 5;
const int PART_LEFT_HAND       = 6;
const int PART_ROD_RIGHT       = 7;
const int PART_ROD_LEFT        = 8;

DxPlus::Vec2 playerBasePosition = {
    DxPlus::CLIENT_WIDTH / 2.0f,
    DxPlus::CLIENT_HEIGHT - 195.0f
};

void PlayerImage()
{
    // 体の画像
    player[PART_BODY].spriteID = LoadGraph(L"./Data/images/character.png");
    if (player[PART_BODY].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/character.png");
    }

    // 右腕の画像
    player[PART_RIGHT_ARM].spriteID = LoadGraph(L"./Data/images/left.png");
    if (player[PART_RIGHT_ARM].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/left.png");
    }

    // 右腕長（追加）
    player[PART_RIGHT_ARM_LONG].spriteID = LoadGraph(L"./Data/images/left_arm.png");
    if (player[PART_RIGHT_ARM_LONG].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/left_arm.png");
    }

    // 右手の画像
    player[PART_RIGHT_HAND].spriteID = LoadGraph(L"./Data/images/left_hand.png");
    if (player[PART_RIGHT_HAND].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/left_hand.png");
    }

    // 左腕の画像
    player[PART_LEFT_ARM].spriteID = LoadGraph(L"./Data/images/right.png");
    if (player[PART_LEFT_ARM].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/right.png");
    }

    // 左腕長（追加）
    player[PART_LEFT_ARM_LONG].spriteID = LoadGraph(L"./Data/images/right_arm.png");
    if (player[PART_LEFT_ARM_LONG].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/right_arm.png");
    }

    // 左手の画像
    player[PART_LEFT_HAND].spriteID = LoadGraph(L"./Data/images/right_hand.png");
    if (player[PART_LEFT_HAND].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/right_hand.png");
    }

    // 右の釣り竿の画像
    player[PART_ROD_RIGHT].spriteID = LoadGraph(L"./Data/images/facing_right.png");
    if (player[PART_ROD_RIGHT].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/facing_right.png");
    }

    // 左の釣り竿の画像
    player[PART_ROD_LEFT].spriteID = LoadGraph(L"./Data/images/facing_left.png");
    if (player[PART_ROD_LEFT].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/facing_left.png");
    }
}

void PlayerReset() {
    DxPlus::Vec2 Armoffset = { 37.0f,-52.0f };
    DxPlus::Vec2 LongArmoffset = { 33.5f,-43.0f };
	DxPlus::Vec2 Handoffset = { 108.0f,-50.0f };

    for (int i = 0; i < PLAYER_NUM; ++i) {
        switch (i) {
         
         
        case PART_BODY: 
        
            player[i].position = { playerBasePosition.x,
                                   playerBasePosition.y + 147.0f };
            // 足元基準（ボディ）
            player[i].Center    = { 84.0f, 294.0f };
            player[i].scale     = { 1.0f, 1.0f };
            break;

        case PART_RIGHT_ARM:
            player[i].position  = { playerBasePosition.x - Armoffset.x,
                                    playerBasePosition.y - Armoffset.y };
            player[i].Center    = { 84.0f, 23.0f };
            player[i].scale     = { 1.0f, 1.0f };
            break;

        case PART_RIGHT_ARM_LONG:
            player[i].position  = { playerBasePosition.x - LongArmoffset.x,
                                    playerBasePosition.y - LongArmoffset.y };
            player[i].Center    = { 100.0f, 56.0f };
            player[i].scale     = { 1.0f, 1.0f };
            break;

        case PART_RIGHT_HAND:
            player[i].position = { playerBasePosition.x - LongArmoffset.x - Handoffset.x,
                                   playerBasePosition.y - LongArmoffset.y + Handoffset.y };
            player[i].Center   = { 18.5f, 18.0f };
            player[i].scale    = { 1.0f, 1.0f };
            break;

        case PART_LEFT_ARM:
            player[i].position = { playerBasePosition.x + Armoffset.x,
                                   playerBasePosition.y - Armoffset.y };
            player[i].Center   = { 0.0f, 23.0f };
            player[i].scale    = { 1.0f, 1.0f };
            break;

        case PART_LEFT_ARM_LONG:
            player[i].position = { playerBasePosition.x + LongArmoffset.x,
                                   playerBasePosition.y - LongArmoffset.y };
            player[i].Center   = { 0.0f, 56.0f };
            player[i].scale    = { 1.0f, 1.0f };
            break;

        case PART_LEFT_HAND:
            player[i].position = { playerBasePosition.x + LongArmoffset.x + Handoffset.x,
                                   playerBasePosition.y - LongArmoffset.y + Handoffset.y };
            player[i].Center   = { 18.5f, 18.0f };
            player[i].scale    = { 1.0f, 1.0f };
            break;

        case PART_ROD_RIGHT:
            player[i].position = { player[PART_LEFT_HAND].position.x,
                                    player[PART_LEFT_HAND].position.y};
            player[i].Center   = { 18.0f, 180.0f };
            player[i].scale    = { 1.0f, 1.0f };
            break;

        case PART_ROD_LEFT:
            player[i].position = { player[PART_RIGHT_HAND].position.x,
                                    player[PART_RIGHT_HAND].position.y };
            player[i].Center   = { 120.0f, 180.0f };
            player[i].scale    = { 1.0f, 1.0f };
            break;

        default:
            DxPlus::Utils::FatalError(L"playerの体配置にエラー");
            break;
        }
    }
}

void PlayerDraw(bool right) {
   if(right){
       // 右向き
       DxPlus::Sprite::Draw(player[PART_BODY].spriteID, player[PART_BODY].position, player[PART_BODY].scale, player[PART_BODY].Center);
       DxPlus::Sprite::Draw(player[PART_LEFT_HAND].spriteID, player[PART_LEFT_HAND].position, player[PART_LEFT_HAND].scale, player[PART_LEFT_HAND].Center);
       DxPlus::Sprite::Draw(player[PART_LEFT_ARM_LONG].spriteID, player[PART_LEFT_ARM_LONG].position, player[PART_LEFT_ARM_LONG].scale, player[PART_LEFT_ARM_LONG].Center);
       DxPlus::Sprite::Draw(player[PART_RIGHT_ARM].spriteID, player[PART_RIGHT_ARM].position, player[PART_RIGHT_ARM].scale, player[PART_RIGHT_ARM].Center);
       DxPlus::Sprite::Draw(player[PART_RIGHT_ARM].spriteID, player[PART_RIGHT_ARM].position, player[PART_RIGHT_ARM].scale, player[PART_RIGHT_ARM].Center);
       DxPlus::Sprite::Draw(player[PART_ROD_RIGHT].spriteID, player[PART_ROD_RIGHT].position, player[PART_ROD_RIGHT].scale, player[PART_ROD_RIGHT].Center);
   }
   else {
       // 左向き
       DxPlus::Sprite::Draw(player[PART_BODY].spriteID, player[PART_BODY].position, player[PART_BODY].scale, player[PART_BODY].Center);
       DxPlus::Sprite::Draw(player[PART_RIGHT_HAND].spriteID, player[PART_RIGHT_HAND].position, player[PART_RIGHT_HAND].scale, player[PART_RIGHT_HAND].Center);
       DxPlus::Sprite::Draw(player[PART_RIGHT_ARM_LONG].spriteID, player[PART_RIGHT_ARM_LONG].position, player[PART_RIGHT_ARM_LONG].scale, player[PART_RIGHT_ARM_LONG].Center);
       DxPlus::Sprite::Draw(player[PART_LEFT_ARM].spriteID, player[PART_LEFT_ARM].position, player[PART_LEFT_ARM].scale, player[PART_LEFT_ARM].Center);
       DxPlus::Sprite::Draw(player[PART_LEFT_ARM].spriteID, player[PART_LEFT_ARM].position, player[PART_LEFT_ARM].scale, player[PART_LEFT_ARM].Center);
       DxPlus::Sprite::Draw(player[PART_ROD_LEFT].spriteID, player[PART_ROD_LEFT].position, player[PART_ROD_LEFT].scale, player[PART_ROD_LEFT].Center);
   }
}

void PlayerDelete() {
    for (int i = 0; i < PLAYER_NUM; ++i) {
        if (player[i].spriteID != -1) {
            DxPlus::Sprite::Delete(player[i].spriteID);
            player[i].spriteID = -1;
        }
    }
}