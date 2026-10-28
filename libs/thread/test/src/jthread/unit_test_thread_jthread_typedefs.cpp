/**
 *	@file	unit_test_thread_jthread_typedefs.cpp
 *
 *	@brief
 *
 *	using id = thread::id;
 *
 *	using native_handle_type = thread::native_handle_type;
 *
 *	template<class T>
 *	using name_hint = thread::name_hint<T>;
 *
 *	using stack_size_hint = thread::stack_size_hint;
 */

#include <hamon/thread/jthread.hpp>
#include <hamon/type_traits/is_same.hpp>

static_assert(hamon::is_same_v<hamon::jthread::id, hamon::thread::id>, "");
static_assert(hamon::is_same_v<hamon::jthread::native_handle_type, hamon::thread::native_handle_type>, "");
static_assert(hamon::is_same_v<hamon::jthread::name_hint<char>, hamon::thread::name_hint<char>>, "");
static_assert(hamon::is_same_v<hamon::jthread::stack_size_hint, hamon::thread::stack_size_hint>, "");
