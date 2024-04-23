#pragma once
#include "BAE_Def.h"
#if defined(MESSAGE_WHEN_INCLUDED)
#pragma message(MESSAGE_WHEN_INCLUDED("BAE_Time.h"))
#endif
#include <chrono>

namespace bae
{
	class Game;

#if defined(MESSAGE_WHEN_CLASS_DECLARED)
#pragma message(MESSAGE_WHEN_CLASS_DECLARED(class Time))
#endif
	class Time
	{
		friend class Game;

	private:
		bool _isWorking;
		bool _useFixedTimeForPhysics;
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

		bool GetUseFixedTimeForPhysics() const noexcept;
		void SetUseFixedTimeForPhysics(in<bool> useFixedTimeForPhysics) noexcept;

		float GetTimeScale() const noexcept;

		void SetTimeScale(in<float> timeScale) noexcept;

		float GetMinTimestep() const noexcept;

		void SetMinTimestep(in<float> timeScale) noexcept;

		float GetMaxTimestep() const noexcept;

		void SetMaxTimestep(in<float> timeScale) noexcept;

		float GetFixedTimestep() const noexcept;

		void SetFixedTimestep(in<float> timeScale) noexcept;

		float GetPhysicsTimestep() const noexcept;

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

		float PhysicsDeltaTime() const noexcept;
		double PhysicsDeltaTimeDouble() const noexcept;

		float UnscaledPhysicsDeltaTime() const noexcept;
		double UnscaledPhysicsDeltaTimeDouble() const noexcept;

	private:
		bool _IsFixedUpdateQueued() noexcept;

		void _SleepUntilNextFrame() noexcept;
	};
}