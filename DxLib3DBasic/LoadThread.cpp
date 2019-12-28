#include "LoadThread.hpp"



/// ---------------------------------------------------------------------------------------
LoadThread::LoadThread(const int max, const std::vector<std::string> path, const std::vector<ELOADFILE> type, std::function<void(const int, const int, const int)> t_loadFunc)
{
	std::vector<int>().swap(m_loadData);
	std::vector<ELOADFILE>().swap(m_loadType);

	m_num = 0;
	m_end = false;
	m_time = 0;

	m_function = t_loadFunc;

	m_loadData.resize(max);

	m_loadType = type;

	SetUseASyncLoadFlag(TRUE);
	for (int i = 0; i < max; ++i)
	{
		switch (type.at(i))
		{
			// UI�֌W�̉摜�̂Ƃ�
		case ELOADFILE::graph:
			m_loadData.at(i) = LoadGraph(path.at(i).c_str());
			break;


			// 2D�nSE�̂Ƃ�
		case ELOADFILE::soundEffect:
			m_loadData.at(i) = LoadSoundMem(path.at(i).c_str());
			break;


			// ���f���f�[�^�̂Ƃ�
		case ELOADFILE::model:
			m_loadData.at(i) = MV1LoadModel(path.at(i).c_str());
			break;


			// BGM�̂Ƃ�
		case ELOADFILE::backGroundMusic:
			SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
			m_loadData.at(i) = LoadSoundMem(path.at(i).c_str());
			SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
			break;


			// 3D�T�E���h�̂Ƃ�
		case ELOADFILE::sound3DEffect:
			SetCreate3DSoundFlag(TRUE);
			m_loadData.at(i) = LoadSoundMem(path.at(i).c_str());
			SetCreate3DSoundFlag(FALSE);
			break;
		}
	}
	SetUseASyncLoadFlag(FALSE);

	m_maxNum = GetASyncLoadNum();
}



/// ---------------------------------------------------------------------------------------
LoadThread::~LoadThread()
{
	for (int i = 0; i < m_loadType.size(); ++i)
	{
		switch (m_loadType.at(i))
		{
			// UI�֌W�̉摜�̂Ƃ�
		case ELOADFILE::graph:
			GRAPHIC_RELEASE(m_loadData.at(i));
			break;


			// 2D�nSE�̂Ƃ�
		case ELOADFILE::soundEffect:
			SOUND_RELEASE(m_loadData.at(i));
			break;


			// ���f���f�[�^�̂Ƃ�
		case ELOADFILE::model:
			MODEL_RELEASE(m_loadData.at(i));
			break;


			// BGM�̂Ƃ�
		case ELOADFILE::backGroundMusic:
			SOUND_RELEASE(m_loadData.at(i));
			break;


			// 3D�T�E���h�̂Ƃ�
		case ELOADFILE::sound3DEffect:
			SOUND_RELEASE(m_loadData.at(i));
			break;


		default:
			break;
		}
	}
	std::vector<int>().swap(m_loadData);
	std::vector<ELOADFILE>().swap(m_loadType);
}



/// ---------------------------------------------------------------------------------------
void LoadThread::Process()
{
	m_function(m_time++, m_maxNum, m_maxNum - GetASyncLoadNum());

	if (GetASyncLoadNum() == 0)
	{
		m_end = true;
	}
}
