#include "Vegetable.h"
#include "AllManager.h"


Entity2D vegetable[VEGETABLE_NUM];
extern Entity2D enemy[ENEMY_NUM];
extern Entity2D hook;



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
        case 1://��
            vegetable[i].spriteID = LoadGraph(L"./Data/images/beef.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/beef.png");
            }
            break;
        case 2://�p�v���J
            vegetable[i].spriteID = LoadGraph(L"./Data/images/paprika.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/paprika.png");
            }
            break;
        case 3://�ŃL�m�R
            vegetable[i].spriteID = LoadGraph(L"./Data/images/poison_mushroom.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/poison_mushroom.png");
            }
            break;
        case 4://�j���W��
             vegetable[i].spriteID = LoadGraph(L"./Data/images/carrot.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/carrot.png");
            }
			break;
        case 5: //�i�X
            vegetable[i].spriteID = LoadGraph(L"./Data/images/eggplant.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/eggplant.png");
			}
			break;
		case 6://�g�}�g
            vegetable[i].spriteID = LoadGraph(L"./Data/images/tomato.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/tomato.png");
			}   
			break;
        case 7://�s�[�}��
            vegetable[i].spriteID = LoadGraph(L"./Data/images/pepper.png");
            if (vegetable[i].spriteID == -1) {
                DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/pepper.png");
            }
			break;
        default:
            DxPlus::Utils::FatalError(L"��؂̉摜�����݂��܂���I");
            break;
        };

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
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f; // 100 �s�N�Z��/�b
            vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;

            break;
        case 1://��
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f; // 100 �s�N�Z��/�b
            vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;
			break;
        case 2://�p�v���J
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f; // 100 �s�N�Z��/�b
            vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;
			break;
        case 3://�ŃL�m�R
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f; // 100 �s�N�Z��/�b
            vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;
			break;
         case 4://�j���W��
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f; // 100 �s�N�Z��/�b
            vegetable[i].JumpPower = 15.0f;
			vegetable[i].moveVegetable = 0;
            break;
        case 5: //�i�X
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f; // 100 �s�N�Z��/�b
			vegetable[i].JumpPower = 15.0f;
            vegetable[i].moveVegetable = 0;
			break;
            case 6://�g�}�g
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
			vegetable[i].speed = 3.0f; // 100 �s�N�Z��/�b
            vegetable[i].JumpPower = 15.0f;
			vegetable[i].moveVegetable = 0;
            break;
        case 7://�s�[�}��
            vegetable[i].scale = { 0.5f, 0.5f };
            vegetable[i].center = { 49.0f, 49.0f };
            vegetable[i].speed = 3.0f; // 100 �s�N�Z��/�b
			vegetable[i].JumpPower = 15.0f;
			vegetable[i].moveVegetable = 0;
			break;

		default:
			DxPlus::Utils::FatalError(L"��؂̉摜�����݂��܂���I");
			break;
        }
    }

}



// --- �����̍X�V�i�P���ȎO�p�g�ŏ㉺�j ---
void UpdateVegetable(int i, float deltaTime,HookState hookState)
{
    if (!vegetable[i].isActive) return;

    switch (vegetable[i].moveVegetable)
    {
    case 0: // �ʏ�

       
        // �O�i
        vegetable[i].position.x += vegetable[i].speed * deltaTime;

        // �d�͉����x��������
        vegetable[i].velocity.y += vegetable[i].gravity * deltaTime;

        // �n�ʁibaseY�j�ɓ��B�����璵�˕Ԃ�
        // velocity.y > 0�i�������ɗ������j�̂Ƃ��������˕Ԃ�
        if (vegetable[i].position.y >= vegetable[i].baseY && vegetable[i].velocity.y > 0)
        {
            vegetable[i].position.y = vegetable[i].baseY;
            vegetable[i].velocity.y = -vegetable[i].JumpPower; // ���˕Ԃ�
        }

        // �ʒu���X�V
        vegetable[i].position.y += vegetable[i].velocity.y * deltaTime;
        break;

    case 1: // �t�b�N�ɕ߂܂���
        vegetable[i].position = { hook.position };
        if (hookState == Idle) {
            vegetable[i].moveVegetable = 2;
        }
		vegetable[i].angle -= 6.0f;
        break;

    case 2: // �t�b�N�ɕ߂܂���������ꂽ
        vegetable[i].moveVegetable = 3;
        break;
    case 3:
    {
  
        const float ByeByeSpeed = 5.0f;
        const float AngleSpeed = 0.5f;
        if (vegetable[i].position.x > DxPlus::CLIENT_WIDTH / 2)
        {
            vegetable[i].position.x -= ByeByeSpeed * deltaTime * 1;
            vegetable[i].position.y += ByeByeSpeed * deltaTime * 1.1;
            vegetable[i].angle += AngleSpeed;
        }
        else
        {
            vegetable[i].position.x += ByeByeSpeed * deltaTime * 1;
            vegetable[i].position.y += ByeByeSpeed * deltaTime * 1.1;
            vegetable[i].angle += AngleSpeed;

        }


        break;
    }


    default:
        break;
    }

    // ��ʊO�ɏo�����A�N�e�B�u�ɂ���
    if (vegetable[i].position.x < -100 || vegetable[i].position.x > DxPlus::CLIENT_WIDTH + 100 
        || vegetable[i].position.y < -100 || vegetable[i].position.y > DxPlus::CLIENT_HEIGHT+ 100)
    {
        vegetable[i].isActive = false;
		vegetable[i].moveVegetable = 0;
		vegetable[i].velocity = { 0,0 };
    }
}


void SpawnTimeVegetable(int i , int* Timer) {
	if (vegetable[i].isActive) return;
    if (*Timer < 0) {
	
        vegetable[i].position        = randamSpawn();                // ��ʊO����X�^�[�g	
        vegetable[i].speed = 3.0f; 
        vegetable[i].speed = (vegetable[i].position.x < DxPlus::CLIENT_WIDTH/2) ? vegetable[i].speed : -vegetable[i].speed; // �E����Ȃ獶�ցA������Ȃ�E��
        vegetable[i].isActive        = true;
		*Timer                       = GetRand(60) + 60;
        vegetable[i].baseY           = vegetable[i].position.y;      // ���
		vegetable[i].velocity.y = 0;                            // �������x
		vegetable[i].angle = 0;

    } 
}

void onHookHit(const DxPlus::Vec2& targetPos, Entity2D* hook, int i)
{
    // ���S���`�F�b�N
    if (i < 0 || i >= VEGETABLE_NUM) return;

    // ��؂��t�b�N�ɂ�������
    hook->isCarryingVegetable = true;
    hook->carriedVegetable = &vegetable[i];

    if (vegetable[i].moveVegetable == 0) {
        vegetable[i].moveVegetable = 1;
        vegetable[i].velocity = { 0, 0 }; // �K�v�Ȃ珉����
        // vegetable[i].angle = 0; // �󋵂ɉ�����
    }
}


// --- �`��֐� ---
void VegetableDraw(int i)
{
    if (!vegetable[i].isActive) return;
	if (vegetable[i].spriteID == -1) return;
    if(vegetable[i].speed > 0)
    DxPlus::Sprite::Draw(vegetable[i].spriteID, vegetable[i].position, vegetable[i].scale, vegetable[i].center,vegetable[i].angle);
    else
        DxPlus::Sprite::Draw(vegetable[i].spriteID, vegetable[i].position, { -vegetable[i].scale.x ,vegetable[i].scale.y }, vegetable[i].center,-vegetable[i].angle);
}

// --- ����֐� ---
void VegetableDelete(int i)
{
    if (vegetable[i].spriteID != -1) {
        DxPlus::Sprite::Delete(vegetable[i].spriteID);
        vegetable[i].spriteID = -1;
    }
}
