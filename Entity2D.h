#pragma once
#include "DxPlus/DxPlus.h"

struct Entity2D
{
    //�ʒu�֌W
    DxPlus::Vec2 position = {};
    DxPlus::Vec2 velocity = {};
    //�摜
    int spriteID = -1;
	DxPlus::Vec2 scale = { 1.0f, 1.0f };
	DxPlus::Vec2 Center = { 64.0f, 64.0f };


    //player
    int score = 0;
    //Vegetable
    int havescore = 0;
	bool isActive = false;
	float speed = 0.0f;
	int type = 0; //�@0:�L���x�c
    float  baseY;        // ���
    float amplitude;    // �U���i�ő卂�� - baseY�j
    float period;       // �����i�b�j
    float timeAcc = 0;  // �ݐώ��ԁi�����ŊǗ��j

};
const int PLAYER_NUM = 9;

const int VEGETABLE_NUM = 12;
const int VEGETABLE_TYPE = 1; // 0:�L���x�c