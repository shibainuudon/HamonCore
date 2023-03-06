/**
 *	@file	reference_wrapper.hpp
 *
 *	@brief	reference_wrapper クラステンプレートの定義
 */

#ifndef HAMON_FUNCTIONAL_REFERENCE_WRAPPER_HPP
#define HAMON_FUNCTIONAL_REFERENCE_WRAPPER_HPP

#include <hamon/functional/fwd/reference_wrapper_fwd.hpp>
#include <hamon/functional/config.hpp>

#if defined(HAMON_USE_STD_REFERENCE_WRAPPER)

namespace hamon
{

using std::reference_wrapper;

}	// namespace hamon

#else

#include <hamon/functional/invoke.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>
#include <utility>

namespace hamon
{

template <typename T>
class reference_wrapper
{
private:
	HAMON_CONSTEXPR
	static T* FUN(T& r) HAMON_NOEXCEPT { return hamon::addressof(r); }

	static void FUN(T&&) = delete;

public:
	using type = T;

	template <
		typename U,
		typename = hamon::enable_if_t<
			!hamon::is_same<reference_wrapper, hamon::remove_cvref_t<U>>::value
		>,
		typename = decltype(reference_wrapper::FUN(std::declval<U>()))
	>
	HAMON_CONSTEXPR
	reference_wrapper(U&& u)
		HAMON_NOEXCEPT_IF_EXPR(reference_wrapper::FUN(std::declval<U>()))
		: m_ptr(reference_wrapper::FUN(hamon::forward<U>(u)))
	{}

	HAMON_CONSTEXPR
	reference_wrapper(reference_wrapper const&) = default;

	HAMON_CXX14_CONSTEXPR reference_wrapper&
	operator=(reference_wrapper const&) = default;

	HAMON_CONSTEXPR operator T& () const HAMON_NOEXCEPT
	{
		return this->get();
	}

	HAMON_CONSTEXPR T& get() const HAMON_NOEXCEPT
	{
		return *m_ptr;
	}

	template <typename... Args>
	HAMON_CONSTEXPR hamon::invoke_result_t<T&, Args...>
	operator()(Args&&... args) const
	{
#if defined(HAMON_HAS_CXX17_IF_CONSTEXPR)
		if constexpr (hamon::is_object<type>::value)
		{
			static_assert(sizeof(type), "type must be complete");
		}
#endif
		return hamon::invoke(get(), hamon::forward<Args>(args)...);
	}

private:
	T* m_ptr;
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)

template <typename T>
reference_wrapper(T&) -> reference_wrapper<T>;

#endif

}	// namespace hamon

#endif

#endif // HAMON_FUNCTIONAL_REFERENCE_WRAPPER_HPP
