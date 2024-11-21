#include <kyosu/kyosu.hpp>
#include <eve/wide.hpp>
#include <iostream>

int main()
{
  std::cout << "Real:\n";
  std::cout << "  complex(72.9f)      -> " << kyosu::complex(72.9f) << "\n";

  std::cout << "Complex:\n";
  std::cout << "  complex(3.5f, 2.9f) -> " << kyosu::complex(3.5f,-2.9f) << "\n";

  std::cout << "SIMD real:\n";
  eve::wide<double,eve::fixed<2>> w(3.5f,-2.9f);
  std::cout << "  complex(w)          -> " << kyosu::complex(w) << "\n";

  std::cout << "SIMD complex:\n";
  eve::wide<double,eve::fixed<2>> wr(3.5f,-2.9f), wi(1.0, -3.0);
  std::cout << "  complex(wr, wi)     -> " << kyosu::complex(wr, wi) << "\n";

  std::cout << "Mixed complex:\n";
  std::cout << "  complex(wr  , 9.5)  -> " << kyosu::complex(wr, 9.5) << "\n";
  std::cout << "  complex(-6.3,  wi)  -> " << kyosu::complex(-6.3, wi) << "\n";
}
