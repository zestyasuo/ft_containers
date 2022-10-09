#ifndef utils_HPP 
# define utils_HPP
namespace ft {

template<typename T>
void	swap(T &x, T &y)
{
	T	tmp;

	tmp = x;
	x = y;
	y = tmp;
}



static class	nullptr_t
{
	public:
		template <class T>
		operator T*() const { return (0); }
		template<class C, class T>
		operator T C::*() const { return (0); }
	private:
		void operator&() const;

} u_nullptr = {};
}

#endif