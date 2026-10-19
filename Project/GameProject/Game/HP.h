#pragma once
#include "../Base/Base.h"


class Hp : public Base {
private:
	CFont* m_font; // フォント用ポインタ
	
public:
	Hp();
	void Update();
	void Draw();

};
