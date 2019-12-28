#pragma once
#include <vector>
#include <string>
#include <functional>
#include "DxLib.h"



/*
ロードのファイルを指定するための列挙
*/
enum class ELOADFILE { graph, soundEffect, model, backGroundMusic, sound3DEffect };



/*
マクロ
*/
// ポインタ用解放マクロ
#define POINTER_RELEASE(p) { if(p!=nullptr) {delete (p); (p)=nullptr; } }
// 2D関連画像解放マクロ
#define GRAPHIC_RELEASE(p) { if(p!=-1) { DeleteGraph(p); (p)=-1; } }
// 3D関連画像解放マクロ
#define MODEL_RELEASE(p) { if(p!=-1) { MV1DeleteModel(p); (p)=-1; } }
// 音解放マクロ
#define SOUND_RELEASE(p) { if(p!=-1) { StopSoundMem(p); DeleteSoundMem(p); (p)=-1; } }
// シャドウマップ解放マクロ
#define SHADOW_MAP_RELEASE(p) { if(p!=-1) { DeleteShadowMap(p); (p)=-1; } }



/*
全体の基本的なことを管理する
*/
class Basic
{
};

