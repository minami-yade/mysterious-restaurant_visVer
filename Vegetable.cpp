#include "Vegetable.h"
#include "AllManager.h"


Entity2D vegetable[VEGETABLE_NUM];


// --- �摜�ǂݍ��݊֌W ---
void VegetableImage()
{
       
    for (int i = 0; i < VEGETABLE_NUM; ++i)
    {
        switch (i % VEGETABLE_TYPE) {
        case 0: //�@�L���x�c
            vegetable[i].spriteID = LoadGraph(L"./Data/images/cabbage.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/cabbage.png");
            }
            break;

        default:
            DxPlus::Utils::FatalError(L"��؂̉摜�����݂��܂���I");
            break;
        }
    }

   
}

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void VegetableReset()
{
    for (int i = 0; i < VEGETABLE_NUM; ++i)
    {
        vegetable[i].isActive = false;
        vegetable[i].havescore = 50;
    
        switch (i % VEGETABLE_TYPE) {
		case 0: //�@�L���x�c
            vegetable[i].type = 0;
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 141.0f, 81.0f };
            vegetable[i].speed = 3.0f; // 100 �s�N�Z��/�b
            break;
		default:
			DxPlus::Utils::FatalError(L"��؂̉摜�����݂��܂���I");
			break;
        }
    }

}



// --- �����̍X�V�i�P���ȎO�p�g�ŏ㉺�j ---
void UpdateVegetable(int i, float deltaTime)
{
    if (!vegetable[i].isActive) return;

    // �O�i
    vegetable[i].position.x += vegetable[i].speed * deltaTime;

    // �d�͉����x��������
    vegetable[i].velocity.y += vegetable[i].gravity * deltaTime;

    // �n�ʁibaseY�j�ɓ��B�����璵�˕Ԃ�
    if (vegetable[i].position.y >= vegetable[i].baseY)
    {
        // �ʒu���X�V
        vegetable[i].position.y =  vegetable[i].baseY;
        vegetable[i].velocity.y += -vegetable[i].JumpPower;
    }

    // �ʒu���X�V
    vegetable[i].position.y += vegetable[i].velocity.y * deltaTime;

    // ��ʊO�ɏo�����A�N�e�B�u�ɂ���
    if (vegetable[i].position.x < -100 || vegetable[i].position.x > DxPlus::CLIENT_WIDTH + 100)
    {
        vegetable[i].isActive = false;
    }
}


void SpawnTimeVegetable(int i , int* Timer) {
	if (vegetable[i].isActive) return;
    if (*Timer < 0) {
	
        vegetable[i].position        = randamSpawn();                // ��ʊO����X�^�[�g	
        vegetable[i].speed = (vegetable[i].position.x < DxPlus::CLIENT_WIDTH/2) ? vegetable[i].speed : -vegetable[i].speed; // �E����Ȃ獶�ցA������Ȃ�E��
        vegetable[i].isActive        = true;
		*Timer                       = GetRand(240) + 60;            //�S�b����T�b
        vegetable[i].baseY           = vegetable[i].position.y;      // ���
    } 
}

// --- �`��֐� ---
void VegetableDraw(int i)
{
    if (!vegetable[i].isActive) return;
	if (vegetable[i].spriteID == -1) return;
    if(vegetable[i].speed > 0)
    DxPlus::Sprite::Draw(vegetable[i].spriteID, vegetable[i].position, vegetable[i].scale, vegetable[i].center);
    else
        DxPlus::Sprite::Draw(vegetable[i].spriteID, vegetable[i].position, { -vegetable[i].scale.x ,vegetable[i].scale.y }, vegetable[i].center);
}

// --- ����֐� ---
void VegetableDelete(int i)
{
    if (vegetable[i].spriteID != -1) {
        DxPlus::Sprite::Delete(vegetable[i].spriteID);
        vegetable[i].spriteID = -1;
    }
}
