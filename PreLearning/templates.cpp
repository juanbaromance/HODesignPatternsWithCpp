#include <iostream>

// Basic idea of variadic arguments where pattern matching/specicaization  is fully deployed
template<typename T> bool pair_comparer(T) { return false;}
template<typename T> bool pair_comparer(T a, T b) {  return a == b; }
template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {  return a == b && pair_comparer(args...); }

namespace containerdisplay
{
  template<typename T, template<class,class...> class C, class... Args>
  std::ostream& operator <<(std::ostream& os, const C<T,Args...>& objs)
  {
    for ( auto const & obj : objs )
      os << obj << ' ';
    return os;
  }

}

template <typename T1, typename T2>
struct TFormer {
public:
    TFormer( const T1 && _t1, const T2 && _t2 ) : t1( _t1 ), t2(_t2 ) {}
    auto valueOfT2() const { return __PRETTY_FUNCTION__ + std::string(".") + t2; }
private:
  T1 t1;
  T2 t2;
};

template<typename T1>
struct TFormer< T1, std::string>
{
public:
    using T2 = std::string;
    TFormer(const T1 &&t1_, T2 && arg ) : t1(t1_), t2(arg ){}
    auto valueOfT2() const { return __PRETTY_FUNCTION__ + std::string("..") + t2; }
    auto magicZip(){ return std::make_pair( t1,t2 ); }
private:
  T1 t1;
  T2 t2;
};

#include <vector>
int main()
{
    TFormer< int, std::string> f(1,"helper");
    std::cout << f.valueOfT2() << std::endl;

    std::vector<int> tmp = { 1, 2, 3 };
    {
        {
            using namespace containerdisplay;
            std::cout << __PRETTY_FUNCTION__ << "." << pair_comparer<int>(4, 4, 1, 1) << tmp << "\n" ;
        }

        const auto & [ i, k ] = TFormer(1,std::string("One")).magicZip();
        std::cout << i << ":" << k << "\n";
    }
    return 0;
}
