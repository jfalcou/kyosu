//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <kyosu/details/callable.hpp>

namespace kyosu
{
  template<typename Options> struct airy_bi_t : eve::elementwise_callable<airy_bi_t, Options>
  {
    template<concepts::cayley_dickson_like Z> KYOSU_FORCEINLINE constexpr Z operator()(Z const& z) const noexcept
    {
      return KYOSU_CALL(z);
    }

    KYOSU_CALLABLE_OBJECT(airy_bi_t, airy_bi_);
  };

  //======================================================================================================================
  //! @addtogroup functions
  //! @{
  //!   @var airy_bi
  //!   @brief Computes the airy function \f$Bi\f$
  //!
  //!   @groupheader{Header file}
  //!
  //!   @code
  //!   #include <kyosu/functions.hpp>
  //!   @endcode
  //!
  //!   @groupheader{Callable Signatures}
  //!
  //!   @code
  //!   namespace kyosu
  //!   {
  //!      template<kyosu::concepts::cayley_dickson_like T> constexpr auto airy_bi(T z) noexcept;
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!     * `z`: Value to process.
  //!
  //!   **Return value**
  //!
  //!     -  A real type input z calls [eve::airy_bi(z)](@ref eve::airy_bi).
  //!     -  returns \f$ Bi(z) \f$.
  //!
  //!  @groupheader{External references}
  //!   *  [Wolfram MathWorld: Airy Functions](https://mathworld.wolfram.com/AiryFunctions.html)
  //!   *  [Wikipedia: Airy function](https://en.wikipedia.org/wiki/Airy_function)
  //!   *  [DLMF: Airy and Related Functions](https://dlmf.nist.gov/9.2)
  //!
  //!  @groupheader{Example}
  //!  @godbolt{doc/airy_bi.cpp}
  //======================================================================================================================
  inline constexpr auto airy_bi = eve::functor<airy_bi_t>;
  //======================================================================================================================
  //! @}
  //======================================================================================================================
}

namespace kyosu::_
{
  template<typename Z, eve::callable_options O>
  KYOSU_FORCEINLINE constexpr auto airy_bi_(KYOSU_DELAY(), O const&, Z z) noexcept
  {
    if constexpr (concepts::real<Z>) return eve::airy_bi(z);
    else if constexpr (kyosu::concepts::complex<Z>) return _::bi(z);
    else return _::cayley_extend(kyosu::airy_bi, z);
  }
}
