#pragma once
#include"Base/Base.h"


class StickyWeb : public Base
{
private:
	CImage m_img;

public:
	StickyWeb(const CVector2D& pos);

	void Update();
	void Draw();
};
