/**
 *	@file	nothrow_forward_range.hpp
 *
 *	@brief	nothrow_forward_range を定義
 */

#ifndef HAMON_MEMORY_RANGES_DETAIL_NOTHROW_FORWARD_RANGE_HPP
#define HAMON_MEMORY_RANGES_DETAIL_NOTHROW_FORWARD_RANGE_HPP

#include <hamon/memory/ranges/detail/nothrow_input_range.hpp>
#include <hamon/memory/ranges/detail/nothrow_forward_iterator.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/config.hpp>

namespace hamon
{
namespace ranges
{
namespace detail
{

// 27.11.2 Special memory concepts[special.mem.concepts]

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename R>
HAMON_CONCEPT_OR_BOOL nothrow_forward_range =
	hamon::ranges::detail::nothrow_input_range<R> &&
	hamon::ranges::detail::nothrow_forward_iterator<hamon::ranges::iterator_t<R>>;

#else

template <typename R>
struct nothrow_forward_range_impl
{
private:
	template <typename R2,
		typename = hamon::enable_if_t<
			hamon::ranges::detail::nothrow_input_range<R2> &&
			hamon::ranges::detail::nothrow_forward_iterator<hamon::ranges::iterator_t<R2>>
		>
	>
	static auto test(int) -> hamon::true_type;

	template <typename>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<R>(0));
};

template <typename R>
HAMON_CONCEPT_OR_BOOL nothrow_forward_range = nothrow_forward_range_impl<R>::type::value;

#endif

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_MEMORY_RANGES_DETAIL_NOTHROW_FORWARD_RANGE_HPP
