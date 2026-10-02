#pragma once
#include"Base/Base.h"


class Effect : public Base
{
private:

	enum {
		_effect_web
	};

	CImage m_img;

public:
	Effect(const CVector2D& pos);
	void Update();
	void Draw();

	static TexAnimData effectAnimData[];

};
