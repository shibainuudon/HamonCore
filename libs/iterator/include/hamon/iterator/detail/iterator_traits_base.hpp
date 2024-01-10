/**
 *	@file	iterator_traits_base.hpp
 *
 *	@brief	iterator_traits_base の定義
 */

#ifndef HAMON_ITERATOR_DETAIL_ITERATOR_TRAITS_BASE_HPP
#define HAMON_ITERATOR_DETAIL_ITERATOR_TRAITS_BASE_HPP

#include <hamon/iterator/detail/cpp17_input_iterator.hpp>
#include <hamon/iterator/detail/cpp17_random_access_iterator.hpp>
#include <hamon/iterator/detail/cpp17_bidirectional_iterator.hpp>
#include <hamon/iterator/detail/cpp17_forward_iterator.hpp>
#include <hamon/iterator/detail/cpp17_iterator.hpp>
#include <hamon/iterator/detail/has_member_difference_type.hpp>
#include <hamon/iterator/detail/has_member_value_type.hpp>
#include <hamon/iterator/detail/has_member_reference.hpp>
#include <hamon/iterator/detail/has_member_iterator_category.hpp>
#include <hamon/iterator/bidirectional_iterator_tag.hpp>
#include <hamon/iterator/iter_reference_t.hpp>
#include <hamon/iterator/input_iterator_tag.hpp>
#include <hamon/iterator/indirectly_readable_traits.hpp>
#include <hamon/iterator/incrementable_traits.hpp>
#include <hamon/iterator/output_iterator_tag.hpp>
#include <hamon/iterator/forward_iterator_tag.hpp>
#include <hamon/iterator/random_access_iterator_tag.hpp>
#include <hamon/detail/overload_priority.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/conditional.hpp>
#include <hamon/type_traits/conjunction.hpp>
#include <hamon/type_traits/type_identity.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace detail
{

// [iterator.traits]/3.1
template <typename I>
struct iterator_traits_base_nested_types
{
private:
	template <typename I2, typename R = typename I2::pointer>
	static auto ptr(hamon::detail::overload_priority<1>) -> hamon::type_identity<R>;

	template <typename I2>
	static auto ptr(hamon::detail::overload_priority<0>) -> hamon::type_identity<void>;

public:
	using iterator_category = typename I::iterator_category;
	using value_type        = typename I::value_type;
	using difference_type   = typename I::difference_type;
	using pointer           = typename decltype(ptr<I>(hamon::detail::overload_priority<1>{}))::type;
	using reference         = typename I::reference;
};

// [iterator.traits]/3.2
template <typename I>
struct iterator_traits_base_cpp17_input_iterator
{
private:
	// [iterator.traits]/3.2.1
	template <typename I2, typename R = typename I2::pointer>
	static auto ptr(hamon::detail::overload_priority<2>) -> hamon::type_identity<R>;

	template <typename I2, typename R = decltype(hamon::declval<I2&>().operator->())>
	static auto ptr(hamon::detail::overload_priority<1>) -> hamon::type_identity<R>;

	template <typename I2>
	static auto ptr(hamon::detail::overload_priority<0>) -> hamon::type_identity<void>;

	// [iterator.traits]/3.2.2
	template <typename I2, typename R = typename I2::reference>
	static auto ref(hamon::detail::overload_priority<1>) -> hamon::type_identity<R>;

	template <typename I2>
	static auto ref(hamon::detail::overload_priority<0>) -> hamon::type_identity<hamon::iter_reference_t<I2>>;

	// [iterator.traits]/3.2.3
	template <typename I2, typename R = typename I2::iterator_category>
	static auto cat(hamon::detail::overload_priority<4>) -> R;
	
	template <typename I2, typename = hamon::enable_if_t<hamon::detail::cpp17_random_access_iterator_t<I2>::value>>
	static auto cat(hamon::detail::overload_priority<3>) -> hamon::random_access_iterator_tag;

	template <typename I2, typename = hamon::enable_if_t<hamon::detail::cpp17_bidirectional_iterator_t<I2>::value>>
	static auto cat(hamon::detail::overload_priority<2>) -> hamon::bidirectional_iterator_tag;

	template <typename I2, typename = hamon::enable_if_t<hamon::detail::cpp17_forward_iterator_t<I2>::value>>
	static auto cat(hamon::detail::overload_priority<1>) -> hamon::forward_iterator_tag;

	template <typename I2>
	static auto cat(hamon::detail::overload_priority<0>) -> hamon::input_iterator_tag;

public:
	using iterator_category = decltype(cat<I>(hamon::detail::overload_priority<4>{}));
	using value_type        = typename hamon::indirectly_readable_traits<I>::value_type;
	using difference_type   = typename hamon::incrementable_traits<I>::difference_type;
	using pointer           = typename decltype(ptr<I>(hamon::detail::overload_priority<2>{}))::type;
	using reference         = typename decltype(ref<I>(hamon::detail::overload_priority<1>{}))::type;
};

// [iterator.traits]/3.3
template <typename I>
struct iterator_traits_base_cpp17_iterator
{
private:
	// [iterator.traits]/3.2.1
	template <typename I2, typename R = typename hamon::incrementable_traits<I2>::difference_type>
	static auto dif(hamon::detail::overload_priority<1>) -> hamon::type_identity<R>;

	template <typename I2>
	static auto dif(hamon::detail::overload_priority<0>) -> hamon::type_identity<void>;

public:
	using iterator_category = hamon::output_iterator_tag;
	using value_type        = void;
	using difference_type   = typename decltype(dif<I>(hamon::detail::overload_priority<1>{}))::type;
	using pointer           = void;
	using reference         = void;
};

// [iterator.traits]/3.4
template <typename I>
struct iterator_traits_base_no_members
{
};

template <typename I>
using with_nested_types = hamon::conjunction<
	hamon::detail::has_member_difference_type_t<I>,
	hamon::detail::has_member_value_type_t<I>,
	hamon::detail::has_member_reference_t<I>,
	hamon::detail::has_member_iterator_category_t<I>
>;

template <typename I>
using iterator_traits_base =
hamon::conditional_t<with_nested_types<I>::value,
	iterator_traits_base_nested_types<I>,
hamon::conditional_t<hamon::detail::cpp17_input_iterator_t<I>::value,
	iterator_traits_base_cpp17_input_iterator<I>,
hamon::conditional_t<hamon::detail::cpp17_iterator_t<I>::value,
	iterator_traits_base_cpp17_iterator<I>,
	iterator_traits_base_no_members<I>
>>>;

}	// namespace detail

}	// namespace hamon

#endif // HAMON_ITERATOR_DETAIL_ITERATOR_TRAITS_BASE_HPP
