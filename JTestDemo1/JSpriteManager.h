#pragma once
#include "JSprite.h"
#include "JSingleton.h"

class JSpriteManager : public JSingleton<JSpriteManager>
{
	friend class JSingleton<JSpriteManager>;
public:
	std::vector<W_STR> m_rtNameList;
	std::vector<std::vector<nCube<2>>> m_rtSpriteList;
private:
	std::unordered_map<std::wstring, JSprite*> m_List;
public:
	bool gameDataLoad(const TCHAR* pszLoad);
	bool load(std::wstring fileName, std::wstring spriteName);
	bool release();
private:
	JSpriteManager() {};
	~JSpriteManager() = default;
	JSpriteManager(const JSpriteManager&) = delete;
	JSpriteManager& operator=(const JSpriteManager&) = delete;
};

