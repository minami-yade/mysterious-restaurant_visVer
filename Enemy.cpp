#include "Enemy.h"
#include "AllManager.h"

// --------------------------------------------------
// Enemy.cpp - �G�l�~�[�iUFO�܂ށj����
// --------------------------------------------------
extern int GameMode;

Entity2D enemy[ENEMY_NUM];
extern Entity2D hook;
extern Entity2D vegetable[VEGETABLE_NUM];

int mouseAnimDeg[MOUSE_ANIM_NUM] = {};
int ufoAnimDeg[UFO_ANIM_NUM] = {};
int ufoSprite = -1;

const int UFO_SPAWN_PERCENT = 40;
const float MOUSE_ANIM_INTERVAL = 3.0f;

float UFO_MOVE_SPEED = 2.5f;
const float UFO_LIGHT_INTERVAL = 3.0f;

const float UFO_DROP_DURATION = 30.0f;//������
const float UFO_DROP_DISTANCE = 300.0f;//����
const float UFO_ASCEND_SPEED = 10.0f;//�㏸���x
const float DEFAULT_FADE_SPEED = 1.5f;

const float UFO_HIT_RADIUS = 48.0f;
const float VEG_HIT_RADIUS = 40.0f;

const float UFO_FALL_SPEED = 3.0f;
const float UFO_FALL_ROT_SPEED = 720.0f;

int modeSpeed = 0;



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
        enemy[i].havescore = -100;

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
            enemy[i].havescore = -100;
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
            DxPlus::Utils::FatalError(L"�G�̉摜�����݂��܂���I");
            break;
        }
       
        if (GameMode == 0) {
            modeSpeed = 1.0f;
        }
        else if (GameMode == 1) {
            modeSpeed = 1.5f;
        }
        else if (GameMode == 2) {
            modeSpeed = 3.0f;
        }

    }
}

void UpdateEnemy(int i, float deltaTime, HookState& hookState, int *score)
{
    if (!enemy[i].isActive) {
        if (enemy[i].isUFO && enemy[i].ufoHasVegetable && enemy[i].ufoVegetableIndex >= 0) {
            vegetable[enemy[i].ufoVegetableIndex].isActive = false; // ��؂��A�N�e�B�u��
            enemy[i].ufoVegetableIndex = -1;
            enemy[i].ufoHasVegetable = false;
        }
        return;
    }

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

    // UFO�̓��쏈��
    switch (enemy[i].moveenemy) {
    case 0:
        // UFO�������ɗ����瓮�����~�߂�
        if (enemy[i].isUFO && fabs(enemy[i].position.x - DxPlus::CLIENT_WIDTH / 2.0f) < 10.0f) {
            enemy[i].speed = 0.0f; // �����ړ����~
            if (enemy[i].ufoDropState == 0)
                enemy[i].ufoDropState = 1; // ��Ԃ��u��؂��擾����v�ɕύX
        }

        if (enemy[i].ufoDropState == 1) { // ��؂��擾���鏈��
            enemy[i].ufoDropTimer += deltaTime;
            if (enemy[i].ufoDropTimer < 70.0f) { // �������Ɉړ�
                enemy[i].position.y += UFO_FALL_SPEED * deltaTime;
            } else if (!enemy[i].ufoHasVegetable) { // ��؂������Ă��Ȃ��ꍇ�̂ݎ擾
                enemy[i].ufoHasVegetable = true; // ��؂��擾
                enemy[i].ufoVegetableIndex = GetRand(VEGETABLE_NUM - 1); // �����_���Ȗ�؂��擾
                enemy[i].ufoDropState = 2; // ��Ԃ��u�㏸�v�ɕύX
                enemy[i].ufoDropTimer = 0.0f; // �^�C�}�[�����Z�b�g
                *score -= 200; // ��؂����ꂽ�y�i���e�B
            }
            break;
        }

        if (enemy[i].ufoDropState == 2) { // �㏸����
            enemy[i].position.y -= UFO_ASCEND_SPEED * deltaTime; // �㏸
            if (enemy[i].position.y < -100.0f) { // ��ʊO�ɏo�����A�N�e�B�u��
                enemy[i].isActive = false;
                enemy[i].ufoDropState = 0;
                enemy[i].ufoHasVegetable = false;
                enemy[i].ufoVegetableIndex = -1;
            }
            break;
        }

        // �ʏ�ړ���
        if (enemy[i].ufoDropState == 0) {
            enemy[i].position.x += enemy[i].speed * deltaTime; // �����ړ�
        }


        else if (enemy[i].ufoDropState == 3) { // ��������
            enemy[i].position.y += UFO_FALL_SPEED * deltaTime * 10; // ����
            enemy[i].angle += enemy[i].angularVelocity * deltaTime; // ��]
		}
        break;

    case 1: // �t�b�N�ɕ߂܂���
        hookState = Returning;
        if (enemy[i].helpEnemy) enemy[i].speed *= -5;
        enemy[i].moveenemy = 0;
        break;

    default:
        DxPlus::Utils::FatalError(L"enemyMove error");
        break;
    }

    // UFO����؂������Ă���ꍇ�A��؂̉摜�̂ݕ\�����邽�߁A�ʒu�X�V�ⓖ���蔻��𖳌���
    if (enemy[i].isUFO && enemy[i].ufoHasVegetable && enemy[i].ufoVegetableIndex >= 0) {
        // ��؂̈ʒu��UFO�̈ʒu�ɌŒ�i�ړ����W�b�N�͍폜�j
        vegetable[enemy[i].ufoVegetableIndex].position = {
            enemy[i].position.x,
            enemy[i].position.y + 96.0f
        };
    }

    // UFO�̃A�j���[�V�������X�V
    if (enemy[i].isUFO) {
        enemy[i].ufoLightTimer += deltaTime;
        if (enemy[i].ufoLightTimer >= UFO_LIGHT_INTERVAL) {
            enemy[i].ufoLightTimer -= UFO_LIGHT_INTERVAL;
            enemy[i].ufoLightAnim = (enemy[i].ufoLightAnim + 1) % UFO_ANIM_NUM;
        }
    } else { // �l�Y�~�̂�
        enemy[i].timer += deltaTime;
        if (enemy[i].timer >= MOUSE_ANIM_INTERVAL) {
            enemy[i].timer -= MOUSE_ANIM_INTERVAL;
            enemy[i].mouseAnim = (enemy[i].mouseAnim + 1) % MOUSE_ANIM_NUM;
            enemy[i].spriteID = mouseAnimDeg[enemy[i].mouseAnim];
        }
    }

    // ��ʊO�ɏo�����A�N�e�B�u��
    if (enemy[i].position.x < -200 || enemy[i].position.x > DxPlus::CLIENT_WIDTH + 200
        || enemy[i].position.y < -200 || enemy[i].position.y > DxPlus::CLIENT_HEIGHT + 200) {
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
            enemy[i].position.y = 200.0f;
            enemy[i].speed = fromRight ? -UFO_MOVE_SPEED  * modeSpeed : UFO_MOVE_SPEED * modeSpeed;
            enemy[i].spriteID = ufoSprite;
            enemy[i].scale = { 0.8f, 0.8f }; // �X�P�[������������������
            enemy[i].center = { 71.0f, 62.0f };
            enemy[i].havescore = 30;
        } else {
            enemy[i].isUFO = false;
            enemy[i].speed = fromRight ? -UFO_MOVE_SPEED* modeSpeed : UFO_MOVE_SPEED * modeSpeed;
            enemy[i].speed = (enemy[i].position.x < DxPlus::CLIENT_WIDTH / 2) ? enemy[i].speed : -enemy[i].speed;
            if (enemy[i].mouseAnim < 0 || enemy[i].mouseAnim >= MOUSE_ANIM_NUM) enemy[i].mouseAnim = 0;
            enemy[i].spriteID = mouseAnimDeg[enemy[i].mouseAnim];
            enemy[i].scale = { 0.7f, 0.7f };
            enemy[i].center = { 80.0f, 79.0f };
			enemy[i].havescore = -100;
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

    // UFO�{�̂Ƀt�b�N�����������ꍇ�A�ⓚ���p�Ō��ď�Ԃɂ���
    if (enemy[i].isUFO) {
        enemy[i].fading = false;
        enemy[i].ufoDropState = 3; // �������
        enemy[i].ufoBeingTaken = false;
        enemy[i].angularVelocity = UFO_FALL_ROT_SPEED * (GetRand(2) ? 1.0f : -1.0f); // �����_���ȉ�]����
        enemy[i].moveenemy = 1;
        enemy[i].helpEnemy = true;
        return;
    }

    // UFO�ȊO�̓G�ɑ΂��鏈��
    enemy[i].moveenemy = 1;
    enemy[i].helpEnemy = true;
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

        if (enemy[i].ufoHasVegetable && enemy[i].ufoVegetableIndex >= 0 && enemy[i].ufoVegetableIndex < VEGETABLE_NUM) {
            int vegIndex = enemy[i].ufoVegetableIndex;
            int vegSprite = vegetable[vegIndex].spriteID;
            if (vegSprite != -1) {
                DxPlus::Vec2 vegPos = { enemy[i].position.x, enemy[i].position.y + 96.0f };
                DxPlus::Vec2 vegScale = { 0.5f, 0.5f };
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
