#include "GameTime.h"

Time::Time() : 
	_timeScale(1.0f), 
	_minTimestep(1.0f / 60.0f),
	_maxTimestep(1.0f / 5.0f),
	_fixedTimestep(1.0f / 60.0f),
	_lastTimeCount(0.0),
	_currentTimeCount(0.0),
	_fixedTimeCount(0.0),
	_isFixedUpdate(false)
{ }

Time::~Time()
{
}
