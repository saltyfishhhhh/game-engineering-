#pragma once

#include "ParsePackFile.h"
#include "Enemy.h"
#include "Hero.h"
#include <memory>
#include <vector>
#include <random>
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"

using std::get;
using std::shared_ptr;
using std::make_shared;
using std::vector;
using std::uniform_int_distribution;
using std::default_random_engine;

class GameMain
{
public:
	GameMain();
	~GameMain();
	void InitGame();

	void addNewEnemy();
	

	void Run();

	void ProcEvent(); //process user input 
	void DrawScene(); //draw the ui with data

	void UpdateData();	//update the data

	void DrawHero();
	void DrawHeroBullets();

	void DrawEnemy();
	void DrawEnemyBullets();


	sf::Texture texture;
	sf::Texture background;
	sf::Texture gameover;
	sf::Font font;
	
	sf::Music m_music_achievement;
	sf::Music m_music_big_spaceship_flying;
	sf::Music m_music_bullet;
	sf::Music m_music_button;
	sf::Music m_music_enemy1_down;
	sf::Music m_music_enemy2_down;
	sf::Music m_music_enemy3_down;
	sf::Music m_music_game_music;
	sf::Music m_music_game_over;
	sf::Music m_music_get_bomb;
	sf::Music m_music_get_double_laser;
	sf::Music m_music_out_porp;
	sf::Music m_music_use_bomb;

	sf::Music m_music;
	sf::RenderWindow m_window;

	shared_ptr<sf::Sprite> m_sprite;
	shared_ptr<sf::Sprite> m_sprite_background;
	shared_ptr<sf::Sprite> m_sprite_gameover;
	int m_curenemyindex = 0;
	int m_curheroindex = 0;
	int m_normal_enemy_hit_count = 0; //when reach to 50, big boss come out
	int m_max_normal_enemy_hits_count = 50;
	vector<shared_ptr<Enemy>>	m_alive_enemys;
	vector<sf::Vector2i>	m_enemy_bullets;
	Objects*	m_enemy_bullet;
	int m_enemy_bullet_index = 0;
	shared_ptr<Hero>	m_hero;
	int m_hero_bullet_index = 1;
	Objects*	m_hero_bullet;
	vector<sf::Vector2i> m_hero_bullets;
	shared_ptr<sf::Text>	m_textTag;
	sf::Font		m_font;

	bool m_pause = false;
	bool m_game_over = false;
	bool m_win = false;

	int m_enemy_speed = 10;
	int m_enemy_bullet_step = 15;
	int m_hero_step = 24;
	int m_hero_bullet_step = 15;

	int m_width = 480;
	int m_height = 800;

	bool m_play_out_porp = false;

	int m_fps = 5;		//use to flush the window times per second, and emit one bullet per second, (both hero and enemey)
	int m_index = 0;	//when m_index = 0, the enemy and hero emit one bullet
	
	shared_ptr<default_random_engine> m_rand_engine;
	shared_ptr<uniform_int_distribution<int>>	m_random_dis;

	ParsePackFile p;
};

