#include <vector>
#include <iostream>

// ////////////////////////////////////////////////////////
// Templated variadics functions

// c++17 folds
template <typename ...T>
void auditorC17( T&& ...x )
{
    using namespace std;
    ( cout << ... << x );
    ( cout << "\n").flush();
}

// c++14 recursion strategy
template <typename T>
auto auditorC14(T& t){ return t; }
template <typename T1, typename ...T>
void auditorC14( T1&& arg, T&& ...x )
{
    std::cout << " " << arg << auditorC14( x...) << "\n";
}

void test_variadics_function()
{
    using namespace std;
    auto tmp( string( __PRETTY_FUNCTION__ ) );
    auditorC17(1, 2, 3, tmp );
    auditorC14( tmp, "next#" + string("(helper)") );
}

// ////////////////////////////////////////////////////////
// Templated Variadics classes
template <typename ...> struct Group;

// Single attribute
template <typename T1>
struct Group<T1>{
    T1 t1_;

    Group() = default;
    explicit Group( const T1 & t1) : t1_ ( t1 ){}
    explicit Group( const T1 && t1) : t1_ ( std::move(t1) ){}
    explicit operator const T1&() const { return t1_ ; }
    explicit operator T1&() const { return t1_ ; }
};

// Multiple attribute
template <typename T1, typename ...T>
struct Group<T1, T...> : Group<T...> {
    T1 t1_;
    Group() = default;
    explicit Group( const T1 & t1, T && ...t )
        : Group<T...> ( std::forward<T>(t) ... ), t1_ ( t1 )
    {}
    explicit Group( const T1 && t1, T && ...t )
        : Group<T...> ( std::forward<T>(t) ... ), t1_ ( std::move(t1) )
    {}
    explicit operator const T1&() const { return t1_ ; }
    explicit operator T1&() { return t1_ ; }
};

template <typename...T>
auto makeGroup(T...args){ return Group<T...>( std::forward<T>(args)...); }

///
/// \brief test_variadics_class
///
void test_variadics_class()
{
    using namespace std;
    Group<int,size_t,string> var(3,4,"MyTuple");
    auto bundle = makeGroup(3,4,"MyTuple");
}


// Overloaded Lambdas using above strategies
// C++14 Approach
// Forward declaration
template <typename ...> struct overload_set;

// Single parameter constructor
template <typename F1>
struct overload_set<F1> : public F1 {
    overload_set( F1&& f1 ) : F1( std::move( f1 ) ){}
    overload_set( const F1& f1 ) : F1( f1 ){}
    using F1::operator();
};

//// Generic parameter constructor
template <typename F1, typename ... F>
struct overload_set<F1, F ...> : public F1, public overload_set<F ...> {
    overload_set( F1&& f1, F && ... f )
        : F1( std::move(f1) ), overload_set<F...>( std::forward<F>(f) ...){}
    overload_set(const F1 & f1, F &... f )
        : F1( f1 ), overload_set<F...>(std::forward<F>(f) ...){}
    using F1::operator();
};

// using c++17 above could be sumarized as
template <typename ... F>
struct overload_set : public F ... {
    overload_set( F&& ... f) : F(std::forward<F>(f)) ... {}
    using F::operator() ... ;
};


// Below function template roles as a factory of variadic lambdas
template <typename ... F>
auto overload( F && ... f ){ return overload_set<F...>( std::forward<F>(f)... ); }

void test_variadics_lambdas()
{
    using namespace std;

    int m(3);
    string n("String");

    auto f = overload (
     []( int *m ){ std::cout << *m << endl; },
     []( string & m ){ std::cout << m << endl; }
    );

    f( & m );
    f( n );
}


int main()
{
    test_variadics_class();
    test_variadics_lambdas();
}
