/**
 *	@file	tuple_leaf.hpp
 *
 *	@brief	tuple_leaf の定義
 */

#ifndef HAMON_TUPLE_DETAIL_TUPLE_LEAF_HPP
#define HAMON_TUPLE_DETAIL_TUPLE_LEAF_HPP

#include <hamon/cstddef/size_t.hpp>
#include <hamon/memory/allocator_arg_t.hpp>
#include <hamon/memory/detail/uses_allocator_construction_type.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/type_traits/is_constructible.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace tuple_detail {

struct ctor_from_elems_tag {};
struct ctor_from_tuple_tag {};

HAMON_WARNING_PUSH()
HAMON_WARNING_DISABLE_MSVC(4244)
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-float-conversion")
HAMON_WARNING_DISABLE_CLANG("-Wimplicit-int-float-conversion")
HAMON_WARNING_DISABLE_GCC("-Wconversion")
HAMON_WARNING_DISABLE_GCC("-Wfloat-conversion")

template <hamon::size_t I, typename T>
struct tuple_leaf
{
private:
	T	m_value;

public:
	HAMON_CXX11_CONSTEXPR
	tuple_leaf()
		: m_value() {}

	template <typename U,
		typename = hamon::enable_if_t<
			hamon::is_constructible<T, U>::value>>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(U&& u)
		: m_value(hamon::forward<U>(u)) {}

	template <typename Alloc, typename... Args>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(hamon::allocator_arg_t, Alloc const& alloc, Args&&... args)
		: tuple_leaf(
			hamon::detail::uses_allocator_construction_type_t<T, Alloc, Args...>{},
			alloc,
			hamon::forward<Args>(args)...)
	{}

private:
	template <typename Alloc, typename... Args>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(hamon::detail::uses_allocator_construction_type::NoAlloc, Alloc const&, Args&&... args) noexcept
		: m_value(hamon::forward<Args>(args)...) {}

	template <typename Alloc, typename... Args>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(hamon::detail::uses_allocator_construction_type::FirstAlloc, Alloc const& alloc, Args&&... args) noexcept
		: m_value(hamon::allocator_arg_t{}, alloc, hamon::forward<Args>(args)...) {}

	template <typename Alloc, typename... Args>
	HAMON_CXX11_CONSTEXPR
	tuple_leaf(hamon::detail::uses_allocator_construction_type::LastAlloc, Alloc const& alloc, Args&&... args) noexcept
		: m_value(hamon::forward<Args>(args)..., alloc) {}

public:
	HAMON_CXX14_CONSTEXPR T &       get() &       { return m_value; }
	HAMON_CXX11_CONSTEXPR T const&  get() const&  { return m_value; }
	HAMON_CXX14_CONSTEXPR T &&      get() &&      { return hamon::forward<T>(m_value); }
	HAMON_CXX11_CONSTEXPR T const&& get() const&& { return hamon::forward<T const>(m_value); }
};

HAMON_WARNING_POP()

}	// namespace tuple_detail
}	// namespace hamon

#endif // HAMON_TUPLE_DETAIL_TUPLE_LEAF_HPP
