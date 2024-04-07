#include "BAE_Time.h"
#include "BAE_Game.h"
#include <cmath>
#include <chrono>
#include <thread>
#include "Math/Func/BAE_Comparison.h"

namespace bae
{
	Time::Time() :
		_timeScale(1.0f),
		_useFixedTimeForPhysics(true),
		_minTimestep(1.0f / 60.0f),
		_maxTimestep(1.0f / 5.0f),
		_fixedTimestep(1.0f / 60.0f),
		_unscaledCurrentTimeCount(0.0),
		_unscaledLastTimeCount(_unscaledCurrentTimeCount),
		_unscaledFixedTimeCount(0.0),
		_currentTimeCount(_unscaledCurrentTimeCount),
		_lastTimeCount(_unscaledLastTimeCount),
		_fixedTimeCount(_unscaledFixedTimeCount),
		_nextFrameTime(std::chrono::system_clock::now()),
		_isWorking(true) { }

	Time::~Time()
	{

	}

	bool Time::GetUseFixedTimeForPhysics() const noexcept
	{
		return _useFixedTimeForPhysics;
	}

	void Time::SetUseFixedTimeForPhysics(in<bool> useFixedTimeForPhysics) noexcept
	{
		_useFixedTimeForPhysics = useFixedTimeForPhysics;
	}

	float Time::GetTimeScale() const noexcept { return _timeScale; }

	void Time::SetTimeScale(in<float> timeScale) noexcept 
	{ _timeScale = Clamp(timeScale, 0.0f, 1000.0f); }

	float Time::GetMinTimestep() const noexcept 
	{ return _minTimestep; }

	void Time::SetMinTimestep(in<float> timeScale) noexcept 
	{ _minTimestep = Clamp(timeScale, 0.001f, 1.0f); }

	float Time::GetMaxTimestep() const noexcept 
	{ return _maxTimestep; }

	void Time::SetMaxTimestep(in<float> timeScale) noexcept 
	{ _maxTimestep = Clamp(timeScale, 0.001f, 1.0f); }

	float Time::GetFixedTimestep() const noexcept 
	{ return _fixedTimestep; }

	void Time::SetFixedTimestep(in<float> timeScale) noexcept 
	{ _fixedTimestep = Clamp(timeScale, 0.001f, 1.0f); }

	float Time::GetPhysicsTimestep() const noexcept 
	{ return _useFixedTimeForPhysics ? GetFixedTimestep() : GetTimeScale(); }

	float Time::SecondsAfterStart() const noexcept 
	{ return (float)_currentTimeCount; }
	double Time::SecondsAfterStartDouble() const noexcept 
	{ return _currentTimeCount; }

	float Time::UnscaledSecondsAfterStart() const noexcept 
	{ return (float)_unscaledCurrentTimeCount; }
	double Time::UnscaledSecondsAfterStartDouble() const noexcept 
	{ return _unscaledCurrentTimeCount; }

	float Time::DeltaTime() const noexcept 
	{ return Min((float)(_currentTimeCount - _lastTimeCount), _maxTimestep * _timeScale); }
	double Time::DeltaTimeDouble() const noexcept 
	{ return Min(_currentTimeCount - _lastTimeCount, (double)_maxTimestep * (double)_timeScale); }

	float Time::UnscaledDeltaTime() const noexcept 
	{ return Min((float)(_unscaledCurrentTimeCount - _unscaledLastTimeCount), _maxTimestep); }
	double Time::UnscaledDeltaTimeDouble() const noexcept 
	{ return Min(_unscaledCurrentTimeCount - _unscaledLastTimeCount, (double)_maxTimestep); }

	float Time::FixedDeltaTime() const noexcept 
	{ return _fixedTimestep; }
	double Time::FixedDeltaTimeDouble() const noexcept 
	{ return (double)_fixedTimestep; }

	float Time::UnscaledFixedDeltaTime() const noexcept 
	{ return _fixedTimestep / _timeScale; }
	double Time::UnscaledFixedDeltaTimeDouble() const noexcept 
	{ return (double)_fixedTimestep / (double)_timeScale; }

	float Time::PhysicsDeltaTime() const noexcept 
	{ return _useFixedTimeForPhysics ? FixedDeltaTime() : DeltaTime(); }
	double Time::PhysicsDeltaTimeDouble() const noexcept 
	{ return _useFixedTimeForPhysics ? FixedDeltaTimeDouble() : DeltaTimeDouble(); }

	float Time::UnscaledPhysicsDeltaTime() const noexcept 
	{ return _useFixedTimeForPhysics ? UnscaledFixedDeltaTime() : UnscaledDeltaTime(); }
	double Time::UnscaledPhysicsDeltaTimeDouble() const noexcept 
	{ return _useFixedTimeForPhysics ? UnscaledFixedDeltaTimeDouble() : UnscaledDeltaTimeDouble(); }

	bool Time::_IsFixedUpdateQueued() noexcept
	{
		if (_fixedTimeCount < _currentTimeCount)
		{
			_fixedTimeCount = Max(_fixedTimeCount, _currentTimeCount - GetMaxTimestep());

			_fixedTimeCount += _fixedTimestep;
			_unscaledFixedTimeCount += _fixedTimestep / _timeScale;
			return true;
		}
		else
			return false;
	}

	void Time::_SleepUntilNextFrame() noexcept
	{
		std::this_thread::sleep_until(_nextFrameTime);

		auto now = std::chrono::system_clock::now();

		_nextFrameTime = now + std::chrono::milliseconds(llroundf(_minTimestep * 1000.0f));
		
		_unscaledLastTimeCount = _unscaledCurrentTimeCount;
		_unscaledCurrentTimeCount = ((double)SDL_GetTicks64()) / 1000.0;

		_lastTimeCount = _currentTimeCount;
		_currentTimeCount += (_unscaledCurrentTimeCount - _unscaledLastTimeCount) * _timeScale;
	}
}