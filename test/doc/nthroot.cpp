#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  using kyosu::nthroot;
  using kyosu::complex_t;

   using wi_t =  eve::wide<unsigned int, eve::fixed<4>>;
   using wf_t =  eve::wide<float       , eve::fixed<4>>;
   wi_t  wn = eve::iota(eve::as<wi_t>())+1;
   wf_t  wf{5.0f,  2.3f, 1.2f, 0.0f};

  std::cout << "wn                          " << wn <<  std::endl;
  std::cout << "wf                          " << wf <<  std::endl;
  std::cout << "kyosu::nthroot(16.0, wn)    " << kyosu::nthroot(16.0, wn) <<  std::endl;
  std::cout << "kyosu::nthroot(16.0, 4, wn) " << kyosu::nthroot(16.0, 4, wn) <<  std::endl;
  std::cout << "kyosu::nthroot(16.0, -2)    " << kyosu::nthroot(16.0, -2.0) <<  std::endl;
  std::cout << "kyosu::nthroot(wf, wn)      " << kyosu::nthroot(wf, wn)   <<  std::endl;
  std::cout << "kyosu::nthroot(wf, wn, 3)   " << kyosu::nthroot(wf, wn, 3) <<  std::endl;
  std::cout << "all eight rooth of 1        " << kyosu::nthroot(1.0, 8, eve::wide{0, 1, 2, 3, 4, 5, 6, 7}) <<  std::endl;


  return 0;
}
