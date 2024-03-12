/**
 *	@file	non_propagating_cache.hpp
 *
 *	@brief	non_propagating_cache の定義
 */

#ifndef HAMON_RANGES_ADAPTORS_DETAIL_NON_PROPAGATING_CACHE_HPP
#define HAMON_RANGES_ADAPTORS_DETAIL_NON_PROPAGATING_CACHE_HPP

#include <hamon/memory/addressof.hpp>
#include <hamon/type_traits/is_object.hpp>
#include <hamon/type_traits/enable_if.hpp>
#include <hamon/optional.hpp>

namespace hamon {
namespace ranges {
namespace detail {

// 26.7.4 Non-propagating cache[range.nonprop.cache]

#if defined(HAMON_HAS_CXX20_CONCEPTS)
template <typename T>
requires hamon::is_object_v<T>	// [range.nonprop.cache]/1.1
#else
template <typename T, typename = hamon::enable_if_t<hamon::is_object<T>::value>>
#endif
struct non_propagating_cache : public hamon::optional<T>
{
	using base_type = hamon::optional<T>;
	using base_type::base_type;
	using base_type::operator=;

	HAMON_CXX14_CONSTEXPR
	non_propagating_cache() noexcept {}

	// [range.nonprop.cache]/1.2
	HAMON_CXX14_CONSTEXPR
	non_propagating_cache(non_propagating_cache const&) noexcept
		: base_type()
	{}

	// [range.nonprop.cache]/1.3
	HAMON_CXX14_CONSTEXPR
	non_propagating_cache(non_propagating_cache&& other) noexcept
	{
		other.reset();
	}

	// [range.nonprop.cache]1.4
	HAMON_CXX14_CONSTEXPR non_propagating_cache&
	operator=(non_propagating_cache const& other) noexcept
	{
		if (hamon::addressof(other) != this)
		{
			this->reset();
		}
		return *this;
	}

	// [range.nonprop.cache]1.5
	HAMON_CXX14_CONSTEXPR non_propagating_cache&
	operator=(non_propagating_cache&& other) noexcept
	{
		this->reset();
		other.reset();
		return *this;
	}

	// [range.nonprop.cache]1.6
	template <typename I>
	HAMON_CXX14_CONSTEXPR T& emplace_deref(I const& i)
	{
		this->emplace(*i);
		return this->value();
	}
};

}	// namespace detail
}	// namespace ranges
}	// namespace hamon

#endif // HAMON_RANGES_ADAPTORS_DETAIL_NON_PROPAGATING_CACHE_HPP
