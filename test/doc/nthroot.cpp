#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::nthroot;
  using kyosu::complex_t;

   using wi_t =  eve::wide<unsigned int, eve::fixed<4>>;
   auto wn = eve::iota(eve::as<wi_t>())+1;

  std::cout << "wn                          " << wn <<  std::endl;
  std::cout << "kyosu::nthroot(16.0, wn)    " << kyosu::nthroot(16.0, wn) <<  std::endl;
  std::cout << "kyosu::nthroot(16.0, 4, wn) " << kyosu::nthroot(16.0, 4, wn) <<  std::endl;


  return 0;
}
