#include "hook.h"

Entity2D hook;

HookState hookState = Idle;


// --- �摜�ǂݍ��݊֌W ---
void hookImage()
{

    hook.spriteID = LoadGraph(L"./Data/images/hook_png.png");
    if (hook.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/hook_png.png");
    }

}

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
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

    hook.angle = 12;
}

void Updatehook(float deltaTime, int x, int y, DxPlus::Vec2 pointer,bool left)
{
    DxLib::GetMousePoint(&x, &y);
    pointer = { static_cast<float>(x), static_cast<float>(y) };

    hook.angle += 0.5f;
    if (hookState == Idle)
    {
        hook.position = left ? hook.HomePositionRight : hook.HomePositionLeft;
    }

    int mousInput = DxLib::GetMouseInput();
    if (mousInput & MOUSE_INPUT_LEFT && hookState == Idle)
    {
        hook.target = pointer;
        hookState = FlyingOut;
    }

    float dx = hook.target.x - hook.position.x;
    float dy = hook.target.y - hook.position.y;
    float distanceSq = dx * dx + dy * dy;
    float thresholdSq = 40.0f;

    if (distanceSq > thresholdSq)
    {
        float distance = std::sqrt(distanceSq);
        float speed = 20.0f;
        float moveX = (dx / distance) * speed * deltaTime;
        float moveY = (dy / distance) * speed * deltaTime;

        hook.position.x += moveX;
        hook.position.y += moveY;
    }
    else
    {
        // ���B������ʒu���Œ�
        hook.position = hook.target;

        if (hookState == FlyingOut)
        {
            if(left)
                hook.target = hook.HomePositionRight;
			else
                hook.target = hook.HomePositionLeft;
            
            hookState = Returning;
        }
        else if (hookState == Returning)
        {
            hookState = Idle;
        }
    }
}

void checkHookCollider(const DxPlus::Vec2& targetPos, float targetRadius)
{

    float hookRadius = 10.0f;            // �t�b�N�̔��a�i�C�Ӂj

    // 2�_�Ԃ̋������v�Z
    float dx = hook.position.x - targetPos.x;
    float dy = hook.position.y - targetPos.y;
    float distanceSq = dx * dx + dy * dy;

    // ���a�̍��v
    float radiusSum = hookRadius + targetRadius;

    // �����蔻��i������2��Ɣ��a�̍��v��2����r�j
    if (distanceSq <= radiusSum * radiusSum)
    {
        // �������Ă���
        onHookHit(targetPos); // �q�b�g���̏����i��F�G�Ƀ_���[�W�Ȃǁj
    }
}

void onHookHit(const DxPlus::Vec2& targetPos)
{
    // �t�b�N�������ɓ��������Ƃ��̏����������ɋL�q
    // ��: �G�Ƀ_���[�W��^����A�A�C�e�����擾����Ȃ�
    // �����ł͒P���Ƀt�b�N��߂������̗�������܂�
    hookState = Returning;
}

// --- �`��֐� ---
void hookDraw()
{
    DxPlus::Sprite::Draw(hook.spriteID, hook.position, hook.scale, hook.center,hook.angle);

}

// --- ����֐� ---
void hookDelete()
{

}
