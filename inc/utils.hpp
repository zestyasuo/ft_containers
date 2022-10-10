#ifndef utils_HPP
#define utils_HPP
namespace ft
{

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
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	template <class T>
	class iterator_traits<T *>
	{
	public:
		typedef typename std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
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
	struct iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template <typename T>
	class RandomAccessIterator : public iterator<std::random_access_iterator_tag, T>
	{
	public:
		typedef typename iterator_traits<T *>::pointer pointer;
		typedef typename iterator_traits<T *>::value_type value_type;
		typedef typename iterator_traits<T *>::difference_type difference_type;
		typedef typename iterator_traits<T *>::reference reference;
		typedef typename iterator_traits<T *>::iterator_category iterator_category;
		RandomAccessIterator() : _ptr()
		{
		}

		RandomAccessIterator(pointer ptr) : _ptr(ptr) {}

		RandomAccessIterator(RandomAccessIterator const &other) : _ptr(other._ptr)
		{
		}

		RandomAccessIterator &operator=(RandomAccessIterator const &other)
		{
			if (this == &other)
				return *this;
			RandomAccessIterator new_ptr(other);
			return new_ptr;
		}

		virtual ~RandomAccessIterator()
		{
		}

	protected:
		pointer _ptr;
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
}

#endif