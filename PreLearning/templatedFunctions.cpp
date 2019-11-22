#include <iostream>
#include <typeinfo>

void whatami( int x   ) { std::cout << x << "." << __PRETTY_FUNCTION__ << std::endl; }
void whatami( long x  ) { std::cout << x << "." << __PRETTY_FUNCTION__ << std::endl; }
void whatami( double x ) { std::cout << x << "." << __PRETTY_FUNCTION__ << std::endl; }

// Is simply a case of use this is only a templated function which matches above signature so
// below template is added to overload space
template <typename T> void whatami( T* x  ) { std::cout << x << "." << __PRETTY_FUNCTION__ << std::endl; }
// universal reference
template <typename T> void whatami( T&& ) { std::cout << "." << __PRETTY_FUNCTION__ << std::endl; }


int main()
{
    int i = 5;
    struct p{};

    whatami(i);
    whatami(p());
    whatami(& i);

    float f(5.0);

    // Rules: if any overload matches try better template
    // otherwise promote to double reaching double overload
    whatami(f);

    return 0;
}
