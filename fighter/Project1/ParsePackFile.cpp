#include "ParsePackFile.h"



using namespace std;

ParsePackFile::ParsePackFile()
{
}


ParsePackFile::~ParsePackFile()
{
}

bool ParsePackFile::parseFile(const string file)
{
	string image_postfix = ".png";
	bool bret = false;
	ifstream ifs(file);
	if (!ifs.good()) return bret;
	string line;
	while (!std::getline(ifs, line).eof())
	{
		if (line.find(image_postfix) != string::npos)
		{
			m_imageFile = "image/"+line;
		}
		else if (line.find("enemy") != string::npos)
		{
			for (int i = 1; i <= 3; ++i)
			{
				auto key = "enemy" + to_string(i);
				if (line.find(key) != string::npos) //enemy+i
				{
					Objects& obj = m_enemys[key];
					auto key_hit = key + "_hit";
					auto key_n = key + "_n";
					auto key_down = key + "_down";
					if (line.find(key_hit)!=string::npos)
					{
						parseSprite(ifs, obj, hit, line);
					}
					else if (line == key)
					{
						parseSprite(ifs, obj, normal, line);
					}
					else if (line.find(key_n)!=string::npos)
					{
						parseSprite(ifs, obj, nnumber, line);
					}
					else if (line.find(key_down)!=string::npos)
					{
						parseSprite(ifs, obj, down, line);
					}
					break;
				}
			}
		}
		else if (line.find("game_pause") != string::npos)
		{
			Objects& obj = m_game_pauses[line];
			parseSprite(ifs, obj, press, line);

		}
		else if (line.find("bullet") != string::npos)
		{
			Objects& obj = m_bullets[line];
			parseSprite(ifs, obj, normal, line);
		}
		else if (line.find("bomb") != string::npos)
		{
			Objects& obj = m_bombs[line];
			parseSprite(ifs, obj, normal, line);
		}
		else if (line.find("hero") != string::npos)
		{
			if (line == "hero1" || line == "hero2")
			{
				Objects& obj = m_heros[line];
				parseSprite(ifs, obj, normal, line);
			}
			else
			{
				for (int i = 1; i <= 2; ++i)
				{
					auto key = "hero" + std::to_string(i);
					Objects& obj = m_heros[key];
					parseSprite(ifs, obj, down, line);
				}
			}
		}
		else if (line.find("ufo") != string::npos)
		{
			Objects& obj = m_ufos[line];
			parseSprite(ifs, obj, normal, line);
		}
	}
	bret = true;
	return bret;
}

void ParsePackFile::parseSprite(ifstream& ifs, Objects& obj, sprite_type type, string objx)
{
	SpritePosInfo info;
	info.m_spritName = objx;
	string line;
	getline(ifs, line); //rotate
	 
	getline(ifs, line); //xy
	info.m_xy = parseLine(line);
	
	getline(ifs, line);//size
	info.m_size = parseLine(line);

	getline(ifs, line); //origin
	info.m_orig = parseLine(line);

	getline(ifs, line); //offset
	info.m_offset = parseLine(line);

	getline(ifs, line); //index
	

	switch (type)
	{
	case hit:
		obj.m_hit.insert({ objx, info });
		break;
	case nnumber:
		obj.m_n.insert({ objx, info });
		break;
	case down:
		obj.m_down.insert({ objx, info });
		break;
	case normal:
		obj.m_normal = info;
		obj.m_name = objx;
		break;
	case press:
		obj.m_press = info;
		obj.m_pressname = line;
		break;
	default:
		break;
	}
}

tuple<int, int> ParsePackFile::parseLine(string line)
{
	using std::atoi;
	int first, second;
	line = line.substr(line.find(':') + 2);
	string a = line.substr(0, line.find(','));
	string b = line.substr(line.find(',') + 2);
	first = atoi(a.c_str());
	second = atoi(b.c_str());
	return make_tuple(first, second);
}

void ParsePackFile::genSprite(sf::Texture& texture)
{
	for (auto& it : m_bullets)
	{
		it.second.InitSprite(texture);
	}
	for (auto& it : m_enemys)
	{
		it.second.InitSprite(texture);
	}
	for (auto& it : m_heros)
	{
		it.second.InitSprite(texture);
	}
	for (auto& it : m_game_pauses)
	{
		it.second.InitSprite(texture);
	}
	for (auto& it : m_ufos)
	{
		it.second.InitSprite(texture);
	}
	for (auto& it : m_bombs)
	{
		it.second.InitSprite(texture);
	}
}
