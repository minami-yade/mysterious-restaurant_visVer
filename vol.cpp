#include "vol.h"

float g_volume = 255.0f; // ���̂͂�����1�����I

float GetVolume()
{
    return g_volume;
}

void SetVolume(float newVolume)
{
    g_volume = std::clamp(newVolume, 0.0f, 255.0f);
}
//std::clamp�i�����񂾁[�ǁE�����Ձj�́A
//�u�l�����͈̔͂Ɏ��߂�v�i�͂ݏo���Ȃ��悤�ɂ���j���߂̊֐��ł��B