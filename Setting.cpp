#include "DxPlus/DxPlus.h"
#include "Setting.h"
#include "WinMain.h"
#include "Entity2D.h"
#include "Back.h"



Entity2D settingBack[TITLE_BACK_NUM];
constexpr int SETTING_BUTTON_NUM = 6;// �{�^���̐�
enum SettingButtonType {
    VolUp,
    VolDown,
    easy,
	normal,
	hard,
    BackToTitle
};
Entity2D settingButton[SETTING_BUTTON_NUM];//�w�Z�̎����ɂ����܂��B�����܂ł�������Ă܂���//hai
Entity2D setBackground;
//----------------------------------------------------------------------
// �萔
//----------------------------------------------------------------------

// �A�j���[�V�����p
float settingBackAnimTimer = 0.0f;
int settingBackAnimFrame = 0;
float settingBackAnimSpeed = 0.05f; // �b�i�������قǁj
//----------------------------------------------------------------------
// �ϐ�
//----------------------------------------------------------------------

int SettingState;
float SettingFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// �����ݒ�
//----------------------------------------------------------------------
void Setting_Init()
{
	setBackground.spriteID = LoadGraph(L"./Data/images/kanban.png");
    if(setBackground.spriteID == -1){
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/kanban.png");
	}

    const wchar_t* setBackPaths[TITLE_BACK_NUM] = {
        L"./Data/images/b1 (1).png",
        L"./Data/images/b2 (1).png",
        L"./Data/images/b3 (1).png",
        L"./Data/images/b4 (1).png",
        L"./Data/images/b5 (1).png"
    };
    for (int j = 0; j < TITLE_BACK_NUM; ++j)
    {
        settingBack[j].spriteID = LoadGraph(setBackPaths[j]);
        if (settingBack[j].spriteID == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + setBackPaths[j]).c_str());
        }
	}
    for(int i=0;i<SETTING_BUTTON_NUM;++i){
        switch (i)
        {
            case VolUp:
                settingButton[i].spriteID = LoadGraph(L"./Data/images/vol_up.png");
				break;
			case VolDown:
				settingButton[i].spriteID = LoadGraph(L"./Data/images/vol_down.png");
				break;
			case easy:
				settingButton[i].spriteID = LoadGraph(L"./Data/images/easy.png");
				break;
			case normal:
				settingButton[i].spriteID = LoadGraph(L"./Data/images/normals.png");
				break;
			case hard:
				settingButton[i].spriteID = LoadGraph(L"./Data/images/hard.png");
				break;
			case BackToTitle:
				settingButton[i].spriteID = LoadGraph(L"./Data/images/back_to_title.png");
				break;


        default:
			DxPlus::Utils::FatalError(L"Invalid SettingButtonType value.");
            break;
        }

	}
    Setting_Reset();
}

//----------------------------------------------------------------------
// ���Z�b�g
//----------------------------------------------------------------------
void Setting_Reset()
{
    // �A�j���[�V�����p�ϐ��̃��Z�b�g
    settingBackAnimTimer = 0.0f;
    settingBackAnimFrame = 0;

	//�{�^���p�ϐ��̃��Z�b�g
    for (int i = 0; i < SETTING_BUTTON_NUM; ++i) {
        switch (i)
        {
        case VolUp:
            settingButton[i].position = { 900.0f, 200.0f };
            break;
        case VolDown:
            settingButton[i].position = { 700.0f, 200.0f };
            break;
        case easy:
            settingButton[i].position = { 400.0f, 200.0f };
            break;
        case normal:
            settingButton[i].position = { 400.0f, 400.0f };
            break;
        case hard:
            settingButton[i].position = { 400.0f, 600.0f };
            break;
        case BackToTitle:
            settingButton[i].position = { 700.0f, 600.0f };
            break;


        default:
            DxPlus::Utils::FatalError(L"Invalid SettingButtonType value.");
            break;
        }
    }
	// �t�F�[�h�p�ϐ��̃��Z�b�g
    SettingState = 0;
    SettingFadeTimer = 1.0f;


}
//----------------------------------------------------------------------
// �X�V����
//----------------------------------------------------------------------
void Setting_Update()
{   
	// �A�j���[�V�����X�V
	settingBackAnimTimer += settingBackAnimSpeed;
	if (settingBackAnimTimer >= 1.0f) {
		settingBackAnimTimer = 0.0f;
		settingBackAnimFrame = (settingBackAnimFrame + 1) % TITLE_BACK_NUM;

	}
   

	// �t�F�[�h�C�� / �t�F�[�h�A�E�g����
    Setting_Fade();
}

void Setting_Button(DxPlus::Vec2 pos, float radius, int *upDown, bool plus) {
    // �}�E�X�̈ʒu���擾
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    DxPlus::Vec2 mousePos = { static_cast<float>(mouseX), static_cast<float>(mouseY) };

    // �}�E�X�ƃ{�^���̒��S�̋������v�Z
    float distance = std::sqrt(std::pow(mousePos.x - pos.x, 2) + std::pow(mousePos.y - pos.y, 2));

    // �����蔻��
    bool isHit = distance <= radius;

    // �f�o�b�O�\��: �{�^���̉~�`���E��`��
    int color = isHit ? GetColor(255, 255, 255) : GetColor(255, 0, 0); 
    DrawCircle(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(radius), color, TRUE);

    // �}�E�X�N���b�N��Ԃ��擾
    static bool wasMousePressed = false; // �O��̃N���b�N��Ԃ�ێ�
    int mouseInput = GetMouseInput();
    bool isMouseClicked = (mouseInput & MOUSE_INPUT_LEFT) != 0;

    // �����蔻�肪�������A���N���b�N�������ꂽ�u�Ԃ̂ݏ��������s
    if (isHit && isMouseClicked && !wasMousePressed && SettingState == 1) {
        *upDown += plus ? 1 : -1;
    }

    // ���݂̃N���b�N��Ԃ�ۑ�
    wasMousePressed = isMouseClicked;
}


//----------------------------------------------------------------------
// �`�揈��
//----------------------------------------------------------------------
void Setting_Render()
{
    int frames = settingBackAnimFrame % TITLE_BACK_NUM;
    if (settingBack[frames].spriteID != -1) {
        DxPlus::Sprite::Draw(settingBack[frames].spriteID, {0.0f,0.0f}, { 1.0f,1.0f }, { 0.0f,0.0f });
    }
	DxPlus::Sprite::Draw(setBackground.spriteID, { 0.0f,0.0f }, { 1.0f,1.0f }, { 0.0f,0.0f });

    for (int i = 0; i < SETTING_BUTTON_NUM; ++i) {
        switch (i)
        {
        case VolUp:
			DxPlus::Sprite::Draw(settingButton[i].spriteID, settingButton[i].position, { 1.0f,1.0f }, { 0.0f,0.0f });
			break;
		case VolDown:
			DxPlus::Sprite::Draw(settingButton[i].spriteID, settingButton[i].position, { 1.0f,1.0f }, { 0.0f,0.0f });
			break;
		case easy:
			DxPlus::Sprite::Draw(settingButton[i].spriteID, settingButton[i].position, { 1.0f,1.0f }, { 0.0f,0.0f });
			break;
		case normal:
			DxPlus::Sprite::Draw(settingButton[i].spriteID, settingButton[i].position, { 1.0f,1.0f }, { 0.0f,0.0f });
			break;
		case hard:
			DxPlus::Sprite::Draw(settingButton[i].spriteID, settingButton[i].position, { 1.0f,1.0f }, { 0.0f,0.0f });
			break;
		case BackToTitle:
			DxPlus::Sprite::Draw(settingButton[i].spriteID, settingButton[i].position, { 1.0f,1.0f }, { 0.0f,0.0f });
			break;

        default:
            DxPlus::Utils::FatalError(L"Invalid SettingButtonType value.");
            break;
        }
    }
    //������g���ă{�^���쐬
    Setting_Button({ 200.0f, 300.0f }, 50.0f, &SettingState, true);

    // �t�F�[�h�C�� / �t�F�[�h�A�E�g�p 
    if (SettingFadeTimer > 0.0f) {
        //���
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * SettingFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Setting_Fade()
{
    switch (SettingState) {
    case 0: // �t�F�[�h�C���� 
    {
        SettingFadeTimer -= 1 / 60.0f;
        if (SettingFadeTimer < 0.0f) {
            SettingFadeTimer = 0.0f;
            SettingState++;
        }
        break;
    }
    case 1: // �ʏ펞
    {
        // BackSpace �L�[�������ꂽ��^�C�g���ɖ߂� 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            SettingState++;
        }
        break;
    }
    case 2: // �t�F�[�h�A�E�g��
    {
        SettingFadeTimer += 1 / 10.0f;
        if (SettingFadeTimer > 1.0f) {
            SettingFadeTimer = 1.0f;
            nextScene = SceneTitle;
        }
        break;
    }
    default:
        DxPlus::Utils::FatalError(L"Invalid SettingState value.");
        break;

    }

}


//----------------------------------------------------------------------
void Setting_End()
{
    for (int i = 0; i < TITLE_BACK_NUM; ++i) {
        if (settingBack[i].spriteID != -1) {
            DxPlus::Sprite::Delete(settingBack[i].spriteID);
            settingBack[i].spriteID = -1; // �����ɏ�����
        }
    }
}
