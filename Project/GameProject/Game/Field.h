#pragma once
#include"Base/Base.h"


class Field : public Base {
private:
	//前景
	CImage m_foreground;

	//地面の高さ
	float m_ground_y;

public:
	//コンストラクタ
	Field(const CVector2D& pos);
	void Draw();

	//地面の高さを取得
	float GetGroundY() {
		return m_ground_y;
	}
};
