#ifndef utils_HPP
# define utils_HPP
# include <cstddef>
# include <limits>
# include <sstream>
# include <typeinfo>
# include <iostream>
# include <typeinfo>

namespace ft
{
	// enable if
	template<bool B, class T = void>
	struct enable_if
	{
	};
	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};
	// pair and make pair
	template<class T1, class T2>
	struct pair {
		typedef T1	first_type;
		typedef T2	second_type;
		first_type first;
		second_type second;

		pair(void) : first(), second(){}
		template<class U, class V>
		pair (const pair<U, V> &pr) : first(pr.first), second(pr.second) {}
		pair (first_type const &f, second_type const &s) : first(f), second(s) {}
		pair	&operator=(pair const &pr)
		{
			if (*this == pr)
				return (*this);
			first = pr.first;
			second = pr.second;
			return (*this);
		}
	};

	template <class T1, class T2>
	pair<T1, T2>	make_pair(T1 a, T2 b)
	{
		return pair<T1, T2>(a,b);
	}

	template <class T1, class T2>
	bool	operator==(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
	{
		return lhs.first == rhs.first && lhs.second == rhs.second;
	}

	template <class T1, class T2>
	bool	operator<(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
	{
		return lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second);
	}
	template <class T1, class T2>
	bool	operator!=(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
	{
		return !(lhs == rhs);
	}
	template <class T1, class T2>
	bool	operator<=(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
	{
		return !(rhs < lhs);
	}
	template <class T1, class T2>
	bool	operator>(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
	{
		return rhs < lhs;
	}
	template <class T1, class T2>
	bool	operator>=(pair<T1, T2> const &lhs, pair<T1, T2> const &rhs)
	{
		return !(lhs < rhs);
	}

// is integral

	template<bool is_integral, typename T>
	struct is_intergral_res {
		typedef T type;
		static const bool value = is_integral;
	};

	template <typename>
	struct is_integral_type : public is_intergral_res<false, bool> {};
	
	template <>
	struct is_integral_type<bool> : public is_intergral_res<true, bool> {};

	template <>
	struct is_integral_type<char> : public is_intergral_res<true, char> {};

	template <>
	struct is_integral_type<signed char> : public is_intergral_res<true, signed char> {};

	template <>
	struct is_integral_type<short int> : public is_intergral_res<true, short int> {};

	template <>
	struct is_integral_type<int> : public is_intergral_res<true, int> {};

	template <>
	struct is_integral_type<long int> : public is_intergral_res<true, long int> {};

	template <>
	struct is_integral_type<long long int> : public is_intergral_res<true, long long int> {};

	template <>
	struct is_integral_type<unsigned char> : public is_intergral_res<true, unsigned char> {};
	
	template <>
	struct is_integral_type<unsigned short int> : public is_intergral_res<true, unsigned short int> {};

	template <>
	struct is_integral_type<unsigned int> : public is_intergral_res<true, unsigned int> {};

	template <>
	struct is_integral_type<unsigned long int> : public is_intergral_res<true, unsigned long int> {};

	template <>
	struct is_integral_type<unsigned long long int> : public is_intergral_res<true, unsigned long long int> {};
	
	template <typename T>
	struct is_integral : public is_integral_type<T> {};

// Iterator tags
	class random_access_iterator_tag {};
	class bidirectional_iterator_tag {};
	class forward_iterator_tag {};
	class input_iterator_tag {};
	class output_iterator_tag {};

	template <bool is_valid, typename T>
	struct valid_iterator_tag_res {
		typedef T type;
		const static bool value = is_valid;
	};

	template <typename T>
	struct is_input_iterator_tagged : public valid_iterator_tag_res<false, T> {};

	template <>
	struct is_input_iterator_tagged<ft::random_access_iterator_tag> : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<ft::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<ft::forward_iterator_tag> : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};

	template <>
	struct is_input_iterator_tagged<ft::input_iterator_tag> : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};
//----------
	template <typename T>
	struct is_ft_iterator_tagged : public valid_iterator_tag_res<false, T> {};

	template <>
	struct is_ft_iterator_tagged <ft::random_access_iterator_tag> : public valid_iterator_tag_res<true, ft::random_access_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<ft::bidirectional_iterator_tag> : public valid_iterator_tag_res<true, ft::bidirectional_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<ft::forward_iterator_tag> : public valid_iterator_tag_res<true, ft::forward_iterator_tag> {};

	template <>
	struct is_ft_iterator_tagged<ft::input_iterator_tag> : public valid_iterator_tag_res<true, ft::input_iterator_tag> {};


	template<typename T>
	class InvalidIteratorException : public std::exception
	{
		private:
			std::string _msg;
		public:
			InvalidIteratorException() throw()
			{
				_msg = "Is invalid iterator tag: " + std::string(typeid(T).name());
			}
			InvalidIteratorException(InvalidIteratorException const &) throw() {}
			InvalidIteratorException &operator=(InvalidIteratorException const &) throw() {}
			virtual ~InvalidIteratorException() throw() {}
			virtual const char *what() const throw()
			{
				return _msg.c_str();
			}
	};

	template <typename T>
	void swap(T &x, T &y)
	{
		T tmp;

		tmp = x;
		x = y;
		y = tmp;
	}

	template <class Iterator>
	class iterator_traits
	{
	public:
		typedef typename Iterator::difference_type		difference_type;
		typedef typename Iterator::value_type			value_type;
		typedef typename Iterator::pointer				pointer;
		typedef typename Iterator::reference			reference;
		typedef typename Iterator::iterator_category	iterator_category;
	};

	template <class T>
	class iterator_traits<T *>
	{
	public:
		typedef typename std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef ft::random_access_iterator_tag iterator_category;
	};

	template <class T>
	class iterator_traits<const T *>
	{
	public:
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class Category, class T, class Distance = ptrdiff_t,
			  class Pointer = T *, class Reference = T &>
	class iterator
	{
		public:
			typedef T value_type;
			typedef Distance difference_type;
			typedef Pointer pointer;
			typedef Reference reference;
			typedef Category iterator_category;
	};

	template<class InputIterator>
	typename ft::iterator_traits<InputIterator>::difference_type
			distance(InputIterator first, InputIterator last)
			{
				typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
				while (first != last)
				{
					first++;
					rtn++;
				}
				return rtn;
			}

	template <class T>
	class bidirectional_iterator : ft::iterator<ft::bidirectional_iterator_tag, T>
	{
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;
		pointer _elem;
	};


	static class nullptr_t
	{
	public:
		template <class T>
		operator T *() const { return (0); }
		template <class C, class T>
		operator T C::*() const { return (0); }

	private:
		void operator&() const;

	} u_nullptr = {};

	template<typename T>
	struct TreeNode
	{
		typedef T value_type;
		
		value_type		value;
		TreeNode		*parent;
		TreeNode		*left;
		TreeNode		*right;

		TreeNode(void) : value(), parent(u_nullptr), left(u_nullptr), right(u_nullptr)
		{}

		TreeNode(value_type const &val, TreeNode *parent = u_nullptr, TreeNode *left = u_nullptr, TreeNode *right = u_nullptr)
		: value(val), parent(parent), left(left), right(right)
		{}

		TreeNode(TreeNode *parent = u_nullptr, TreeNode *left = u_nullptr, TreeNode *right = u_nullptr) : value(), parent(parent), left(left), right(right)
		{}

		TreeNode(TreeNode const &other) : value(other.value), parent(other.parent), left(other.left), right(other.right)
		{}

		virtual ~TreeNode() {}

		TreeNode	&operator=(TreeNode const &other)
		{
			if (&other == this)
				return (*this);
			value = other.value;
			parent = other.parent;
			left = other.left;
			right = other.right;
			return (*this);
		}

		bool	operator==(TreeNode const &other)
		{
			if (value == other.value)
				return true;
			return false;
		}
	};
	
}

#endif