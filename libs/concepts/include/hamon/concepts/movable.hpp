/**
 *	@file	movable.hpp
 *
 *	@brief	movable の定義
 */

#ifndef HAMON_CONCEPTS_MOVABLE_HPP
#define HAMON_CONCEPTS_MOVABLE_HPP

#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::movable;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/swappable.hpp>

namespace hamon
{

template <typename T>
concept movable =
	std::is_object<T>::value &&
	hamon::move_constructible<T> &&
	hamon::assignable_from<T&, T> &&
	hamon::swappable<T>;

}	// namespace detail

#else

#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/assignable_from.hpp>
#include <hamon/concepts/swappable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <type_traits>

namespace hamon
{

namespace detail
{

template <typename T>
struct movable_impl
{
private:
	template <typename U>
	static auto test(int) -> hamon::conjunction<
		std::is_object<U>,
		hamon::move_constructible<U>,
		hamon::assignable_from<U&, U>,
		hamon::swappable<U>>;

	template <typename U>
	static auto test(...) -> std::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using movable = typename detail::movable_impl<T>::type;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T>
using movable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::movable<T>>;
#else
	hamon::movable<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_MOVABLE_HPP
