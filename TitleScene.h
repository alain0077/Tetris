#pragma once

#include "AbstractScene.h"

enum eTitleSelect {
	Start,
	Instructions,
	End,
	TitleNum,
};

class TitleScene : public AbstractScene
{
public:
	TitleScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~TitleScene() = default;
	void initialize() override;
	bool update() override;
	void finalize() const override;
	void draw() const override;

private:
	int _nowSelect;
};