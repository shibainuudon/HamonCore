/**
 *	@file	simple_allocator.hpp
 *
 *	@brief	simple_allocator を定義
 */

#ifndef HAMON_MEMORY_DETAIL_SIMPLE_ALLOCATOR_HPP
#define HAMON_MEMORY_DETAIL_SIMPLE_ALLOCATOR_HPP

#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/equality_comparable.hpp>
#include <hamon/concepts/same_as.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

// [allocator.requirements.general]/99

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Alloc>
concept simple_allocator =
	requires(Alloc alloc, hamon::size_t n)
	{
		{ *alloc.allocate(n) } -> hamon::same_as<typename Alloc::value_type&>;
		{ alloc.deallocate(alloc.allocate(n), n) };
	} &&
	hamon::copy_constructible<Alloc> &&
	hamon::equality_comparable<Alloc>;

template <typename Alloc>
concept not_simple_allocator = !simple_allocator<Alloc>;

#else

template <typename Alloc>
struct simple_allocator_impl
{
private:
	template <typename U,
		typename P = decltype(hamon::declval<U>().allocate(hamon::declval<hamon::size_t>())),
		typename = hamon::enable_if_t<hamon::same_as<decltype(*hamon::declval<P>()), typename U::value_type&>::value>,
		typename = decltype(hamon::declval<U>().deallocate(hamon::declval<P>(), hamon::declval<hamon::size_t>()))
	>
	static auto test(int) -> hamon::conjunction<
		hamon::copy_constructible<U>,
		hamon::equality_comparable<U>>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Alloc>(0));
};

template <typename Alloc>
using simple_allocator =
	typename simple_allocator_impl<Alloc>::type;

template <typename Alloc>
using not_simple_allocator = hamon::negation<simple_allocator<Alloc>>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_MEMORY_DETAIL_SIMPLE_ALLOCATOR_HPP
