#pragma once
#include"Base/Base.h"


class Slash : public Base {
private:

	//アニメーションの種類
	enum {
		eAnimSlash,
	};

	//画像オブジェクト
	CImage m_img;
	float m_houkou;
	
	//消滅までのタイマー
	//int m_timer = 0;

public:
	Slash(const CVector2D& pos, float hpukou);
	void Update();
	void Draw();
	void Collision(Base* b);

	static TexAnimData _anim_data[];

	//反転フラグ
	int m_dir = 1;	//1=右、 -1=左
};
