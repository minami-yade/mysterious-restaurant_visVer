#pragma once
#include "Entity2D.h"


// --- �摜�ǂݍ��݊֌W ---
void VegetableImage();

// --- ���Z�b�g�֐��i�����z�u���Ԃ̏������j ---
void VegetableReset();

// --- �����̍X�V�i�P���ȎO�p�g�ŏ㉺�j ---
void UpdateVegetable(int i,float deltaTime);

// ��ʊO���烉���_���ɏo��

void SpawnTimeVegetable(int i, int* Timer);

// --- �`��֐� ---
void VegetableDraw(int i);

// --- ����֐� ---
void VegetableDelete(int i);