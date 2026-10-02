#include"Tree2.h"
#include"Effect.h"

Tree2::Tree2() : Base(eType_Tree2)
{
	m_img1 = COPY_RESOURCE("Tree2", CImage);
	m_img2 = COPY_RESOURCE("Tree2", CImage);
	m_img3 = COPY_RESOURCE("Tree2", CImage);
	m_img4 = COPY_RESOURCE("Tree2", CImage);
	m_img5 = COPY_RESOURCE("Tree2", CImage);



	m_img1.SetSize(96, 96);
	m_img2.SetSize(96, 96);
	m_img3.SetSize(96, 96);
	m_img4.SetSize(96, 96);
	m_img5.SetSize(96, 96);

	m_img1.SetCenter(48, 84);
	//m_rect = CRect(-48, -84, 48, 12);

	m_img2.SetCenter(48, 84);
	//m_rect = CRect(-48, -84, 48, 12);

	m_img3.SetCenter(48, 84);
	//m_rect = CRect(-48, -84, 48, 12);

	m_img4.SetCenter(48, 84);
	//m_rect = CRect(-48, -84, 48, 12);

	m_img5.SetCenter(48, 84);
	//m_rect = CRect(-48, -84, 48, 12);

	m_pos1 = CVector2D(190, 334);
	m_pos2 = CVector2D(570, 334);
	m_pos3 = CVector2D(950, 334);
	m_pos4 = CVector2D(1330, 334);
	m_pos5 = CVector2D(1710, 250);

	m_rect = CRect(-48, -84, 48, 12);

}

void Tree2::Draw()
{

	//334

	m_img1.SetPos(m_pos1);
	m_img1.Draw();

	m_img2.SetPos(m_pos2);
	m_img2.Draw();

	m_img3.SetPos(m_pos3);
	m_img3.Draw();

	m_img4.SetPos(m_pos4);
	m_img4.Draw();

	m_img5.SetPos(m_pos5);
	m_img5.Draw();
}
