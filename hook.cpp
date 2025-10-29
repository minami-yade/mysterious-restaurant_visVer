#include "hook.h"
#include "vegetable.h"
#include "Enemy.h"
#include"vol.h"


Entity2D hook;
extern Entity2D player[PLAYER_NUM];
extern Entity2D vegetable[VEGETABLE_NUM];

HookState hookState = Idle;

int vol_hook;
int vol_bowl_back;



// --- 画像読み込み関係 ---
void hookImage()
{

    hook.spriteID = LoadGraph(L"./Data/images/hook_png.png");
    if (hook.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/hook_png.png");
    }
    //ついでにサウンド
    vol_hook = DxLib::LoadSoundMem(L"./Data/Sounds/fish.mp3");
    if (vol_hook == -1)
    {
        DxPlus::Utils::FatalError(L"./Data/Sound/fish.mp3");
    } 
    //vol_bowl_back = DxLib::LoadSoundMem(L"./Data/Sounds/Push.mp3");
    //if (vol_bowl_back == -1)
    //{
    //    DxPlus::Utils::FatalError(L"./Data/Sound/Push.mp3");
    //}
}

// --- リセット関数（初期配置や状態の初期化） ---
void hookReset(DxPlus::Vec2 playerBasePosition)
{
    int Xoffset = 195;
    int Yoffset = 138;

    hook.HomePositionLeft.x = playerBasePosition.x - Xoffset;
    hook.HomePositionLeft.y = playerBasePosition.y - Yoffset;

    hook.HomePositionRight.x = playerBasePosition.x + Xoffset;
    hook.HomePositionRight.y = playerBasePosition.y - Yoffset;

    hook.position = hook.HomePositionRight;
    hook.target = hook.HomePositionRight;

    hook.scale = { 0.5f, 0.5f };
    hook.center = { 49.0f, 62.0f };
    hook.velocity = { 0.0f, 0.0f };
    hook.gravity = 0.98f;

    hook.reachedUpHook = false;
    hook.upHookLeft = { hook.HomePositionLeft.x, DxPlus::CLIENT_HEIGHT - 48 - 50 };
    hook.upHookRight = { hook.HomePositionRight.x, DxPlus::CLIENT_HEIGHT - 48 - 50 };

    hook.angle = 12;
    hookState = Idle;

    ChangeVolumeSoundMem((int)GetVolume(), vol_hook);
}



void Updatehook(float deltaTime, int x, int y, DxPlus::Vec2 pointer, bool left)
{
    pointer = { static_cast<float>(x), static_cast<float>(y) };

    hook.angle += 0.3f;//回転




    if (hookState == Idle)
    {
        hook.position = left ? hook.HomePositionRight : hook.HomePositionLeft;
        hook.velocity = { 0.0f, 0.0f };

    }
    for (int i = 0; i < VEGETABLE_NUM; ++i)
    {
        if (vegetable[i].moveVegetable == 1) {
            hook.reachedUpHook = true;
            hookState = Returning;
        }
    }

    int mouseInput = DxLib::GetMouseInput();
    static int prevMouseInput = 0;

    // 左クリックが「今押されていて、前フレームは押されていなかった」＝押した瞬間
    if ((mouseInput & MOUSE_INPUT_LEFT) && !(prevMouseInput & MOUSE_INPUT_LEFT)) {
       
        if (hookState == FlyingOut)//飛んでる時に押したら
        {

            if (hook.position.y > DxPlus::CLIENT_HEIGHT - 48.0f)//地面
                hookState = Returning;//もどる
            if (hookState == Returning)
            {
                //PlaySoundMem(vol_bowl_back, DX_PLAYTYPE_BACK);
            }

        }

        if
            (hookState == Idle)//止まってる時に押したら
        { //sound
        PlaySoundMem(vol_hook, DX_PLAYTYPE_BACK);
            DxPlus::Vec2 dir = pointer - hook.position;
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len > 1.0f)
            {
                dir.x /= len;
                dir.y /= len;
                float launchSpeed = 30.0f; // 初速
                hook.velocity = { dir.x * launchSpeed / 2, dir.y * launchSpeed };
                hook.reachedUpHook = false;
                hookState = FlyingOut;
            }
        }


    }



    if (hookState == Returning)
    {
        DxPlus::Vec2 CheckPoint = !hook.reachedUpHook
            ? (left ? hook.upHookRight : hook.upHookLeft)
            : (left ? hook.HomePositionRight : hook.HomePositionLeft);

        DxPlus::Vec2 dir = CheckPoint - hook.position;
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);

        if (len > 20.0f) // まだ遠い
        {
            dir.x /= len;
            dir.y /= len;
            float returnSpeed = 40.0f;
            hook.velocity = { dir.x * returnSpeed, dir.y * returnSpeed };
        }
        else // 近づいたら
        {
            if (!hook.reachedUpHook) {
                hook.reachedUpHook = true; // upHook に到達 → 次は Home へ
            }
            else {
                hookState = Idle; // Home に到達 → 終了
            }
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


void checkHookCollider(const DxPlus::Vec2& targetPos, float targetRadius, int i, bool veg)
{
    float hookRadius = 10.0f;            // フックの半径

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
        if (veg)
            onHookHit(targetPos, &hook, i);
        else
            onHookEnemyHit(targetPos, &hook, i);
    }
}



// --- 描画関数 ---
void hookDraw(bool left)
{
    DxPlus::Sprite::Draw(hook.spriteID, hook.position, hook.scale, hook.center, hook.angle);


    // 糸の描画（ベジェ曲線でたわみを表現）


    float time = static_cast<float>(DxLib::GetNowCount()) / 1000.0f; // 秒単位の時間

    DxPlus::Vec2 start = left ? hook.HomePositionRight : hook.HomePositionLeft;
    DxPlus::Vec2 end = hook.position;

    float length = std::sqrt((end - start).x * (end - start).x + (end - start).y * (end - start).y);
    float swayAmount = std::min(40.0f, length * 0.2f);

    // 中間点：
    DxPlus::Vec2 mid = (start + end) * 0.5f;
    mid.y += swayAmount;
    mid.x += std::sin(time * 6.0f) * 8.0f; // 横揺れ

    const int segmentCount = 24;
    for (int i = 0; i < segmentCount; ++i) {
        float t1 = static_cast<float>(i) / segmentCount;
        float t2 = static_cast<float>(i + 1) / segmentCount;

        auto bezier = [](const DxPlus::Vec2& p0, const DxPlus::Vec2& p1, const DxPlus::Vec2& p2, float t) {
            float u = 1.0f - t;
            return p0 * (u * u) + p1 * (2 * u * t) + p2 * (t * t);
            };

        DxPlus::Vec2 p1 = bezier(start, mid, end, t1);
        DxPlus::Vec2 p2 = bezier(start, mid, end, t2);

        DrawLine(static_cast<int>(p1.x), static_cast<int>(p1.y),
            static_cast<int>(p2.x), static_cast<int>(p2.y),
            GetColor(0, 0, 0));
    }
}

// --- 解放関数 ---
void hookDelete()
{
    if (hook.spriteID != -1) {
        DxPlus::Sprite::Delete(hook.spriteID);
        hook.spriteID = -1;
    }
    //ついでにサウンド
 
    if (vol_hook == -1) {
        DxPlus::Utils::FatalError(L"./Data/Sounds/Push.mp3");
    }


}
