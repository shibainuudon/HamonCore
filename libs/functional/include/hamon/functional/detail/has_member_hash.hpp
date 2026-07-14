/**
 *	@file	has_member_hash.hpp
 *
 *	@brief	has_member_hash コンセプトの定義
 */

#ifndef HAMON_FUNCTIONAL_DETAIL_HAS_MEMBER_HASH_HPP
#define HAMON_FUNCTIONAL_DETAIL_HAS_MEMBER_HASH_HPP

#include <hamon/detail/decay_copy.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_hash =
	requires(T&& t)
	{
		{ decay_copy(hamon::forward<T>(t).hash()) } -> hamon::convertible_to<hamon::size_t>;
	};

#else

template <typename T>
struct has_member_hash_impl
{
private:
	template <typename U,
		typename B = decltype(decay_copy(hamon::declval<U&>().hash())),
		typename = hamon::enable_if_t<hamon::convertible_to<B, hamon::size_t>>
	>
	static auto test(int) -> hamon::true_type;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
HAMON_CONCEPT_OR_BOOL has_member_hash = has_member_hash_impl<T>::type::value;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_FUNCTIONAL_DETAIL_HAS_MEMBER_HASH_HPP
