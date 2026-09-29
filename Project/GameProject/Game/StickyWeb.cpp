#include"StickyWeb.h"

StickyWeb::StickyWeb() : Base(eType_StickyWeb)
{
	m_img = COPY_RESOURCE("StickyWeb", CImage);
	//m_pos = pos;

	m_img.SetSize(256, 256);
}

void StickyWeb::Update()
{

}

void StickyWeb::Draw()
{
	//m_img.SetPos(m_pos);
	m_img.Draw();
}