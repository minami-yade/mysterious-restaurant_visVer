#include "bowl.h"

Entity2D bowl;
Entity2D bowlEffect[BOWL_EFFECT_NUM];

// --- �摜�ǂݍ��݊֌W ---
void bowlImage() {

    // bowl�̉摜
    bowl.spriteID = LoadGraph(L"./Data/images/bowl.png");
    if (bowl.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/bowl.png");
    }
    for (size_t i = 0; i < BOWL_EFFECT_NUM; ++i) {
        switch (i)
        {
        case 0://�j���W��
            bowlEffect[i].effectID = LoadGraph(L"./Data/images/carrot.png");
            if (bowlEffect[i].effectID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/carrot.png");
            }
            break;

        case 1://�s�[�}��
            bowlEffect[i].effectID = LoadGraph(L"./Data/images/pepper.png");
            if (bowlEffect[i].effectID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/pepper.png");
            }
            break;

        case 2://�Ƃ܂�
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

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void bowlReset() {
    bowl.position = { DxPlus::CLIENT_WIDTH / 2.0f, DxPlus::CLIENT_HEIGHT - 48.0f };
    bowl.scale = { 0.75f,0.75f };
    bowl.center = { 76.0f ,60.0f };//���S��bottom
    bowl.radius = 50.0f;

}

void checkbowlCollider(Entity2D& entity,int i) {


    // 2�_�Ԃ̋������v�Z
    float dx = bowl.position.x - entity.position.x;
    float dy = bowl.position.y - entity.position.y;
    float distanceSq = dx * dx + dy * dy;

    // ���a�̍��v
    float radiusSum = bowl.radius + entity.radius;

    // �����蔻��
    if (distanceSq <= radiusSum * radiusSum)
    {
        // �������Ă���
        Score(entity.havescore); // �X�R�A���Z
		entity.isActive = false; // ��A�N�e�B�u�ɂ���
		entity.position = { -100,-100 };//��ʊO��
		entity.moveVegetable = 0;
        entity.moveenemy = 1;
		entity.velocity = { 0,0 };
    }

}

// --- �`��֐� ---
void bowlDraw() {
    DxPlus::Sprite::Draw(bowl.spriteID, bowl.position, bowl.scale, bowl.center);
}

// --- ����֐� ---
void bowlDelete() {
    if (bowl.spriteID != -1) {
        DxPlus::Sprite::Delete(bowl.spriteID);
        bowl.spriteID = -1;
    }
}
