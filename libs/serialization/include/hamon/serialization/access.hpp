/**
 *	@file	access.hpp
 *
 *	@brief	accessの定義
 */

#ifndef HAMON_SERIALIZATION_ACCESS_HPP
#define HAMON_SERIALIZATION_ACCESS_HPP

#include <hamon/concepts/convertible_to.hpp>
#include <hamon/serialization/version.hpp>
#include <hamon/type_traits/bool_constant.hpp>
#include <hamon/utility/forward.hpp>
#include <hamon/utility/declval.hpp>

namespace hamon
{

namespace serialization
{

class access
{
public:
	template <typename Archive, typename T, typename... Args>
	struct has_member_serialize
	{
	private:
		template <typename A2, typename T2, typename... Args2>
		static auto test(int) -> decltype(
			hamon::declval<T2>().serialize(hamon::declval<A2>(), hamon::declval<Args2>()...),
			hamon::true_type());

		template <typename A2, typename T2, typename... Args2>
		static auto test(...) -> hamon::false_type;

		using type = decltype(test<Archive, T, Args...>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T, typename... Args>
	struct has_member_save
	{
	private:
		template <typename A2, typename T2, typename... Args2>
		static auto test(int) -> decltype(
			hamon::declval<T2>().save(hamon::declval<A2>(), hamon::declval<Args2>()...),
			hamon::true_type());

		template <typename A2, typename T2, typename... Args2>
		static auto test(...) -> hamon::false_type;

		using type = decltype(test<Archive, T, Args...>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T, typename... Args>
	struct has_member_load
	{
	private:
		template <typename A2, typename T2, typename... Args2>
		static auto test(int) -> decltype(
			hamon::declval<T2>().load(hamon::declval<A2>(), hamon::declval<Args2>()...),
			hamon::true_type());

		template <typename A2, typename T2, typename... Args2>
		static auto test(...) -> hamon::false_type;

		using type = decltype(test<Archive, T, Args...>(0));

	public:
		static const bool value = type::value;
	};

	template <typename T>
	struct has_member_get_class_version
	{
	private:
		template <typename U,
			typename R = decltype(hamon::declval<U>().get_class_version())
		>
		static auto test(int) -> hamon::convertible_to_t<R, version_t>;

		template <typename U>
		static auto test(...) -> hamon::false_type;

		using type = decltype(test<T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename T>
	struct has_member_get_class_id
	{
	private:
		template <typename U,
			typename R = decltype(hamon::declval<U>().get_class_id())
		>
		static auto test(int) -> hamon::convertible_to_t<R, const char*>;

		template <typename U>
		static auto test(...) -> hamon::false_type;

		using type = decltype(test<T>(0));

	public:
		static const bool value = type::value;
	};

	template <typename Archive, typename T, typename... Args>
	static void serialize(Archive& ar, T& t, Args&&... args)
	{
		t.serialize(ar, hamon::forward<Args>(args)...);
	}

	template <typename Archive, typename T, typename... Args>
	static void save(Archive& ar, T const& t, Args&&... args)
	{
		t.save(ar, hamon::forward<Args>(args)...);
	}
	
	template <typename Archive, typename T, typename... Args>
	static void load(Archive& ar, T& t, Args&&... args)
	{
		t.load(ar, hamon::forward<Args>(args)...);
	}

	template <typename T>
	static version_t get_class_version(T const& t)
	{
		return static_cast<version_t>(t.get_class_version());
	}

	template <typename T>
	static const char* get_class_id(T const& t)
	{
		return t.get_class_id();
	}

	template <typename T>
	static const char* static_class_id()
	{
		return T::static_class_id();
	}
};

}	// namespace serialization

}	// namespace hamon

#endif // HAMON_SERIALIZATION_ACCESS_HPP
