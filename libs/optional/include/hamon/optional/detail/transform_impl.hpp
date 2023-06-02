/**
 *	@file	transform_impl.hpp
 *
 *	@brief	transform_impl の定義
 */

#ifndef HAMON_OPTIONAL_DETAIL_TRANSFORM_IMPL_HPP
#define HAMON_OPTIONAL_DETAIL_TRANSFORM_IMPL_HPP

#include <hamon/optional/nullopt.hpp>
#include <hamon/optional/optional.hpp>
#include <hamon/optional/detail/construct_from_invoke_tag.hpp>
#include <hamon/type_traits/invoke_result.hpp>
#include <hamon/type_traits/is_array.hpp>
#include <hamon/type_traits/is_same.hpp>
#include <hamon/type_traits/remove_cv.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/in_place.hpp>
#include <hamon/config.hpp>

namespace hamon
{

namespace optional_detail
{

struct transform_impl
{
	template <typename F, typename Optional>
	HAMON_CXX11_CONSTEXPR auto operator()(F&& f, Optional&& opt) const
	-> hamon::optional<hamon::remove_cv_t<hamon::invoke_result_t<F, decltype(hamon::forward<Optional>(opt).value())>>>
	{
		// [optional.monadic]/7
		using U = hamon::remove_cv_t<hamon::invoke_result_t<F, decltype(hamon::forward<Optional>(opt).value())>>;

		// [optional.monadic]/8
		static_assert(!hamon::is_array<U>::value, "");
		static_assert(!hamon::is_same<U, hamon::in_place_t>::value, "");
		static_assert(!hamon::is_same<U, hamon::nullopt_t>::value, "");

		// TODO
		// The declaration
		// U u(invoke(std::forward<F>(f), value()));
		// is well-formed for some invented variable u.

		// [optional.monadic]/9
		return hamon::forward<Optional>(opt).has_value() ?
			hamon::optional<U>(optional_detail::construct_from_invoke_tag{},
				hamon::forward<F>(f), hamon::forward<Optional>(opt).value()) :
			hamon::optional<U>();
	}
};

}	// namespace optional_detail

}	// namespace hamon

#endif // HAMON_OPTIONAL_DETAIL_TRANSFORM_IMPL_HPP
