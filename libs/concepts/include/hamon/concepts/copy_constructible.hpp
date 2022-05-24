/**
 *	@file	copy_constructible.hpp
 *
 *	@brief	copy_constructible の定義
 */

#ifndef HAMON_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
#define HAMON_CONCEPTS_COPY_CONSTRUCTIBLE_HPP

#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::copy_constructible;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>

namespace hamon
{

template <typename T>
concept copy_constructible =
	hamon::move_constructible<T> &&
	hamon::constructible_from<T, T&>       && hamon::convertible_to<T&, T> &&
	hamon::constructible_from<T, T const&> && hamon::convertible_to<T const&, T> &&
	hamon::constructible_from<T, T const>  && hamon::convertible_to<T const, T>;

}	// namespace hamon

#else

#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T>
struct copy_constructible_impl
{
private:
	template <typename U>
	static auto test(int) -> hamon::conjunction<
		hamon::move_constructible<U>,
		hamon::constructible_from<U, U&>,       hamon::convertible_to<U&, U>,
		hamon::constructible_from<U, U const&>, hamon::convertible_to<U const&, U>,
		hamon::constructible_from<U, U const>,  hamon::convertible_to<U const, U>>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using copy_constructible =
	typename detail::copy_constructible_impl<T>::type;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T>
using copy_constructible_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::copy_constructible<T>>;
#else
	hamon::copy_constructible<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_COPY_CONSTRUCTIBLE_HPP
