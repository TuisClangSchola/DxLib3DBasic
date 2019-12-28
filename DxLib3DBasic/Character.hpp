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

	float m_animSpeed;

	int m_attachMotion;

	int m_attachNum;

	float m_totalTime;

	float m_nowPlayTime;

	float m_motionBlendTime;

	int m_preAttach;

	float m_preMotionPlayTime;

	enum class MOTION { dash, idle };

	void Player_PlayAnim(int attach);

	void Player_AnimProcess();

	void MoveProcess(const float t_angle);


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
その４：スッと移動する。ゆっくり移動させゆっくり停止させる必要がある。
*/

