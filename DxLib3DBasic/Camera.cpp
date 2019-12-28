#include "Camera.hpp"



/// ------------------------------------------------------------------------------------
void Camera::RLrotate(const float speed, float& axisOne, float& axisTwo)
{
	const float tempX = axisOne;
	const float tempY = axisTwo;
	axisOne = tempX * cosf(speed) + tempY * sinf(speed);
	axisTwo = -tempX * sinf(speed) + tempY * cosf(speed);
}



/// ------------------------------------------------------------------------------------
Camera::Camera(const VECTOR charaarea)
{
	// 遠近法カメラの初期化
	perspesctiveViewArea = VGet(0, 150, 0);
	cameraPerspectiveArea = VGet(0, 530, 700);


	// プレイヤーの座標初期化
	charaArea = VAdd(charaarea, VGet(0.0f, 80.0f, 0.0f));


	// 基本情報初期化
	speed = DX_PI_F / 90;
	angle = 0.0f;
	m_mouseAreaX = BasicParam::winWidth / 2;
	m_mouseAreaY = BasicParam::winHeight / 2;


	// 遠近法カメラだったら
	SetCameraNearFar(100.0f, 9500.0f);	// カメラの描画範囲を指定
	SetCameraPositionAndTarget_UpVecY(VAdd(cameraPerspectiveArea, charaArea), VAdd(perspesctiveViewArea, charaArea));
}



/// ------------------------------------------------------------------------------------
Camera::~Camera()
{
}



/// ------------------------------------------------------------------------------------
void Camera::Process(const VECTOR charaarea)
{
	charaArea = VAdd(charaarea, VGet(0.0f, 40.0f, 0.0f));		// キャラの位置を更新

	GetMousePoint(&m_mouseAreaX, &m_mouseAreaY);

	// 左に回転中
	if (m_mouseAreaX < BasicParam::winWidth / 2 - 10)
	{
		// 遠近法カメラの回転処理
		RLrotate(speed, cameraPerspectiveArea.x, cameraPerspectiveArea.z);


		// カメラの方向
		if (angle > DX_TWO_PI_F)
		{
			angle = 0;
		}
		angle += speed;
		SetMousePoint(BasicParam::winWidth / 2, BasicParam::winHeight / 2);
	}
	// 右に回転中
	if (m_mouseAreaX > BasicParam::winWidth / 2 + 10)
	{
		// 遠近法カメラの回転処理
		RLrotate(-speed, cameraPerspectiveArea.x, cameraPerspectiveArea.z);


		// カメラの方向
		if (angle < -DX_TWO_PI_F)
		{
			angle = 0;
		}
		angle -= speed;
		SetMousePoint(BasicParam::winWidth / 2, BasicParam::winHeight / 2);
	}

	SetCameraPositionAndTarget_UpVecY(VAdd(cameraPerspectiveArea, charaArea), VAdd(perspesctiveViewArea, charaArea));
}
