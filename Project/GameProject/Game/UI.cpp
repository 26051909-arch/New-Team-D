#include "UI.h" 
#include "Result/Result.h"
#include"Player.h"

/*static TexAnim _hp_anim[] = {
	{ 0, 60 }, { 1, 60 }, { 2, 60 }, { 3, 60 }, { 4, 60 }, { 5, 60 },
	{ 6, 60 }, { 7, 60 }, { 8, 60 }, { 9, 60 }, { 10, 60 }, { 11, 60 },
	{ 12, 60 }, { 13, 60 }, { 14, 60 }, { 15, 60 }, { 16, 60 }, { 17, 60 },
	{ 18, 60 }, { 19, 60 }, { 20, 60 }, { 21, 60 }, { 22, 60 }, { 23, 60 },
	{ 24, 60 }, { 25, 60 }, { 26, 60 }, { 27, 60 }, { 28, 60 }, { 29, 60 },
	{ 30, 60 }, { 31, 60 }, { 32, 60 }, { 33, 60 }, { 34, 60 }, { 35, 60 },
	{ 36, 60 }, { 37, 60 }, { 38, 60 }, { 39, 60 }, { 40, 60 }, { 41, 60 },
	{ 42, 60 }, { 43, 60 }, { 44, 60 }, { 45, 60 }, { 46, 60 }, { 47, 60 },
	{ 48, 60 }, { 49, 60 },
};
TexAnimData hp_anim_data[] = {
	ANIMDATA(_hp_anim),
};*/

UI::UI() : Base(eType_UI) {
	// 登録したフォントリソースを取得
	m_font = GET_RESOURCE("UIFont", CFont);
	//m_img_hp = COPY_RESOURCE("HP", CImage);

	m_cnt = 0;

}
	void UI::Update() {
		m_cnt++;

		//プレイヤーがいなくなったらリザルト画面へ
		if(Base::FindObject(eType_Player) == nullptr)
		{
			int day = (m_cnt / 8400) + 1; // 生き延びた日数を計算 

			Base::KillAll();
			new Result(day); // 背景画像付きのリザルト画面を生成！ 
		}
	
	}
	

	void UI::Draw() {
		// 140秒（8,400フレーム）ごとに日数を+1計算（1日目からスタート）
		int day = (m_cnt / 8400) + 1;

		// 1. 日数の描画
		if (m_font) {
			// 画面左上に白色 (R=1, G=1, B=1) で描画
			m_font ->Draw(37, 190, 1.0f, 1.0f, 1.0f, "%d日目", day);
		}
		/*m_img_hp.SetPos(67, 120);
		m_img_hp.SetSize(115, 110);
		m_img_hp.ChangeAnimation(0, false, 30);
		m_img_hp.Draw();*/
	}