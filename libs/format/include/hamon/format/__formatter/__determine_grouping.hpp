/**
 *	@file	__determine_grouping.hpp
 *
 *	@brief	__determine_grouping の定義
 */

#ifndef HAMON_FORMAT___FORMATTER___DETERMINE_GROUPING_HPP
#define HAMON_FORMAT___FORMATTER___DETERMINE_GROUPING_HPP

#include <hamon/string.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace __formatter
{

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)	// '' から '' への変換です。データが失われる可能性があります。
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-conversion")

/**
 * Determines the required grouping based on the size of the input.
 *
 * The grouping's last element will be repeated. For simplicity this repeating
 * is unwrapped based on the length of the input. (When the input is short some
 * groups are not processed.)
 *
 * @returns The size of the groups to write. This means the number of
 * separator characters written is size() - 1.
 *
 * @note Since zero-sized groups cause issues they are silently ignored.
 *
 * @note The grouping field of the locale is always a @c std::string,
 * regardless whether the @c std::numpunct's type is @c char or @c wchar_t.
 */
inline hamon::string
__determine_grouping(ptrdiff_t __size, const hamon::string& __grouping)
{
//	_LIBCPP_ASSERT_INTERNAL(!__grouping.empty() && __size > __grouping[0],
//							"The slow grouping formatting is used while there will be no separators written");
	hamon::string __r;
	auto __end = __grouping.end() - 1;
	auto __ptr = __grouping.begin();

	while (true)
	{
		__size -= *__ptr;
		if (__size > 0)
		{
			__r.push_back(*__ptr);
		}
		else
		{
			// __size <= 0 so the value pushed will be <= *__ptr.
			__r.push_back(*__ptr + __size);
			return __r;
		}

		// Proceed to the next group.
		if (__ptr != __end)
		{
			do
			{
				++__ptr;
				// Skip grouping with a width of 0.
			}
			while (*__ptr == 0 && __ptr != __end);
		}
	}

	HAMON_UNREACHABLE();
}

HAMON_WARNING_POP()

}	// namespace __formatter

}	// namespace hamon

#endif // HAMON_FORMAT___FORMATTER___DETERMINE_GROUPING_HPP
