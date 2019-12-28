#include <string>
#include "LoadThread.hpp"
#include "Game.hpp"



/// --------------------------------------------------------------------------------------------------
// ���[�h��ʗp
int loadDraw;
void LoadScreen(const int t_time, const int t_max, const int t_now)
{
	int angle = t_time % 32;
	DrawRotaGraph(BasicParam::winWidth / 2, BasicParam::winHeight / 2, 1.0f, static_cast<int>(DX_PI_F / angle), loadDraw, false);
}



/// --------------------------------------------------------------------------------------------------
bool Init(const int t_winWidth, const int t_winHeight, const int t_bitColor, std::string t_projectName)
{
	BasicParam::winWidth = t_winWidth;
	BasicParam::winHeight = t_winHeight;
	BasicParam::bitColor = t_bitColor;

#ifdef _DEBUG
	SetOutApplicationLogValidFlag(TRUE);	// ���O�e�L�X�g�o�͂���
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ���O�e�L�X�g�o�͂��Ȃ�
#endif


	SetWindowText(t_projectName.c_str());					// ���C���E�C���h�E�̃E�C���h�E�^�C�g����ύX����
	SetBackgroundColor(255, 255, 255);			// �w�i�F�𔒂ɕύX
	ChangeWindowMode(TRUE);						// �E�B���h�E�Y���[�h�ɂ�����


	SetGraphMode(BasicParam::winWidth, BasicParam::winHeight, BasicParam::bitColor);			// ��ʃT�C�Y�ݒ�
	GetDefaultState(&BasicParam::winWidth, &BasicParam::winHeight, &BasicParam::bitColor);		// �f�t�H���g�E�B���h�E�l�𓾂�
	SetWindowSize(BasicParam::winWidth, BasicParam::winHeight);					// �f�t�H���g�E�B���h�E�T�C�Y�ɍ��킹�ăQ�[���T�C�Y��ύX

	SetUseDirect3DVersion(DX_DIRECT3D_11);		// Direct3D11���g�p����
	SetEnableXAudioFlag(TRUE);					// XAudio���g�p����悤�ɂ���
	SetUseLarge3DPositionSupport(TRUE);			// ����ȍ��W�l���T�|�[�g


	SetAlwaysRunFlag(TRUE);				// ����ʂł���ɃA�N�e�B�u�ɕύX

	// �c�w���C�u��������������
	if (DxLib_Init() == -1)
	{
		return false;			// �G���[���N�����璼���ɏI��
	}


	SetAlwaysRunFlag(TRUE);			// ����ʂł���ɃA�N�e�B�u�ɕύX
	SetDrawScreen(DX_SCREEN_BACK);	// �w�i�`��
	SetMouseDispFlag(FALSE);		// �}�E�X�J�[�\��������


	return true;
}



/// --------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if (Init(1920, 1080, 32, "Game") == false) return -1;

	bool loadNow = true;

	loadDraw = LoadGraph("media\\load.png");

	std::vector<std::string> m_fileName;
	std::vector<ELOADFILE> m_fileType;

	m_fileName.push_back("media\\model\\animation\\animation_all.mv1");
	m_fileType.push_back(ELOADFILE::model);
	m_fileName.push_back("media\\model\\animation\\animation_all.mv1");
	m_fileType.push_back(ELOADFILE::model);

	LoadThread* mp_loadThread = new LoadThread(m_fileName.size(), m_fileName, m_fileType, LoadScreen);

	Game* mp_game = nullptr;


	// ���C�����[�v
	while (!ScreenFlip() && !ProcessMessage() && !ClearDrawScreen() && !CheckHitKey(KEY_INPUT_ESCAPE))
	{
		if (loadNow)
		{
			mp_loadThread->Process();
			if (mp_loadThread->GetEnd())
			{
				loadNow = false;
				mp_game = new Game(mp_loadThread->GetFile());

				POINTER_RELEASE(mp_loadThread);

				std::vector<std::string>().swap(m_fileName);
				std::vector<ELOADFILE>().swap(m_fileType);
			}
		}
		else
		{
			mp_game->Update();
		}
	}


	// �폜
	POINTER_RELEASE(mp_game);
	GRAPHIC_RELEASE(loadDraw);
	DxLib_End();		// DX���C�u�����̌�n��


	return 0;
}


/*
�S�̓I�Ɉ�����邱�ƁB���؂��ł͂Ȃ��B
*/