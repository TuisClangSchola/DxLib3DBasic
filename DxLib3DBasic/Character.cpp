#include "Character.hpp"



/// ------------------------------------------------------------------------------------
Character::Character(const int& t_model)
{
	m_model = 0;
	m_model = MV1DuplicateModel(t_model);

	m_area = VGet(0.0f, 0.0f, 0.0f);

	m_walkSpeed = 0.0f;

	m_moveFlag = false;

	m_direction[0] = false;
	m_direction[1] = false;
	m_direction[2] = false;
	m_direction[3] = false;
	m_preDirection[0] = false;
	m_preDirection[1] = false;
	m_preDirection[2] = false;
	m_preDirection[3] = false;

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
	m_moveFlag = false;


	// 左方向に移動するフラッグが立っているとき
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_direction[static_cast<int>(DIRECTION::left)] = true;
		m_area.x += cosf(-t_angle) * m_walkSpeed;
		m_area.z += sinf(-t_angle) * m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
	// 右方向に移動するフラッグが立っているとき
	if (CheckHitKey(KEY_INPUT_D))
	{
		m_direction[static_cast<int>(DIRECTION::right)] = true;
		m_area.x += cosf(-t_angle) * -m_walkSpeed;
		m_area.z += sinf(-t_angle) * -m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
	// 下に移動するフラッグが立っているとき
	if (CheckHitKey(KEY_INPUT_S))
	{
		m_direction[static_cast<int>(DIRECTION::down)] = true;
		m_area.x += sinf(t_angle) * m_walkSpeed;
		m_area.z += cosf(t_angle) * m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
	// 上に移動するフラッグが立っているとき
	if (CheckHitKey(KEY_INPUT_W))
	{
		m_direction[static_cast<int>(DIRECTION::up)] = true;
		m_area.x += sinf(t_angle) * -m_walkSpeed;
		m_area.z += cosf(t_angle) * -m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}

	if (m_moveFlag)
	{
		if (m_walkSpeed < 10.0f) 
		{
			m_walkSpeed += 0.5f;
		}
		else if (m_walkSpeed != 10.0f)
		{
			m_walkSpeed = 10.0f;
		}
	}
	else
	{
		if (m_walkSpeed > 0.0f)
		{
			m_walkSpeed -= 2.0f;
		}
		else if (m_walkSpeed <= 0.0f)
		{
			m_walkSpeed = 0.0f;
			m_direction[0] = false;
			m_direction[1] = false;
			m_direction[2] = false;
			m_direction[3] = false;
		}
	}

	MV1SetRotationXYZ(m_model, VGet(0.0f, t_angle, 0.0f));
	MV1SetPosition(m_model, m_area);
}
