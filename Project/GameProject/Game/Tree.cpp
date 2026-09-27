#include"Tree.h"


Tree::Tree(const CVector2D& pos) : Base(eType_Tree)
{
	m_tree = COPY_RESOURCE("Tree", CImage);

	m_tree.SetSize(400, 50);

	//m_tree.SetCenter(200, 30);

	m_pos = pos;

	//m_ground_y = 400;
	//m_ground_y = 685;

	m_ground_y = m_pos.y;

}

void Tree::Draw()
{
	m_tree.SetPos(m_pos);
	m_tree.Draw();
}