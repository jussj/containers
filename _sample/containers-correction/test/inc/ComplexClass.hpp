#ifndef COMPLEXCLASS_HPP
# define COMPLEXCLASS_HPP

template<class T>
class	IncrediblyComplex {
	public:
		IncrediblyComplex() : _nb(42), _ptr(new T) {}
		//IncrediblyComplex() : _nb(42), _ptr(new char) {}
		
		IncrediblyComplex(int n, T type) : _nb(n), _ptr(new T) {
		//IncrediblyComplex(int n, char type) : _nb(n), _ptr(new char) {
			*_ptr = type;
		}
		IncrediblyComplex(IncrediblyComplex const &src)
			: _nb(src._nb), _ptr(new T) {
			//: _nb(src._nb), _ptr(new char) {
			*_ptr 	= *src._ptr;
		}
		~IncrediblyComplex() {
			delete _ptr;
		}
		int	getNb() const {
			return _nb;
		}
		T	getPtr() const {
			return *_ptr;
		}
	private:
		int	_nb;
		//char	*_ptr;
		T	*_ptr;
};

template<class T>
std::ostream &    operator<<(std::ostream & o, const IncrediblyComplex<T> &obj) {
    o << "(" << obj.getNb() << "; " << obj.getPtr() << ")"; 
    return    o;
}

#endif	/* COMPLEXCLASS_HPP */
