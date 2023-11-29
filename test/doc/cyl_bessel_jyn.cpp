#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>

int main()
{
  using kyosu::cyl_bessel_jyn;
  using z_t = kyosu::complex_t<double>;
  std::cout.precision(16);
  std::cout << std::scientific << std::endl;
  int n = 5;
  // int sn = eve::sign(n);
  int nn = abs(n);
  std::vector< z_t> js(nn+1), ys(nn+1);
  auto z = z_t(20.0, 3.0);
  auto [jn, yn] =  cyl_bessel_jyn(n, z, js, ys);
  std::cout << "jn = " << jn << std::endl;
  std::cout << "yn = " << yn << std::endl << std::endl;
  std::cout << std::endl;
  for(int i=0; i <= nn ; ++i)
  {
    std::cout << "j[" << i << "] = " << js[i]/* << "vs " << kyosu::cyl_bessel_jn(i, z)*/ << std::endl;
  }
  std::cout << std::endl;
  for(int i=0; i <= nn ; ++i)
  {
    std::cout << "y[" << i << "] = " << ys[i]/* << "vs " << kyosu::cyl_bessel_yn(i, z)*/ << std::endl;
  }
  return 0;
}
