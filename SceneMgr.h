#pragma once

#include <stack>
#include <memory>
#include "AbstractScene.h"
#include "IOnSceneChangedListener.h"

class SceneMgr final : public IOnSceneChangedListener
{
public:
	SceneMgr();
	~SceneMgr() = default;
	bool update();
	void onSceneChanged(const eScene scene, const Parameter& parameter, const bool stackClear) override;

private:
	std::stack<std::shared_ptr<AbstractScene>> _sceneStack;
};