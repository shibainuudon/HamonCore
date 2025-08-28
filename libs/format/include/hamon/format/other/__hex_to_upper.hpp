/**
 *	@file	__hex_to_upper.hpp
 *
 *	@brief	__hex_to_upper の定義
 */

#ifndef HAMON_FORMAT_OTHER___hex_to_upper_HPP
#define HAMON_FORMAT_OTHER___hex_to_upper_HPP


namespace hamon
{

inline constexpr char __hex_to_upper(char __c)
{
	switch (__c)
	{
	case 'a':
		return 'A';
	case 'b':
		return 'B';
	case 'c':
		return 'C';
	case 'd':
		return 'D';
	case 'e':
		return 'E';
	case 'f':
		return 'F';
	}
	return __c;
}

}	// namespace hamon

#endif // HAMON_FORMAT_OTHER___hex_to_upper_HPP
