#include <eve/wide.hpp>
#include <iostream>
#include <kyosu/kyosu.hpp>

int main()
{
  using kyosu::cbrt;
  using kyosu::complex_t;

  using wi_t = eve::wide<unsigned int, eve::fixed<4>>;
  using wf_t = eve::wide<float, eve::fixed<4>>;
  wi_t wk = eve::iota(eve::as<wi_t>()) + 1;
  wf_t wf{5.0f, 2.3f, -1.2f, 0.0f};

  std::cout << "wk                          " << wk << std::endl;
  std::cout << "wf                          " << wf << std::endl;
  std::cout << "kyosu::cbrt(16.0, wk)    " << kyosu::cbrt(16.0, wk) << std::endl;
  std::cout << "kyosu::cbrt(wf, wk)      " << kyosu::cbrt(wf, wk) << std::endl;
  std::cout << "kyosu::cbrt(wf)          " << kyosu::cbrt(wf) << std::endl;

  return 0;
}
