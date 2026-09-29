#include"Tree.h"


Tree::Tree(const CVector2D& pos) : Base(eType_Tree)
{
	m_tree = COPY_RESOURCE("Tree", CImage);


	m_tree.SetSize(1920, 96);
	//m_tree.SetCenter(960, 48);

	m_pos = pos;

	//m_ground_y = 470;
	//m_ground_y = 670;

	//ìñÇΩÇËîªíËÇÃíZå`Çê›íË
	/*m_rect.m_left = 0;  // 1920 / 2
	m_rect.m_right = 1920;
	m_rect.m_top = 0;   // 96 / 2
	m_rect.m_bottom = 96;*/


	/*m_rect.m_left = m_pos.x;
	m_rect.m_right = m_pos.x + 1920;
	m_rect.m_top = m_pos.y;
	m_rect.m_bottom = m_pos.y + 96;*/

	m_ground_y = m_pos.y;

}

void Tree::Draw()
{
	m_tree.SetPos(m_pos);
	m_tree.Draw();

}