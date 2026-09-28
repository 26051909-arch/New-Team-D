#pragma once 
#include "../Base/Base.h"

class Field : public Base {
private:
	enum {
		eAnimBgAnim,
	};
	CImage m_img; // 背景画像用オブジェクト
	CImage m_foreground;
	//地面の高さ
	float m_ground_y;

public:
	Field(const CVector2D& pos); // コンストラクタ
	void Update(); // 更新処理
	void Draw(); // 描画処理
	// main.cppのADD\_RESOURCEで使用するアニメーションデータ
	static TexAnimData _anim_data[];
	//地面の高さを取得
	float GetGroundY() {
		return m_ground_y;
	}
};