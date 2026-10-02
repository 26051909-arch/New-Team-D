#pragma once
#include"Base/Base.h"

class Tree2 : public Base
{
private:
	CImage m_img1;
	CImage m_img2;
	CImage m_img3;
	CImage m_img4;
	CImage m_img5;

	CVector2D m_pos1;
	CVector2D m_pos2;
	CVector2D m_pos3;
	CVector2D m_pos4;
	CVector2D m_pos5;

public:
	Tree2();

	void Draw();
	
};
