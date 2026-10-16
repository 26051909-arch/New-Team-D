#include"Hp.h"
#include"Player.h"


Hp::Hp() : Base(eType_Hp) {
	m_font = GET_RESOURCE("UIFont", CFont);
}

void Hp::Update() {

}

void Hp::Draw() {


	Player* player =
		static_cast<Player*>(Base::FindObject(eType_Player));

	if (player != nullptr&& m_font)
	{
		int hp = (int)player->GetHP();

		// âÊñ ç∂è„Ç…HPÇï\é¶
		m_font->Draw(1690, 100, 1.0f, 1.0f, 1.0f, "HPÅF%d", hp);
	}

	/*m_img.SetPos(67, 154);
	m_img.SetSize(16, 64);
	m_img.ChangeAnimation(0);
	m_img.Draw();*/

}
