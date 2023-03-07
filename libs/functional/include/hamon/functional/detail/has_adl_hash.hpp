/**
 *	@file	has_adl_hash.hpp
 *
 *	@brief	has_adl_hash
 */

#ifndef HAMON_FUNCTIONAL_DETAIL_HAS_ADL_HASH_HPP
#define HAMON_FUNCTIONAL_DETAIL_HAS_ADL_HASH_HPP

#include <hamon/detail/decay_copy.hpp>
#include <hamon/concepts/detail/class_or_enum.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <cstddef>

namespace hamon
{

namespace detail
{

template <typename T> void hash(T&) = delete;
template <typename T> void hash(T const&) = delete;

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept has_adl_hash =
	hamon::detail::class_or_enum<hamon::remove_reference_t<T>> &&
	requires(T&& t)
	{
		{ decay_copy(hash(hamon::forward<T>(t))) } -> hamon::convertible_to<std::size_t>;
	};

#else

template <typename T>
struct has_adl_hash_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<
			hamon::detail::class_or_enum<
				hamon::remove_reference_t<U>
			>::value
		>,
		typename B = decltype(decay_copy(hash(hamon::declval<U&>())))
	>
	static auto test(int) -> hamon::convertible_to<B, std::size_t>;
	
	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using has_adl_hash = typename has_adl_hash_impl<T>::type;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_DETAIL_HAS_ADL_HASH_HPP
