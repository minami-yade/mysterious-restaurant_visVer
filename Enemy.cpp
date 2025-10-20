#include "Enemy.h"
#include "AllManager.h"


Entity2D enemy[ENEMY_NUM];
extern Entity2D hook;

int mouseAnimDeg[MOUSE_ANIM_NUM] = { -1, -1, -1, -1 };

// --- �摜�ǂݍ��݊֌W ---
void EnemyImage()
{

    // �摜�͈�x�������[�h����
    const wchar_t* paths[MOUSE_ANIM_NUM] = {
        L"./Data/images/1.png",
        L"./Data/images/2.png",
        L"./Data/images/3.png",
        L"./Data/images/4.png"
    };

    for (int j = 0; j < MOUSE_ANIM_NUM; ++j)
    {
        mouseAnimDeg[j] = LoadGraph(paths[j]);
        if (mouseAnimDeg[j] == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + paths[j]).c_str());
        }
    }

    // �e�G�l�~�[�̏��� spriteID �����蓖�āimouseAnim ���͈͊O�Ȃ� 0 �ɕ␳�j
    for (int i = 0; i < ENEMY_NUM; ++i)
    {
        if (enemy[i].mouseAnim < 0 || enemy[i].mouseAnim >= MOUSE_ANIM_NUM) enemy[i].mouseAnim = 0;
        enemy[i].spriteID = mouseAnimDeg[enemy[i].mouseAnim];
    }
}

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void EnemyReset()
{

    for (int i = 0; i < ENEMY_NUM; ++i)
    {
        enemy[i].isActive = false;
        enemy[i].havescore = 50;

        switch (i % ENEMY_TYPE) {
        case 0: // nezumi
            enemy[i].scale = { 0.7f, 0.7f };
            enemy[i].center = { 80.0f, 79.0f };
            enemy[i].speed = 0.7f; 
            enemy[i].moveenemy = 0;
            enemy[i].havescore = -100;
            enemy[i].helpEnemy = false;
			enemy[i].mouseAnim = 0;
            break;
        default:
            DxPlus::Utils::FatalError(L"�G�̉摜�����݂��܂���I");
            break;
        }
    }
 

}




void UpdateEnemy(int i, float deltaTime, HookState& hookState)
{
    if (!enemy[i].isActive) return;

    switch (enemy[i].moveenemy)
    {
    case 0: // �ʏ�
        // �O�i�E�ʒu�X�V
        enemy[i].position.x += enemy[i].speed * deltaTime;
        enemy[i].position.y += enemy[i].velocity.y * deltaTime;

        // �A�j���[�V�����i���ԃx�[�X�Ői�߁A�t���[�����Ń��b�v�j
        {
            const float animInterval = 4.0f; // �傫���ƒx���Ȃ�

            enemy[i].timer += deltaTime;
            if (enemy[i].timer >= animInterval)
            {
                enemy[i].timer -= animInterval;
                // ���W�����̏������C���i+1 �Ŏ��t���[���A�z�񒷂Ń��b�v�j
                enemy[i].mouseAnim = (enemy[i].mouseAnim + 1) % MOUSE_ANIM_NUM;
            }
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

    // ��ʊO�`�F�b�N ...
    if (enemy[i].position.x < -100 || enemy[i].position.x > DxPlus::CLIENT_WIDTH + 100
        || enemy[i].position.y < -100 || enemy[i].position.y > DxPlus::CLIENT_HEIGHT + 100)
    {
        enemy[i].isActive = false;
        enemy[i].moveenemy = 0;
        enemy[i].velocity = { 0,0 };
    }
}


void SpawnTimeEnemy(int i, int* Timer) {
    if (enemy[i].isActive) return;
    if (*Timer < 0) {

        enemy[i].position = { GetRand(2) ? DxPlus::CLIENT_WIDTH + 50.0f : -50.0f,DxPlus::CLIENT_HEIGHT - 48 };                // ��ʊO����X�^�[�g	
        enemy[i].speed = 0.7f;
        enemy[i].speed = (enemy[i].position.x < DxPlus::CLIENT_WIDTH / 2) ? enemy[i].speed : -enemy[i].speed; // �E����Ȃ獶�ցA������Ȃ�E��
        enemy[i].isActive = true;
        *Timer = GetRand(240) + 300;
        enemy[i].velocity.y = 0;                            // �������x
        enemy[i].angle = 0;
		enemy[i].helpEnemy = false;

    }
}
void onHookEnemyHit(const DxPlus::Vec2& targetPos, Entity2D* hook, int i) {
    
    if (enemy[i].helpEnemy) return; // ���łɕ߂܂��Ă���ꍇ�͖���
    enemy[i].moveenemy = 1;
	enemy[i].helpEnemy = true;
	// �t�b�N�ɕ߂܂����ꍇ�̏����������ɒǉ�
}

// --- �`��֐� ---
void EnemyDraw(int i)
{
    if (!enemy[i].isActive) return;

    // mouseAnim �����S�Ɉ���
    int frame = enemy[i].mouseAnim;
    if (frame < 0) frame = 0;
    frame %= MOUSE_ANIM_NUM;

    int sprite = mouseAnimDeg[frame];
    if (sprite == -1) return;

    if (enemy[i].speed < 0)
        DxPlus::Sprite::Draw(sprite, enemy[i].position, enemy[i].scale, enemy[i].center, enemy[i].angle);
    else
        DxPlus::Sprite::Draw(sprite, enemy[i].position, { -enemy[i].scale.x,enemy[i].scale.y}, enemy[i].center, enemy[i].angle);
}

// --- ����֐� ---
void EnemyDelete(int i)
{
    if (enemy[i].spriteID != -1) {
        DxPlus::Sprite::Delete(enemy[i].spriteID);
        enemy[i].spriteID = -1;
    }
}
