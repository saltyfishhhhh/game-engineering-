#pragma once
#include "SpritePosInfo.h"
#include "Objects.h"
#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include <tuple>

using  std::string;
using std::map;
using std::ifstream;
using std::tuple;

enum sprite_type
{
	hit,
	nnumber,
	down,
	normal,
	press,
};

class ParsePackFile
{
public:
	ParsePackFile();
	~ParsePackFile();
	bool parseFile(const string file);
	void parseSprite(ifstream& ifs, Objects& obj, sprite_type type,string objx);
	tuple<int, int> parseLine(string line);
	void genSprite(sf::Texture& texture);
//private:
	string m_imageFile="";
	string m_backImage = "image/background.png";
	string m_gameoverImage = "image/gameover.png";
	map<string, Objects> m_bullets;
	map<string, Objects> m_enemys;
	map<string, Objects> m_heros;
	map<string, Objects> m_game_pauses;
	map<string, Objects> m_ufos;
	map<string, Objects> m_bombs;
};

