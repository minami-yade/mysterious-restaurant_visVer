#include "DxPlus/DxPlus.h"
#include "Setting.h"
#include "WinMain.h"
#include "Entity2D.h"
#include "Back.h"



Entity2D settingBack[TITLE_BACK_NUM];
constexpr int SETTING_BUTTON_NUM = 6;// ボタンの数
enum SettingButtonType {
    VolUp,
    VolDown,
    easy,
	normal,
	hard,
    BackToTitle
};
Entity2D settingButton[SETTING_BUTTON_NUM];//学校の自分にいいます。ここまでしかやってません//hai
Entity2D setBackground;
//----------------------------------------------------------------------
// 定数
//----------------------------------------------------------------------

// アニメーション用
float settingBackAnimTimer = 0.0f;
int settingBackAnimFrame = 0;
float settingBackAnimSpeed = 0.05f; // 秒（小さいほど）
//----------------------------------------------------------------------
// 変数
//----------------------------------------------------------------------

int SettingState;
float SettingFadeTimer;
extern int nextScene;

//----------------------------------------------------------------------
// 初期設定
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
// リセット
//----------------------------------------------------------------------
void Setting_Reset()
{
    // アニメーション用変数のリセット
    settingBackAnimTimer = 0.0f;
    settingBackAnimFrame = 0;

	//ボタン用変数のリセット
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
	// フェード用変数のリセット
    SettingState = 0;
    SettingFadeTimer = 1.0f;


}
//----------------------------------------------------------------------
// 更新処理
//----------------------------------------------------------------------
void Setting_Update()
{   
	// アニメーション更新
	settingBackAnimTimer += settingBackAnimSpeed;
	if (settingBackAnimTimer >= 1.0f) {
		settingBackAnimTimer = 0.0f;
		settingBackAnimFrame = (settingBackAnimFrame + 1) % TITLE_BACK_NUM;

	}
   

	// フェードイン / フェードアウト処理
    Setting_Fade();
}

void Setting_Button(DxPlus::Vec2 pos, float radius, int *upDown, bool plus) {
    // マウスの位置を取得
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    DxPlus::Vec2 mousePos = { static_cast<float>(mouseX), static_cast<float>(mouseY) };

    // マウスとボタンの中心の距離を計算
    float distance = std::sqrt(std::pow(mousePos.x - pos.x, 2) + std::pow(mousePos.y - pos.y, 2));

    // 当たり判定
    bool isHit = distance <= radius;

    // デバッグ表示: ボタンの円形境界を描画
    int color = isHit ? GetColor(255, 255, 255) : GetColor(255, 0, 0); 
    DrawCircle(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(radius), color, TRUE);

    // マウスクリック状態を取得
    static bool wasMousePressed = false; // 前回のクリック状態を保持
    int mouseInput = GetMouseInput();
    bool isMouseClicked = (mouseInput & MOUSE_INPUT_LEFT) != 0;

    // 当たり判定が成立し、かつクリックが押された瞬間のみ処理を実行
    if (isHit && isMouseClicked && !wasMousePressed && SettingState == 1) {
        *upDown += plus ? 1 : -1;
    }

    // 現在のクリック状態を保存
    wasMousePressed = isMouseClicked;
}


//----------------------------------------------------------------------
// 描画処理
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
    //これを使ってボタン作成
    Setting_Button({ 200.0f, 300.0f }, 50.0f, &SettingState, true);

    // フェードイン / フェードアウト用 
    if (SettingFadeTimer > 0.0f) {
        //画面
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * SettingFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0)); DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }



}



void Setting_Fade()
{
    switch (SettingState) {
    case 0: // フェードイン中 
    {
        SettingFadeTimer -= 1 / 60.0f;
        if (SettingFadeTimer < 0.0f) {
            SettingFadeTimer = 0.0f;
            SettingState++;
        }
        break;
    }
    case 1: // 通常時
    {
        // BackSpace キーが押されたらタイトルに戻す 
        int input = DxPlus::Input::GetButtonDown(DxPlus::Input::PLAYER1);
        if (input & DxPlus::Input::BUTTON_SELECT) {
            SettingState++;
        }
        break;
    }
    case 2: // フェードアウト中
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
            settingBack[i].spriteID = -1; // 解放後に初期化
        }
    }
}
