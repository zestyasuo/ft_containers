#ifndef vector_HPP 
# define vector_HPP
# include <memory.h>
# include <algorithm>
# include <cstddef>
# include "utils.hpp"

namespace ft
{
	template<
	class T,
	class Allocator = std::allocator<T>
	> class vector
	{
	public:
		typedef T											value_type;
		typedef	Allocator									allocator_type;
		typedef typename allocator_type::reference				reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer				pointer;
		typedef typename allocator_type::const_pointer			const_pointer;
		typedef typename allocator_type::size_type				size_type;
		vector(const allocator_type &alloc = allocator_type()) : alloc_(alloc), start_(u_nullptr), end_(u_nullptr) {};
		// vector(vector const &copy);
		~vector(void) {};
		// vector &operator=(vector const &rhs);
	private:
		allocator_type	alloc_;
		pointer	start_;
		pointer	end_;
	};

}
#endif