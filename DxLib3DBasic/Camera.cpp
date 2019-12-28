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
	zRota = VGet(0, 530, 700);


	// 遠近法カメラだったら
	SetCameraNearFar(100.0f, 9500.0f);	// カメラの描画範囲を指定
	SetCameraPositionAndTarget_UpVecY(VAdd(cameraPerspectiveArea, charaArea), VAdd(perspesctiveViewArea, charaArea));
	// SoundProcess::Set3DRadius(VSize(cameraPerspectiveArea));
}



/// ------------------------------------------------------------------------------------
Camera::~Camera()
{
}



/// ------------------------------------------------------------------------------------
void Camera::Process(const VECTOR charaarea)
{
	charaArea = VAdd(charaarea, VGet(0.0f, 80.0f, 0.0f));		// キャラの位置を更新


	//// 左に回転中
	//if (DLLXinput::GetPadThumbData(DLLXinput::GetPlayerPadNumber(), DLLXinput::XINPUT_PAD::STICK_RIGHT_X) < 0)
	//{
	//	// 遠近法カメラの回転処理
	//	RLrotate(speed * (BASICPARAM::cameraHorizonReturn ? -1.0f : 1.0f), cameraPerspectiveArea.x, cameraPerspectiveArea.z);
	//	// 正射影カメラの回転処理
	//	RLrotate(speed * (BASICPARAM::cameraHorizonReturn ? -1.0f : 1.0f), cameraOrthoArea.x, cameraOrthoArea.z);


	//	// カメラの方向
	//	if ((angle >= DX_TWO_PI_F && !BASICPARAM::cameraHorizonReturn)
	//		|| (angle <= -DX_TWO_PI_F && BASICPARAM::cameraHorizonReturn))
	//	{
	//		angle = 0;
	//	}
	//	angle = angle + (speed * (BASICPARAM::cameraHorizonReturn ? -1.0f : 1.0f));
	//}
	//// 右に回転中
	//if (DLLXinput::GetPadThumbData(DLLXinput::GetPlayerPadNumber(), DLLXinput::XINPUT_PAD::STICK_RIGHT_X) > 0)
	//{
	//	// 遠近法カメラの回転処理
	//	RLrotate(-speed * (BASICPARAM::cameraHorizonReturn ? -1.0f : 1.0f), cameraPerspectiveArea.x, cameraPerspectiveArea.z);
	//	// 正射影カメラの回転処理
	//	RLrotate(-speed * (BASICPARAM::cameraHorizonReturn ? -1.0f : 1.0f), cameraOrthoArea.x, cameraOrthoArea.z);


	//	// カメラの方向
	//	if ((angle <= -DX_TWO_PI_F && !BASICPARAM::cameraHorizonReturn)
	//		|| (angle >= DX_TWO_PI_F && BASICPARAM::cameraHorizonReturn))
	//	{
	//		angle = 0;
	//	}
	//	angle = angle - (speed * (BASICPARAM::cameraHorizonReturn ? -1.0f : 1.0f));
	//}


	// 3Dサウンドの更新
	// SoundProcess::SetLisnerViewArea(perspesctiveViewArea);
	// SoundProcess::SetLisnerArea(cameraPerspectiveArea);
}
