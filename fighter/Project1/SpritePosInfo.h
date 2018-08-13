#pragma once
#include <string>
#include <tuple>
using std::string;
using std::tuple;
typedef tuple<int,int> POS_TYPE;

typedef POS_TYPE SIZE_TYPE;
typedef POS_TYPE ORIG_TYPE;
typedef POS_TYPE OFFSET_TYPE;

class SpritePosInfo
{
public:
	SpritePosInfo();
	~SpritePosInfo();
	
//private:
	std::string m_spritName;
	bool m_rotate = false;
	int m_index = -1;
	POS_TYPE	m_xy;
	SIZE_TYPE	m_size;
	ORIG_TYPE	m_orig;
	OFFSET_TYPE	m_offset;
};

