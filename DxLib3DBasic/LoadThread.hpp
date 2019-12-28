#pragma once
#include "Basic.hpp"


/*
�񓯊��Ń��[�h���s���N���X
*/
class LoadThread
{
private:
	// ���[�h������
	int m_num;

	// �ő働�[�h��
	int m_maxNum;

	// ���[�h��������
	std::vector<int> m_loadData;

	// ���[�h�������̂̃^�C�v
	std::vector<ELOADFILE> m_loadType;

	// �I���������ǂ���
	bool m_end;

	// ���[�h���
	std::function<void(const int, const int, const int)> m_function;

	// ���[�h�̎���
	int m_time;


public:
	// �R���X�g���N�^
	LoadThread(const int t_max, const std::vector<std::string> t_path, const std::vector<ELOADFILE> t_type, std::function<void(const int, const int, const int)> t_loadFunc);

	// �f�X�g���N�^
	~LoadThread();


	// �v���Z�X
	void Process();


	// ���[�h�������̂�n��
	const std::vector<int> GetFile() const { return m_loadData; }

	// ���[�h�I�������ǂ���
	const bool GetEnd() const { return m_end; }
};