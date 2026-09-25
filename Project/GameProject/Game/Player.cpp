#include"Player.h"

Player::Player(const CVector2D& pos, bool flip) : Base(eType_Player) 
{
	m_img = COPY_RESOURCE("Player", CImage);

}