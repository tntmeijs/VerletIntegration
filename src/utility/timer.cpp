#include "timer.hpp"

void vi::Timer::Start()
{
	m_start = std::chrono::steady_clock::now();
	m_current = m_start;
}

void vi::Timer::Update()
{
	m_current = std::chrono::steady_clock::now();
}

float vi::Timer::Duration() const
{
	std::chrono::duration<float> delta = m_current - m_start;
	std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(delta);
	return milliseconds.count();
}
