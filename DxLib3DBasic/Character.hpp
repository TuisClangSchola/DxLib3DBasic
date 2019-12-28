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

	VECTOR preArea;

	float m_modelHeight;

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
	Character(const int& t_model, const int& t_panelModel);
	~Character();


	void Draw();
	void Process(const float t_angle);

	bool HitCircleReturn(VECTOR hitUnderArea, float width);

	const VECTOR GetArea() const { return m_area; }

	const float GetHeight() const { return MV1GetFramePosition(m_model, 7).y; }
};


/*
ちょっとプログラムに意地悪をしました。正確に言えば俺が作ったときのやつから色々削った(*''ω''*)。理由：だんだんめんどくさくなってきた
それを考慮してアドバイス。
その１：キーボードのみの制御しかしていない。コントローラーでやるならスティックの傾きを正確にやる必要がある。ちなみにその場合デッドロックについても考慮しないと凄いことになる。
その２：斜め方向めちゃ早い。*sqrt(2)とかをやればよくなる。
その３：前しか向いてない。MV1SetRotationXYZに一工夫入れるだけで出来る。
その４：スッと移動する。ゆっくり移動させゆっくり停止させる必要がある。
その５：ステージのあたり判定ない（というかモデル無い）。実際に3Dやるなら地面よりちょい上にリスポーンさせるようにしないと確率で虚空に沈む。
その５：ステージとかOBB以外のあたり判定の処理はさせてない。参考としてこれが良い。https://dxlib.xsrv.jp/program/dxprogram_3DAction.html 内の→ void Player_Move( VECTOR MoveVector )
その６：光源とか明るさとか何も弄ってないからめっちゃ暗い。楽するならマテリアル関係の関数使って無理やり明るくさせる。
その７：影が無い。足元の影なら、https://dxlib.xsrv.jp/program/dxprogram_3DAction.html 内の→void Player_ShadowRender( void )を参考にすればいい。楽して影を作りたければSetUseShadowMapを使えばいい。正確にやりたいならシェーダ。なんにしても影を付けるモデル（ステージモデル）とかないと出来ない（やりにくい）。
*/

