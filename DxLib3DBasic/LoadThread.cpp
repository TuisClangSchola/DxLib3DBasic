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
			// UI関係の画像のとき
		case ELOADFILE::graph:
			m_loadData.at(i) = LoadGraph(path.at(i).c_str());
			break;


			// 2D系SEのとき
		case ELOADFILE::soundEffect:
			m_loadData.at(i) = LoadSoundMem(path.at(i).c_str());
			break;


			// モデルデータのとき
		case ELOADFILE::model:
			m_loadData.at(i) = MV1LoadModel(path.at(i).c_str());
			break;


			// BGMのとき
		case ELOADFILE::backGroundMusic:
			SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
			m_loadData.at(i) = LoadSoundMem(path.at(i).c_str());
			SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
			break;


			// 3Dサウンドのとき
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
			// UI関係の画像のとき
		case ELOADFILE::graph:
			GRAPHIC_RELEASE(m_loadData.at(i));
			break;


			// 2D系SEのとき
		case ELOADFILE::soundEffect:
			SOUND_RELEASE(m_loadData.at(i));
			break;


			// モデルデータのとき
		case ELOADFILE::model:
			MODEL_RELEASE(m_loadData.at(i));
			break;


			// BGMのとき
		case ELOADFILE::backGroundMusic:
			SOUND_RELEASE(m_loadData.at(i));
			break;


			// 3Dサウンドのとき
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
