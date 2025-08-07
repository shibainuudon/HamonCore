/**
 *	@file	__format_to_n_buffer.hpp
 *
 *	@brief	__format_to_n_buffer の定義
 */

#ifndef HAMON_FORMAT___FORMAT___FORMAT_TO_N_BUFFER_HPP
#define HAMON_FORMAT___FORMAT___FORMAT_TO_N_BUFFER_HPP

#include <hamon/format/__format/__fmt_char_type.hpp>
#include <hamon/format/__format/__buffer_selector.hpp>
#include <hamon/format/__format/__max_output_size.hpp>
#include <hamon/format/format_to_n_result.hpp>
#include <hamon/iterator/iter_difference_t.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/utility/move.hpp>

namespace hamon
{

namespace __format
{

// A buffer that counts and limits the number of insertions.
template <class _OutIt, __format::__fmt_char_type _CharT>
class __format_to_n_buffer : private __format::__buffer_selector<_OutIt, _CharT>::type
{
public:
	using _Base = typename __format::__buffer_selector<_OutIt, _CharT>::type;

	[[nodiscard]] __format_to_n_buffer(_OutIt __out_it, hamon::iter_difference_t<_OutIt> __n)
		: _Base{hamon::move(__out_it), hamon::addressof(__max_output_size_)}
		, __max_output_size_{__n < 0 ? size_t {0} : static_cast<size_t>(__n)}
	{}

	[[nodiscard]] auto __make_output_iterator()
	{
		return _Base::__make_output_iterator();
	}

	[[nodiscard]] hamon::format_to_n_result<_OutIt> __result() &&
	{
		return {static_cast<_Base&&>(*this).__out_it(),
			static_cast<hamon::iter_difference_t<_OutIt>>(__max_output_size_.__code_units_written())};
	}

private:
	__format::__max_output_size __max_output_size_;
};

}	// namespace __format

}	// namespace hamon

#endif // HAMON_FORMAT___FORMAT___FORMAT_TO_N_BUFFER_HPP
