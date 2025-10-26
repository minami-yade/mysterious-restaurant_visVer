#include "player.h"


Entity2D player[PLAYER_NUM];
enum PartType {
    PART_BODY_DEF,
    PART_BODY_HAP,
    PART_BODY_SAD,
    PART_RIGHT_ARM,
    PART_RIGHT_ARM_LONG,
    PART_RIGHT_HAND,
    PART_LEFT_ARM,
    PART_LEFT_ARM_LONG,
    PART_LEFT_HAND,
    PART_ROD_RIGHT,
    PART_ROD_LEFT,
};

const float playerSize = 0.75f;


DxPlus::Vec2 playerBasePosition = {
    DxPlus::CLIENT_WIDTH / 2.0f,
	DxPlus::CLIENT_HEIGHT - 145.0f* playerSize - 48.0f
};

void PlayerImage()
{
    // 体の画像
    player[PART_BODY_DEF].spriteID = LoadGraph(L"./Data/images/normal.png");
    if (player[PART_BODY_DEF].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/normal.png");
    }
    player[PART_BODY_HAP].spriteID = LoadGraph(L"./Data/images/happy.png");
    if (player[PART_BODY_HAP].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/happy.png");
    }
    player[PART_BODY_SAD].spriteID = LoadGraph(L"./Data/images/sad.png");
    if (player[PART_BODY_SAD].spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/sad.png");
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

        player[i].scale = { playerSize, playerSize };

        switch (i) {

        case PART_BODY_DEF:
            player[i].position = {
                playerBasePosition.x,
                playerBasePosition.y + 147.0f * player[i].scale.y
            };
            player[i].center = { 84.0f, 294.0f };
            break;

        case PART_BODY_HAP:
            player[i].position = {
                playerBasePosition.x,
                playerBasePosition.y + 147.0f * player[i].scale.y
            };
            player[i].center = { 84.0f, 294.0f };
            break;

        case PART_BODY_SAD:
            player[i].position = {
                playerBasePosition.x,
                playerBasePosition.y + 147.0f * player[i].scale.y
            };
            player[i].center = { 84.0f, 294.0f };
            break;

        case PART_RIGHT_ARM:
            player[i].position = {
                playerBasePosition.x - Armoffset.x * player[i].scale.x,
                playerBasePosition.y - Armoffset.y * player[i].scale.y
            };
            player[i].center = { 84.0f, 23.0f };
            break;

        case PART_RIGHT_ARM_LONG:
            player[i].position = {
                playerBasePosition.x - LongArmoffset.x * player[i].scale.x,
                playerBasePosition.y - LongArmoffset.y * player[i].scale.y
            };
            player[i].center = { 100.0f, 56.0f };
            break;

        case PART_RIGHT_HAND:
            player[i].position = {
                playerBasePosition.x - (LongArmoffset.x + Handoffset.x) * player[i].scale.x,
                playerBasePosition.y - LongArmoffset.y * player[i].scale.y + Handoffset.y * player[i].scale.y
            };
            player[i].center = { 18.5f, 18.0f };
            break;

        case PART_LEFT_ARM:
            player[i].position = {
                playerBasePosition.x + Armoffset.x * player[i].scale.x,
                playerBasePosition.y - Armoffset.y * player[i].scale.y
            };
            player[i].center = { 0.0f, 23.0f };
            break;

        case PART_LEFT_ARM_LONG:
            player[i].position = {
                playerBasePosition.x + LongArmoffset.x * player[i].scale.x,
                playerBasePosition.y - LongArmoffset.y * player[i].scale.y
            };
            player[i].center = { 0.0f, 56.0f };
            break;

        case PART_LEFT_HAND:
            player[i].position = {
                playerBasePosition.x + (LongArmoffset.x + Handoffset.x) * player[i].scale.x,
                playerBasePosition.y - LongArmoffset.y * player[i].scale.y + Handoffset.y * player[i].scale.y
            };
            player[i].center = { 18.5f, 18.0f };
            break;

        case PART_ROD_RIGHT:
            player[i].position = player[PART_LEFT_HAND].position;
            player[i].center = { 18.0f, 180.0f };
            break;

        case PART_ROD_LEFT:
            player[i].position = player[PART_RIGHT_HAND].position;
            player[i].center = { 120.0f, 180.0f };
            break;

        default:
            DxPlus::Utils::FatalError(L"playerの体配置にエラー");
            break;
        }
    }
}
// 表情フラグ
extern bool isHap;
extern bool isSad;

void PlayerDraw(bool right) {
   if(right){
       // 右向き
       DxPlus::Sprite::Draw(player[PART_LEFT_HAND].spriteID, player[PART_LEFT_HAND].position, player[PART_LEFT_HAND].scale, player[PART_LEFT_HAND].center);
       DxPlus::Sprite::Draw(player[PART_LEFT_ARM_LONG].spriteID, player[PART_LEFT_ARM_LONG].position, player[PART_LEFT_ARM_LONG].scale, player[PART_LEFT_ARM_LONG].center);
       DxPlus::Sprite::Draw(player[PART_RIGHT_ARM].spriteID, player[PART_RIGHT_ARM].position, player[PART_RIGHT_ARM].scale, player[PART_RIGHT_ARM].center);
       DxPlus::Sprite::Draw(player[PART_RIGHT_ARM].spriteID, player[PART_RIGHT_ARM].position, player[PART_RIGHT_ARM].scale, player[PART_RIGHT_ARM].center);
       DxPlus::Sprite::Draw(player[PART_ROD_RIGHT].spriteID, player[PART_ROD_RIGHT].position, player[PART_ROD_RIGHT].scale, player[PART_ROD_RIGHT].center);
   }
   else {
       // 左向き
       DxPlus::Sprite::Draw(player[PART_RIGHT_HAND].spriteID, player[PART_RIGHT_HAND].position, player[PART_RIGHT_HAND].scale, player[PART_RIGHT_HAND].center);
       DxPlus::Sprite::Draw(player[PART_RIGHT_ARM_LONG].spriteID, player[PART_RIGHT_ARM_LONG].position, player[PART_RIGHT_ARM_LONG].scale, player[PART_RIGHT_ARM_LONG].center);
       DxPlus::Sprite::Draw(player[PART_LEFT_ARM].spriteID, player[PART_LEFT_ARM].position, player[PART_LEFT_ARM].scale, player[PART_LEFT_ARM].center);
       DxPlus::Sprite::Draw(player[PART_LEFT_ARM].spriteID, player[PART_LEFT_ARM].position, player[PART_LEFT_ARM].scale, player[PART_LEFT_ARM].center);
       DxPlus::Sprite::Draw(player[PART_ROD_LEFT].spriteID, player[PART_ROD_LEFT].position, player[PART_ROD_LEFT].scale, player[PART_ROD_LEFT].center);
   }

   //表情
   int OjiFace = PART_BODY_DEF;
   static float isFaceTimer = 0.0f;
   if (isFaceTimer > 90.0f) {//１．５秒経過で元に戻る
	   isHap = false;
	   isSad = false;
	   isFaceTimer = 0.0f;
   }
   if(isHap){
       OjiFace = PART_BODY_HAP;
       isFaceTimer++;
   }
   else if(isSad){
       OjiFace = PART_BODY_SAD;
       isFaceTimer++;
   }
   else {
       OjiFace = PART_BODY_DEF;
   }
   DxPlus::Sprite::Draw(player[OjiFace].spriteID, player[OjiFace].position, player[OjiFace].scale, player[OjiFace].center);
}

void PlayerDelete() {
    for (int i = 0; i < PLAYER_NUM; ++i) {
        if (player[i].spriteID != -1) {
            DxPlus::Sprite::Delete(player[i].spriteID);
            player[i].spriteID = -1;
        }
    }
}