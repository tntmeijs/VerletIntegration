#ifndef TIMER_HPP
#define TIMER_HPP

#include <chrono>

namespace vi
{
	class Timer
	{
	public:
		/**
		 * Start recording a time interval
		 */
		void Start();

		/**
		 * Update the timer to the current time
		 */
		void Update();

		/**
		 * Get the current time since the start
		 *
		 * @return	Time since the start of the timer
		 */
		float Duration() const;

	private:
		/** Timestamp when the clock was started */
		std::chrono::steady_clock::time_point m_start;

		/** Timestamp at the most recent tick */
		std::chrono::steady_clock::time_point m_current;
	};
}

#endif //! TIMER_HPP
