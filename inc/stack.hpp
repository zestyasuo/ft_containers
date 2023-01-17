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
		explicit stack(const container_type &cont = container_type()) : _container(cont) {}
		stack(const stack &other): _container(other._container) {}
		stack	&operator=(const stack &other) {
			_container = other._container;
			return (*this);
		}
		bool empty(void) const
		{
			return _container.empty();
		}
		void pop(void)
		{
			_container.pop_back();
		}
		void push(const value_type &value)
		{
			_container.push_back(value);
		}
		size_type size() const
		{
			return _container.size();
		}
		value_type &top()
		{
			return _container.back();
		}
		const value_type &top() const
		{
			return _container.back();
		}
		~stack(void){};

	template <class T_, class Container_> friend bool operator==(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator!=(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator<(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator<=(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator>(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);
	template <class T_, class Container_> friend bool operator>=(const stack<T_, Container_> &lhs, const stack<T_, Container_> &rhs);

	private:
		container_type _container;
	};

	template <class T, class Container> bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container == rhs._container;
	}
	template <class T, class Container> bool operator!=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container != rhs._container;
	}
	template <class T, class Container> bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container < rhs._container;
	}
	template <class T, class Container> bool operator<=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container <= rhs._container;
	}
	template <class T, class Container> bool operator>(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container > rhs._container;
	}
	template <class T, class Container> bool operator>=(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
	{
		return lhs._container >= rhs._container;
	}
}
#endif