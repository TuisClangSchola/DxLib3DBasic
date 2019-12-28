#pragma once
#include <vector>
#include <string>
#include <functional>
#include "DxLib.h"



/*
���[�h�̃t�@�C�����w�肷�邽�߂̗�
*/
enum class ELOADFILE { graph, soundEffect, model, backGroundMusic, sound3DEffect };



/*
�E�B���h�E�T�C�Y�����߂�
*/
namespace BasicParam
{
	extern int winWidth;
	extern int winHeight;
	extern int bitColor;
}



/*
�}�N��
*/
// �|�C���^�p����}�N��
#define POINTER_RELEASE(p) { if(p!=nullptr) {delete (p); (p)=nullptr; } }
// 2D�֘A�摜����}�N��
#define GRAPHIC_RELEASE(p) { if(p!=-1) { DeleteGraph(p); (p)=-1; } }
// 3D�֘A�摜����}�N��
#define MODEL_RELEASE(p) { if(p!=-1) { MV1DeleteModel(p); (p)=-1; } }
// ������}�N��
#define SOUND_RELEASE(p) { if(p!=-1) { StopSoundMem(p); DeleteSoundMem(p); (p)=-1; } }
// �V���h�E�}�b�v����}�N��
#define SHADOW_MAP_RELEASE(p) { if(p!=-1) { DeleteShadowMap(p); (p)=-1; } }

