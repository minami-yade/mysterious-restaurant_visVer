#include "DxPlus/DxPlus.h"
#include "WinMain.h"
#include "Game.h"
#include "Title.h"
#include "Result.h"
#include "Clear.h"
#include "Battle.h"


int currentScene = SceneNone;
int nextScene = SceneTitle;

int fontID1 = -1;

//�J�X�^���E�B���h�E�v���V�[�W���̃v���g�^�C�v�錾
static LRESULT CALLBACK CustomWinProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

int WINAPI wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
	constexpr bool WINDOWED = TRUE; //�E�B���h�E���[�h

	// DxPIus()X ���C�v����)�̏�����
	if (DxPlus::Initialize(DxPlus::CLIENT_WIDTH, DxPlus::CLIENT_HEIGHT, WINDOWED) == -1)
	{
		return -1;//���������s
	}
	//�E�B���h�E�v���V�[�W����ݒ�
	DxLib::SetHookWinProc(CustomWinProc);

	//Game_Init();
	if (AddFontResourceExW(L"./Data/Fonts/Yusei_Magic/YuseiMagic-Regular.ttf", FR_PRIVATE, 0) == 0)
	{
		DxPlus::Utils::FatalError(L"Failed to add font: ./Data/Fonts/Yusei_Magic/YuseiMagic-Regular.ttf");
	}
	fontID1 = DxPlus::Text::InitializeFont(L"Yusei Magic", 30, 5);
	if (fontID1 == -1)
	{
		DxPlus::Utils::FatalError(L"Failed to init font: Yusei Magic");
	}

	//�Q �[ ���� �[ �v
	while (DxPlus::GameLoop())
	{
		//�V-�����؂�ւ��Ȃ� 
		if (nextScene != SceneNone) {
			//���̃V �[ ���̏I���֐����Ă�
			switch (currentScene) {

			case SceneTitle:
				Title_End();
				break;

			case SceneGame:
				Game_End();
				break;

			case SceneResult:
				Result_End();
				break;
			case SceneBattle:
				Battle_End();
				break;
			case SceneClear:
				Clear_End();
				break;
			}

			//���̃V�[���̏����ݒ�֐����Ă�
			switch (nextScene) {

			case SceneTitle:
				Title_Init();
				break;

			case SceneGame:
				Game_Init();
				break;

			case SceneResult:
				Result_Init();
				break;

			case SceneBattle:
				Battle_Init();
				break;

			case SceneClear:
				Clear_Init();
				break;

			}

			//�V�[���̐؂�ւ��𔽉f�����A���̃V�[���w����N���A���Ă��� 
			currentScene = nextScene;
			nextScene = SceneNone;
		}

		DxPlus::Input::Update();

		//���̃V�[���̍X�V�����ƕ`�揈�����Ă� 
		switch (currentScene) {

		case SceneTitle:
			Title_Update();
			Title_Render();
			break;

		case SceneGame:
			Game_Update();
			Game_Render();
			break;

		case SceneResult:
			Result_Update();
			Result_Render();
			break;

		case SceneClear:
			Clear_Update();
			Clear_Render();
			break;

		case SceneBattle:
			Battle_Update();
			Battle_Render();
			break;
		}

		//DxPlus::Debug::Draw();

		//��ʂ��N���A����
		DxLib::ScreenFlip();
		DxLib::ClearDrawScreen();
	}
	//Game_End();
	//�I�������֐����Ă� 
	switch (currentScene) {

	case SceneTitle:
		Title_End();
		break;

	case SceneGame:
		Game_End();
		break;

	case SceneResult:
		Result_End();
		break;

	case SceneClear:
		Clear_End();
		break;

	case SceneBattle:
		Battle_End();
		break;
	
	}


	// DxPIus �̏I������
	DxPlus::ShutDown();

	//�߂�l�� 0 �ł悢
	return 0;
}

//�E�C���h�E�u���V �[ �W��
LRESULT CALLBACK CustomWinProc(HWND, UINT msg, WPARAM wParam, LPARAM)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE)
		{
			PostQuitMessage(0);
		}
		break;
	}
	return 0;
}