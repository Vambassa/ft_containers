#ifndef FT_UTILS_HPP
#define FT_UTILS_HPP

#include "iterator.hpp"

namespace ft
{
	template<class T>
	void swap(T& a, T& b)
	{
		T tmp = a;
		a = b;
		b = tmp;
	}

	template <class InputIt1, class InputIt2>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2) {
		for (; first1 != last1; ++first1, ++first2) {
			if (!(*first1 == *first2)) {
				return false;
			}
		}
		return true;
	}

	template<class InputIt1, class InputIt2>
	bool	lexicographical_compare(InputIt1 first1, InputIt1 last1,
									InputIt2 first2, InputIt2 last2)
	{
		for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
		{
			if (*first1 < *first2) return true;
			if (*first2 < *first1) return false;
		}
		return (first1 == last1) && (first2 != last2);
	}

	namespace detail
	{
		template<class It>
		typename ft::iterator_traits<It>::difference_type
			do_distance(It first, It last, std::input_iterator_tag)
			{
				typename std::iterator_traits<It>::difference_type result = 0;
				while (first != last)
				{
					++first;
					++result;
				}
				return result;
			}

		template<class It>
		typename ft::iterator_traits<It>::difference_type
			do_distance(It first, It last, std::random_access_iterator_tag)
			{
				return last - first;
			}
	}

	template<class It>
	typename ft::iterator_traits<It>::difference_type distance(It first, It last)
	{
		return detail::do_distance(first, last,
			typename ft::iterator_traits<It>::iterator_category());
	}
}

#endif