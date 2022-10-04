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
	public:
		typedef T value_type;
		typedef Allocator allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename allocator_type::size_type size_type;
		// iterators :
		vector(const allocator_type &alloc = allocator_type()) : _alloc(alloc), _array(u_nullptr), _size(0), _capacity(0){};
		vector operator=(const value_type &other)
		{
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
		void resize(size_type n, value_type val = value_type())
		{
			pointer new_array;

			if (n < _size)
			{
				_alloc.deallocate(_array[n], _size - n);
				_size = n;
			}
			if (n > _size)
			{
				new_array = _alloc.allocate(_capacity > n ?: _capacity
											: n);
				for (size_type i = 0; i < _size; i++)
					new_array[i] = _array[i];
				for (size_type i = _size; i < n; i++)
					new_array[i] = val;
				_alloc.deallocate(_array[0], _size);
				_array = new_array;
				_capacity = _capacity > n ?: _capacity : n;
				size = n;
			}
		}
		void reserve(size_type n)
		{
			pointer new_array;
			if (n > _capacity)
			{
				new_array = _alloc.allocate(n);
				for (size_type i = 0, i < _size, i++)
					new_array[i] = _array[i];
				_capacity = n;
			}
		}
		reference operator[](size_type n)
		{
			return *_array[n];
		}
		const_reference operator[](size_type n) const
		{
			return *_array[n];
		}
		reference at(size_type n)
		{
			return *_array[n];
		}
		const_reference at(size_type n) const
		{
			return *_array[n];
		}
		reference front()
		{
			return *_array[0];
		}
		const_reference front() const
		{
			return *_array[0];
		}
		reference back()
		{
			return *_array[_size - 1];
		}
		const_reference back() const
		{
			return *_array[_size - 1];
		}
		value_type *data() noexcept
		{
			return _array;
		}
		const value_type* data() const noexcept
		{
			return _array;
		}
		~vector(void){};
		// vector &operator=(vector const &rhs);
	private:
		allocator_type _alloc;
		pointer _array;
		size_type _size;
		size_type _capacity;
	};

}
#endif