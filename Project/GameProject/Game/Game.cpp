#include "Game.h" 
#include "Field.h"
#include "Player.h" 
#include"Enemy1.h"
#include"Enemy2.h"
#include"Enemy4.h"
#include "UI.h"
#include "../Title/Title.h" // ゲームオーバー時にタイトルへ戻す場合

Game::Game() : Base(eType_Scene) {
	new Field(CVector2D(0, 0));
	new Player(CVector2D(256, 400), false);
	new Enemy1(CVector2D(0, 540), true);
	new Enemy2(CVector2D(1800, 400), false);
	new Enemy4(CVector2D(0, 200), true);

	
	m_enemy1_time = 0;
	m_enemy4_time = 0;
	new UI();
}

void Game::Update() {

	//Enemy1のランダム出現
	m_enemy1_time++;

	if (m_enemy1_time >= 300) {
		//①高さ0～540の間のどこか
		float random_y =rand() % 541;

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


	//Enemy4のランダム出現
	m_enemy4_time++;

	if (m_enemy4_time >= 1800) {

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


	if (!Base::FindObject(eType_Player)&&PUSH(CInput::eButton1)) {
		Base::KillAll();
		new Title();
	}
}