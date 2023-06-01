#include <iostream>
#include <algorithm>

namespace MyEnum
{
  enum Type
  {
    a = 100,
    b = 220,
    c = -1
  };

  static const Type All[] = { a, b, c };
}

void fun( const MyEnum::Type e )
{
  std::cout << e << std::endl;
}

int main()
{
  // all
  for ( const auto e : MyEnum::All )
    fun( e );

  // some
  for ( const auto e : { MyEnum::a, MyEnum::b } )
    fun( e );

  // all
  std::for_each( std::begin( MyEnum::All ), std::end( MyEnum::All ), fun );

  return 0;
}
