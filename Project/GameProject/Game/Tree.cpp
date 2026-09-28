#include"Tree.h"


Tree::Tree(const CVector2D& pos) : Base(eType_Tree)
{
	m_tree = COPY_RESOURCE("Tree", CImage);


	m_tree.SetSize(680, 70);


	m_pos = pos;

	//m_ground_y = 470;
	//m_ground_y = 670;

	m_ground_y = m_pos.y;

}

void Tree::Draw()
{
	m_tree.SetPos(m_pos);
	m_tree.Draw();

}