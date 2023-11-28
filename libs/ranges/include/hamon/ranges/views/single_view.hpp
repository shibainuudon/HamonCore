/**
 *	@file	single_view.hpp
 *
 *	@brief	single_view の定義
 */

#ifndef HAMON_RANGES_VIEWS_SINGLE_VIEW_HPP
#define HAMON_RANGES_VIEWS_SINGLE_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::single_view;

namespace views {

using std::ranges::views::single;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/views/view_interface.hpp>
#include <hamon/ranges/detail/movable_box.hpp>
#include <hamon/concepts/move_constructible.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/copy_constructible.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/detail/constrained_param.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/decay.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/utility/in_place.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::move_constructible T> requires hamon::is_object_v<T>
#else
template <typename T, typename = hamon::enable_if_t<hamon::move_constructible<T>::value && hamon::is_object<T>::value>>
#endif
class single_view : public hamon::ranges::view_interface<single_view<T>>
{
private:
	HAMON_NO_UNIQUE_ADDRESS	hamon::ranges::detail::movable_box<T> m_value;

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	single_view()
		requires hamon::default_initializable<T> = default;
#else	
	template <HAMON_CONSTRAINED_PARAM_D(hamon::default_initializable, U, T)>
	HAMON_CXX11_CONSTEXPR
	single_view()
	HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<U>::value)
		: m_value(){}
#endif

	template <HAMON_CONSTRAINED_PARAM_D(hamon::copy_constructible, U, T)>
	HAMON_CXX11_CONSTEXPR explicit
	single_view(T const& t)
	// requires hamon::copy_constructible<T>
		// [range.single.view]/1
		: m_value(t)
	{}
	
	HAMON_CXX11_CONSTEXPR explicit
	single_view(T&& t)
		// [range.single.view]/2
		: m_value(hamon::move(t))
	{}

	template <typename... Args,
		typename = hamon::enable_if_t<hamon::constructible_from_t<T, Args...>::value>>
	// requires hamon::constructible_from<T, Args...>
	HAMON_CXX11_CONSTEXPR explicit
	single_view(hamon::in_place_t, Args&&... args)
		// [range.single.view]/3
		: m_value{hamon::in_place, hamon::forward<Args>(args)...}
	{}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T*	// nodiscard as an extension
	begin() HAMON_NOEXCEPT
	{
		// [range.single.view]/4
		return data();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const*	// nodiscard as an extension
	begin() const HAMON_NOEXCEPT
	{
		// [range.single.view]/4
		return data();
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T*	// nodiscard as an extension
	end() HAMON_NOEXCEPT
	{
		// [range.single.view]/5
		return data() + 1;
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const*	// nodiscard as an extension
	end() const HAMON_NOEXCEPT
	{
		// [range.single.view]/5
		return data() + 1;
	}

	HAMON_NODISCARD static HAMON_CXX11_CONSTEXPR hamon::size_t	// nodiscard as an extension
	size() HAMON_NOEXCEPT
	{
		// [range.single.view]/6
		return 1;
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR T*	// nodiscard as an extension
	data() HAMON_NOEXCEPT
	{
		// [range.single.view]/7
		return m_value.operator->();
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR T const*	// nodiscard as an extension
	data() const HAMON_NOEXCEPT
	{
		// [range.single.view]/7
		return m_value.operator->();
	}
};

#if defined(HAMON_HAS_CXX17_DEDUCTION_GUIDES)
template <typename T>
single_view(T) -> single_view<T>;
#endif

namespace views {

namespace detail {

struct single_fn
{
	//[range.single.overview]/2
	template <typename T>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR single_view<hamon::decay_t<T>>
	operator()(T&& t) const
		HAMON_NOEXCEPT_IF_EXPR(single_view<hamon::decay_t<T>>(hamon::forward<T>(t)))
	{
		return single_view<hamon::decay_t<T>>(hamon::forward<T>(t));
	}
};

}	// namespace detail

HAMON_INLINE_VAR HAMON_CONSTEXPR
detail::single_fn single{};

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_VIEWS_SINGLE_VIEW_HPP
