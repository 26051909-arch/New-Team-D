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
	

	int m_eat_count;
};
//extern TexAnimData hp_anim_data[];