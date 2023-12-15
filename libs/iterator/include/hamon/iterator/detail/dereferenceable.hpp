/**
 *	@file	dereferenceable.hpp
 *
 *	@brief	dereferenceable の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_DEREFERENCEABLE_HPP
#define HAMON_ITERATOR_DETAIL_DEREFERENCEABLE_HPP

#include <hamon/iterator/detail/can_reference.hpp>
#include <hamon/iterator/concepts/detail/is_void_pointer.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
concept dereferenceable =
	requires(T& t)
	{
		{ *t } -> hamon::detail::can_reference;
	};

template <typename T>
using dereferenceable_t = hamon::bool_constant<dereferenceable<T>>;

#else

template <typename T>
struct dereferenceable_impl
{
private:
	template <typename U,
		typename = hamon::enable_if_t<!hamon::detail::is_void_pointer<U>::value>,
		typename U2 = decltype(*hamon::declval<U&>())
	>
	static auto test(int) -> hamon::detail::can_reference<U2>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

template <typename T>
using dereferenceable =
	typename detail::dereferenceable_impl<T>::type;

template <typename T>
using dereferenceable_t = dereferenceable<T>;

#endif

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_DEREFERENCEABLE_HPP
