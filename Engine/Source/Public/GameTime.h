#pragma once
#include <chrono>

class Time
{
private:
	float _timeScale;
	float _minTimestep;
	float _maxTimestep;
	float _fixedTimestep;

	double _unscaledCurrentTimeCount;
	double _unscaledLastTimeCount;
	double _unscaledFixedTimeCount;
	double _currentTimeCount;
	double _lastTimeCount;
	double _fixedTimeCount;
	std::chrono::system_clock::time_point _nextFrameTime;

public:
	Time();
	~Time();

	float GetTimeScale() const noexcept;
	void SetTimeScale(float timeScale) noexcept;

	float GetMinTimestep() const noexcept;
	void SetMinTimestep(float timeScale) noexcept;

	float GetMaxTimestep() const noexcept;
	void SetMaxTimestep(float timeScale) noexcept;

	float GetFixedTimestep() const noexcept;
	void SetFixedTimestep(float timeScale) noexcept;

	float SecondsAfterStart() const noexcept;
	double SecondsAfterStartDouble() const noexcept;

	float UnscaledSecondsAfterStart() const noexcept;
	double UnscaledSecondsAfterStartDouble() const noexcept;

	float DeltaTime() const noexcept;
	double DeltaTimeDouble() const noexcept;

	float UnscaledDeltaTime() const noexcept;
	double UnscaledDeltaTimeDouble() const noexcept;

	float FixedDeltaTime() const noexcept;
	double FixedDeltaTimeDouble() const noexcept;

	float UnscaledFixedDeltaTime() const noexcept;
	double UnscaledFixedDeltaTimeDouble() const noexcept;

	bool IsFixedUpdate() const noexcept;

	void SleepUntilNextFrame() noexcept;
};