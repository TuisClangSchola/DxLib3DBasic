#include "Character.hpp"



/// -------------------------------------------------------------------------
void Character::Player_PlayAnim(int attach)
{
	// 今のモーションが違うものだったら
	if (m_attachNum != attach)
	{
		// 直前のモーションが有効だったらデタッチする
		if (m_preAttach != -1 && m_motionBlendTime < 1.0f)
		{
			MV1DetachAnim(m_model, m_preAttach);
			m_preAttach = -1;
		}


		// 今のモーションを過去とする
		m_preAttach = m_attachMotion;
		m_preMotionPlayTime = m_nowPlayTime;


		// 新しいモーションをアタッチする
		m_attachNum = attach;
		m_attachMotion = MV1AttachAnim(m_model, m_attachNum, -1, false);
		m_nowPlayTime = 0.0f;


		// 再生中のモーションを１００％の状態 にする
		if (m_preMotionPlayTime == -1)
		{
			m_motionBlendTime = 1.0f;
		}
		else
		{
			m_motionBlendTime = 0.0f;
		}
	}
}



/// ------------------------------------------------------------------------------------
void Character::Player_AnimProcess()
{
	// ブレンド率が１以下の場合は１に近づける
	if (m_motionBlendTime < 1.0)
	{
		m_motionBlendTime += 0.075f;
		if (m_motionBlendTime >= 1.0f)
		{
			m_motionBlendTime = 1.0f;
		}
	}


	// 再生している現在のモーションの処理
	if (m_attachMotion != -1)
	{
		// モーションの総時間を取得
		m_totalTime = MV1GetAttachAnimTotalTime(m_model, m_attachMotion);


		// 再生時間を進める
		m_nowPlayTime += m_animSpeed;


		// 再生時間が総時間に到達していたらループさせる
		if (m_nowPlayTime >= m_totalTime)
		{
			m_nowPlayTime = fmodf(m_nowPlayTime, m_totalTime);
		}


		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(m_model, m_attachMotion, m_nowPlayTime);


		// アニメーション１のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(m_model, m_attachMotion, m_motionBlendTime);
	}


	// 再生している直前のモーションの処理
	if (m_preAttach != -1)
	{
		// アニメーションの総時間を取得
		m_totalTime = MV1GetAttachAnimTotalTime(m_model, m_preAttach);


		// 再生時間を進める
		m_preMotionPlayTime += m_animSpeed;


		// 再生時間が総時間に到達していたら再生時間をループさせる
		if (m_preMotionPlayTime > m_totalTime)
		{
			m_preMotionPlayTime = fmodf(m_preMotionPlayTime, m_totalTime);
		}


		// 変更した再生時間をモデルに反映させる
		MV1SetAttachAnimTime(m_model, m_preAttach, m_preMotionPlayTime);


		// アニメーション２のモデルに対する反映率をセット
		MV1SetAttachAnimBlendRate(m_model, m_preAttach, (1.0f - m_motionBlendTime));
	}
}



/// ------------------------------------------------------------------------------------
void Character::MoveProcess(const float t_angle)
{
	m_moveFlag = false;


	// 左方向に移動するフラッグが立っているとき
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_area.x += cosf(-t_angle) * m_walkSpeed;
		m_area.z += sinf(-t_angle) * m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
	// 右方向に移動するフラッグが立っているとき
	if (CheckHitKey(KEY_INPUT_D))
	{
		m_area.x += cosf(-t_angle) * -m_walkSpeed;
		m_area.z += sinf(-t_angle) * -m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
	// 下に移動するフラッグが立っているとき
	if (CheckHitKey(KEY_INPUT_S))
	{
		m_area.x += sinf(t_angle) * m_walkSpeed;
		m_area.z += cosf(t_angle) * m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
	// 上に移動するフラッグが立っているとき
	if (CheckHitKey(KEY_INPUT_W))
	{
		m_area.x += sinf(t_angle) * -m_walkSpeed;
		m_area.z += cosf(t_angle) * -m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
}



/// ------------------------------------------------------------------------------------
Character::Character(const int& t_model)
{
	m_model = 0;
	m_model = MV1DuplicateModel(t_model);

	m_attachNum = static_cast<int>(MOTION::dash);
	m_attachMotion = MV1AttachAnim(m_model, m_attachNum, -1, false);
	m_totalTime = MV1GetAttachAnimTotalTime(m_model, m_attachMotion);

	m_area = VGet(0.0f, 0.0f, 0.0f);

	m_walkSpeed = 5.0f;
	m_animSpeed = 0.5f;

	m_moveFlag = false;

	MV1SetPosition(m_model, m_area);
}



/// ------------------------------------------------------------------------------------
Character::~Character()
{
	MODEL_RELEASE(m_model);
}



/// ------------------------------------------------------------------------------------
void Character::Draw()
{
	MV1DrawModel(m_model);
}



/// ------------------------------------------------------------------------------------
void Character::Process(const float t_angle)
{
	MoveProcess(t_angle);

	if (m_moveFlag)
	{
		Player_PlayAnim(static_cast<int>(MOTION::dash));
	}
	else
	{
		Player_PlayAnim(static_cast<int>(MOTION::idle));
	}

	Player_AnimProcess();

	MV1SetRotationXYZ(m_model, VGet(0.0f, t_angle, 0.0f));
	MV1SetPosition(m_model, m_area);
}
