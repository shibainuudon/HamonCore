/**
 *	@file	access.hpp
 *
 *	@brief	accessの定義
 */

#ifndef HAMON_SERIALIZATION_ACCESS_HPP
#define HAMON_SERIALIZATION_ACCESS_HPP

#include <utility>
#include <type_traits>

namespace hamon
{

namespace serialization
{

class access
{
public:
	template <typename Archive, typename T>
	struct has_member_serialize
	{
	private:
		template <typename A2, typename T2>
		static auto test(int) -> decltype(
			std::declval<T2>().serialize(std::declval<A2>()),
			std::true_type());

		template <typename A2, typename T2>
		static auto test(...) -> std::false_type;

		using type = decltype(test<Archive, T>(0));

	public:
		static const bool value = type::value;
	};
	
	template <typename Archive, typename T>
	static void serialize(Archive& ar, T& t)
	{
		t.serialize(ar);
	}
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_ACCESS_HPP
