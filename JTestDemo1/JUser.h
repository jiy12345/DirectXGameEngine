#pragma once
#include"JBaseObject.h"
#include"JSpriteManager.h"

enum SPRITE {
	IDLE_DOWN,
	IDLE_RIGHT,
	IDLE_LEFT,
	IDLE_UP,
	IDLE_RIGHT_UP,
	IDLE_LEFT_UP,
};

class JUser : public JBaseObject
{
public:
	SPRITE					m_curSprite = IDLE_DOWN;
	int						m_iIndex = 0;
	float					m_fStep;
	float					m_fEffectTimer = 0.0f;
	std::vector<JSprite>	m_vSpriteInfo;
public:
	bool init() override;
	bool frame() override;
public:
	void updateUVCoord() override;
	void setCurDirection(float angle);
};

