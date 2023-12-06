/**
 *	@file	owning_view.hpp
 *
 *	@brief	owning_view の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_OWNING_VIEW_HPP
#define HAMON_RANGES_ADAPTORS_OWNING_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::owning_view;

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/concepts/range.hpp>
#include <hamon/ranges/concepts/sized_range.hpp>
#include <hamon/ranges/concepts/contiguous_range.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/ranges/concepts/detail/is_initializer_list.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/begin.hpp>
#include <hamon/ranges/end.hpp>
#include <hamon/ranges/iterator_t.hpp>
#include <hamon/ranges/sentinel_t.hpp>
#include <hamon/ranges/empty.hpp>
#include <hamon/ranges/size.hpp>
#include <hamon/ranges/data.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/negation.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/utility/move.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 26.7.6.3 Class template owning_view[range.owning.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::ranges::range R>
	requires hamon::movable<R> &&
		(!hamon::ranges::detail::is_initializer_list<R>::value) // see [range.refinements]
#else
template <typename R,
	typename = hamon::enable_if_t<hamon::conjunction<
		hamon::ranges::range_t<R>,
		hamon::movable_t<R>,
		hamon::negation<hamon::ranges::detail::is_initializer_list<R>>
	>::value>
>
#endif
class owning_view : public hamon::ranges::view_interface<owning_view<R>>
{
private:
	R m_r = R();

public:
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	owning_view() requires hamon::default_initializable<R> = default;
#else
	template <typename R2 = R,
		typename = hamon::enable_if_t<hamon::default_initializable_t<R2>::value>>
	owning_view() HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<R2>::value)
	{}
#endif

	HAMON_CXX11_CONSTEXPR owning_view(R&& t)
	HAMON_NOEXCEPT_IF(hamon::is_nothrow_move_constructible<R>::value)	// noexcept as an extension
		// [range.owning.view]/2
		: m_r(hamon::move(t))
	{}

	owning_view(owning_view&&) = default;
	owning_view& operator=(owning_view&&) = default;

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR R&	// nodiscard as an extension
	base() & HAMON_NOEXCEPT
	{
		return m_r;
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR R const&	// nodiscard as an extension
	base() const & HAMON_NOEXCEPT
	{
		return m_r;
	}
	
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR R&&	// nodiscard as an extension
	base() && HAMON_NOEXCEPT
	{
		return hamon::move(m_r);
	}
	
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR R const&&	// nodiscard as an extension
	base() const && HAMON_NOEXCEPT
	{
		return hamon::move(m_r);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	hamon::ranges::iterator_t<R> begin()
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::begin(m_r))	// noexcept as an extension
	{
		return hamon::ranges::begin(m_r);
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	hamon::ranges::sentinel_t<R> end()
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::end(m_r))	// noexcept as an extension
	{
		return hamon::ranges::end(m_r);
	}

	template <typename R2 = R const,
		typename = hamon::enable_if_t<hamon::ranges::range_t<R2>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	begin() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::begin(m_r))	// noexcept as an extension
	->decltype(hamon::ranges::begin(hamon::declval<R2&>()))
//		requires hamon::ranges::range<R const>
	{
		return hamon::ranges::begin(m_r);
	}

	template <typename R2 = R const,
		typename = hamon::enable_if_t<hamon::ranges::range_t<R2>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	end() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::end(m_r))	// noexcept as an extension
	->decltype(hamon::ranges::end(hamon::declval<R2&>()))
//		requires hamon::ranges::range<R const>
	{
		return hamon::ranges::end(m_r);
	}

	template <typename R2 = R,
		typename = decltype(hamon::ranges::empty(hamon::declval<R2&>()))>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR bool	// nodiscard as an extension
	empty()
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::empty(m_r))	// noexcept as an extension
//		requires requires { hamon::ranges::empty(m_r); }
	{
		return hamon::ranges::empty(m_r);
	}
	
	template <typename R2 = R const,
		typename = decltype(hamon::ranges::empty(hamon::declval<R2&>()))>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR bool	// nodiscard as an extension
	empty() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::empty(m_r))	// noexcept as an extension
//		requires requires { hamon::ranges::empty(m_r); }
	{
		return hamon::ranges::empty(m_r);
	}

	template <typename R2 = R,
		typename = hamon::enable_if_t<hamon::ranges::sized_range_t<R2>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	size()
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::size(m_r))	// noexcept as an extension
	->decltype(hamon::ranges::size(hamon::declval<R2&>()))
//		requires hamon::ranges::sized_range<R>
	{
		return hamon::ranges::size(m_r);
	}

	template <typename R2 = R const,
		typename = hamon::enable_if_t<hamon::ranges::sized_range_t<R2>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	size() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::size(m_r))	// noexcept as an extension
	->decltype(hamon::ranges::size(hamon::declval<R2&>()))
//		requires hamon::ranges::sized_range<R const>
	{
		return hamon::ranges::size(m_r);
	}

	template <typename R2 = R,
		typename = hamon::enable_if_t<hamon::ranges::contiguous_range_t<R2>::value>>
	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR auto	// nodiscard as an extension
	data()
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::data(m_r))	// noexcept as an extension
	->decltype(hamon::ranges::data(hamon::declval<R2&>()))
//		requires hamon::ranges::contiguous_range<R>
	{
		return hamon::ranges::data(m_r);
	}

	template <typename R2 = R const,
		typename = hamon::enable_if_t<hamon::ranges::contiguous_range_t<R2>::value>>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto	// nodiscard as an extension
	data() const
	HAMON_NOEXCEPT_IF_EXPR(hamon::ranges::data(m_r))	// noexcept as an extension
	->decltype(hamon::ranges::data(hamon::declval<R2&>()))
//		requires hamon::ranges::contiguous_range<R const>
	{
		return hamon::ranges::data(m_r);
	}
};

template <typename T>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(
	HAMON_RANGES_ENABLE_BORROWED_RANGE(T),
	hamon::ranges::owning_view<T>);

}	// namespace ranges
}	// namespace hamon

#endif

#endif // HAMON_RANGES_ADAPTORS_OWNING_VIEW_HPP
