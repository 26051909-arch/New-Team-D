#pragma once
#include "../Base/Base.h"

class Title : public Base {
private:
	CImage m_img; // タイトル背景画像
	CFont* m_font; // タイトル文字表示用フォント
	int m_cnt; // 連打誤操作防止用カウンタ

public:
	Title();
	void Update() override;
	void Draw() override;
};