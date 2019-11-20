// Basic idea of variadic arguments where pattern matching is fully deployed
template<typename T> bool pair_comparer(T) { return false;}
template<typename T> bool pair_comparer(T a, T b) {  return a == b; }
template<typename T, typename... Args>
bool pair_comparer(T a, T b, Args... args) {  return a == b && pair_comparer(args...); }

#include <iostream>
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

#include <vector>
int main()
{
    std::vector<int> tmp = { 1, 2, 3 };
    {
        using namespace containerdisplay;
        std::cout << __PRETTY_FUNCTION__ << "." << pair_comparer<int>(4, 4, 1, 1) << tmp ;
    }
}