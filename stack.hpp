#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"
#include "utils.hpp"

namespace ft
{
	template< class T, class Container = ft::vector<T> >
	class stack
	{
	public:
		typedef Container							container_type;
		typedef typename Container::value_type		value_type;
		typedef typename Container::size_type		size_type;
		typedef typename Container::reference		reference;
		typedef typename Container::const_reference	const_reference;

		explicit stack(const Container& cont = Container()) : _c(cont) {};
		stack(const stack& other) : _c(other._c) {};
		~stack() {};

		stack& operator=(const stack& other)
		{
			_c = other._c;
			return *this;
		}

		// Element access

		reference top()
		{
			return _c.back();
		}

		const_reference top() const
		{
			return _c.back();
		}

		// Capacity

		bool empty() const
		{
			return _c.empty();
		}

		size_type size() const
		{
			return _c.size();
		}

		// Modifiers

		void push(const value_type& value)
		{
			return _c.push_back(value);
		}

		void pop()
		{
			_c.pop_back();
		}

		// Non-member functions

		friend bool operator==(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs._c == rhs._c;
		}

		friend bool operator!=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs._c != rhs._c;
		}

		friend bool operator<(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs._c < rhs._c;
		}

		friend bool operator<=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs._c <= rhs._c;
		}

		friend bool operator>(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs._c > rhs._c;
		}

		friend bool operator>=(const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
		{
			return lhs._c >= rhs._c;
		}

	protected:
		Container	_c;
	};

}

#endif