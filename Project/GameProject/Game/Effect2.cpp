#include"Effect2.h"
#include"Player.h"


Effect2::Effect2(const CVector2D& pos, bool flip) : Base(eType_Effect2)
{
	m_img = COPY_RESOURCE("Effect2", CImage);
	m_img2 = COPY_RESOURCE("Effect2", CImage);
	
	m_pos = pos;
	m_pos_left = pos;
	m_pos_right = pos;


	//îºåa
	m_rad = 64;

	m_img.SetSize(128, 128);
	m_img.SetCenter(64, 64);

	m_img2.SetSize(128, 128);
	m_img2.SetCenter(64, 64);

	m_img.ChangeAnimation(eAnimShock, true);
	m_img2.ChangeAnimation(eAnimShock, true);

}

void Effect2::Update()
{
	const int move_speed = 9;

	// ç∂âEÇ…è’åÇîgÇçLÇ∞ÇÈ
	m_pos_left.x -= move_speed;
	m_pos_right.x += move_speed;

	// ÉAÉjÉÅÅ[ÉVÉáÉìÇçXêV
	m_img.UpdateAnimation();
	m_img2.UpdateAnimation();


	// àÍíËéûä‘åoâﬂÇµÇΩÇÁè¡Ç∑
	m_timer++;


	if (m_timer >= 180)
	{
		SetKill();
	}

}


void Effect2::Draw()
{

	const float offsetY = 40.0f;  // è„Ç…Ç∏ÇÁÇ∑ó 


	//ç∂ë§ÇÃè’åÇîg
	CVector2D posLeft = m_pos_left;
	posLeft.y -= offsetY;
	m_img.SetPos(posLeft);
	m_img.Draw();


	//âEë§ÇÃè’åÇîg
	CVector2D posRight = m_pos_right;
	posRight.y -= offsetY;
	m_img2.SetFlipH(true);  // ç∂âEîΩì]
	m_img2.SetPos(posRight);
	m_img2.Draw();
}


void Effect2::Collision(Base* b)
{
	
}

bool Effect2::HitTest(const CVector2D& pos, float rad) const
{
	const float hit_rad = m_rad + rad;

	// ç∂ë§ÇÃè’åÇîg
	float dx = pos.x - m_pos_left.x;
	float dy = pos.y - m_pos_left.y;

	if (dx * dx + dy * dy <= hit_rad * hit_rad) {
		return true;
	}

	// âEë§ÇÃè’åÇîg
	dx = pos.x - m_pos_right.x;
	dy = pos.y - m_pos_right.y;

	if (dx * dx + dy * dy <= hit_rad * hit_rad) {
		return true;
	}

	return false;
}


static TexAnim _shock[] = {
	{18,3},
	{19,3},
	{20,3},
	{21,3},
	{19,3},
	{20,3},
	{21,3},
	{19,3},
	{20,3},
	{21,3},
};


TexAnimData Effect2::_anim_data[] = {
	ANIMDATA(_shock),
};