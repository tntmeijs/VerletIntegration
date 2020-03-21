#ifndef LITERALS_HPP
#define LITERALS_HPP

constexpr double operator"" _Hz(unsigned long long frequency)
{
	return 1.0 / static_cast<double>(frequency);
}

#endif //! LITERALS_HPP
