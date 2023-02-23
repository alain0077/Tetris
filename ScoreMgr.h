#pragma once

#include "IIncScoreListener.h"

#include <vector>

class ScoreMgr final : public IIncScoreListener
{
public:
	ScoreMgr();
	~ScoreMgr() = default;
	void init();
	bool update();
	void draw() const;

	// Add N to the score.
	void IncScore(int) override;

	/*
	* return final score
	* Will change to add according to survival time dependence
	*/
	int getFilalScore() { return _score; }

	// return final time
	int getTime();

	// stop time
	void stopTime() { _stopFlag = true; }

	// start time
	void startTime() { _stopFlag = false; }

private:
	int _time;
	int _preCount;
	int _score;
	bool _stopFlag;
};