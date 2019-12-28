#pragma once
#include "Basic.hpp"



/*
今回は天下無双に頑張ってもらいました。
*/
class Character
{
private:
	int m_model;

	VECTOR m_area;

	float m_walkSpeed;

	bool m_moveFlag;

	enum class DIRECTION { left, down, right, up };

	bool m_direction[4];
	bool m_preDirection[4];


public:
	Character(const int& t_model);
	~Character();


	void Draw();
	void Process(const float t_angle);

	const VECTOR GetArea() const { return m_area; }
};


/*
ちょっとプログラムに意地悪をしました。正確に言えば俺が作ったときのやつから色々削った(*''ω''*)
それを考慮してアドバイス。
その１：キーボードのみの制御しかしていない。コントローラーでやるならスティックの傾きを正確にやる必要がある。
その２：斜め方向めちゃ早い。*sqrt(2)とかをやればよくなる。
その３：前しか向いてない。MV1SetRotationXYZに一工夫入れるだけで出来る。
その４：ゆっくり停止していない。単純にめんどくさくなった。
*/

