#include <string>
#include "LoadThread.hpp"
#include "Game.hpp"



/// --------------------------------------------------------------------------------------------------
// ロード画面用
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
	SetOutApplicationLogValidFlag(TRUE);	// ログテキスト出力する
#elif NDEBUG
	SetOutApplicationLogValidFlag(FALSE);	// ログテキスト出力しない
#endif


	SetWindowText(t_projectName.c_str());					// メインウインドウのウインドウタイトルを変更する
	SetBackgroundColor(255, 255, 255);			// 背景色を白に変更
	ChangeWindowMode(TRUE);						// ウィンドウズモードにさせる


	SetGraphMode(BasicParam::winWidth, BasicParam::winHeight, BasicParam::bitColor);			// 画面サイズ設定
	GetDefaultState(&BasicParam::winWidth, &BasicParam::winHeight, &BasicParam::bitColor);		// デフォルトウィンドウ値を得る
	SetWindowSize(BasicParam::winWidth, BasicParam::winHeight);					// デフォルトウィンドウサイズに合わせてゲームサイズを変更

	SetUseDirect3DVersion(DX_DIRECT3D_11);		// Direct3D11を使用する
	SetEnableXAudioFlag(TRUE);					// XAudioを使用するようにする
	SetUseLarge3DPositionSupport(TRUE);			// 巨大な座標値をサポート


	SetAlwaysRunFlag(TRUE);				// 裏画面でも常にアクティブに変更

	// ＤＸライブラリ初期化処理
	if (DxLib_Init() == -1)
	{
		return false;			// エラーが起きたら直ちに終了
	}


	SetAlwaysRunFlag(TRUE);			// 裏画面でも常にアクティブに変更
	SetDrawScreen(DX_SCREEN_BACK);	// 背景描画
	SetMouseDispFlag(FALSE);		// マウスカーソルを消す


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


	// メインループ
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


	// 削除
	POINTER_RELEASE(mp_game);
	GRAPHIC_RELEASE(loadDraw);
	DxLib_End();		// DXライブラリの後始末


	return 0;
}