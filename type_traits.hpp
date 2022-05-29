#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

namespace ft
{
	// enable_if

	template<bool B, class T = void>
	struct enable_if {};

	template<class T>
	struct enable_if<true, T> { typedef T type; };

	// is_integral

	template <typename>
	struct is_integral : std::false_type {};

	template <>
	struct is_integral<bool> : std::true_type {};

	template <>
	struct is_integral<char> : std::true_type {};

	template <>
	struct is_integral<char16_t> : std::true_type {};

	template <>
	struct is_integral<char32_t> : std::true_type {};

	template <>
	struct is_integral<signed char> : std::true_type {};

	template <>
	struct is_integral<short> : std::true_type {};

	template <>
	struct is_integral<int> : std::true_type {};

	template <>
	struct is_integral<long> : std::true_type {};

	template <>
	struct is_integral<long long> : std::true_type {};

	template <>
	struct is_integral<unsigned char> : std::true_type {};

	template <>
	struct is_integral<unsigned short> : std::true_type {};

	template <>
	struct is_integral<unsigned int> : std::true_type {};

	template <>
	struct is_integral<unsigned long> : std::true_type {};

	template <>
	struct is_integral<unsigned long long> : std::true_type {};

}

#endif
