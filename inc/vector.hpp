#ifndef vector_HPP
#define vector_HPP
#include <memory.h>
#include <algorithm>
#include <cstddef>
#include "utils.hpp"

namespace ft
{
	template <
		class T,
		class Allocator = std::allocator<T> >
	class vector
	{
		template <typename L>
		class Iterator : public RandomAccessIterator<L>
		{
			typedef RandomAccessIterator<L> _super;

		public:
			Iterator() : _super() {}
			Iterator(typename _super::pointer ptr) : _super(ptr) {}
			Iterator(Iterator const &other) : _super(other) {}
			~Iterator() {}

			Iterator &operator++()
			{
				++this->_ptr;
				return *this;
			}
			Iterator operator++(int)
			{
				Iterator tmp(*this);
				++this->_ptr;
				return tmp;
			}
			Iterator &operator--()
			{
				++this->_ptr;
				return *this;
			}
			Iterator operator--(int)
			{
				Iterator tmp(*this);
				--this->_ptr;
				return tmp;
			}
			Iterator operator+(typename _super::difference_type const &other) const
			{
				return this->_ptr + other;
			}
			Iterator operator-(typename _super::difference_type const &other) const
			{
				return this->_ptr - other;
			}
			Iterator &operator+=(typename _super::difference_type const n)
			{
				this->_ptr += n;
				return *this;
			}
			Iterator &operator-=(typename _super::difference_type const n)
			{
				this->_ptr -= n;
				return *this;
			}
			typename _super::reference operator*() const
			{
				return *(this->_ptr);
			}
			typename _super::pointer operator->() const
			{
				return this->_ptr;
			}
			typename _super::reference operator[](typename _super::difference_type n)
			{
				return *(this->_ptr + n);
			}
		};

	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::size_type size_type;
		typedef Iterator<value_type> iterator;
		typedef Iterator<const value_type> const_iterator;
		explicit vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _array(0), _size(0), _capacity(0){};

		explicit vector(size_type n, value_type &val = value_type(), const allocator_type &alloc = allocator_type())
			: _alloc(alloc), _size(n), _capacity(n)
		{
			_array = _alloc.allocate(n);
			for (size_type i = 0; i < n; i++)
				_alloc.construct(&_array[i], val);
		}

		vector(const vector &other)
		{
			*this = other;
		}

		vector &operator=(const vector &other)
		{
			if (this == &other)
				return *this;
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			_size = other.size();
			if (_capacity < _size)
			{
				if (_capacity != 0)
					_alloc.deallocate(_array, _capacity);
				_array = _alloc.allocate(_size);
				_capacity = _size;
			}
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_array[i], other[i]);
			return *this;
		}

		size_type size(void) const
		{
			return (_size);
		}
		size_type max_size(void) const
		{
			return _alloc.max_size();
		}
		size_type capacity(void) const
		{
			return (_capacity);
		}
		bool empty(void) const
		{
			return _size == 0;
		}

		void reserve(size_type n)
		{
			if (n < _capacity)
				return;
			pointer new_array = _alloc.allocate(n);
			try
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&new_array[i], _array[i]);
			}
			catch (std::exception &e)
			{
				for (size_type i = 0; new_array[i] && i < _size; i++)
					_alloc.destroy(&new_array[i]);
				_alloc.deallocate(new_array, n);
				throw;
			}
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			if (_capacity)
				_alloc.deallocate(_array, _capacity);
			_capacity = n;
			_array = new_array;
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (_size == n)
				return;
			if (n > _capacity)
				reserve(n);
			if (n > _size)
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(&_array[i], val);
				_size = n;
			}
			else if (n < _size)
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(&_array[i]);
				_size = n;
			}
		}

		void push_back(value_type const &el)
		{
			if (_size == _capacity)
				reserve(_capacity == 0 ? 1 : _capacity * 2);
			_alloc.construct(&_array[_size], el);
			_size++;
		}

		void pop_back(void)
		{
			_alloc.destroy(_array + _size - 1);
			_size--;
		}

		reference operator[](size_type n)
		{
			return _array[n];
		}

		const_reference operator[](size_type n) const
		{
			return _array[n];
		}

		reference at(size_type n)
		{
			if (n > _capacity)
				throw std::out_of_range("out of range");
			return _array[n];
		}

		const_reference at(size_type n) const
		{
			if (n > _capacity)
				throw std::out_of_range("out of range");
			return _array[n];
		}

		reference front()
		{
			return _array[0];
		}

		const_reference front() const
		{
			return _array[0];
		}

		reference back()
		{
			return _array[_size - 1];
		}

		const_reference back() const
		{
			return _array[_size - 1];
		}

		allocator_type get_allocator() const
		{
			return (allocator_type(_alloc));
		}

		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			_size = 0;
		}

		void assign(size_type n, const value_type &val)
		{
			resize(n);
			clear();
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.construct(&_array[i], val);
			}
		}

		void swap(vector &other)
		{
			ft::swap(_alloc, other._alloc);
			ft::swap(_array, other._array);
			ft::swap(_size, other._size);
			ft::swap(_capacity, other._capacity);
		}

		~vector(void)
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			if (_capacity)
				_alloc.deallocate(_array, _capacity);
		};
		template <class T_, class Alloc>
		friend bool operator==(const vector<T_, Alloc> &lhs, const vector<T_, Alloc> &rhs);
		template <class T_, class Alloc>
		friend bool operator!=(const vector<T_, Alloc> &lhs, const vector<T_, Alloc> &rhs);
		template <class T_, class Alloc>
		friend bool operator<(const vector<T_, Alloc> &lhs, const vector<T_, Alloc> &rhs);
		template <class T_, class Alloc>
		friend bool operator<=(const vector<T_, Alloc> &lhs, const vector<T_, Alloc> &rhs);
		template <class T_, class Alloc>
		friend bool operator>(const vector<T_, Alloc> &lhs, const vector<T_, Alloc> &rhs);
		template <class T_, class Alloc>
		friend bool operator>=(const vector<T_, Alloc> &lhs, const vector<T_, Alloc> &rhs);

		iterator begin()
		{
			return (iterator(_array));
		}
		const_iterator begin() const
		{
			return (const_iterator(_array));
		}
		iterator end() const
		{
			return (iterator(_array + (_size)));
		}

	private:
		allocator_type _alloc;
		pointer _array;
		size_type _size;
		size_type _capacity;
	};

	// template <class T, class Alloc>
	// bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	// {
	// }
	// template <class T, class Alloc>
	// bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	// {
	// }
	// template <class T, class Alloc>
	// bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	// {
	// }
	// template <class T, class Alloc>
	// bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	// {
	// }
	// template <class T, class Alloc>
	// bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	// {
	// }
	// template <class T, class Alloc>
	// bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	// {
	// }

	template <class T, class Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif