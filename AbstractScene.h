#pragma once

#include "IOnSceneChangedListener.h"
#include "Parameter.h"

class AbstractScene
{
protected:
	IOnSceneChangedListener* _implSceneChanged;
public:
	AbstractScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~AbstractScene() = default;
	virtual void initialize() = 0;
	virtual bool update() = 0;
	virtual void finalize() const = 0;
	virtual void draw() const = 0;
};