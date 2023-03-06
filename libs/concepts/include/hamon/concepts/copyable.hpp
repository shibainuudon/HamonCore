/**
 *	@file	copyable.hpp
 *
 *	@brief	copyable の定義
 */

#ifndef HAMON_CONCEPTS_COPYABLE_HPP
#define HAMON_CONCEPTS_COPYABLE_HPP

#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::copyable;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/concepts/assignable_from.hpp>

namespace hamon
{

template <typename T>
concept copyable =
	hamon::copy_constructible<T> &&
	hamon::movable<T> &&
	hamon::assignable_from<T&, T&> &&
	hamon::assignable_from<T&, const T&> &&
	hamon::assignable_from<T&, const T>;

}	// namespace hamon

#else

#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct copyable_impl
{
private:
	template <typename U>
	static auto test(int) -> hamon::conjunction<
		hamon::copy_constructible<U>,
		hamon::movable<U>,
		hamon::assignable_from<U&, U&>,
		hamon::assignable_from<U&, const U&>,
		hamon::assignable_from<U&, const U>>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using copyable =
	typename detail::copyable_impl<T>::type;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/negation.hpp>

namespace hamon
{

template <typename T>
using copyable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::copyable<T>>;
#else
	hamon::copyable<T>;
#endif

// not_copyable
#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <typename T>
concept not_copyable = !hamon::copyable<T>;
#else
template <typename T>
using not_copyable = hamon::negation<hamon::copyable<T>>;
#endif

template <typename T>
using not_copyable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::not_copyable<T>>;
#else
	hamon::not_copyable<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_COPYABLE_HPP
