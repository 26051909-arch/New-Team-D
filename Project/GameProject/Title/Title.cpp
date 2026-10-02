#include "Title.h"
#include "../Game/Game.h"

//#include "../Game/Game.h" // ゲームシーンを呼び出すためにインクルード
Title::Title() : Base(eType_Scene) {
	m_img = COPY_RESOURCE("Title", CImage);
	m_img.SetSize(1980,1080);
	m_img.SetCenter(0, 0);
	m_cnt = 0;
}

void Title::Update() {
	if (m_cnt++ > 1 && PUSH(CInput::eButton1)) {
		Base::KillAll();
		new Game();
	}
}
void Title::Draw() {
	m_img.SetPos(CVector2D(0, 0));
	m_img.Draw();
}