#include "Field.h"
// ----------------------------------------------------

// ----------------------------------------------------
// コンストラクタ（初期化処理）
// ----------------------------------------------------
Field::Field(const CVector2D& pos) : Base(eType_Field) {
	// リソースから画像を複製
	m_img = COPY_RESOURCE("Back_Ground", CImage);

	m_foreground = COPY_RESOURCE("ForeGround", CImage);


	//前景の設定
	m_img.SetSize(1920, 1080);
	m_foreground.SetSize(1920, 320);

	m_ground_y = 820;
	
	// 0番のアニメーションをループ再生開始（true = ループ）
	m_img.ChangeAnimation(0, true);

}

// ----------------------------------------------------
// 更新処理（毎フレーム実行）
// ----------------------------------------------------
void Field::Update() {
	m_img.UpdateAnimation();
}

// ----------------------------------------------------
// 描画処理（毎フレーム実行）
// ----------------------------------------------------
void Field::Draw() {
	// 画面左上（0, 0）の位置に描画
	m_img.SetPos(CVector2D(0, 0));
	m_img.Draw();
	m_foreground.SetPos(CVector2D(0, m_ground_y));
	m_foreground.Draw();
}

// ----------------------------------------------------
// アニメーションデータの設定（4枚の画像を4200フレームごとに切り替え）
// ----------------------------------------------------
static TexAnim _bg_anim[] = {
	{ 0, 4200 },
	{ 1, 4200 },
	{ 2, 4200 },
	{ 3, 4200 },
};

// クラス静的変数としてアニメーションデータを登録
TexAnimData Field::_anim_data[] = {
	ANIMDATA(_bg_anim),
};
