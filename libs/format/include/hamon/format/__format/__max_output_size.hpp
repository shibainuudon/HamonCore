/**
 *	@file	__max_output_size.hpp
 *
 *	@brief	__max_output_size の定義
 */

#ifndef HAMON_FORMAT___FORMAT___MAX_OUTPUT_SIZE_HPP
#define HAMON_FORMAT___FORMAT___MAX_OUTPUT_SIZE_HPP

#include <hamon/algorithm/min.hpp>

namespace hamon
{

namespace __format
{

// A helper to limit the total size of code units written.
class __max_output_size
{
public:
	[[nodiscard]] explicit __max_output_size(size_t __max_size) : __max_size_ {__max_size} {}

	// This function adjusts the size of a (bulk) write operations. It ensures the
	// number of code units written by a __output_buffer never exceeds
	// __max_size_ code units.
	[[nodiscard]] size_t __write_request(size_t __code_units)
	{
		size_t __result =
			__code_units_written_ < __max_size_ ? hamon::min(__code_units, __max_size_ - __code_units_written_) : 0;
		__code_units_written_ += __code_units;
		return __result;
	}

	[[nodiscard]] size_t __code_units_written() const noexcept { return __code_units_written_; }

private:
	size_t __max_size_;
	// The code units that would have been written if there was no limit.
	// format_to_n returns this value.
	size_t __code_units_written_ {0};
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___MAX_OUTPUT_SIZE_HPP
