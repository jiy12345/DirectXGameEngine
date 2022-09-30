#pragma once
#include "JSprite.h"
#include "JSingleton.h"

class JSpriteManager : public JSingleton<JSpriteManager>
{
	friend class JSingleton<JSpriteManager>;
private:
	std::unordered_map<std::wstring, std::vector<JSprite>> m_List;
public:
	bool load(std::vector<JSprite> &m_vSprite, std::wstring fileName);
	bool release();
private:
	JSpriteManager() {};
	~JSpriteManager() = default;
	JSpriteManager(const JSpriteManager&) = delete;
	JSpriteManager& operator=(const JSpriteManager&) = delete;
};

#define I_Sprite JSpriteManager::GetInstance()
