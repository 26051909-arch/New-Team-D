#include "Game.h" 
#include "Field.h"
#include "Player.h" 
#include"Enemy1.h"
#include"Enemy2.h"
#include"Enemy3.h"
#include"Enemy4.h"
#include"Enemy5.h"
#include"Enemy6.h"
#include "UI.h"
#include"Hp.h"
#include "../Title/Title.h" // ゲームオーバー時にタイトルへ戻す場合

Game::Game() : Base(eType_Scene) {
	new Field(CVector2D(0, 0));
	new Player(CVector2D(256, 805), false);
	new Enemy1(CVector2D(0, 540), true);
	new Enemy2(CVector2D(10, 805), true);
	//new Enemy3(CVector2D(1800, 805), false);
	new Enemy4(CVector2D(0, 200), true);
	new Enemy5(CVector2D(2000, 800), true);
	//new Enemy6(CVector2D(2000, 600), false);

	
	m_enemy1_time = 0;
	m_enemy2_time = 0;
	m_enemy4_time = 0;
	m_enemy6_time = 0;
	new UI();


	new Hp();
}

void Game::Update() {

	m_day_time++;

	//一日6900フレーム(115秒)
	if (m_day_time >= 6900) {
		m_day_time = 0;
	}


	// 時間帯の設定
	bool is_morning = (m_day_time < 1800);

	bool is_noon =
		(m_day_time >= 1800 && m_day_time < 3600);

	bool is_evening =
		(m_day_time >= 3600 && m_day_time < 4500);

	bool is_night =
		(m_day_time >= 4500);



	//Enemy1のランダム出現
	m_enemy1_time++;

	//3秒に一回出現
	if (m_enemy1_time >= 180) {
		//①高さ0～540の間のどこか
		float random_y = rand() % 541;

		//②左右のどちらか
		if (rand() % 2 == 0) {
			//左から出現
			new Enemy1(CVector2D(0, random_y), true);
		}
		else {
			//右から出現
			new Enemy1(CVector2D(1920, random_y), false);
		}
		m_enemy1_time = 0;
	}


	// Enemy2：朝・夕方・夜に出現（6秒に1回）
	if (is_morning || is_evening || is_night) {
		//Enemy2のランダム出現
		m_enemy2_time++;

		//10秒に一回出現
		if (m_enemy2_time >= 360) {

			//②左右のどちらか
			if (rand() % 2 == 0) {
				//左から出現
				new Enemy2(CVector2D(0, 805), true);
			}
			else {
				//右から出現
				new Enemy2(CVector2D(SCREEN_WIDTH + 180, 805), false);
			}
			m_enemy2_time = 0;
		}
	}


	// Enemy3：昼・夕方に出現（7秒に1回）
	if (is_noon || is_evening) {
		m_enemy3_time++;

		if (m_enemy3_time >= 420) {
			if (rand() % 2 == 0) {
				new Enemy3(CVector2D(0, 805), true);
			}
			else {
				new Enemy3(CVector2D(SCREEN_WIDTH + 180, 805), false);
			}

			m_enemy3_time = 0;
		}
	}
	else {
		m_enemy3_time = 0;
	}



	//Enemy4のランダム出現
	m_enemy4_time++;

	//25秒に一回出現
	if (m_enemy4_time >= 1500) {

		//②左右のどちらか
		if (rand() % 2 == 0) {
			//左から出現
			new Enemy4(CVector2D(0, 300), true);
		}
		else {
			//右から出現
			new Enemy4(CVector2D(1920, 300), false);
		}
		m_enemy4_time = 0;

	}


	// Enemy6：夜に出現
	if (is_night) {
		m_enemy6_time++;

		if (m_enemy6_time >= 1300) {
			if (rand() % 2 == 0) {
				new Enemy6(CVector2D(-500, 810), true);
			}
			else {
				new Enemy6(CVector2D(SCREEN_WIDTH + 500, 810), false);
			}
			m_enemy6_time = 0;
		}
	}
	else {
		// 夜以外はタイマーをリセット
		m_enemy6_time = 0;
	}


	if (!Base::FindObject(eType_Player)&&PUSH(CInput::eButton1)) {
		Base::KillAll();
		new Title();
	}
}