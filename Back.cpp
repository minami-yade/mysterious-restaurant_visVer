#include "Back.h"

Entity2D titleBack[TITLE_BACK_NUM];
Entity2D Button[TITLE_BUTTON_NUM];
Entity2D TitlePlay[TITLE_BACKPLAY_NUM];
enum ButtonType {
    Title,
    Start,
    Settings,
    Fin
};
Entity2D gameBack;
Entity2D gameFloor;
DxPlus::Vec2 buttonBase = { 700.0f, 0.0f };

// �A�j���[�V�����p
float titleBackAnimTimer = 0.0f;
int titleBackAnimFrame = 0;
float titleBackAnimSpeed = 0.05f; // �b�i�������قǁj

// �X�P�[����ԗp�ϐ�
DxPlus::Vec2 currentScale = { 1.0f, 1.0f }; // �����X�P�[��
const DxPlus::Vec2 targetScale = { 3.5f, 3.5f }; // �ڕW�X�P�[��
const float scaleSpeed = 0.3f; // �X�P�[����ԑ��x�i�������قǂ������j


//���U���g--------------------------
int ResultAnimation[RESULT_ANIM_COUNT];
// �A�j���[�V�����p�̕ϐ�
int currentFrame = 0; // ���݂̃t���[��
float animTimer = 0.0f; // �A�j���[�V�����^�C�}�[
const float animSpeed = 0.1f; // �A�j���[�V�������x�i�b�j




void TitleBackImage() {
    const wchar_t* BacksPaths[TITLE_BACK_NUM] = {
        L"./Data/images/b1 (1).png",
        L"./Data/images/b2 (1).png",
        L"./Data/images/b3 (1).png",
        L"./Data/images/b4 (1).png",
        L"./Data/images/b5 (1).png"
    };
    const wchar_t* ButtonPaths[TITLE_BUTTON_NUM] = {
		L"./Data/images/title_logo1.png", // Title
		L"./Data/images/start.png",      // Start
		L"./Data/images/setting.png",    // Settings   
		L"./Data/images/quit_game.png",  // Fin
    };
    const wchar_t* titlePlayPaths[TITLE_BACKPLAY_NUM] = {
        L"./Data/images/b1.png",
        L"./Data/images/b2.png",
        L"./Data/images/b3.png",
        L"./Data/images/b4.png",
        L"./Data/images/b5.png",
        L"./Data/images/b6.png",
        L"./Data/images/b7.png",
        L"./Data/images/b8.png",
    };
    for (int j = 0; j < TITLE_BACK_NUM; ++j)
    {
        titleBack[j].spriteID = LoadGraph(BacksPaths[j]);
        if (titleBack[j].spriteID == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + BacksPaths[j]).c_str());
        }
    }
    for (int j = 0; j < TITLE_BUTTON_NUM; ++j)
    {
        Button[j].spriteID = LoadGraph(ButtonPaths[j]);
        if (Button[j].spriteID == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + ButtonPaths[j]).c_str());
        }
    }
    for(int i=0;i<TITLE_BACKPLAY_NUM;++i){
        TitlePlay[i].spriteID = LoadGraph(titlePlayPaths[i]);
        if (TitlePlay[i].spriteID == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"failed to load sprite : ") + titlePlayPaths[i]).c_str());
        }
	}
}

void TitleBackReset() {
    // �A�j���[�V�����p�ϐ��̃��Z�b�g
    titleBackAnimTimer = 0.0f;
    titleBackAnimFrame = 0;
    // �X�P�[����ԗp�ϐ��̃��Z�b�g
    currentScale = { 1.0f, 1.0f };

    
}


 
   


void GameBackImage() {
    gameBack.spriteID = LoadGraph(L"./Data/images/haikei.png");
    if (gameBack.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/haikei.png");
    }
    gameFloor.spriteID = LoadGraph(L"./Data/images/front_lane.png");
    if (gameFloor.spriteID == -1) {
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/front_lane.png");
    }

}


int ButtonPosition(DxPlus::Vec2 pos, DxPlus::Vec2 mousePos)
{
    int width = 370;  // ���iX�����j
    int height = 90;  // �����iY�����j

    DxPlus::Vec2 leftTop = pos;
    DxPlus::Vec2 rightBottom = { pos.x + width, pos.y + height };

    DrawBox(
        leftTop.x,
        leftTop.y,
        rightBottom.x,
        rightBottom.y,
        DxLib::GetColor(255, 0, 0),
        true
    );

    return (leftTop.x < mousePos.x && leftTop.y < mousePos.y &&
        rightBottom.x > mousePos.x && rightBottom.y > mousePos.y);
}

void GameBackUpdate() {
}

void TitleBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center, bool start, bool set, bool fin, bool* gamePlay) {
    // �^�C�g���w�i�A�j���[�V�����`��
    if (*gamePlay) {
        // �X�P�[�����Ԃ��ď��X�ɑ傫������
        currentScale.x += (targetScale.x - currentScale.x) * scaleSpeed * titleBackAnimSpeed;
        currentScale.y += (targetScale.y - currentScale.y) * scaleSpeed * titleBackAnimSpeed;

        // �^�C�g���v���C�A�j���[�V�����`��i1�񂾂��Đ��j
        int playFrame = titleBackAnimFrame;
        if (playFrame >= TITLE_BACKPLAY_NUM) {
            playFrame = TITLE_BACKPLAY_NUM - 1; // �Ō�̃t���[���Ŏ~�߂�
        }
        if (TitlePlay[playFrame].spriteID != -1) {
            DxPlus::Sprite::Draw(TitlePlay[playFrame].spriteID, position, currentScale, center); // �g��̂�
        }
    } else {
        // �ʏ�̃^�C�g���w�i�A�j���[�V�����i�J��Ԃ��j
        int frame = titleBackAnimFrame % TITLE_BACK_NUM;
        if (titleBack[frame].spriteID != -1) {
            DxPlus::Sprite::Draw(titleBack[frame].spriteID, position, scale, center);
        }
    }

    // �{�^���`��
    for (int i = 0; i < TITLE_BUTTON_NUM; ++i) {
        if (Button[i].spriteID != -1) {
            DxPlus::Vec2 offset;
            DxPlus::Vec2 buttonScale;

            if (i == 0) { // �^�C�g�����S
                offset = { -50.0f, 50.0f };
                buttonScale = { 0.5f, 0.5f };
            } else { // ���̑��̃{�^��
                offset = { 100.0f, 80.0f + i * 144.0f };
                buttonScale = { 0.9f, 0.9f };
            }

            float alpha = 255.0f;
            float crick = 100.0f;
            if (start && i == 1) {
                alpha = crick; // �Â�
            }
            if (set && i == 2) {
                alpha = crick;
            }
            if (fin && i == 3) {
                alpha = crick;
            }

            DxPlus::Sprite::Draw(Button[i].spriteID, buttonBase + offset, buttonScale, { 0.0f, 0.0f }, 0.0f, GetColor(alpha, alpha, alpha));
        }
    }

    // �A�j���[�V�����X�V
    if (*gamePlay) {
        // TitlePlay �̃A�j���[�V�����͈�񂾂��Đ�
        if (titleBackAnimFrame < TITLE_BACKPLAY_NUM - 1) {
            titleBackAnimTimer += titleBackAnimSpeed * 3; // �`�摬�x
            if (titleBackAnimTimer >= 1.0f) {
                titleBackAnimTimer -= 1.0f;
                titleBackAnimFrame++;
            }
        }
    } else {
        // �ʏ�̃^�C�g���w�i�A�j���[�V�����͌J��Ԃ�
        titleBackAnimTimer += titleBackAnimSpeed;
        if (titleBackAnimTimer >= 1.0f) {
            titleBackAnimTimer -= 1.0f;
            titleBackAnimFrame = (titleBackAnimFrame + 1) % TITLE_BACK_NUM;
        }
    }
}

void GameBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center) {
    DxPlus::Sprite::Draw(gameBack.spriteID,position, scale, center);
}

void GameFloorDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center) {
    DxPlus::Sprite::Draw(gameFloor.spriteID, position, scale, center);
}

void TitleBackDelete() {
    // titleBack �z��̃X�v���C�g���폜
    for (int i = 0; i < TITLE_BACK_NUM; ++i) {
        if (titleBack[i].spriteID != -1) {
            DxPlus::Sprite::Delete(titleBack[i].spriteID);
            titleBack[i].spriteID = -1; // �����ɏ�����
        }
    }

    // Button �z��̃X�v���C�g���폜
    for (int i = 0; i < TITLE_BUTTON_NUM; ++i) {
        if (Button[i].spriteID != -1) {
            DxPlus::Sprite::Delete(Button[i].spriteID);
            Button[i].spriteID = -1; // �����ɏ�����
        }
    }

    // TitlePlay �z��̃X�v���C�g���폜
    for (int i = 0; i < TITLE_BACKPLAY_NUM; ++i) {
        if (TitlePlay[i].spriteID != -1) {
            DxPlus::Sprite::Delete(TitlePlay[i].spriteID);
            TitlePlay[i].spriteID = -1; // �����ɏ�����
        }
    }
}

void GameBackDelete() {
    if (gameBack.spriteID != -1) {
        DxPlus::Sprite::Delete(gameBack.spriteID);
    }
}

struct Rank {

	int spriteID = -1;
	DxPlus::Vec2 BasePos = { 340.0f, 350.0f };
	DxPlus::Vec2 pos = { BasePos };
	DxPlus::Vec2 scale = { 0.8f, 0.8f };
	DxPlus::Vec2 center = { 0.0f, 0.0f };

};  
enum RankType {
    Star0,
    Star1,
    Star2,
    Star3,
};
Rank ResultRank[5];
Rank TitleTo;

const int MIN_SCORE_FOR_1_STAR  = 500;    // 1�����l�����邽�߂̍ŏ��X�R�A
const int MIN_SCORE_FOR_2_STARS = 1000;  // 2�����l�����邽�߂̍ŏ��X�R�A
const int MIN_SCORE_FOR_3_STARS = 2000;  // 3�����l�����邽�߂̍ŏ��X�R�A


// Result�֘A--------------------------
void ResultBackImage() {
    const wchar_t* animPaths[RESULT_ANIM_COUNT] = {
        L"./Data/images/Result1.png",
        L"./Data/images/Result2.png",
        L"./Data/images/Result3.png",
        L"./Data/images/Result4.png",
        L"./Data/images/Result5.png",
        L"./Data/images/Result6.png",
        L"./Data/images/Result7.png"
    };

    for (int i = 0; i < RESULT_ANIM_COUNT; ++i) {
        ResultAnimation[i] = LoadGraph(animPaths[i]);
        if (ResultAnimation[i] == -1) {
            DxPlus::Utils::FatalError((std::wstring(L"Failed to load sprite: ") + animPaths[i]).c_str());
        }
    }

    //����
    //���O
	ResultRank[Star0].spriteID = LoadGraph(L"./Data/images/star0.png");
    if(ResultRank[Star0].spriteID == -1){
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/star0.png");
	}
	//���P
	ResultRank[Star1].spriteID = LoadGraph(L"./Data/images/star1.png");
    if(ResultRank[Star1].spriteID == -1){
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/star1.png");
	}
	//���Q
	ResultRank[Star2].spriteID = LoadGraph(L"./Data/images/star2.png");
    if(ResultRank[Star2].spriteID == -1){
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/star2.png");
	}
	//���R
	ResultRank[Star3].spriteID = LoadGraph(L"./Data/images/star3.png");
    if (ResultRank[Star3].spriteID == -1) {
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/star3.png");
    }
    //�^�C�g����
	TitleTo.spriteID = LoadGraph(L"./Data/images/back_title.png");
    if (TitleTo.spriteID == -1) {
        DxPlus::Utils::FatalError(L"Failed to load sprite: ./Data/images/back_title.png");
    }
	TitleTo.pos = { TitleTo.BasePos.x + 0.0f, TitleTo.BasePos.y + 230.0f };// �����ʒu	
    ResultRank[Star0].center = { 269.5f, 330.0f };
	ResultRank[Star1].center = { 269.5f, 330.0f };
	ResultRank[Star2].center = { 269.5f, 330.0f };
	ResultRank[Star3].center = { 269.5f, 330.0f };

	TitleTo.center = { 89.5f, 11.0f };
}

void ResultBackReset() {
    currentFrame = 0;
    animTimer = 0.0f;
	TitleTo.scale = { 1.0f,1.0f };
}

void ResultBackUpdate(int mouX,int mouY,int *resultState) {
    animTimer += animSpeed;
        static int prevMouseInput = 0;
        int currentMouseInput = GetMouseInput();
    // �t���[����i�߂�
    if (animTimer >= 1.0f) {
        animTimer -= 1.0f;
        currentFrame = (currentFrame + 1) % RESULT_ANIM_COUNT; // ���[�v
    }
	int titletoWidth = 179 * TitleTo.scale.x; // �^�C�g���փ{�^���̕�
    int titletoHeight = 22 * TitleTo.scale.y; // �^�C�g���փ{�^���̍���
    if (mouX > TitleTo.pos.x - titletoWidth/2 && mouX < TitleTo.pos.x + titletoWidth/2 &&
        mouY > TitleTo.pos.y - titletoHeight/2 && mouY < TitleTo.pos.y + titletoHeight/2)
    {


        if ((currentMouseInput & MOUSE_INPUT_LEFT) && !(prevMouseInput & MOUSE_INPUT_LEFT)) {
            *resultState = 2;
        }

 

        TitleTo.scale = { 1.2f,1.2f };
        
    }
    else {
        TitleTo.scale = { 1.0f,1.0f };
    }
    prevMouseInput = currentMouseInput;
}

void ResultBackDraw(DxPlus::Vec2 position, DxPlus::Vec2 scale, DxPlus::Vec2 center,int score) {
    if (ResultAnimation[currentFrame] != -1) {
		DxPlus::Sprite::Draw(ResultAnimation[currentFrame], position, scale, center);
    }
    //�X�R�A�ɂ���ĕ\����ς���
    if (score >= MIN_SCORE_FOR_3_STARS) {
        DxPlus::Sprite::Draw(ResultRank[Star3].spriteID, ResultRank[Star3].pos, ResultRank[Star3].scale, ResultRank[Star3].center);
    }
    else if (score >= MIN_SCORE_FOR_2_STARS) {
        DxPlus::Sprite::Draw(ResultRank[Star2].spriteID, ResultRank[Star2].pos, ResultRank[Star2].scale, ResultRank[Star2].center);
    }
    else if (score >= MIN_SCORE_FOR_1_STAR) {
        DxPlus::Sprite::Draw(ResultRank[Star1].spriteID, ResultRank[Star1].pos, ResultRank[Star1].scale, ResultRank[Star1].center);
    }
    else {
        DxPlus::Sprite::Draw(ResultRank[Star0].spriteID, ResultRank[Star0].pos, ResultRank[Star0].scale, ResultRank[Star0].center);
	}

	DxPlus::Sprite::Draw(TitleTo.spriteID, TitleTo.pos, TitleTo.scale, TitleTo.center);

}

void ResultBackDelete() {
    for (int i = 0; i < RESULT_ANIM_COUNT; ++i) {
        if (ResultAnimation[i] != -1) {
            DxPlus::Sprite::Delete(ResultAnimation[i]);
            ResultAnimation[i] = -1;
        }
    }
}
