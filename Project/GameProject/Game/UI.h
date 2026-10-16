#pragma once
#include "../Base/Base.h"

class UI : public Base {
private:
	CFont* m_font; // フォント用ポインタ
	int m_cnt; // 経過フレーム数カウンタ
	//CImage m_img_hp;

public:
	UI();
	void Update() override;
	void Draw() override;
	
};
//extern TexAnimData hp_anim_data[];