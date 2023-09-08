/**
 *	@file	iterator_traits_base.hpp
 *
 *	@brief	iterator_traits_base の定義
 */

#ifndef HAMON_ITERATOR_CONCEPTS_DETAIL_ITERATOR_TRAITS_BASE_HPP
#define HAMON_ITERATOR_CONCEPTS_DETAIL_ITERATOR_TRAITS_BASE_HPP

#include <hamon/iterator/concepts/detail/iter_with_nested_types.hpp>
#include <hamon/iterator/concepts/detail/iter_without_nested_types.hpp>
#include <hamon/iterator/concepts/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/concepts/detail/cpp17_randacc_iterator.hpp>
#include <hamon/iterator/concepts/detail/cpp17_bidi_iterator.hpp>
#include <hamon/iterator/concepts/detail/cpp17_fwd_iterator.hpp>
#include <hamon/iterator/concepts/detail/cpp17_iterator.hpp>
#include <hamon/iterator/concepts/detail/has_iterator_category.hpp>
#include <hamon/iterator/concepts/detail/has_pointer.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/iterator/output_iterator_tag.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/void_t.hpp>
#include <hamon/utility/declval.hpp>
#include <iterator>

namespace hamon
{

namespace detail
{

template <typename Iterator, typename = void>
struct iterator_traits_base {};

template <typename Iterator>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires hamon::detail::iter_with_nested_types<Iterator>
#endif
struct iterator_traits_base<Iterator
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, hamon::enable_if_t<hamon::detail::iter_with_nested_types<Iterator>::value>
#endif
>
{
private:
	template <typename Iter, typename = void>
	struct ptr
	{
		using type = void;
	};

	template <typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires requires { typename Iter::pointer; }
#endif
	struct ptr<Iter
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, hamon::void_t<typename Iter::pointer>
#endif
	>
	{
		using type = typename Iter::pointer;
	};

public:
	using iterator_category = typename Iterator::iterator_category;
	using value_type	    = typename Iterator::value_type;
	using difference_type   = typename Iterator::difference_type;
	using pointer	        = typename ptr<Iterator>::type;
	using reference	        = typename Iterator::reference;
};

template <typename Iterator>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires
	hamon::detail::iter_without_nested_types<Iterator> &&
	hamon::detail::cpp17_input_iterator<Iterator>
#endif
struct iterator_traits_base<Iterator
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, hamon::enable_if_t<
		hamon::detail::iter_without_nested_types<Iterator>::value &&
		hamon::detail::cpp17_input_iterator<Iterator>::value
	>
#endif
>
{
private:
	template <typename Iter, typename = void>
	struct cat
	{
		using type = hamon::input_iterator_tag;
	};

	template <typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires requires { typename Iter::iterator_category; }
#endif
	struct cat<Iter
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, hamon::enable_if_t<hamon::detail::has_iterator_category<Iter>::value>
#endif
	>
	{
		using type = typename Iter::iterator_category;
	};

	template <typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires (
		!requires { typename Iter::iterator_category; } &&
		hamon::detail::cpp17_randacc_iterator<Iter>
	)
#endif
	struct cat<Iter
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, hamon::enable_if_t<
			!hamon::detail::has_iterator_category<Iter>::value &&
			hamon::detail::cpp17_randacc_iterator<Iter>::value
		>
#endif
	>
	{
		using type = std::random_access_iterator_tag;
	};

	template <typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires (
		!requires { typename Iter::iterator_category; } &&
		!hamon::detail::cpp17_randacc_iterator<Iter> &&
		hamon::detail::cpp17_bidi_iterator<Iter>
	)
#endif
	struct cat<Iter
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, hamon::enable_if_t<
			!hamon::detail::has_iterator_category<Iter>::value &&
			!hamon::detail::cpp17_randacc_iterator<Iter>::value &&
			hamon::detail::cpp17_bidi_iterator<Iter>::value
		>
#endif
	>
	{
		using type = std::bidirectional_iterator_tag;
	};

	template <typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires (
		!requires { typename Iter::iterator_category; } &&
		!hamon::detail::cpp17_bidi_iterator<Iter> &&
		hamon::detail::cpp17_fwd_iterator<Iter>
	)
#endif
	struct cat<Iter
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, hamon::enable_if_t<
			!hamon::detail::has_iterator_category<Iter>::value &&
			!hamon::detail::cpp17_bidi_iterator<Iter>::value &&
			hamon::detail::cpp17_fwd_iterator<Iter>::value
		>
#endif
	>
	{
		using type = std::forward_iterator_tag;
	};

	template <typename Iter, typename = void, typename = void>
	struct ptr
	{
		using type = void;
	};

	template <typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires requires { typename Iter::pointer; }
#endif
	struct ptr<Iter
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, hamon::enable_if_t<
			hamon::detail::has_pointer<Iter>::value
		>
#endif
	>
	{
		using type = typename Iter::pointer;
	};

	template <typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires (
		!requires { typename Iter::pointer; } &&
		requires(Iter& it) { it.operator->(); }
	)
#endif
	struct ptr<Iter
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, hamon::enable_if_t<
			!hamon::detail::has_pointer<Iter>::value
		>,
		hamon::void_t<decltype(hamon::declval<Iter&>().operator->())>
#endif
	>
	{
		using type = decltype(hamon::declval<Iter&>().operator->());
	};

	template <typename Iter, typename = void>
	struct ref
	{
		using type = hamon::iter_reference_t<Iter>;
	};

	template <typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires requires { typename Iter::reference; }
#endif
	struct ref<Iter
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, hamon::void_t<typename Iter::reference>
#endif
	>
	{
		using type = typename Iter::reference;
	};

public:
	using iterator_category = typename cat<Iterator>::type;
	using value_type        = typename hamon::indirectly_readable_traits<Iterator>::value_type;
	using difference_type   = typename hamon::incrementable_traits<Iterator>::difference_type;
	using pointer	        = typename ptr<Iterator>::type;
	using reference	        = typename ref<Iterator>::type;
};

template <typename Iterator>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
requires
	hamon::detail::iter_without_nested_types<Iterator> &&
	hamon::detail::cpp17_iterator<Iterator>
#endif
struct iterator_traits_base<Iterator
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
	, hamon::enable_if_t<
		hamon::detail::iter_without_nested_types<Iterator>::value &&
		!hamon::detail::cpp17_input_iterator<Iterator>::value &&
		hamon::detail::cpp17_iterator<Iterator>::value
	>
#endif
>
{
private:
	template <typename Iter, typename = void>
	struct diff
	{
		using type = void;
	};

	template <typename Iter>
#if defined(HAMON_HAS_CXX20_CONCEPTS)
	requires requires { typename hamon::incrementable_traits<Iter>::difference_type; }
#endif
	struct diff<Iter
#if !defined(HAMON_HAS_CXX20_CONCEPTS)
		, hamon::void_t<typename hamon::incrementable_traits<Iter>::difference_type>
#endif
	>
	{
		using type = typename hamon::incrementable_traits<Iter>::difference_type;
	};

public:
	using iterator_category = hamon::output_iterator_tag;
	using value_type	    = void;
	using difference_type   = typename diff<Iterator>::type;
	using pointer	        = void;
	using reference	        = void;
};

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_CONCEPTS_DETAIL_ITERATOR_TRAITS_BASE_HPP
