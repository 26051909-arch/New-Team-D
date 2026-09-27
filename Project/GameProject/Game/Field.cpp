#include"Field.h"


Field::Field(const CVector2D& pos) : Base(eType_Field)
{
	m_foreground = COPY_RESOURCE("ForeGround", CImage);
	m_mount = COPY_RESOURCE("Mount", CImage);
	//m_tree = COPY_RESOURCE("Tree", CImage);


	//‘OŒi‚Ìİ’è
	m_foreground.SetSize(1920, 280);
	//‹ßŒi‚Ìİ’è
	//m_tree.SetSize(390, 50);
	//‰“Œi‚Ìİ’è
	m_mount.SetSize(1920, 1080);

	m_ground_y = 820;
}

void Field::Draw()
{
	m_mount.Draw();

	//m_tree.SetPos(0, 685);
	//m_tree.Draw();


	m_foreground.SetPos(CVector2D(0, m_ground_y));
	m_foreground.Draw();

}