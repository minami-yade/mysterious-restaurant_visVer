#include "hook.h"
#include "vegetable.h"

Entity2D hook;
extern Entity2D player[PLAYER_NUM];

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
	hook.velocity = { 0.0f, 0.0f };
	hook.gravity = 0.98f;

    hook.angle = 12;
}



void Updatehook(float deltaTime, int x, int y, DxPlus::Vec2 pointer, bool left)
{
    DxLib::GetMousePoint(&x, &y);
    pointer = { static_cast<float>(x), static_cast<float>(y) };

    hook.angle += 0.3f;//��]

    if (hookState == Idle)
    {
        hook.position = left ? hook.HomePositionRight : hook.HomePositionLeft;
        hook.velocity = { 0.0f, 0.0f };
    }

    int mouseInput = DxLib::GetMouseInput();
    static int prevMouseInput = 0;

    // ���N���b�N���u��������Ă��āA�O�t���[���͉�����Ă��Ȃ������v���������u��
    if ((mouseInput & MOUSE_INPUT_LEFT) && !(prevMouseInput & MOUSE_INPUT_LEFT)) {

        if (hookState == FlyingOut)//���ł鎞�ɉ�������
        {
            hookState = Returning;//���ǂ�
        }

		if (hookState == Idle)//�~�܂��Ă鎞�ɉ�������
        {
            DxPlus::Vec2 dir = pointer - hook.position;
            float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);
            if (len > 1.0f)
            {
                dir.x /= len;
                dir.y /= len;
                float launchSpeed = 30.0f; // ����
                hook.velocity = { dir.x * launchSpeed/2, dir.y * launchSpeed };
                hookState = FlyingOut;
            }
        }

    }
    if (hookState == Returning) //�߂鏈��
    {

        DxPlus::Vec2 home = left ? hook.HomePositionRight : hook.HomePositionLeft;//�E�����ɖ߂�
        DxPlus::Vec2 dir = home - hook.position;;//��
        float len = std::sqrt(dir.x * dir.x + dir.y * dir.y);;
		if (len > 20.0f)//�����Ȃ�
        {
            if (hook.position.x == home.x) {
				hook.position.y += 5.0f;
            }
            else {
                dir.x /= len;
                dir.y /= len;
                float returnSpeed = 3.5f;//�߂鑁��
                hook.velocity = { dir.x * returnSpeed, dir.y * returnSpeed };
               

            }
        }
        else //�߂��Ȃ�
        {
            hookState = Idle;
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


void checkHookCollider(const DxPlus::Vec2& targetPos, float targetRadius,int i)
{

    float hookRadius = 10.0f;            // �t�b�N�̔��a�i�C�Ӂj

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
        onHookHit(targetPos,&hook,&player[0], i); // �q�b�g���̏����i��F�G�Ƀ_���[�W�Ȃǁj
    }
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
