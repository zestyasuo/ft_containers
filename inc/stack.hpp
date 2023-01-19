#ifndef stack_HPP
#define stack_HPP
#include <algorithm>
# include "vector.hpp"
# include <deque>

namespace ft
{
	template <class T, class Container = std::deque<T> >
	class stack
	{
	public:
		typedef Container				container_type;
		typedef T						value_type;
		typedef typename Container::size_type size_type;
		explicit stack(const container_type &cont = container_type()) : c(cont) {}
		stack(const stack &other): c(other.c) {}
		stack	&operator=(const stack &other) {
			c = other.c;
			return (*this);
		}
		bool empty(void) const
		{
			return c.empty();
		}
		void pop(void)
		{
			c.pop_back();
		}
		void push(const value_type &value)
		{
			c.push_back(value);
		}
		size_type size() const
		{
			return c.size();
		}
		value_type &top()
		{
			return c.back();
		}
		const value_type &top() const
		{
			return c.back();
		}
		~stack(void){};

	template <class T_, class Container_> friend bool operator==(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator!=(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator<(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator<=(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator>(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator>=(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);

	protected:
		container_type c;
	};

	template <class T, class Container> bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.c == rhs.c;
	}
	template <class T, class Container> bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.c != rhs.c;
	}
	template <class T, class Container> bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.c < rhs.c;
	}
	template <class T, class Container> bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.c <= rhs.c;
	}
	template <class T, class Container> bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.c > rhs.c;
	}
	template <class T, class Container> bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs.c >= rhs.c;
	}
}
#endif