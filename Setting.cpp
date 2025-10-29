#include "DxPlus/DxPlus.h"
#include "Setting.h"
#include "WinMain.h"
#include "Entity2D.h"
#include "Back.h"
#include"vol.h"



Entity2D settingBack[TITLE_BACK_NUM];
constexpr int SETTING_BUTTON_NUM = 6;// ボタンの数
enum SettingButtonType {
    VolRight,
    VolLeft,
    easy,
	normal,
	hard,
    BackToTitle,
    vol_right,
    vol_left
};
Entity2D settingButton[SETTING_BUTTON_NUM];//学校の自分にいいます。ここまでしかやってません//hai
Entity2D setBackground;
//----------------------------------------------------------------------
// 定数
//----------------------------------------------------------------------
bool wasMousePressed = false;

// アニメーション用
float settingBackAnimTimer = 0.0f;
int settingBackAnimFrame = 0;
float settingBackAnimSpeed = 0.05f; // 秒（小さいほど）
//----------------------------------------------------------------------
// 変数
//----------------------------------------------------------------------

int GameMode = 1; // 0: easy, 1: normal, 2: hard


int SettingState;
float SettingFadeTimer;
extern int nextScene;
int vol_kachi2;

bool prevHit[SETTING_BUTTON_NUM] = { false };
//----------------------------------------------------------------------
// 初期設定
//----------------------------------------------------------------------
void Setting_Init()
{
	setBackground.spriteID = LoadGraph(L"./Data/images/kanban.png");
    if(setBackground.spriteID == -1){
        DxPlus::Utils::FatalError(L"failed to load sprite : ./Data/images/kanban.png");
	}
    vol_kachi2 = DxLib::LoadSoundMem(L"./Data/Sounds/shush.mp3");
    if (vol_kachi2 == -1)
    {
        DxPlus::Utils::FatalError(L"./Data/Sounds/shush.mp3");
    }	ChangeVolumeSoundMem((int)GetVolume(), vol_kachi2);

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
            case VolRight:
                settingButton[i].spriteID = LoadGraph(L"./Data/images/vol_up.png");
				break;
			case VolLeft:
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
				settingButton[i].spriteID = LoadGraph(L"./Data/images/goback_title.png");
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
        float baseX = 200.0f;
        switch (i)
        {
        case VolRight:
            settingButton[i].position = { 925.0f, 250.0f };
            break;
        case VolLeft:
            settingButton[i].position = { 675.0f, 250.0f };
            break;
        case easy:
            settingButton[i].position = { baseX, 275.0f };
            break;
        case normal:
            settingButton[i].position = { baseX, 405.0f };
            break;
        case hard:
            settingButton[i].position = { baseX, 535.0f };
            break;
        case BackToTitle:
            settingButton[i].position = { 600.0f, 400.0f };
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

void Setting_Button_CI(DxPlus::Vec2 pos, float radius, int* upDown, bool plus) {
    // マウスの位置を取得
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    DxPlus::Vec2 mousePos = { static_cast<float>(mouseX), static_cast<float>(mouseY) };
    bool isHit = false;

 
        // マウスとボタンの中心の距離を計算
        float distance = std::sqrt(std::pow(mousePos.x - pos.x, 2) + std::pow(mousePos.y - pos.y, 2));

        // 当たり判定
        isHit = distance <= radius;
#if _DEBUG
        // デバッグ表示: ボタンの円形境界を描画
        int color = isHit ? GetColor(255, 255, 255) : GetColor(255, 0, 0);
        DrawCircle(static_cast<int>(pos.x), static_cast<int>(pos.y), static_cast<int>(radius), color, FALSE);
#endif
  

        // マウスクリック状態を取得
        wasMousePressed = false; // 前回のクリック状態を保持
        int mouseInput = GetMouseInput();
        bool isMouseClicked = (mouseInput & MOUSE_INPUT_LEFT) != 0;

        // 当たり判定が成立し、かつクリックが押された瞬間のみ処理を実行
        if (isHit && isMouseClicked && !wasMousePressed && SettingState == 1) {
            *upDown += plus ? 1 : -1;
        }

        // 現在のクリック状態を保存
        wasMousePressed = isMouseClicked;

    
}

void Setting_Button_SQ(DxPlus::Vec2 pos, DxPlus::Vec2 length, int mode) {
    bool isHit = false;
    // マウスの位置を取得
    int mouseX, mouseY;
    GetMousePoint(&mouseX, &mouseY);
    DxPlus::Vec2 mousePos = { static_cast<float>(mouseX), static_cast<float>(mouseY) };
    // 当たり判定
    isHit = (mousePos.x > pos.x && mousePos.x < pos.x + length.x &&
        mousePos.y > pos.y && mousePos.y < pos.y + length.y);
#if _DEBUG
    // デバッグ表示: ボタンの矩形境界を描画
    int color = isHit ? GetColor(255, 255, 255) : GetColor(255, 0, 0);
    DrawBox(static_cast<int>(pos.x), static_cast<int>(pos.y),
        static_cast<int>(pos.x + length.x), static_cast<int>(pos.y + length.y),
        color, FALSE);
#endif
    // マウスクリック状態を取得
    wasMousePressed = false; // 前回のクリック状態を保持
    int mouseInput = GetMouseInput();
    bool isMouseClicked = (mouseInput & MOUSE_INPUT_LEFT) != 0;



    if (isHit && !prevHit[mode]) {
        PlaySoundMem(vol_kachi2, DX_PLAYTYPE_BACK);
    }

    if (isHit)
    {
        settingButton[mode].scale = { 1.2f,1.2f };
    }
    else
    {
        settingButton[mode].scale = { 1.0f,1.0f };
    }
    // 当たり判定が成立し、かつクリックが押された瞬間のみ処理を実行
    if (isHit && isMouseClicked && !wasMousePressed && SettingState == 1) {
        if (mode == BackToTitle) {
            SettingState = 2; // フェードアウト状態に変更
        }
        else {
            GameMode = mode - 2; // 他のボタンの処理
        }
    }

    // 現在のクリック状態を保存
    wasMousePressed = isMouseClicked;

    prevHit[mode] = isHit;
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
        // 現在のモード以外のボタンを薄くする
        if (i == easy + GameMode) {
            DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255); // 通常描画
        }
        else if (i == 2 || i == 3 || i == 4) {

            DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128); // 半透明
        }
        if (i == BackToTitle)
            DxPlus::Sprite::Draw(settingButton[i].spriteID, settingButton[i].position, { 1.0f,1.0f }, { 0.0f,0.0f });
        else
            DxPlus::Sprite::Draw(settingButton[i].spriteID, settingButton[i].position, { settingButton[i].scale }, { 0.0f,0.0f });
        DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

    }
    // ボタンの当たり判定処理
    Setting_Button_SQ(settingButton[easy].position, {230,50}, easy);
    Setting_Button_SQ(settingButton[normal].position, {170,50}, normal);
    Setting_Button_SQ(settingButton[hard].position, {300,50}, hard);

    
    DxPlus::Vec2 BaseSize = { 50,100 };
    DxPlus::Vec2 StartPos = settingButton[BackToTitle].position;
    DxPlus::Vec2 Offset = { 20, 4 }; // 少しずつずらす量

    for (int i = 0; i < 20; ++i) {
        DxPlus::Vec2 pos = StartPos + Offset * i;
        Setting_Button_SQ(pos, BaseSize, BackToTitle);
    }

    // フェードイン / フェードアウト用
    if (SettingFadeTimer > 0.0f) {
        DxLib::SetDrawBlendMode(DX_BLENDMODE_ALPHA, (int)(255 * SettingFadeTimer));
        DxPlus::Primitive2D::DrawRect({ 0,0 }, { DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT },
            DxLib::GetColor(0, 0, 0));
        DxLib::SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
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
