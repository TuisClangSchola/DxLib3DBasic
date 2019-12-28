#pragma once
#include "Basic.hpp"


/*
非同期でロードを行うクラス
*/
class LoadThread
{
private:
	// ロードした個数
	int m_num;

	// 最大ロード個数
	int m_maxNum;

	// ロードしたもの
	std::vector<int> m_loadData;

	// ロードしたもののタイプ
	std::vector<ELOADFILE> m_loadType;

	// 終了したかどうか
	bool m_end;

	// ロード画面
	std::function<void(const int, const int, const int)> m_function;

	// ロードの時間
	int m_time;


public:
	// コンストラクタ
	LoadThread(const int t_max, const std::vector<std::string> t_path, const std::vector<ELOADFILE> t_type, std::function<void(const int, const int, const int)> t_loadFunc);

	// デストラクタ
	~LoadThread();


	// プロセス
	void Process();


	// ロードしたものを渡す
	const std::vector<int> GetFile() const { return m_loadData; }

	// ロード終えたかどうか
	const bool GetEnd() const { return m_end; }
};