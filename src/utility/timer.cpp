#include "timer.hpp"

void vi::Timer::Reset()
{
	m_start = std::chrono::steady_clock::now();
	m_current = m_start;
}

void vi::Timer::Tick()
{
	m_current = std::chrono::steady_clock::now();
}

double vi::Timer::Duration() const
{
	return std::chrono::duration<double>(m_current - m_start).count();
}
