#pragma once 
#include "../Base/Base.h"

class Game : public Base {
private:
	//ハエ出現用のタイマー
	int m_enemy1_time;
public: 
	Game();			// コンストラクタ（ゲーム開始時に呼ばれる） 
	void Update();	// 更新処理 
};