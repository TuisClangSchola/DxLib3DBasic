#include "Character.hpp"



/// -------------------------------------------------------------------------
void Character::Player_PlayAnim(int attach)
{
	// ���̃��[�V�������Ⴄ���̂�������
	if (m_attachNum != attach)
	{
		// ���O�̃��[�V�������L����������f�^�b�`����
		if (m_preAttach != -1 && m_motionBlendTime < 1.0f)
		{
			MV1DetachAnim(m_model, m_preAttach);
			m_preAttach = -1;
		}


		// ���̃��[�V�������ߋ��Ƃ���
		m_preAttach = m_attachMotion;
		m_preMotionPlayTime = m_nowPlayTime;


		// �V�������[�V�������A�^�b�`����
		m_attachNum = attach;
		m_attachMotion = MV1AttachAnim(m_model, m_attachNum, -1, false);
		m_nowPlayTime = 0.0f;


		// �Đ����̃��[�V�������P�O�O���̏�� �ɂ���
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
	// �u�����h�����P�ȉ��̏ꍇ�͂P�ɋ߂Â���
	if (m_motionBlendTime < 1.0)
	{
		m_motionBlendTime += 0.075f;
		if (m_motionBlendTime >= 1.0f)
		{
			m_motionBlendTime = 1.0f;
		}
	}


	// �Đ����Ă��錻�݂̃��[�V�����̏���
	if (m_attachMotion != -1)
	{
		// ���[�V�����̑����Ԃ��擾
		m_totalTime = MV1GetAttachAnimTotalTime(m_model, m_attachMotion);


		// �Đ����Ԃ�i�߂�
		m_nowPlayTime += m_animSpeed;


		// �Đ����Ԃ������Ԃɓ��B���Ă����烋�[�v������
		if (m_nowPlayTime >= m_totalTime)
		{
			m_nowPlayTime = fmodf(m_nowPlayTime, m_totalTime);
		}


		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(m_model, m_attachMotion, m_nowPlayTime);


		// �A�j���[�V�����P�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(m_model, m_attachMotion, m_motionBlendTime);
	}


	// �Đ����Ă��钼�O�̃��[�V�����̏���
	if (m_preAttach != -1)
	{
		// �A�j���[�V�����̑����Ԃ��擾
		m_totalTime = MV1GetAttachAnimTotalTime(m_model, m_preAttach);


		// �Đ����Ԃ�i�߂�
		m_preMotionPlayTime += m_animSpeed;


		// �Đ����Ԃ������Ԃɓ��B���Ă�����Đ����Ԃ����[�v������
		if (m_preMotionPlayTime > m_totalTime)
		{
			m_preMotionPlayTime = fmodf(m_preMotionPlayTime, m_totalTime);
		}


		// �ύX�����Đ����Ԃ����f���ɔ��f������
		MV1SetAttachAnimTime(m_model, m_preAttach, m_preMotionPlayTime);


		// �A�j���[�V�����Q�̃��f���ɑ΂��锽�f�����Z�b�g
		MV1SetAttachAnimBlendRate(m_model, m_preAttach, (1.0f - m_motionBlendTime));
	}
}



/// ------------------------------------------------------------------------------------
void Character::MoveProcess(const float t_angle)
{
	m_moveFlag = false;


	// �������Ɉړ�����t���b�O�������Ă���Ƃ�
	if (CheckHitKey(KEY_INPUT_A))
	{
		m_area.x += cosf(-t_angle) * m_walkSpeed;
		m_area.z += sinf(-t_angle) * m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
	// �E�����Ɉړ�����t���b�O�������Ă���Ƃ�
	if (CheckHitKey(KEY_INPUT_D))
	{
		m_area.x += cosf(-t_angle) * -m_walkSpeed;
		m_area.z += sinf(-t_angle) * -m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
	// ���Ɉړ�����t���b�O�������Ă���Ƃ�
	if (CheckHitKey(KEY_INPUT_S))
	{
		m_area.x += sinf(t_angle) * m_walkSpeed;
		m_area.z += cosf(t_angle) * m_walkSpeed;
		if (!m_moveFlag) m_moveFlag = true;
	}
	// ��Ɉړ�����t���b�O�������Ă���Ƃ�
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
