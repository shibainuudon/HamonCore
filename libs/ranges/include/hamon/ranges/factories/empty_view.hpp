/**
 *	@file	empty_view.hpp
 *
 *	@brief	empty_view の定義
 */

#ifndef HAMON_RANGES_FACTORIES_EMPTY_VIEW_HPP
#define HAMON_RANGES_FACTORIES_EMPTY_VIEW_HPP

#include <hamon/ranges/config.hpp>

#if defined(HAMON_USE_STD_RANGES)

namespace hamon {
namespace ranges {

using std::ranges::empty_view;

namespace views {

using std::ranges::views::empty;

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#else

#include <hamon/ranges/utility/view_interface.hpp>
#include <hamon/ranges/concepts/enable_borrowed_range.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/cstddef/size_t.hpp>
#include <hamon/config.hpp>

namespace hamon {
namespace ranges {

// 26.6.2.2 Class template empty_view [range.empty.view]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <typename T> requires hamon::is_object_v<T>
#else
template <typename T, typename = hamon::enable_if_t<hamon::is_object<T>::value>>
#endif
class empty_view : public hamon::ranges::view_interface<empty_view<T>>
{
public:
	static HAMON_CXX11_CONSTEXPR T*     begin() HAMON_NOEXCEPT { return nullptr; }
	static HAMON_CXX11_CONSTEXPR T*     end()   HAMON_NOEXCEPT { return nullptr; }
	static HAMON_CXX11_CONSTEXPR T*     data()  HAMON_NOEXCEPT { return nullptr; }
	static HAMON_CXX11_CONSTEXPR size_t size()  HAMON_NOEXCEPT { return 0; }
	static HAMON_CXX11_CONSTEXPR bool   empty() HAMON_NOEXCEPT { return true; }
};

// [range.empty], empty view
template <typename T>
HAMON_RANGES_SPECIALIZE_ENABLE_BORROWED_RANGE(true, hamon::ranges::empty_view<T>);

namespace views {

#if defined(HAMON_HAS_CXX14_VARIABLE_TEMPLATES)

template <typename T>
HAMON_INLINE_VAR HAMON_CONSTEXPR empty_view<T> empty{};

#endif

}	// namespace views

}	// namespace ranges
}	// namespace hamon

#include <hamon/ranges/factories/detail/is_specialization_of_empty_view.hpp>
#include <hamon/type_traits/bool_constant.hpp>

namespace hamon {
namespace detail {

// is_specialization_of_empty_view の特殊化
template <typename T>
struct is_specialization_of_empty_view<hamon::ranges::empty_view<T>>
	: public hamon::true_type {};

}	// namespace detail
}	// namespace hamon

#endif

#endif // HAMON_RANGES_FACTORIES_EMPTY_VIEW_HPP
