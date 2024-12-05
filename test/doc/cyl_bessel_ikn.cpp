#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>
#include <vector>

int main()
{
  using kyosu::cyl_bessel_ikn;
  using z_t = kyosu::complex_t<double>;
  std::cout.precision(16);
  std::cout << std::scientific << std::endl;
  int n = 5;
  // int sn = eve::sign(n);
  int nn = abs(n);
  std::vector< z_t> is(nn+1), ks(nn+1);
  auto z = z_t(20.0, 3.0);
  auto [in, kn] =  cyl_bessel_ikn(n, z, std::span(is), std::span(ks));
  std::cout << "in = " << in << std::endl;
  std::cout << "kn = " << kn << std::endl << std::endl;
  std::cout << std::endl;
  for(int i=0; i <= nn ; ++i)
  {
    std::cout << "i[" << i << "] = " << is[i]/* << "vs " << kyosu::cyl_bessel_in(i, z)*/ << std::endl;
  }
  std::cout << std::endl;
  for(int i=0; i <= nn ; ++i)
  {
    std::cout << "k[" << i << "] = " << ks[i]/* << "vs " << kyosu::cyl_bessel_kn(i, z)*/ << std::endl;
  }
  return 0;
}
