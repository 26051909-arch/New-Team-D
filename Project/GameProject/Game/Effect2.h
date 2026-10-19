#pragma once
#include"Base/Base.h"


class Effect2 : public Base
{
private:

	//アニメーションの種類
	enum {
		_effect_shock
	};

	CImage m_img;

public:
	Effect2(const CVector2D& pos);
	void Update();
	void Draw();

	static TexAnimData _anim_data[];

};