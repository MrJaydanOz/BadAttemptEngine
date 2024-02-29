#pragma once

class Time
{
private:
	float _timeScale;
	float _minTimestep;
	float _maxTimestep;
	float _fixedTimestep;

	double _lastTimeCount;
	double _currentTimeCount;
	double _fixedTimeCount;
	bool _isFixedUpdate;

public:
	Time();
	~Time();

	float SecondsAfterStart() const;
	double SecondsAfterStartDouble() const;

	float DeltaTime() const;
	double DeltaTimeDouble() const;

	bool IsFixedUpdate();

private:

};