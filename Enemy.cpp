#include "Enemy.h"
#include "AllManager.h"

// --------------------------------------------------
// Enemy.cpp - エネミー（UFO含む）処理
// --------------------------------------------------

Entity2D enemy[ENEMY_NUM];
extern Entity2D hook;
extern Entity2D vegetable[VEGETABLE_NUM];

int mouseAnimDeg[MOUSE_ANIM_NUM] = {};
int ufoAnimDeg[UFO_ANIM_NUM] = {};
int ufoSprite = -1;

const int UFO_SPAWN_PERCENT = 100;
const float MOUSE_ANIM_INTERVAL = 3.0f;
const float UFO_MOVE_SPEED = 3.0f;
const float UFO_LIGHT_INTERVAL = 3.0f;

const float UFO_DROP_DURATION = 10.0f;
const float UFO_DROP_DISTANCE = 120.0f;
const float UFO_ASCEND_SPEED = 240.0f;
const float DEFAULT_FADE_SPEED = 1.5f;

const float UFO_HIT_RADIUS = 48.0f;
const float VEG_HIT_RADIUS = 40.0f;

const float UFO_FALL_SPEED = 30.0f;
const float UFO_FALL_ROT_SPEED = 720.0f;

void EnemyImage()
{
    const wchar_t* paths[MOUSE_ANIM_NUM] = {
        L"./Data/images/1.png",
        L"./Data/images/2.png",
        L"./Data/images/3.png",
        L"./Data/images/4.png"
    };
    const wchar_t* ufoPaths[UFO_ANIM_NUM] = {
        L"./Data/images/light1.png",
        L"./Data/images/light2.png",
        L"./Data/images/light3.png",
    };
    const wchar_t* ufoSpritePath = L"./Data/images/ufo.png";

    for (int j = 0; j < MOUSE_ANIM_NUM; ++j)
    {
        mouseAnimDeg[j] = LoadGraph(paths[j]);
        if (mouseAnimDeg[j] == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + paths[j]).c_str());
        }
    }
    for (int j = 0; j < UFO_ANIM_NUM; ++j)
    {
        ufoAnimDeg[j] = LoadGraph(ufoPaths[j]);
        if (ufoAnimDeg[j] == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + ufoPaths[j]).c_str());
        }
    }

    ufoSprite = LoadGraph(ufoSpritePath);
    if (ufoSprite == -1) {
        DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + ufoSpritePath).c_str());
    }

    for (int i = 0; i < ENEMY_NUM; ++i)
    {
        if (enemy[i].mouseAnim < 0 || enemy[i].mouseAnim >= MOUSE_ANIM_NUM) enemy[i].mouseAnim = 0;
        enemy[i].spriteID = mouseAnimDeg[enemy[i].mouseAnim];
    }
}

void EnemyReset()
{
    for (int i = 0; i < ENEMY_NUM; ++i)
    {
        enemy[i].isActive = false;
        enemy[i].havescore = 50;

        switch (i % ENEMY_TYPE) {
        case 0:
            enemy[i].scale = { 0.7f, 0.7f };
            enemy[i].center = { 80.0f, 79.0f };
            enemy[i].speed = 0.7f;
            enemy[i].moveenemy = 0;
            enemy[i].havescore = -100;
            enemy[i].helpEnemy = false;
            enemy[i].mouseAnim = 0;
            enemy[i].isUFO = false;
            enemy[i].ufoLightAnim = 0;
            enemy[i].ufoLightTimer = 0.0f;
            enemy[i].ufoVegetableIndex = -1;
            enemy[i].ufoHasVegetable = false;
            enemy[i].ufoDropState = 0;
            enemy[i].ufoDropTimer = 0.0f;
            enemy[i].ufoBeingTaken = false;
            enemy[i].alpha = 1.0f;
            enemy[i].fading = false;
            enemy[i].fadeSpeed = DEFAULT_FADE_SPEED;
            enemy[i].angularVelocity = 0.0f;
            break;

        case 1:
            enemy[i].scale = { 1.0f, 1.0f };
            enemy[i].center = { 71.0f, 62.0f };
            enemy[i].speed = 0.4f;
            enemy[i].moveenemy = 0;
            enemy[i].havescore = 30;
            enemy[i].helpEnemy = false;
            enemy[i].mouseAnim = -1;
            enemy[i].isUFO = false;
            enemy[i].ufoLightAnim = 0;
            enemy[i].ufoLightTimer = 0.0f;
            enemy[i].ufoVegetableIndex = -1;
            enemy[i].ufoHasVegetable = false;
            enemy[i].spriteID = -1;
            enemy[i].alpha = 1.0f;
            enemy[i].fading = false;
            enemy[i].fadeSpeed = DEFAULT_FADE_SPEED;
            enemy[i].angularVelocity = 0.0f;
            break;

        default:
            DxPlus::Utils::FatalError(L"敵の画像が存在しません！");
            break;
        }
    }
}

void UpdateEnemy(int i, float deltaTime, HookState& hookState)
{
    if (!enemy[i].isActive) return;

    if (enemy[i].fading && enemy[i].ufoDropState != 3) {
        enemy[i].alpha -= enemy[i].fadeSpeed * deltaTime;
        if (enemy[i].alpha <= 0.0f) {
            enemy[i].isActive = false;
            enemy[i].moveenemy = 0;
            enemy[i].velocity = { 0,0 };
            enemy[i].isUFO = false;
            enemy[i].ufoVegetableIndex = -1;
            enemy[i].ufoHasVegetable = false;
            enemy[i].ufoDropState = 0;
            enemy[i].ufoBeingTaken = false;
            enemy[i].alpha = 1.0f;
            enemy[i].fading = false;
            return;
        }
    }

    switch (enemy[i].moveenemy)
    {
    case 0:
        if (enemy[i].ufoDropState != 3) {
            enemy[i].position.x += enemy[i].speed * deltaTime;
        } else {
            enemy[i].position.y += UFO_FALL_SPEED * deltaTime;
            enemy[i].angle += enemy[i].angularVelocity * deltaTime;
            if (enemy[i].position.y > DxPlus::CLIENT_HEIGHT + 80.0f) {
                Score(enemy[i].havescore);
                enemy[i].isActive = false;
                enemy[i].moveenemy = 0;
                enemy[i].velocity = { 0,0 };
                enemy[i].isUFO = false;
                enemy[i].ufoVegetableIndex = -1;
                enemy[i].ufoHasVegetable = false;
                enemy[i].ufoDropState = 0;
                enemy[i].ufoBeingTaken = false;
                enemy[i].alpha = 1.0f;
                enemy[i].fading = false;
                enemy[i].angularVelocity = 0.0f;
                return;
            }
            break;
        }

        enemy[i].position.y += enemy[i].velocity.y * deltaTime;

		if (!enemy[i].isUFO) {
            enemy[i].timer += deltaTime;
            if (enemy[i].timer >= MOUSE_ANIM_INTERVAL) {
                enemy[i].timer -= MOUSE_ANIM_INTERVAL;
                enemy[i].mouseAnim = (enemy[i].mouseAnim + 1) % MOUSE_ANIM_NUM;
            }
        }
		else {
            enemy[i].ufoLightTimer += deltaTime;
            if (enemy[i].ufoLightTimer >= UFO_LIGHT_INTERVAL) {
                enemy[i].ufoLightTimer -= UFO_LIGHT_INTERVAL;
                enemy[i].ufoLightAnim = (enemy[i].ufoLightAnim + 1) % UFO_ANIM_NUM;
            }

            if (enemy[i].ufoDropState == 1) {
                enemy[i].ufoDropTimer += deltaTime;
                float half = UFO_DROP_DURATION * 0.5f;
                if (enemy[i].ufoDropTimer < half) {
                    float v = (UFO_DROP_DISTANCE / half) * deltaTime;
                    enemy[i].position.y += v;
                } else if (enemy[i].ufoDropTimer < UFO_DROP_DURATION) {
                    float v = (UFO_DROP_DISTANCE / half) * deltaTime;
                    enemy[i].position.y -= v;
                } else {
                    enemy[i].ufoDropState = 0;
                    enemy[i].ufoDropTimer = 0.0f;
                }
            }

            float centerX = DxPlus::CLIENT_WIDTH * 0.5f;
            if (!enemy[i].ufoHasVegetable && enemy[i].ufoDropState == 0) {
                bool crossedCenter = false;
                if (enemy[i].speed > 0 && enemy[i].position.x >= centerX - 1.0f) crossedCenter = true;
                if (enemy[i].speed < 0 && enemy[i].position.x <= centerX + 1.0f) crossedCenter = true;

                if (crossedCenter) {
                    enemy[i].ufoVegetableIndex = GetRand(VEGETABLE_TYPE);
                    enemy[i].ufoHasVegetable = true;
                    enemy[i].ufoDropState = 1;
                    enemy[i].ufoDropTimer = 0.0f;
                }
            }

            if (enemy[i].ufoDropState == 2) {
                enemy[i].position.y -= UFO_ASCEND_SPEED * deltaTime;
                if (enemy[i].position.y < -200.0f) {
                    enemy[i].isActive = false;
                    enemy[i].moveenemy = 0;
                    enemy[i].velocity = { 0,0 };
                    enemy[i].isUFO = false;
                    enemy[i].ufoVegetableIndex = -1;
                    enemy[i].ufoHasVegetable = false;
                    enemy[i].ufoDropState = 0;
                    enemy[i].ufoBeingTaken = false;
                }
            }
        }
        break;

    case 1:
        hookState = Returning;
        if (enemy[i].helpEnemy) enemy[i].speed *= -5;
        enemy[i].moveenemy = 0;
        break;

    default:
        DxPlus::Utils::FatalError(L"enemyMove error");
        break;
    }

    if (enemy[i].position.x < -200 || enemy[i].position.x > DxPlus::CLIENT_WIDTH + 200
        || enemy[i].position.y < -200 || enemy[i].position.y > DxPlus::CLIENT_HEIGHT + 200)
    {
        enemy[i].isActive = false;
        enemy[i].moveenemy = 0;
        enemy[i].velocity = { 0,0 };
        enemy[i].isUFO = false;
        enemy[i].ufoVegetableIndex = -1;
        enemy[i].ufoHasVegetable = false;
        enemy[i].ufoDropState = 0;
        enemy[i].ufoBeingTaken = false;
    }
}

void SpawnTimeEnemy(int i, int* Timer) {
    if (enemy[i].isActive) return;
    if (*Timer < 0) {

        bool fromRight = GetRand(2) != 0;
        enemy[i].position = { fromRight ? DxPlus::CLIENT_WIDTH + 50.0f : -50.0f, DxPlus::CLIENT_HEIGHT - 48.0f };

        if (GetRand(100) < UFO_SPAWN_PERCENT) {
            enemy[i].isUFO = true;
            enemy[i].ufoVegetableIndex = -1;
            enemy[i].ufoHasVegetable = false;
            enemy[i].position.y = 80.0f;
            enemy[i].speed = fromRight ? -UFO_MOVE_SPEED : UFO_MOVE_SPEED;
            enemy[i].spriteID = ufoSprite;
            enemy[i].scale = { 1.0f, 1.0f };
            enemy[i].center = { 71.0f, 62.0f };
            enemy[i].havescore = 30;
        } else {
            enemy[i].isUFO = false;
            enemy[i].speed = 0.7f;
            enemy[i].speed = (enemy[i].position.x < DxPlus::CLIENT_WIDTH / 2) ? enemy[i].speed : -enemy[i].speed;
            if (enemy[i].mouseAnim < 0 || enemy[i].mouseAnim >= MOUSE_ANIM_NUM) enemy[i].mouseAnim = 0;
            enemy[i].spriteID = mouseAnimDeg[enemy[i].mouseAnim];
            enemy[i].scale = { 0.7f, 0.7f };
            enemy[i].center = { 80.0f, 79.0f };
        }

        enemy[i].isActive = true;
        *Timer = GetRand(240) + 300;
        enemy[i].velocity.y = 0;
        enemy[i].angle = 0;
        enemy[i].helpEnemy = false;
        enemy[i].alpha = 1.0f;
        enemy[i].fading = false;
        enemy[i].fadeSpeed = DEFAULT_FADE_SPEED;
        enemy[i].ufoDropState = 0;
        enemy[i].ufoBeingTaken = false;
        enemy[i].angularVelocity = 0.0f;
    }
}

void onHookEnemyHit(const DxPlus::Vec2& targetPos, Entity2D* hook, int i) {
    if (enemy[i].helpEnemy) return;

    if (!enemy[i].isUFO) {
        enemy[i].moveenemy = 1;
        enemy[i].helpEnemy = true;
        return;
    }

    if (enemy[i].isUFO && enemy[i].ufoHasVegetable && enemy[i].ufoVegetableIndex >= 0) {
        DxPlus::Vec2 vegPos = { enemy[i].position.x, enemy[i].position.y + 96.0f };
        float dx = targetPos.x - vegPos.x;
        float dy = targetPos.y - vegPos.y;
        if (dx*dx + dy*dy <= VEG_HIT_RADIUS * VEG_HIT_RADIUS) {
            enemy[i].ufoDropState = 2;
            enemy[i].ufoBeingTaken = true;
            enemy[i].fading = true;
            enemy[i].fadeSpeed = DEFAULT_FADE_SPEED * 1.2f;
            enemy[i].moveenemy = 1;
            enemy[i].helpEnemy = true;
            Score(-100);
            return;
        }
    }

    {
        DxPlus::Vec2 bodyPos = enemy[i].position;
        float dx = targetPos.x - bodyPos.x;
        float dy = targetPos.y - bodyPos.y;
        if (dx*dx + dy*dy <= UFO_HIT_RADIUS * UFO_HIT_RADIUS) {
            enemy[i].fading = false;
            enemy[i].ufoDropState = 3;
            enemy[i].ufoBeingTaken = false;
            enemy[i].angularVelocity = UFO_FALL_ROT_SPEED * (GetRand(2) ? 1.0f : -1.0f);
            enemy[i].moveenemy = 1;
            enemy[i].helpEnemy = true;
            return;
        }
    }

    return;
}

void EnemyDraw(int i)
{
    if (!enemy[i].isActive) return;

    DxPlus::Vec2 drawScale = enemy[i].scale;
    if (enemy[i].fading) {
        float s = enemy[i].alpha; if (s < 0.1f) s = 0.1f;
        drawScale.x *= s;
        drawScale.y *= s;
    }

    if (enemy[i].isUFO) {
        if (ufoSprite != -1) {
            DxPlus::Sprite::Draw(ufoSprite, enemy[i].position, drawScale, enemy[i].center, enemy[i].angle);
        }

        int lightFrame = enemy[i].ufoLightAnim % UFO_ANIM_NUM;
        if (lightFrame < 0) lightFrame = 0;
        int lightSprite = ufoAnimDeg[lightFrame];
        if (lightSprite != -1) {
            DxPlus::Vec2 lightPos = { enemy[i].position.x, enemy[i].position.y + 48.0f };
            DxPlus::Vec2 lightScale = { 1.0f, 1.0f };
            DxPlus::Vec2 lightCenter = { 80.0f, 0.0f };
            DxPlus::Sprite::Draw(lightSprite, lightPos, lightScale, lightCenter, 0.0f);
        }

        if (enemy[i].ufoHasVegetable && enemy[i].ufoVegetableIndex >= 0 && enemy[i].ufoVegetableIndex < VEGETABLE_TYPE) {
            int vegIndex = enemy[i].ufoVegetableIndex;
            int vegSprite = -1;
            if (vegIndex < VEGETABLE_NUM) vegSprite = vegetable[vegIndex].spriteID;
            if (vegSprite != -1) {
                DxPlus::Vec2 vegPos = { enemy[i].position.x, enemy[i].position.y + 96.0f };
                DxPlus::Vec2 vegScale = DxPlus::Vec2{ 0.5f, 0.5f };
                DxPlus::Vec2 vegCenter = { 32.0f, 32.0f };
                DxPlus::Sprite::Draw(vegSprite, vegPos, vegScale, vegCenter, 0.0f);
            }
        }
        return;
    }

    int frame = enemy[i].mouseAnim;
    if (frame < 0) frame = 0;
    frame %= MOUSE_ANIM_NUM;

    int sprite = mouseAnimDeg[frame];
    if (sprite == -1) return;

    if (enemy[i].speed < 0)
        DxPlus::Sprite::Draw(sprite, enemy[i].position, drawScale, enemy[i].center, enemy[i].angle);
    else
        DxPlus::Sprite::Draw(sprite, enemy[i].position, { -drawScale.x, drawScale.y }, enemy[i].center, enemy[i].angle);
}

void EnemyDelete(int i)
{
    if (enemy[i].spriteID != -1) {
        DxPlus::Sprite::Delete(enemy[i].spriteID);
        enemy[i].spriteID = -1;
    }
}
