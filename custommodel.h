#pragma once

#include "model.h"

class ModelCustom : public Model {
public:
	virtual void Initialize();
	virtual void Shutdown();

	virtual void Draw();
protected:

};