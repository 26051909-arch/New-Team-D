#pragma once
#include"Base/Base.h"


class Tree : public Base
{
private:

	CImage m_tree;

	//’n–Ê‚Ì‚‚³
	float m_ground_y;

public:
	Tree(const CVector2D& pos);
	void Draw();

	//’n–Ê‚Ì‚‚³‚ğæ“¾
	float GetGroundY() {
		return m_ground_y;
	}

};
