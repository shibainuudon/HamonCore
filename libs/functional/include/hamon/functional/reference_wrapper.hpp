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
#include <hamon/concepts/convertible_to.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/basic_common_reference.hpp>
#include <hamon/type_traits/common_reference.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/remove_cvref.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

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
		typename = decltype(reference_wrapper::FUN(hamon::declval<U>()))
	>
	HAMON_CONSTEXPR
	reference_wrapper(U&& u)
		HAMON_NOEXCEPT_IF_EXPR(reference_wrapper::FUN(hamon::declval<U>()))
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

namespace detail
{

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename T>
constexpr bool is_ref_wrapper = false;

template <typename T>
constexpr bool is_ref_wrapper<hamon::reference_wrapper<T>> = true;

template <typename R, typename T, typename RQ, typename TQ>
concept ref_wrap_common_reference_exists_with =
	hamon::detail::is_ref_wrapper<R> &&
	requires { typename hamon::common_reference_t<typename R::type&, TQ>; } &&
	hamon::convertible_to<RQ, hamon::common_reference_t<typename R::type&, TQ>>;

#else

template <typename T>
struct is_ref_wrapper : public hamon::false_type{};

template <typename T>
struct is_ref_wrapper<hamon::reference_wrapper<T>> : public hamon::true_type{};

template <typename R, typename T, typename RQ, typename TQ>
struct ref_wrap_common_reference_exists_with_impl
{
private:
	template <typename R2, typename T2, typename RQ2, typename TQ2,
		typename = hamon::enable_if_t<hamon::detail::is_ref_wrapper<R2>::value>,
		typename CR = hamon::common_reference_t<typename R2::type&, TQ2>,
		typename = hamon::enable_if_t<hamon::convertible_to<RQ2, CR>::value>
	>
	static auto test(int) -> hamon::true_type;

	template <typename R2, typename T2, typename RQ2, typename TQ2>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<R, T, RQ, TQ>(0));
};

template <typename R, typename T, typename RQ, typename TQ>
using ref_wrap_common_reference_exists_with =
	typename ref_wrap_common_reference_exists_with_impl<R, T, RQ, TQ>::type;

#endif

}	// namespace detail
}	// namespace hamon

namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE
{

template <typename R, typename T, template <typename> class RQual, template <typename> class TQual>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires (
		 hamon::detail::ref_wrap_common_reference_exists_with<R, T, RQual<R>, TQual<T>> &&
		!hamon::detail::ref_wrap_common_reference_exists_with<T, R, TQual<T>, RQual<R>>)
#endif
struct basic_common_reference<R, T, RQual, TQual
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, hamon::enable_if_t<
		 hamon::detail::ref_wrap_common_reference_exists_with<R, T, RQual<R>, TQual<T>>::value &&
		!hamon::detail::ref_wrap_common_reference_exists_with<T, R, TQual<T>, RQual<R>>::value
	>
#endif
>
{
	using type = hamon::common_reference_t<typename R::type&, TQual<T>>;
};

template <typename T, typename R, template <typename> class TQual, template <typename> class RQual>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires (
		 hamon::detail::ref_wrap_common_reference_exists_with<R, T, RQual<R>, TQual<T>> &&
		!hamon::detail::ref_wrap_common_reference_exists_with<T, R, TQual<T>, RQual<R>>)
#endif
struct basic_common_reference<T, R, TQual, RQual
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, hamon::enable_if_t<
		 hamon::detail::ref_wrap_common_reference_exists_with<R, T, RQual<R>, TQual<T>>::value &&
		!hamon::detail::ref_wrap_common_reference_exists_with<T, R, TQual<T>, RQual<R>>::value
	>
#endif
>
{
	using type = hamon::common_reference_t<typename R::type&, TQual<T>>;
};

}	// namespace HAMON_BASIC_COMMON_REFERENCE_NAMESPACE

#endif

#endif // HAMON_FUNCTIONAL_REFERENCE_WRAPPER_HPP
