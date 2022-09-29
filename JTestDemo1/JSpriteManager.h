#pragma once
#include "JSingleton.h"

class JSpriteManager : public JSingleton<JSpriteManager>
{
	friend class JSingleton<JSpriteManager>;

private:
	JSpriteManager() {};
	~JSpriteManager() = default;
	JSpriteManager(const JSpriteManager&) = delete;
	JSpriteManager& operator=(const JSpriteManager&) = delete;
};

