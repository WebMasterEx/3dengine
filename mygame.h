#pragma once

#include <map>
#include "basegame.h"

class CGame : public CBaseGame {
public:
	CGame() : CBaseGame() {

	}

	virtual bool Init();
	virtual bool Update();
	virtual bool Render(float interpolation);
	virtual bool Shutdown();

protected:
	std::map<std::string, Model*> models;
	CLight* light, *light2;
};