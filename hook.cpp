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



// --- �摜�ǂݍ��݊֌W ---
void hookImage()
{

    hook.spriteID = LoadGraph(L"./Data/images/hook_png.png");
    if (hook.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/hook_png.png");
    }
    //���łɃT�E���h
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

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
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

    hook.angle += 0.3f;//��]




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

    // ���N���b�N���u��������Ă��āA�O�t���[���͉�����Ă��Ȃ������v���������u��
    if ((mouseInput & MOUSE_INPUT_LEFT) && !(prevMouseInput & MOUSE_INPUT_LEFT)) {
       
        if (hookState == FlyingOut)//���ł鎞�ɉ�������
        {

            if (hook.position.y > DxPlus::CLIENT_HEIGHT - 48.0f)//�n��
                hookState = Returning;//���ǂ�
            if (hookState == Returning)
            {
                //PlaySoundMem(vol_bowl_back, DX_PLAYTYPE_BACK);
            }

        }

        if
            (hookState == Idle)//�~�܂��Ă鎞�ɉ�������
        { //sound
        PlaySoundMem(vol_hook, DX_PLAYTYPE_BACK);
            DxPlus::Vec2 dir = pointer - hook.position;
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len > 1.0f)
            {
                dir.x /= len;
                dir.y /= len;
                float launchSpeed = 30.0f; // ����
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

        if (len > 20.0f) // �܂�����
        {
            dir.x /= len;
            dir.y /= len;
            float returnSpeed = 40.0f;
            hook.velocity = { dir.x * returnSpeed, dir.y * returnSpeed };
        }
        else // �߂Â�����
        {
            if (!hook.reachedUpHook) {
                hook.reachedUpHook = true; // upHook �ɓ��B �� ���� Home ��
            }
            else {
                hookState = Idle; // Home �ɓ��B �� �I��
            }
        }
    }




    //��
    // ��ʊO�ɏo���狭���I�ɖ߂��ɂ���
    if (hook.position.x < 0 || hook.position.x > DxPlus::CLIENT_WIDTH
        || hook.position.y < 0 || hook.position.y > DxPlus::CLIENT_HEIGHT - 48.0f)
    {
        if (hook.position.y < 0) hook.position.y = 0;
        if (hook.position.y > DxPlus::CLIENT_HEIGHT - 48.0f) hook.position.y = DxPlus::CLIENT_HEIGHT - 48.0f;
        if (hook.position.x < 0) hook.position.x = 0;
        if (hook.position.x > DxPlus::CLIENT_WIDTH) hook.position.x = DxPlus::CLIENT_WIDTH;
        //�������Ȃ��悤�ɂ��邽��

        hook.velocity = { 0,0 };//����Ȃ��ړ����폜

        //hookState = Returning;�@//����������ƒ[�ɍs���Ă��~�܂�
    }

    // ���ł���Ԃ͏d�͂����Z
    if (hookState == FlyingOut)
    {

        hook.velocity.y += hook.gravity * deltaTime;
    }
    // -----------------

    // �������ۂ��ړ��i��������j
    if (hookState == FlyingOut || hookState == Returning)
    {
        hook.position.x += hook.velocity.x * deltaTime;
        hook.position.y += hook.velocity.y * deltaTime;
    }


    prevMouseInput = mouseInput; // ��Ԃ��X�V
}


void checkHookCollider(const DxPlus::Vec2& targetPos, float targetRadius, int i, bool veg)
{
    float hookRadius = 10.0f;            // �t�b�N�̔��a

    // 2�_�Ԃ̋������v�Z
    float dx = hook.position.x - targetPos.x;
    float dy = hook.position.y - targetPos.y;
    float distanceSq = dx * dx + dy * dy;

    // ���a�̍��v
    float radiusSum = hookRadius + targetRadius;

    // �����蔻��
    if (distanceSq <= radiusSum * radiusSum)
    {
        // �������Ă���
        if (veg)
            onHookHit(targetPos, &hook, i);
        else
            onHookEnemyHit(targetPos, &hook, i);
    }
}



// --- �`��֐� ---
void hookDraw(bool left)
{
    DxPlus::Sprite::Draw(hook.spriteID, hook.position, hook.scale, hook.center, hook.angle);


    // ���̕`��i�x�W�F�Ȑ��ł���݂�\���j


    float time = static_cast<float>(DxLib::GetNowCount()) / 1000.0f; // �b�P�ʂ̎���

    DxPlus::Vec2 start = left ? hook.HomePositionRight : hook.HomePositionLeft;
    DxPlus::Vec2 end = hook.position;

    float length = std::sqrt((end - start).x * (end - start).x + (end - start).y * (end - start).y);
    float swayAmount = std::min(40.0f, length * 0.2f);

    // ���ԓ_�F
    DxPlus::Vec2 mid = (start + end) * 0.5f;
    mid.y += swayAmount;
    mid.x += std::sin(time * 6.0f) * 8.0f; // ���h��

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

// --- ����֐� ---
void hookDelete()
{
    if (hook.spriteID != -1) {
        DxPlus::Sprite::Delete(hook.spriteID);
        hook.spriteID = -1;
    }
    //���łɃT�E���h
 
    if (vol_hook == -1) {
        DxPlus::Utils::FatalError(L"./Data/Sounds/Push.mp3");
    }


}
