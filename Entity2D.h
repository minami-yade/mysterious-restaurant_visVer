#pragma once
#include "DxPlus/DxPlus.h"

struct Entity2D
{
    //�ʒu�֌W
    DxPlus::Vec2 position = {};
    DxPlus::Vec2 velocity = {};
	float gravity = 0.98f; // �d�͉����x
	float speed = 0.0f;

    //�摜
    int spriteID = -1;
	DxPlus::Vec2 scale = { 1.0f, 1.0f };
	DxPlus::Vec2 center = { 64.0f, 64.0f };
	bool isActive = false;
	float radius = 30.0f; // �����蔻��p�̔��a
	
	
	//�t�b�N�Ŏg��
	float angle = 0;
	DxPlus::Vec2 target = {};
	DxPlus::Vec2 HomePositionLeft = {};
	DxPlus::Vec2 HomePositionRight = {};
	bool isCarryingVegetable = false;
	Entity2D* carriedVegetable = nullptr; // �|�C���^�ɕύX
	DxPlus::Vec2 upHookLeft = {};
	DxPlus::Vec2 upHookRight = {};
	bool reachedUpHook = false;

    //Vegetable
    int havescore = 0;
	float  baseY = {};        // ���
	float JumpPower = 10.0f;
	int moveVegetable = 0;//0�ʏ�,1�t�b�N�ɕ߂܂���,2�t�b�N�ɕ߂܂���������ꂽ
	int vegAnimNum = -1;


	//mouse
	bool click = false;
	float timer = 0.0f;
	DxPlus::Vec2 pointer = { 0,0 };
	int effectID = -1;

	//enemy
	int moveenemy = 0;//0�ʏ�,1�t�b�N�ɕ߂܂���,2�t�b�N�ɕ߂܂���������ꂽ
	bool helpEnemy = false;
	int mouseAnim = -1;

    // --- UFO �p�t�B�[���h ---
    bool isUFO = false;
    int ufoLightAnim = 0;
    float ufoLightTimer = 0.0f;

    int ufoVegetableIndex = -1;
    bool ufoHasVegetable = false;

    int ufoDropState = 0; // 0=��,1=�h���b�v��,2=�㏸�ޏ�,3=����(�j��)
    float ufoDropTimer = 0.0f;
    bool ufoBeingTaken = false;

    // �t�F�[�h�p
    float alpha = 1.0f;      // 1.0 = �s����, 0.0 = ����
    bool fading = false;
    float fadeSpeed = 1.0f;  // alpha �������x

    // ��]�i�������̉�]���x��ێ��j
    float angularVelocity = 0.0f; // deg/s
};
const int PLAYER_NUM = 11;

const int VEGETABLE_TYPE = 7; // 0:�L���x�c
const int VEGETABLE_NUM = 5 * VEGETABLE_TYPE;
const int VEG_ANIM_NUM = 3; //�A�j���[�V�����t���[����

const int MOUSE_ANIM_NUM = 4;//�A�j���[�V�����t���[����
const int UFO_ANIM_NUM = 3;//�A�j���[�V�����t���[����
const int ENEMY_TYPE = 2; // 0:�˂���
const int ENEMY_NUM = 5 * ENEMY_TYPE;

const int BOWL_EFFECT_NUM = 3;

const int TITLE_BACK_NUM = 5;
const int TITLE_BACKPLAY_NUM = 8;
const int TITLE_BUTTON_NUM = 4;

const int RESULT_ANIM_COUNT = 7;

const int ANI_SOMESHING_NUM = 5;//�����̃A�j���[�V�����\��


enum HookState {
	FlyingOut,
	Returning,
	Idle
};
