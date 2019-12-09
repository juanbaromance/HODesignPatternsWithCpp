#include <iostream>

// SFINAE essentials: 

// Illustrates part of the the compiler overload process resolution. Job follows next steps
// 1.- Type deduction from client code
// 2.- Substitution types exact match on the non templated scope
// 3.- Substitution types on the templated scope
// 4.- Type promotion on the non templated scope
// 5.- Substitution types on the variadic args scope

template <typename T>
void f( T i, T &j   )
{ 
	( std::cout << __PRETTY_FUNCTION__ << " " << i << " : " << std::hex << &j << " : " << j << "\n").flush() ;
}

// Uncomment Below to ground the template, collapsing the resolution here  
void f( int i, int &j ){ ( std::cout << __PRETTY_FUNCTION__ << i << " : " << std::hex << &j << " : " << j << "\n").flush() ; }


int main()
{
	int k{0};

	f(1, k);
	f(1l, k); // doesn't compile without collapse stuff

	return 0;
}