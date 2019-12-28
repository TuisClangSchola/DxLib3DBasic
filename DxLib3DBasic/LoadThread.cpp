#include "LoadThread.hpp"



/// ---------------------------------------------------------------------------------------
LoadThread::LoadThread(const int max, const std::vector<std::string> path, const std::vector<ELOADFILE> type, std::function<void(const int, const int, const int)> t_loadFunc)
{
	std::vector<int>().swap(loadData);
	std::vector<ELOADFILE>().swap(loadType);

	num = 0;
	end = false;
	time = 0;

	m_function = t_loadFunc;

	loadData.resize(max);

	loadType = type;

	SetUseASyncLoadFlag(TRUE);
	for (int i = 0; i < max; ++i)
	{
		switch (type.at(i))
		{
			// UI�֌W�̉摜�̂Ƃ�
		case ELOADFILE::graph:
			loadData.at(i) = LoadGraph(path.at(i).c_str());
			break;


			// 2D�nSE�̂Ƃ�
		case ELOADFILE::soundEffect:
			loadData.at(i) = LoadSoundMem(path.at(i).c_str());
			break;


			// ���f���f�[�^�̂Ƃ�
		case ELOADFILE::model:
			loadData.at(i) = MV1LoadModel(path.at(i).c_str());
			break;


			// BGM�̂Ƃ�
		case ELOADFILE::backGroundMusic:
			SetCreateSoundDataType(DX_SOUNDDATATYPE_FILE);
			loadData.at(i) = LoadSoundMem(path.at(i).c_str());
			SetCreateSoundDataType(DX_SOUNDDATATYPE_MEMNOPRESS);
			break;


			// 3D�T�E���h�̂Ƃ�
		case ELOADFILE::sound3DEffect:
			SetCreate3DSoundFlag(TRUE);
			loadData.at(i) = LoadSoundMem(path.at(i).c_str());
			SetCreate3DSoundFlag(FALSE);
			break;
		}
	}
	SetUseASyncLoadFlag(FALSE);

	maxNum = GetASyncLoadNum();
}



/// ---------------------------------------------------------------------------------------
LoadThread::~LoadThread()
{
	for (int i = 0; i < loadType.size(); ++i)
	{
		switch (loadType.at(i))
		{
			// UI�֌W�̉摜�̂Ƃ�
		case ELOADFILE::graph:
			GRAPHIC_RELEASE(loadData.at(i));
			break;


			// 2D�nSE�̂Ƃ�
		case ELOADFILE::soundEffect:
			SOUND_RELEASE(loadData.at(i));
			break;


			// ���f���f�[�^�̂Ƃ�
		case ELOADFILE::model:
			MODEL_RELEASE(loadData.at(i));
			break;


			// BGM�̂Ƃ�
		case ELOADFILE::backGroundMusic:
			SOUND_RELEASE(loadData.at(i));
			break;


			// 3D�T�E���h�̂Ƃ�
		case ELOADFILE::sound3DEffect:
			SOUND_RELEASE(loadData.at(i));
			break;


		default:
			break;
		}
	}
	std::vector<int>().swap(loadData);
	std::vector<ELOADFILE>().swap(loadType);
}



/// ---------------------------------------------------------------------------------------
void LoadThread::Process()
{
	m_function(time++, maxNum, maxNum - GetASyncLoadNum());

	if (GetASyncLoadNum() == 0)
	{
		end = true;
	}
}
