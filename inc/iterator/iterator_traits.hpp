#ifndef ITERATOR_TRAITS_HPP
# define ITERATOR_TRAITS_HPP

# include <cstddef>		// ptrdiff_t

namespace ft {

	// inherite from std tags for greater portability? does it work with every algo???
	struct output_iterator_tag 	{};
	struct input_iterator_tag 	{};
	struct forward_iterator_tag 		: public input_iterator_tag				{};
	struct bidirectional_iterator_tag 	: public forward_iterator_tag			{};
	struct random_access_iterator_tag 	: public bidirectional_iterator_tag 	{};

	template<class Iter>
	class iterator_traits {
		public:
			typedef typename Iter::difference_type		difference_type;
			typedef typename Iter::value_type			value_type;
			typedef typename Iter::pointer				pointer;
			typedef typename Iter::reference			reference;
			typedef typename Iter::iterator_category	iterator_category;
	};

	template<class T>
	class iterator_traits<T *> {
		public:
			typedef ptrdiff_t					difference_type;
			typedef T							value_type;
			typedef T *							pointer;
			typedef T &							reference;
			typedef random_access_iterator_tag	iterator_category;
	};

	template<class T>
	class iterator_traits<const T *> {
		public:
			typedef ptrdiff_t					difference_type;
			typedef T							value_type;
			typedef const T *					pointer;
			typedef const T &					reference;
			typedef random_access_iterator_tag	iterator_category;
	};

}

#endif
