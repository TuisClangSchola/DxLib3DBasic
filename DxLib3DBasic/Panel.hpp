#pragma once
#include "Basic.hpp"



/*
当たり判定を知らしめるためのパネル
*/
class Panel
{
private:
	int m_model;


public:
	Panel(const int& t_model);
	~Panel();


	void Draw();
};


/*
ちょっとプログラムに意地悪をしました(*''ω''*)。理由：だんだんめんどくさくなってきた
それを考慮してアドバイス。
その１：スクリーン外に出たら描画をさせないようにしていない。CheckCameraViewClip_Boxとかええよ。
その２：モデル用意するのめんどくさかったら天下無双二体目。
*/
