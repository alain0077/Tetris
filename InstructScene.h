#pragma once

#include "AbstractScene.h"

#include <fstream>

class InstructScene : public AbstractScene
{
public:
	InstructScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~InstructScene() = default;
	void initialize() override {};
	bool update() override;
	void finalize() const override {};
	void draw() const override;

private:
	int _NowSelect;
};