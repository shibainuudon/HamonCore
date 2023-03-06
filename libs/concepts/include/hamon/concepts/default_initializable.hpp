/**
 *	@file	default_initializable.hpp
 *
 *	@brief	default_initializable の定義
 */

#ifndef HAMON_CONCEPTS_DEFAULT_INITIALIZABLE_HPP
#define HAMON_CONCEPTS_DEFAULT_INITIALIZABLE_HPP

#include <hamon/concepts/config.hpp>

#if defined(HAMON_USE_STD_CONCEPTS)

namespace hamon
{

using std::default_initializable;

}	// namespace hamon

#elif defined(HAMON_HAS_CXX20_CONCEPTS)

#include <hamon/concepts/constructible_from.hpp>

namespace hamon
{

template <typename T>
concept default_initializable =
	hamon::constructible_from<T> &&
	requires
	{
		T{};
		(void) ::new T;
	};

}	// namespace hamon

#else

#include <hamon/concepts/constructible_from.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

namespace detail
{

template <typename T>
struct default_initializable_impl
{
private:
	template <typename U,
		typename = decltype(U{}),
		typename = decltype((void) ::new U)
	>
	static auto test(int) -> hamon::constructible_from<U>;

	template <typename U>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<T>(0));
};

}	// namespace detail

template <typename T>
using default_initializable =
	typename detail::default_initializable_impl<T>::type;

}	// namespace hamon

#endif

#include <hamon/type_traits/bool_constant.hpp>

namespace hamon
{

template <typename T>
using default_initializable_t =
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	hamon::bool_constant<hamon::default_initializable<T>>;
#else
	hamon::default_initializable<T>;
#endif

}	// namespace hamon

#endif // HAMON_CONCEPTS_DEFAULT_INITIALIZABLE_HPP
