/**
 *	@file	all.hpp
 *
 *	@brief	all の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_ALL_HPP
#define HAMON_RANGES_ADAPTORS_ALL_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {
namespace views {

using std::ranges::views::all;
using std::ranges::views::all_t;

}	// namespace views
}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/adaptors/range_adaptor_closure.hpp>
#include <hamon/ranges/adaptors/ref_view.hpp>
#include <hamon/ranges/adaptors/owning_view.hpp>
#include <hamon/ranges/concepts/view.hpp>
#include <hamon/ranges/concepts/viewable_range.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/detail/decay_copy.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/remove_reference.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {
namespace views {

namespace detail {

#define HAMON_NOEXCEPT_DECLTYPE_RETURN(...) \
	HAMON_NOEXCEPT_IF_EXPR(__VA_ARGS__)     \
	-> decltype(__VA_ARGS__)                \
	{ return __VA_ARGS__; }

// 26.7.6 All view[range.all]

struct all_fn : public hamon::ranges::range_adaptor_closure<all_fn>
{
private:
	// [range.all.general]/2.1
	template <typename T, typename = hamon::enable_if_t<ranges::view_t<hamon::decay_t<T>>::value>>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<2>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			hamon::detail::decay_copy(hamon::forward<T>(t)))

	// [range.all.general]/2.2
	template <typename T>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<1>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			ranges::ref_view<hamon::remove_reference_t<T>>{hamon::forward<T>(t)})

	// [range.all.general]/2.3
	template <typename T>
	static HAMON_CXX11_CONSTEXPR auto
	impl(T&& t, hamon::detail::overload_priority<0>)
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			ranges::owning_view<T>{hamon::forward<T>(t)})

public:
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(T&& t) const
		HAMON_NOEXCEPT_DECLTYPE_RETURN(
			impl(hamon::forward<T>(t), hamon::detail::overload_priority<2>{}))
};

#undef HAMON_NOEXCEPT_DECLTYPE_RETURN

} // namespace detail

inline namespace cpo
{

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::all_fn all{};

}	// inline namespace cpo

template <HAMON_CONSTRAINED_PARAM(hamon::ranges::viewable_range, R)>
using all_t = decltype(hamon::views::all(hamon::declval<R>()));

}	// namespace views
}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_ALL_HPP
