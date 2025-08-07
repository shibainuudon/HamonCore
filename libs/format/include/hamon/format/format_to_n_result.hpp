/**
 *	@file	format_to_n_result.hpp
 *
 *	@brief	format_to_n_result の定義
 */

#ifndef HAMON_FORMAT_FORMAT_TO_N_RESULT_HPP
#define HAMON_FORMAT_FORMAT_TO_N_RESULT_HPP

#include <hamon/format/config.hpp>

#if defined(HAMON_USE_STD_FORMAT)

#include <format>

namespace hamon
{

using std::format_to_n_result;

}	// namespace hamon

#else

#include <hamon/iterator/iter_difference_t.hpp>

namespace hamon
{

template <typename Out>
struct format_to_n_result
{
	Out out;
	hamon::iter_difference_t<Out> size;
};

}	// namespace hamon

#endif

#endif // HAMON_FORMAT_FORMAT_TO_N_RESULT_HPP
