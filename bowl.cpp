#include "bowl.h"

Entity2D bowl;
Entity2D bowlEffect[BOWL_EFFECT_NUM];

// --- 画像読み込み関係 ---
void bowlImage() {

    // bowlの画像
    bowl.spriteID = LoadGraph(L"./Data/images/bowl.png");
    if (bowl.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/bowl.png");
    }
    for (size_t i = 0; i < BOWL_EFFECT_NUM; ++i) {
        switch (i)
        {
        case 0://ニンジン
            bowlEffect[i].effectID = LoadGraph(L"./Data/images/carrot.png");
            if (bowlEffect[i].effectID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/carrot.png");
            }
            break;

        case 1://ピーマン
            bowlEffect[i].effectID = LoadGraph(L"./Data/images/pepper.png");
            if (bowlEffect[i].effectID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/pepper.png");
            }
            break;

        case 2://とまと
            bowlEffect[i].effectID = LoadGraph(L"./Data/images/tomato.png");
            if (bowlEffect[i].effectID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/tomato.png");
            }
            break;

        default:
            DxPlus::Utils::FatalError(L"bowl.h reset error");

            break;
        }

    }
}

// --- リセット関数（初期配置や状態の初期化） ---
void bowlReset() {
    bowl.position = { DxPlus::CLIENT_WIDTH / 2.0f, DxPlus::CLIENT_HEIGHT - 48.0f };
    bowl.scale = { 0.75f,0.75f };
    bowl.center = { 76.0f ,60.0f };//中心のbottom
    bowl.radius = 50.0f;

}

void checkbowlCollider(Entity2D& entity,int i) {


    // 2点間の距離を計算
    float dx = bowl.position.x - entity.position.x;
    float dy = bowl.position.y - entity.position.y;
    float distanceSq = dx * dx + dy * dy;

    // 半径の合計
    float radiusSum = bowl.radius + entity.radius;

    // 当たり判定
    if (distanceSq <= radiusSum * radiusSum)
    {
        // 当たっている
        Score(entity.havescore); // スコア加算
		entity.isActive = false; // 非アクティブにする
		entity.position = { -100,-100 };//画面外へ
		entity.moveVegetable = 0;
        entity.moveenemy = 1;
		entity.velocity = { 0,0 };
    }

}

// --- 描画関数 ---
void bowlDraw() {
    DxPlus::Sprite::Draw(bowl.spriteID, bowl.position, bowl.scale, bowl.center);
}

// --- 解放関数 ---
void bowlDelete() {
    if (bowl.spriteID != -1) {
        DxPlus::Sprite::Delete(bowl.spriteID);
        bowl.spriteID = -1;
    }
}
