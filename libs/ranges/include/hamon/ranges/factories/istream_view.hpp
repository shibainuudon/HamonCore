/**
 *	@file	istream_view.hpp
 *
 *	@brief	istream_view の定義
 */

#ifndef HAMON_RANGES_FACTORIES_ISTREAM_VIEW_HPP
#define HAMON_RANGES_FACTORIES_ISTREAM_VIEW_HPP

#include <hamon/ranges/fwd.hpp>
#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/concepts/constructible_from.hpp>
#include <hamon/concepts/default_initializable.hpp>
#include <hamon/concepts/derived_from.hpp>
#include <hamon/concepts/movable.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/istream/basic_istream.hpp>
#include <hamon/iterator/default_sentinel_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_nothrow_default_constructible.hpp>
#include <hamon/utility/declval.hpp>
#include <hamon/config.hpp>
#include <string>

namespace hamon {
namespace ranges {

namespace detail {

#if defined(HAMON_HAS_CXX20_CONCEPTS)

template <typename Val, typename CharT, typename Traits>
HAMON_CONCEPT_OR_BOOL stream_extractable =
	requires(hamon::basic_istream<CharT, Traits>& is, Val& t)
	{
		is >> t;
	};

#else

template <typename Val, typename CharT, typename Traits>
struct stream_extractable_impl
{
private:
	template <typename V, typename C, typename T,
		typename Stream = hamon::basic_istream<C, T>,
		typename = decltype(hamon::declval<Stream&>() >> hamon::declval<V&>())
	>
	static auto test(int) -> hamon::true_type;

	template <typename V, typename C, typename T>
	static auto test(...) -> hamon::false_type;

public:
	using type = decltype(test<Val, CharT, Traits>(0));
};

template <typename Val, typename CharT, typename Traits>
HAMON_CONCEPT_OR_BOOL stream_extractable =
	stream_extractable_impl<Val, CharT, Traits>::type::value;

#endif

}	// namespace detail

// 26.6.6.2 Class template basic_istream_view	[range.istream.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <hamon::movable Val, typename CharT, typename Traits = std::char_traits<CharT>>
requires hamon::default_initializable<Val> &&
	detail::stream_extractable<Val, CharT, Traits>
#else
template <typename Val, typename CharT, typename Traits = std::char_traits<CharT>,
	typename = hamon::enable_if_t<
		hamon::movable<Val> &&
		hamon::default_initializable<Val> &&
		detail::stream_extractable<Val, CharT, Traits>
	>
>
#endif
class basic_istream_view : public hamon::ranges::view_interface<basic_istream_view<Val, CharT, Traits>>
{
private:
	// [range.istream.iterator], class basic_istream_view​::​iterator
	struct iterator
	{
	public:
		using iterator_concept = hamon::input_iterator_tag;
		using difference_type = hamon::ptrdiff_t;
		using value_type = Val;

		HAMON_CXX11_CONSTEXPR explicit
		iterator(basic_istream_view& parent) HAMON_NOEXCEPT
			// [range.istream.iterator]/1
			: m_parent(hamon::addressof(parent))
		{}

		iterator(iterator const&) = delete;
		iterator(iterator&&) = default;

		iterator& operator=(iterator const&) = delete;
		iterator& operator=(iterator&&) = default;

		iterator& operator++()
		{
			// [range.istream.iterator]/2
			*m_parent->m_stream >> m_parent->m_value;
			return *this;
		}

		void operator++(int)
		{
			// [range.istream.iterator]/3
			++*this;
		}

		HAMON_NODISCARD Val&	// nodiscard as an extension
		operator*() const HAMON_NOEXCEPT	// noexcept as an extension
		{
			// [range.istream.iterator]/4
			return m_parent->m_value;
		}

	private:
		HAMON_NODISCARD bool at_end() const HAMON_NOEXCEPT
		{
			// [range.istream.iterator]/5
			return !*m_parent->m_stream;
		}


		HAMON_NODISCARD friend bool	// nodiscard as an extension
		operator==(iterator const& x, hamon::default_sentinel_t)
			HAMON_NOEXCEPT	// noexcept as an extension
		{
			return x.at_end();
		}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
		HAMON_NODISCARD friend bool	// nodiscard as an extension
		operator!=(iterator const& x, hamon::default_sentinel_t y)
			HAMON_NOEXCEPT	// noexcept as an extension
		{
			return !(x == y);
		}

		HAMON_NODISCARD friend bool	// nodiscard as an extension
		operator==(hamon::default_sentinel_t x, iterator const& y)
			HAMON_NOEXCEPT	// noexcept as an extension
		{
			return y == x;
		}

		HAMON_NODISCARD friend bool	// nodiscard as an extension
		operator!=(hamon::default_sentinel_t x, iterator const& y)
			HAMON_NOEXCEPT	// noexcept as an extension
		{
			return !(x == y);
		}
#endif

	private:
		basic_istream_view* m_parent;
	};

private:
	friend iterator;

	hamon::basic_istream<CharT, Traits>* m_stream;
	Val m_value = Val();

public:
	HAMON_CXX11_CONSTEXPR explicit
	basic_istream_view(hamon::basic_istream<CharT, Traits>& stream)
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<Val>::value)
		// [range.istream.view]/1
		: m_stream(hamon::addressof(stream))
	{}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	iterator begin()
	{
		*m_stream >> m_value;
		return iterator{*this};
	}

	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR	// nodiscard as an extension
	hamon::default_sentinel_t
	end() const HAMON_NOEXCEPT
	{
		// [range.istream.view]/2
		return hamon::default_sentinel;
	}

};

template <typename Val>
using istream_view = basic_istream_view<Val, char>;

template <typename Val>
using wistream_view = basic_istream_view<Val, wchar_t>;

namespace views {

namespace detail {

// [range.istream.overview]/2

template <typename T>
struct istream_fn
{
public:
	template <
		typename U,
		typename CharT = typename U::char_type,
		typename Traits = typename U::traits_type,
		typename IStreamView = hamon::ranges::basic_istream_view<T, CharT, Traits>,
		typename = hamon::enable_if_t<
			hamon::derived_from<U, hamon::basic_istream<CharT, Traits>> &&
			hamon::constructible_from<IStreamView, U&>
		>
	>
	HAMON_NODISCARD HAMON_CXX11_CONSTEXPR auto
	operator()(U& e) const
		HAMON_NOEXCEPT_IF(hamon::is_nothrow_default_constructible<T>::value)
	-> IStreamView
	{
		return IStreamView(e);
	}
};

}	// namespace detail

inline namespace cpo
{

template <typename T>
HAMON_INLINE_VAR HAMON_CXX11_CONSTEXPR
detail::istream_fn<T> istream{};

}	// inline namespace cpo

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_FACTORIES_ISTREAM_VIEW_HPP
