#pragma once

#include "AbstractScene.h"
#include "ScoreMgr.h"
#include "Game.h"

#include <memory>

class GameScene : public AbstractScene
{
public:
	GameScene(IOnSceneChangedListener* impl, const Parameter& parameter);
	virtual ~GameScene() = default;
	void initialize() override;
	bool update() override;
	void finalize() const override;
	void draw() const override;

private:
	int _nowSelect;
	std::shared_ptr<ScoreMgr> _implScore;
	std::unique_ptr<AbstractGame> _implGame;
};