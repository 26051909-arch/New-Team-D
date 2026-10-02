#include "UI.h" 
UI::UI() : Base(eType_UI) {
	// 登録したフォントリソースを取得
	m_font = GET_RESOURCE("UIFont", CFont);
	m_cnt = 0;
	// カウンタの初期化 
}
	void UI::Update() {
		m_cnt++; // 毎フレーム（1/60秒ごとに）カウントアップ
	}
	

	void UI::Draw() {
		// 280秒（16,800フレーム）ごとに日数を+1計算（1日目からスタート）
		int day = (m_cnt / 16800) + 1;

		if (m_font) {
			// 画面左上に白色 (R=1, G=1, B=1) で描画
			m_font ->Draw(37, 65, 1.0f, 1.0f, 1.0f, "%d日目", day);
		}
	}