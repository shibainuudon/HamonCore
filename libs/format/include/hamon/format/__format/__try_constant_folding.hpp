///**
// *	@file	__try_constant_folding.hpp
// *
// *	@brief	__try_constant_folding の定義
// */
//
//#ifndef HAMON_FORMAT___FORMAT___TRY_CONSTANT_FOLDING_HPP
//#define HAMON_FORMAT___FORMAT___TRY_CONSTANT_FOLDING_HPP
//
//#include <hamon/format/basic_format_args.hpp>
//#include <hamon/format/basic_format_context.hpp>
//#include <hamon/format/__format/__output_buffer.hpp>
////#include <hamon/format/other/__visit_format_arg.hpp>
//#include <hamon/algorithm/ranges/find_first_of.hpp>
//#include <hamon/array.hpp>
//#include <hamon/detail/statically_widen.hpp>
//#include <hamon/iterator/back_insert_iterator.hpp>
//#include <hamon/optional.hpp>
//#include <hamon/string.hpp>
//#include <hamon/string_view.hpp>
//#include <hamon/type_traits/is_same.hpp>
//#include <hamon/type_traits/remove_cvref.hpp>
//
//namespace hamon
//{
//
//namespace __format
//{
//
//// Try constant folding the format string instead of going through the whole formatting machinery. If there is no
//// constant folding no extra code should be emitted (with optimizations enabled) and the function returns nullopt. When
//// constant folding is successful, the formatting is performed and the resulting string is returned.
//template <class _CharT>
//[[nodiscard]] hamon::optional<hamon::basic_string<_CharT>>
//__try_constant_folding(
//	hamon::basic_string_view<_CharT> __fmt,
//	hamon::basic_format_args<hamon::basic_format_context<hamon::back_insert_iterator<__format::__output_buffer<_CharT>>, _CharT>> __args)
//{
//	// Fold strings not containing '{' or '}' to just return the string
//	if (bool __is_identity = [&] /*[[__gnu__::__pure__]]*/ // Make sure the compiler knows this call can be eliminated
//		{ return hamon::ranges::find_first_of(__fmt, hamon::array{'{', '}'}) == __fmt.end(); }();
//		true/*__builtin_constant_p(__is_identity)*/ && __is_identity)
//	{
//		return hamon::basic_string<_CharT>{__fmt};
//	}
//
//	// Fold '{}' to the appropriate conversion function
//	if (auto __only_first_arg = __fmt == HAMON_STATICALLY_WIDEN(_CharT, "{}");
//		true/*__builtin_constant_p(__only_first_arg)*/ && __only_first_arg)
//	{
//		if (auto __arg = __args.get(0); true/*__builtin_constant_p(__arg.__type_)*/)
//		{
//			return __arg.visit(
//				[]<class _Tp>(_Tp&& __argument) -> hamon::optional<hamon::basic_string<_CharT>>
//				{
//					if constexpr (hamon::is_same_v<hamon::remove_cvref_t<_Tp>, hamon::basic_string_view<_CharT>>)
//					{
//						return hamon::basic_string<_CharT>{__argument};
//					}
//					else
//					{
//						return nullopt;
//					}
//				});
//		}
//	}
//
//	return nullopt;
//}
//
//}	// namespace __format
//
//}	// namespace hamon
//
//#endif // HAMON_FORMAT___FORMAT___TRY_CONSTANT_FOLDING_HPP
