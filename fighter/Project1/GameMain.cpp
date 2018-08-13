#include "GameMain.h"

#include <chrono>
#include <algorithm>
#include <tuple>

using std::make_tuple;
using std::find_if;

GameMain::GameMain()
{

}


GameMain::~GameMain()
{
}

void GameMain::InitGame()
{
	//ParsePackFile p;
	bool bparse = p.parseFile("image/shoot.pack");
	if (bparse)
	{
		m_window.create(sf::VideoMode(m_width, m_height), "game");
		m_window.setFramerateLimit(m_fps);

		if (!texture.loadFromFile(p.m_imageFile))
			return ;
		if (!background.loadFromFile(p.m_backImage))
			return ;
		if (!gameover.loadFromFile(p.m_gameoverImage))
			return ;
		auto a = p.m_game_pauses.rbegin()->second.m_press;

		sf::IntRect rect(get<0>(a.m_xy), get<1>(a.m_xy), get<0>(a.m_size), get<1>(a.m_size));
		m_sprite = make_shared<sf::Sprite>(texture, rect);
		m_sprite_background = make_shared<sf::Sprite>(background);
		m_sprite_gameover = make_shared<sf::Sprite>(gameover);

		p.genSprite(texture);
		
		if (!font.loadFromFile("arial.ttf"))
			return ;
		if (!m_music.openFromFile("sound/game_music.ogg"))
			return ;
		if (!m_music_achievement.openFromFile("sound/achievement.ogg"))
			return;
		if (!m_music_big_spaceship_flying.openFromFile("sound/big_spaceship_flying.ogg"))
			return;
		if (!m_music_bullet.openFromFile("sound/bullet.ogg"))
			return;
		if (!m_music_button.openFromFile("sound/button.ogg"))
			return;
		if (!m_music_enemy1_down.openFromFile("sound/enemy1_down.ogg"))
			return;
		if (!m_music_enemy2_down.openFromFile("sound/enemy2_down.ogg"))
			return;
		if (!m_music_enemy3_down.openFromFile("sound/enemy3_down.ogg"))
			return;
		if (!m_music_game_music.openFromFile("sound/game_music.ogg"))
			return;
		if (!m_music_game_over.openFromFile("sound/game_over.ogg"))
			return;
		if (!m_music_get_bomb.openFromFile("sound/get_bomb.ogg"))
			return;
		if (!m_music_get_double_laser.openFromFile("sound/get_double_laser.ogg"))
			return;
		if (!m_music_out_porp.openFromFile("sound/out_porp.ogg"))
			return;
		if (!m_music_use_bomb.openFromFile("sound/use_bomb.ogg"))
			return;
		m_hero = make_shared<Hero>();
		if (m_hero->m_index == 0)
		{
			m_hero->m_obj = &(p.m_heros.begin()->second);
		}
		else
		{
			m_hero->m_obj = &(p.m_heros.rbegin()->second);
		}
		m_hero->m_pos = sf::Vector2i(m_width / 2 - get<0>(m_hero->m_obj->m_normal.m_size) / 2,
			m_height - get<1>(m_hero->m_obj->m_normal.m_size));
		m_hero->m_size = m_hero->m_obj->m_normal.m_size;

		unsigned seed = static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count());
		m_rand_engine = make_shared<default_random_engine>(seed);
		m_random_dis = make_shared<uniform_int_distribution<int>>(0, m_width-80);
		addNewEnemy();

		if (m_hero_bullet_index == 0)
		{
			m_hero_bullet = &(p.m_bullets.begin()->second);
			m_enemy_bullet = &(p.m_bullets.rbegin()->second);
		}
		else
		{
			m_hero_bullet = &(p.m_bullets.rbegin()->second);
			m_enemy_bullet = &(p.m_bullets.begin()->second);
		}
		m_font.loadFromFile("font/STHeiti Light.ttc");
		m_textTag = make_shared<sf::Text>();
		
		m_textTag->setFont(m_font);
	}
}

void GameMain::addNewEnemy()
{
	auto enemyx = make_shared<Enemy>();
	
	if (m_normal_enemy_hit_count >= m_max_normal_enemy_hits_count)
	{
		enemyx->m_obj = &(p.m_enemys.rbegin()->second);
		enemyx->m_index = 2;
		enemyx->m_size = make_tuple(166, 260);
	}
	else
	{
		enemyx->m_obj = &(p.m_enemys.begin()->second);
		enemyx->m_index = 0;
		enemyx->m_size = make_tuple(57, 51);
	}
	m_alive_enemys.push_back(enemyx);
	auto initx = (*m_random_dis)(*m_rand_engine);
	enemyx->m_pos.x = initx;
}

void GameMain::Run()
{
	m_music_game_music.setLoop(true);
	m_music_game_music.play();
	while (m_window.isOpen())
	{
		UpdateData();
		ProcEvent();
		if (!m_pause)
		{
			DrawScene();
		}
		else
		{
			m_music_game_music.pause();
		}
	}
}

void GameMain::ProcEvent()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		else if (event.type == sf::Event::KeyReleased) //
		{
			auto curPress = event.key;
			if (curPress.code == sf::Keyboard::Left) //press left
			{
				if (m_hero->m_pos.x <= 0)
				{
					m_play_out_porp = true;
				}
				else
				{
					m_hero->m_pos.x -= m_hero_step;
					if (m_hero->m_pos.x <= 0)
					{
						m_hero->m_pos.x = 0;
						m_play_out_porp = true;
					}
				}
			}
			else if (curPress.code == sf::Keyboard::Right) //press right
			{
				if (m_hero->m_pos.x + get<0>(m_hero->m_size) >= m_width)
				{
					m_play_out_porp = true;
				}
				else
				{
					m_hero->m_pos.x += m_hero_step;
					if (m_hero->m_pos.x + get<0>(m_hero->m_size) >= m_width)
					{
						m_hero->m_pos.x = m_width - get<0>(m_hero->m_size);
						m_play_out_porp = true;
					}
				}
			}
			else if (curPress.code == sf::Keyboard::Up)
			{
				if (m_hero->m_pos.y <= 0)
				{
					m_play_out_porp = true;
					m_play_out_porp = true;
				}
				else
				{
					m_hero->m_pos.y -= m_hero_step;
					if (m_hero->m_pos.y <= 0)
					{
						m_hero->m_pos.y = 0;
						m_play_out_porp = true;

					}
				}
			}
			else if (curPress.code == sf::Keyboard::Down)
			{
				if (m_hero->m_pos.y + get<1>(m_hero->m_size) >= m_height)
				{
					m_play_out_porp = true;
				}
				else
				{
					m_hero->m_pos.y += m_hero_step;
					if (m_hero->m_pos.y + get<1>(m_hero->m_size) >= m_height)
					{
						m_hero->m_pos.y = m_height - get<1>(m_hero->m_size);
					}
				}
			}
			else if (curPress.code == sf::Keyboard::Space)
			{
				m_pause = !m_pause;
				if (m_pause) //display pause button
				{
					
				}
			}
			else
			{
				m_window.close();
			}
		}
	}
}

void GameMain::DrawScene()
{
	m_window.clear();
	//draw background
	m_window.draw(*m_sprite_background);
	if (!m_game_over)
	{
		//draw hero
		DrawHero();
		DrawHeroBullets();
		DrawEnemy();
		DrawEnemyBullets();
	}
	else
	{
		m_window.draw(*m_sprite_gameover);
		if (!m_win)
		{
			m_music_game_music.pause();
			m_music_game_over.play();
		}
		else
		{
			m_textTag->setString("You Win");
			m_textTag->setPosition(100, 100);
			m_music_achievement.pause();
			m_music_achievement.play();
			m_window.draw(*m_textTag);
		}
		m_window.setFramerateLimit(1);
	}
	m_textTag->setString(std::to_string(m_normal_enemy_hit_count));
	m_textTag->setPosition(0, 0);
	if (!m_game_over)
	{
		m_window.draw(*m_textTag);
	}
	m_window.display();
}

void GameMain::UpdateData()
{
	sf::IntRect heroRect{ m_hero->m_pos.x, m_hero->m_pos.y, 
		get<0>(m_hero->m_size), get<1>(m_hero->m_size)};
	for (auto& it : m_enemy_bullets)
	{
		auto size = m_enemy_bullet->m_normal.m_size;
		sf::IntRect bullet{ it.x, it.y, get<0>(size), get<1>(size) };
		if (bullet.intersects(heroRect))
		{
			m_game_over = true;
		}
	}
	vector<sf::Vector2i> vtemp;
	for (auto& it : m_hero_bullets)
	{
		auto size = m_hero_bullet->m_normal.m_size;
		sf::IntRect bulletRect{ it.x, it.y, get<0>(size), get<1>(size) };
		for (auto& itx : m_alive_enemys)
		{
			sf::IntRect enemyRect{ itx->m_pos.x, itx->m_pos.y,
				get<0>(itx->m_size), get<1>(itx->m_size) };
			if (bulletRect.intersects(enemyRect) && itx->m_status == alive)
			{
				itx->m_status = blow;
				vtemp.push_back(it);
			}
		}
	}

	for (auto abc : vtemp)
	{
		auto it = find_if(m_hero_bullets.begin(), m_hero_bullets.end(), 
			[abc](sf::Vector2i v) ->bool 
		{
			return (abc.x == v.x && abc.y == v.y) ? true : false;
			
		});
		if (it != m_hero_bullets.end())
		{
			m_hero_bullets.erase(it);
		}
	}

	if (!m_game_over)
	{
		if (m_index == 0) //generate a new bullet for each enemy and hero
		{
			for (auto& it : m_alive_enemys) //generate bullet for enemy
			{
				if (it->m_status == alive)
				{
					sf::Vector2i v;
					v.x = it->m_pos.x + get<0>(it->m_size) / 2 - 5;
					v.y = it->m_pos.y + get<1>(it->m_size);
					m_enemy_bullets.push_back(v);
					it->m_pos.y += m_enemy_speed;
					auto initx = (*m_random_dis)(*m_rand_engine);
					if (initx < (m_width - 80) / 2) //enemy turn left
					{
						it->m_pos.x -= m_enemy_speed;
						if (it->m_pos.x <= 0)
						{
							it->m_pos.x = 0;
						}
					}
					else //enemy turn right
					{
						it->m_pos.x += m_enemy_speed;
						if (it->m_pos.x >= m_width - 80)
						{
							it->m_pos.x = m_width - 80;
						}
					}

				}
			}
			{ //generate bullet for hero
				sf::Vector2i v;
				v.x = m_hero->m_pos.x + get<0>(m_hero->m_size) / 2 - 5;
				v.y = m_hero->m_pos.y - 21;

				m_hero_bullets.push_back(v);
			}
		}
		for (auto& it : m_enemy_bullets)
		{
			it.y += m_enemy_bullet_step;
		}
		for (auto& it : m_hero_bullets)
		{
			it.y -= m_hero_bullet_step;
		}
		//delete invisible enemy, enemy bullets, hero bulllets.
		auto func_enemy = [this](shared_ptr<Enemy> value) ->bool
		{
			if (value->m_pos.y + get<1>(value->m_size) >= m_height 
				|| value->m_status_sprite_index >= value->m_obj->m_down.size())
			{
				if (value->m_status_sprite_index >= value->m_obj->m_down.size())
				{
					if (value->m_index == 0)
					{
						//m_music_enemy1_down.pause();
						m_music_enemy1_down.play();
					}
					else if (value->m_index == 1)
					{
						//m_music_enemy2_down.pause();
						m_music_enemy2_down.play();
					}
					else if (value->m_index == 2)
					{
						//m_music_enemy3_down.pause();
						m_music_enemy3_down.play();
						m_game_over = true;
						m_win = true;
					}
				}
				return true;
			}
			else
			{
				return false;
			}
		};
		auto it = find_if(m_alive_enemys.begin(), m_alive_enemys.end(), func_enemy);
		while (it != m_alive_enemys.end())
		{
			
			m_alive_enemys.erase(it);
			++m_normal_enemy_hit_count;
			it = find_if(m_alive_enemys.begin(), m_alive_enemys.end(), func_enemy);
		}

		//generate a new enemy
		if (m_alive_enemys.empty())
		{
			addNewEnemy();
		}

		auto func_enemy_bullet = [this](sf::Vector2i pt)->bool
		{
			return pt.y >= m_height ? true : false;
		};
		auto it_enemy = find_if(m_enemy_bullets.begin(), m_enemy_bullets.end(), func_enemy_bullet);
		while (it_enemy != m_enemy_bullets.end())
		{
			m_enemy_bullets.erase(it_enemy);
			it_enemy = find_if(m_enemy_bullets.begin(), m_enemy_bullets.end(), func_enemy_bullet);
		}

		auto func_hero_bullet = [this](sf::Vector2i pt)->bool
		{
			return pt.y <= 0 ? true : false;
		};
		auto it_hero_ = find_if(m_hero_bullets.begin(), m_hero_bullets.end(), func_hero_bullet);
		while (it_hero_ != m_hero_bullets.end())
		{
			m_hero_bullets.erase(it_hero_);
			it_hero_ = find_if(m_hero_bullets.begin(), m_hero_bullets.end(), func_hero_bullet);
		}

		++m_index;
		if (m_index > m_fps)
		{
			m_index = 0;
		}
	}
}

void GameMain::DrawHero()
{
	if (m_play_out_porp)
	{
		m_music_out_porp.stop();
		m_music_out_porp.play();
		m_play_out_porp = false;
	}
	
	switch (m_hero->m_status)
	{
	case alive:
	{
		shared_ptr<sf::Sprite> psprite = m_hero->m_obj->m_normal_sprite;
		psprite->setPosition(float(m_hero->m_pos.x), float(m_hero->m_pos.y));
		m_window.draw(*psprite);
	
	}break;
	case blow:
	{

	}break;
	default:
		break;
	}
}

void GameMain::DrawHeroBullets()
{
	shared_ptr<sf::Sprite> ptarget = nullptr;
	int i = 0;
	for (auto it = p.m_bullets.begin();it!=p.m_bullets.end();++it)
	{
		if (i == m_hero_bullet_index)
		{
			ptarget = it->second.m_normal_sprite;
			break;
		}
		++i;
	}
	for (auto it : m_hero_bullets)
	{
		ptarget->setPosition(float(it.x), float(it.y));
		m_window.draw(*ptarget);
	}
}

void GameMain::DrawEnemy()
{
	for (auto& it : m_alive_enemys)
	{
		switch (it->m_status)
		{
		case alive:
		{
			shared_ptr<sf::Sprite> ptarget = nullptr;
			int i = 0;
			for (auto itx = p.m_enemys.begin(); itx != p.m_enemys.end(); ++itx)
			{
				if (it->m_index == i)
				{
					if (i == 2)
					{
						ptarget = itx->second.m_n_sprites.begin()->second;
					}
					else
					{
						ptarget = itx->second.m_normal_sprite;
					}
					break;
				}
				++i;
			}
			if (ptarget)
			{
				ptarget->setPosition(float(it->m_pos.x), float(it->m_pos.y));
				m_window.draw(*ptarget);
			}
		}break;
		case blow:
		{
			shared_ptr<sf::Sprite> ptarget = nullptr;
			auto status_index = it->m_status_sprite_index;
			if (status_index < it->m_obj->m_down_sprites.size())
			{
				int x = 0;
				for (auto itsprite = it->m_obj->m_down_sprites.begin(); itsprite != it->m_obj->m_down_sprites.end();
					++itsprite)
				{
					if (x == status_index)
					{
						ptarget = itsprite->second;
					}
					++x;
				}
			}
			if (ptarget)
			{
				ptarget->setPosition(float(it->m_pos.x), float(it->m_pos.y));
				m_window.draw(*ptarget);
			}
			++it->m_status_sprite_index;
		}break;
		default:
			break;
		}
	}
}

void GameMain::DrawEnemyBullets()
{
	shared_ptr<sf::Sprite> ptarget = nullptr;
	int i = 0;
	for (auto it = p.m_bullets.begin(); it != p.m_bullets.end(); ++it)
	{
		if (i == m_enemy_bullet_index)
		{
			ptarget = it->second.m_normal_sprite;
			break;
		}
		++i;
	}
	for (auto it : m_enemy_bullets)
	{
		ptarget->setPosition(float(it.x), float(it.y));
		m_window.draw(*ptarget);
	}
}
