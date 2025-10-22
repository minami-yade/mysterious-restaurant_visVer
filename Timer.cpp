#include "Timer.h"

int TimerSpriteID = -1;
int needleSpriteID = -1;
float needleAngle = 0;
float needleSpeed = 0;
const float TIME_LIMIT = 120.0f; // �^�C�����~�b�g�i�b�j
const DxPlus::Vec2 TimerPos = { 640.0f,150.0f };
const DxPlus::Vec2 TimerScale = { 0.5f,0.5f };

void Timer_Image() {
	TimerSpriteID = LoadGraph(L"./Data/Images/not_needle.png");
	if (TimerSpriteID == -1) {
		DxPlus::Utils::FatalError(L"Failed to load not_needle image.");
	}
	needleSpriteID = LoadGraph(L"./Data/Images/needle.png");
	if (needleSpriteID == -1) {
		DxPlus::Utils::FatalError(L"Failed to load needle image.");
	}
}

void Timer_Reset(float& timeLeft) {
	timeLeft = TIME_LIMIT; // �^�C�}�[��������
	needleAngle = 0;
	needleSpeed = 360 / (TIME_LIMIT * 60)* 1.05; // 1�b������̐j�̉�]���x
}

void Timer_Update(float& timeLeft, float deltaTime, int& gameState) {
	
	if(needleAngle > 6.3) {
		needleAngle = 6.3;
	}
	else
		timeLeft -= deltaTime;

	if (timeLeft < 0.0f) {
		timeLeft = 0.0f;
		gameState = 3;//�Q�[�������
	}
	needleAngle += needleSpeed * deltaTime;
	
}

void Timer_DrawGauge(float timeLeft) {
	const float radius = 80.0f * TimerScale.x;
	const int segments = 600;

	float ratio = timeLeft / TIME_LIMIT;
	float endAngle = 360.0f * ratio;

	for (int i = 0; i < segments; ++i) {
		float angleStart = (360.0f / segments) * i;
		float angleEnd = (360.0f / segments) * (i + 1);

		// ���v���Ɍ��炷���߁A360����������͈͂�`��
		if (angleStart >= (360.0f - endAngle)) break;



		// �X�^�[�g�n�_�����
		float radStart = DX_PI * (angleStart - 90.0f) / 180.0f;
		float radEnd = DX_PI * (angleEnd - 90.0f) / 180.0f;

		float x1 = TimerPos.x + cos(radStart) * radius + 2;
		float y1 = TimerPos.y + sin(radStart) * radius;
		float x2 = TimerPos.x + cos(radEnd) * radius + 2;
		float y2 = TimerPos.y + sin(radEnd) * radius;

		DrawTriangle(TimerPos.x + 2, TimerPos.y, x1, y1, x2, y2, GetColor(255, 0, 0), TRUE);
	}
}

void Timer_Draw(float timeLeft) {
	
	DxPlus::Sprite::Draw(TimerSpriteID,  TimerPos, TimerScale, { 176.0f,250.0f });
	Timer_DrawGauge(timeLeft);
	DxPlus::Sprite::Draw(needleSpriteID, TimerPos, TimerScale * 1.2, { 7.0f,74.0f },  needleAngle,GetColor(255,255,255));

}

void Timer_Delete() {
	if (TimerSpriteID != -1) {
		DxLib::DeleteGraph(TimerSpriteID);
		TimerSpriteID = -1;
	}
}
