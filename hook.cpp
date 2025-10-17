#include "hook.h"
#include "vegetable.h"

Entity2D hook;
extern Entity2D player[PLAYER_NUM];

HookState hookState = Idle;


// --- 画像読み込み関係 ---
void hookImage()
{

    hook.spriteID = LoadGraph(L"./Data/images/hook_png.png");
    if (hook.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/hook_png.png");
    }

}

// --- リセット関数（初期配置や状態の初期化） ---
void hookReset(DxPlus::Vec2 playerBasePosition)
{
    int Xoffset = 200;
    int Yoffset = 136;

    hook.HomePositionLeft.x = playerBasePosition.x - Xoffset;
    hook.HomePositionLeft.y = playerBasePosition.y - Yoffset;

	hook.HomePositionRight.x = playerBasePosition.x + Xoffset;
    hook.HomePositionRight.y = playerBasePosition.y - Yoffset;
    hook.position = hook.HomePositionRight;
	hook.target = hook.HomePositionRight;

	hook.scale = { 0.5f,0.5f };
	hook.center = { 49.0f, 62.0f };
	hook.velocity = { 0.0f, 0.0f };
	hook.gravity = 0.98f;

    hook.angle = 12;
}



void Updatehook(float deltaTime, int x, int y, DxPlus::Vec2 pointer, bool left)
{
    DxLib::GetMousePoint(&x, &y);
    pointer = { static_cast<float>(x), static_cast<float>(y) };

    hook.angle += 0.3f;//回転

    if (hookState == Idle)
    {
        hook.position = left ? hook.HomePositionRight : hook.HomePositionLeft;
        hook.velocity = { 0.0f, 0.0f };
    }

    int mouseInput = DxLib::GetMouseInput();
    static int prevMouseInput = 0;

    // 左クリックが「今押されていて、前フレームは押されていなかった」＝押した瞬間
    if ((mouseInput & MOUSE_INPUT_LEFT) && !(prevMouseInput & MOUSE_INPUT_LEFT)) {

        if (hookState == FlyingOut)//飛んでる時に押したら
        {
            hookState = Returning;//もどる
        }

		if (hookState == Idle)//止まってる時に押したら
        {
            DxPlus::Vec2 dir = pointer - hook.position;
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len > 1.0f)
            {
                dir.x /= len;
                dir.y /= len;
                float launchSpeed = 30.0f; // 初速
                hook.velocity = { dir.x * launchSpeed/2, dir.y * launchSpeed };
                hookState = FlyingOut;
            }
        }

    }
    if (hookState == Returning) //戻る処理
    {

        DxPlus::Vec2 home = left ? hook.HomePositionRight : hook.HomePositionLeft;//右か左に戻る
        DxPlus::Vec2 dir = home - hook.position;;//差
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);;
		if (len > 20.0f)//遠いなら
        {
            if (hook.position.x == home.x) {
				hook.position.y += 5.0f;
            }
            else {
                dir.x /= len;
                dir.y /= len;
                float returnSpeed = 3.5f;//戻る早さ
                hook.velocity = { dir.x * returnSpeed, dir.y * returnSpeed };
               

            }
        }
        else //近いなら
        {
            hookState = Idle;
        }

    }





    //仮
    // 画面外に出たら強制的に戻すにする
    if (hook.position.x < 0 || hook.position.x > DxPlus::CLIENT_WIDTH 
        || hook.position.y < 0 || hook.position.y > DxPlus::CLIENT_HEIGHT - 48.0f)
    {
		if (hook.position.y < 0) hook.position.y = 0;
		if (hook.position.y > DxPlus::CLIENT_HEIGHT - 48.0f) hook.position.y = DxPlus::CLIENT_HEIGHT - 48.0f;
		if (hook.position.x < 0) hook.position.x = 0;
		if (hook.position.x > DxPlus::CLIENT_WIDTH) hook.position.x = DxPlus::CLIENT_WIDTH;
        //↑超えないようにするため

        hook.velocity = { 0,0 };//いらない移動を削除

		//hookState = Returning;　//これを消すと端に行っても止まる
    }

    // 飛んでいる間は重力を加算
    if (hookState == FlyingOut)
    {
        hook.velocity.y += hook.gravity * deltaTime;
    }
    // -----------------

    // 物理っぽい移動（減速あり）
    if (hookState == FlyingOut || hookState == Returning)
    {
        hook.position.x += hook.velocity.x * deltaTime;
        hook.position.y += hook.velocity.y * deltaTime;
    }

    prevMouseInput = mouseInput; // 状態を更新
}


void checkHookCollider(const DxPlus::Vec2& targetPos, float targetRadius,int i)
{

    float hookRadius = 10.0f;            // フックの半径（任意）

    // 2点間の距離を計算
    float dx = hook.position.x - targetPos.x;
    float dy = hook.position.y - targetPos.y;
    float distanceSq = dx * dx + dy * dy;

    // 半径の合計
    float radiusSum = hookRadius + targetRadius;

    // 当たり判定
    if (distanceSq <= radiusSum * radiusSum)
    {
        // 当たっている
        onHookHit(targetPos,&hook,&player[0], i); // ヒット時の処理（例：敵にダメージなど）
    }
}



// --- 描画関数 ---
void hookDraw()
{
    DxPlus::Sprite::Draw(hook.spriteID, hook.position, hook.scale, hook.center,hook.angle);

}

// --- 解放関数 ---
void hookDelete()
{

}
