#include "Result.h" 
#include "Title/Title.h" // 階層に合わせて "../Title.h" などにしてください 
Result::Result(int day) : Base(eType_Scene) { 
	m_img = COPY_RESOURCE("GameOver", CImage);
	m_font = GET_RESOURCE("UIFont", CFont);
	m_day = day; // ★ コンストラクタで受け取った day を m_day に代入 
	m_timer = 0;
}

	void Result::Update() {
		m_timer++;
		if (m_timer >= 180){
			Base::KillAll(); 
			new Title();
		} 
	}

	void Result::Draw() {
		m_img.SetPos(0, 0);
		m_img.SetSize(1920, 1080);
		m_img.Draw();
		if (m_font) { // ★ ここは day ではなく m_day にします！ 
			m_font->Draw(800, 650, 1.0f, 1.0f, 1.0f, "%d日生き延びた", m_day);
		}
	}
