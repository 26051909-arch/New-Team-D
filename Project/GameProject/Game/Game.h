#pragma once 
#include "../Base/Base.h"

class Game : public Base {
private:
	//ハエ出現用のタイマー
	int m_enemy1_time;
	//蟻出現用のタイマー
	int m_enemy2_time;
	//コガネムシ出現用のタイマー
	int m_enemy3_time;
	//蝶出現用のタイマー
	int m_enemy4_time;
	//カマキリ出現用のタイマー
	int m_enemy5_time;
	//巨大クモ用のタイマー
	int m_enemy6_time;

	int m_day_time = 0;

public: 
	Game();			// コンストラクタ（ゲーム開始時に呼ばれる） 
	void Update();	// 更新処理 
};