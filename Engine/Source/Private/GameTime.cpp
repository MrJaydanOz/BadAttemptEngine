#include "GameTime.h"
#include "Game.h"
#include <cmath>
#include <chrono>
#include <thread>

Time::Time() : 
	_timeScale(1.0f), 
	_minTimestep(1.0f / 60.0f),
	_maxTimestep(1.0f / 5.0f),
	_fixedTimestep(1.0f / 60.0f),
	_unscaledCurrentTimeCount(0.0),
	_unscaledLastTimeCount(_unscaledCurrentTimeCount),
	_unscaledFixedTimeCount(0.0),
	_currentTimeCount(_unscaledCurrentTimeCount),
	_lastTimeCount(_unscaledLastTimeCount),
	_fixedTimeCount(_unscaledFixedTimeCount),
	_nextFrameTime(std::chrono::system_clock::now())
{ }

Time::~Time()
{

}

float Time::GetTimeScale() const noexcept { return _timeScale; }
void Time::SetTimeScale(float timeScale) noexcept { _timeScale = std::max(0.0f, std::min(timeScale, 1000.0f)); }

float Time::GetMinTimestep() const noexcept { return _minTimestep; }
void Time::SetMinTimestep(float timeScale) noexcept { _minTimestep = std::max(0.001f, std::min(timeScale, 1.0f)); }

float Time::GetMaxTimestep() const noexcept { return _maxTimestep; }
void Time::SetMaxTimestep(float timeScale) noexcept { _maxTimestep = std::max(0.001f, std::min(timeScale, 1.0f)); }

float Time::GetFixedTimestep() const noexcept { return _fixedTimestep; }
void Time::SetFixedTimestep(float timeScale) noexcept { _fixedTimestep = std::max(0.001f, std::min(timeScale, 1.0f)); }

float Time::SecondsAfterStart() const noexcept { return (float)_currentTimeCount; }
double Time::SecondsAfterStartDouble() const noexcept { return _currentTimeCount; }

float Time::UnscaledSecondsAfterStart() const noexcept { return (float)_unscaledCurrentTimeCount; }
double Time::UnscaledSecondsAfterStartDouble() const noexcept { return _unscaledCurrentTimeCount; }

float Time::DeltaTime() const noexcept { return (float)(_currentTimeCount - _lastTimeCount); }
double Time::DeltaTimeDouble() const noexcept { return _currentTimeCount - _lastTimeCount; }

float Time::UnscaledDeltaTime() const noexcept { return (float)(_unscaledCurrentTimeCount - _unscaledLastTimeCount); }
double Time::UnscaledDeltaTimeDouble() const noexcept { return _unscaledCurrentTimeCount - _unscaledLastTimeCount; }

float Time::FixedDeltaTime() const noexcept { return (float)(_fixedTimestep * _timeScale); }
double Time::FixedDeltaTimeDouble() const noexcept { return _fixedTimestep * _timeScale; }

float Time::UnscaledFixedDeltaTime() const noexcept { return (float)_fixedTimestep; }
double Time::UnscaledFixedDeltaTimeDouble() const noexcept { return _fixedTimestep; }

bool Time::IsFixedUpdate() const noexcept { return Game::GetGame()->_isFixedUpdate; }

void Time::SleepUntilNextFrame() noexcept
{
	std::this_thread::sleep_until(_nextFrameTime);

	_nextFrameTime = std::chrono::system_clock::now() + std::chrono::milliseconds(llroundf(_minTimestep));
}
