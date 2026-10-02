#pragma once 
#include "../Base/Base.h"

class Game : public Base {
public: 
	Game();			// コンストラクタ（ゲーム開始時に呼ばれる） 
	void Update();	// 更新処理 
};