#include <exception>

struct EmptyListException : public std::exception{
	const char* what () const throw ()
	{
		return "Empty List";
	}
};

struct WrongIndexListException : public std::exception{
	const char* what () const throw ()
	{
		return "Wrong index";
	}
};

struct ElementNotFoundListException : public std::exception{
	const char* what () const throw ()
	{
		return "Element not found";
	}
};
