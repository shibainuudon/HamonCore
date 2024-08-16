/**
 *	@file	allocator.hpp
 *
 *	@brief	allocator の定義
 */

#ifndef HAMON_MEMORY_ALLOCATOR_HPP
#define HAMON_MEMORY_ALLOCATOR_HPP

#include <memory>

#if defined(__cpp_lib_constexpr_dynamic_alloc) && (__cpp_lib_constexpr_dynamic_alloc >= 201907L) &&	\
	defined(__cpp_lib_allocate_at_least) && (__cpp_lib_allocate_at_least >= 202302L)

namespace hamon
{

using std::allocator;

}	// namespace hamon

#else

#include <hamon/cstddef/size_t.hpp>
#include <hamon/cstddef/ptrdiff_t.hpp>
#include <hamon/memory/allocation_result.hpp>
#include <hamon/new/bad_array_new_length.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/type_traits/is_constant_evaluated.hpp>
#include <hamon/limits.hpp>
#include <hamon/config.hpp>

namespace hamon
{

// 20.2.10 The default allocator[default.allocator]

template <typename T>
class allocator
{
public:
	using value_type                             = T;
	using size_type                              = hamon::size_t;
	using difference_type                        = hamon::ptrdiff_t;
	using propagate_on_container_move_assignment = hamon::true_type;

	HAMON_CXX11_CONSTEXPR allocator() noexcept {}

	HAMON_CXX11_CONSTEXPR allocator(allocator const&) noexcept = default;

	template <typename U>
	HAMON_CXX11_CONSTEXPR allocator(allocator<U> const&) noexcept {}

	HAMON_CXX20_CONSTEXPR ~allocator() = default;

	HAMON_CXX14_CONSTEXPR allocator& operator=(allocator const&) = default;

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	T* allocate(hamon::size_t n)
	{
		// [allocator.members]/4
		if (hamon::numeric_limits<size_t>::max() / sizeof(T) < n)
		{
			hamon::detail::throw_bad_array_new_length();
		}

#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			// std::allocator::allocate はコンパイラマジックによってconstexprになっており、
			// それ以外の方法でconstexprにメモリを確保することはできない。
			return std::allocator<T>{}.allocate(n);
		}
#endif
		// [allocator.members]/5
		return static_cast<T*>(::operator new(n * sizeof(T)));
	}

	HAMON_NODISCARD HAMON_CXX14_CONSTEXPR	// nodiscard as an extension
	hamon::allocation_result<T*> allocate_at_least(hamon::size_t n)
	{
		// [allocator.members]/7
		return { allocate(n), n };
	}

	HAMON_CXX14_CONSTEXPR void deallocate(T* p, hamon::size_t n)
	{
#if defined(HAMON_HAS_CXX20_IS_CONSTANT_EVALUATED)
		if (hamon::is_constant_evaluated())
		{
			// std::allocator::deallocate はコンパイラマジックによってconstexprになっており、
			// それ以外の方法でconstexprにメモリを解放することはできない。
			return std::allocator<T>{}.deallocate(p, n);
		}
#endif
		// [allocator.members]/11
		::operator delete(p);
		(void)n;
	}
};

// 20.2.10.3 Operators[allocator.globals]
template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator==(allocator<T> const&, allocator<U> const&) noexcept
{
	// [allocator.globals]/1
	return true;
}

#if !defined(HAMON_HAS_CXX20_THREE_WAY_COMPARISON)
template <typename T, typename U>
HAMON_CXX11_CONSTEXPR bool
operator!=(allocator<T> const& lhs, allocator<U> const& rhs) noexcept
{
	return !(lhs == rhs);
}
#endif

}	// namespace hamon

#endif

#endif // HAMON_MEMORY_ALLOCATOR_HPP
