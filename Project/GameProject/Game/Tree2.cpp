#include"Tree2.h"

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
	m_rect = CRect(-48, -84, 48, 12);

	m_img2.SetCenter(48, 84);
	m_rect = CRect(-48, -84, 48, 12);

	m_img3.SetCenter(48, 84);
	m_rect = CRect(-48, -84, 48, 12);

	m_img4.SetCenter(48, 84);
	m_rect = CRect(-48, -84, 48, 12);

	m_img5.SetCenter(48, 84);
	m_rect = CRect(-48, -84, 48, 12);

}

void Tree2::Draw()
{

	//334

	m_img1.SetPos(190, 334);
	m_img1.Draw();

	m_img2.SetPos(570, 334);
	m_img2.Draw();

	m_img3.SetPos(950, 334);
	m_img3.Draw();

	m_img4.SetPos(1330, 334);
	m_img4.Draw();

	m_img5.SetPos(1710, 250);
	m_img5.Draw();
}