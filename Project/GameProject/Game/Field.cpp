#include"Field.h"


Field::Field(const CVector2D& pos) : Base(eType_Field)
{
	m_foreground = COPY_RESOURCE("ForeGround", CImage);

	//ëOåiÇÃê›íË
	m_foreground.SetSize(1920, 280);
	m_ground_y = 820;
}

void Field::Draw()
{
	m_foreground.SetPos(CVector2D(0, m_ground_y));
	m_foreground.Draw();

}