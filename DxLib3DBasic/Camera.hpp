#pragma once
#include "Basic.hpp"



/*
通常のカメラのクラス
*/
class Camera
{
private:
	// カメラの位置
	VECTOR m_cameraPerspectiveArea;		// 遠近法カメラ

	// 注視する方向
	VECTOR m_perspesctiveViewArea;		// 遠近法カメラ

	// キャラ位置
	VECTOR m_charaArea;

	// キャラクターのアングル
	float m_angle;

	// 回転スピード
	float m_speed;

	// 回転を行う関数
	void RLrotate(const float t_speed, float& t_axisOne, float& t_axisTwo);

	// マウスの位置
	int m_mouseAreaX, m_mouseAreaY;


public:
	// キャラの位置を引数に取ったコンストラクタ
	Camera(const VECTOR t_charaarea);

	// デストラクタ
	~Camera();


	// キャラの位置を引数に取ったプロセス
	void Process(const VECTOR t_charaarea);

	// キャラクターのアングル
	const float GetAngle() const { return m_angle; }

	// カメラの座標
	const VECTOR GetArea() const { return m_cameraPerspectiveArea; }
};


/*
ちょっとプログラムに意地悪をしました(*''ω''*)。理由：だんだんめんどくさくなってきた
それを考慮してアドバイス。
その１：3D音源を配置するのであればカメラと同じ感じでリスナー用のものがいる。こんなのSet3DSoundListenerPosAndFrontPos_UpVecY
*/