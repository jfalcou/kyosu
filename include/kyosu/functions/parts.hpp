//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright: KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once

#include <kyosu/details/callable.hpp>
#include <kyosu/types/concepts.hpp>
#include <kyosu/types/traits.hpp>
#include <type_traits>

namespace kyosu
{
  template<std::ptrdiff_t Index>
  struct extractor
  {
    template<concepts::cayley_dickson Z>
    KYOSU_FORCEINLINE constexpr decltype(auto) operator()(Z&& z) const noexcept
    {
      using type = eve::element_type_t<std::remove_cvref_t<Z>>;
      if constexpr(Index < type::static_dimension)  return get<Index>(KYOSU_FWD(z));
      else                                          return as_real_type_t<std::remove_cvref_t<Z>>{0};
    }

    template<concepts::real V>
    KYOSU_FORCEINLINE constexpr decltype(auto) operator()(V&& v) const noexcept
    {
      using type = std::remove_cvref_t<V>;
      if constexpr(Index == 0) return KYOSU_FWD(v); else  return type{0};
    }
  };

  //====================================================================================================================
  //! @addtogroup functions
  //! @{
  //====================================================================================================================

  //====================================================================================================================
  //!   @var real
  //!   @brief Extracts the real part of a value.
  //!
  //!   **Defined in Header**
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
  //!     constexpr decltype(auto) real(concepts::cayley_dickson auto&& v)  noexcept; // 1
  //!     constexpr decltype(auto) real(concepts::real auto&& v)            noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Value to process.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the real part of `v`.
  //!   2. Returns a properly const-qualified reference to `v`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/real.cpp}
  //====================================================================================================================
  inline constexpr auto real    = extractor<0>{};

  //====================================================================================================================
  //!   @var ipart
  //!   @brief Extracts the imaginary part of a value.
  //!
  //!   **Defined in Header**
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
  //!     constexpr decltype(auto)  ipart(concepts::cayley_dickson auto&& v)  noexcept; // 1
  //!     constexpr auto            ipart(concepts::real auto&& v)            noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the imaginary part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/ipart.cpp}
  //====================================================================================================================
  inline constexpr auto ipart   = extractor<1>{};

  //! Alias for kyosu::ipart
  inline constexpr auto imag    = extractor<1>{};

  //====================================================================================================================
  //!   @var jpart
  //!   @brief Extracts the \f$j\f$ part of a value.
  //!
  //!   **Defined in Header**
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
  //!     constexpr decltype(auto)  jpart(concepts::cayley_dickson auto&& v)  noexcept; // 1
  //!     constexpr auto            jpart(concepts::complex auto&& v)         noexcept; // 2
  //!     constexpr auto            jpart(concepts::real auto&& v)            noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the \f$j\f$ part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/jpart.cpp}
  //====================================================================================================================
  inline constexpr auto jpart   = extractor<2>{};

  //====================================================================================================================
  //!   @var kpart
  //!   @brief Extracts the \f$k\f$  part of a value.
  //!
  //!   **Defined in Header**
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
  //!     constexpr decltype(auto)  kpart(concepts::cayley_dickson auto&& v)  noexcept; // 1
  //!     constexpr auto            kpart(concepts::complex auto&& v)         noexcept; // 2
  //!     constexpr auto            kpart(concepts::real auto&& v)            noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the \f$k\f$ part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/kpart.cpp}
  //====================================================================================================================
  inline constexpr auto kpart   = extractor<3>{};

  //====================================================================================================================
  //!   @var lpart
  //!   @brief Extracts the \f$l\f$  part of a value.
  //!
  //!   **Defined in Header**
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
  //!     constexpr decltype(auto)  lpart(concepts::cayley_dickson  auto&& v)  noexcept; // 1
  //!     constexpr auto            lpart(concepts::quaternion      auto&& v)  noexcept; // 2
  //!     constexpr auto            lpart(concepts::complex         auto&& v)  noexcept; // 2
  //!     constexpr auto            lpart(concepts::real            auto&& v)  noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the \f$l\f$ part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/lpart.cpp}
  //====================================================================================================================
  inline constexpr auto lpart   = extractor<4>{};

  //====================================================================================================================
  //!   @var lipart
  //!   @brief Extracts the \f$li\f$  part of a value.
  //!
  //!   **Defined in Header**
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
  //!     constexpr decltype(auto)  lipart(concepts::cayley_dickson  auto&& v)  noexcept; // 1
  //!     constexpr auto            lipart(concepts::quaternion      auto&& v)  noexcept; // 2
  //!     constexpr auto            lipart(concepts::complex         auto&& v)  noexcept; // 2
  //!     constexpr auto            lipart(concepts::real            auto&& v)  noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the \f$li\f$ part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/lipart.cpp}
  //====================================================================================================================
  inline constexpr auto lipart  = extractor<5>{};

  //====================================================================================================================
  //!   @var ljpart
  //!   @brief Extracts the \f$lj\f$  part of a value.
  //!
  //!   **Defined in Header**
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
  //!     constexpr decltype(auto)  ljpart(concepts::cayley_dickson  auto&& v)  noexcept; // 1
  //!     constexpr auto            ljpart(concepts::quaternion      auto&& v)  noexcept; // 2
  //!     constexpr auto            ljpart(concepts::complex         auto&& v)  noexcept; // 2
  //!     constexpr auto            ljpart(concepts::real            auto&& v)  noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the \f$li\f$ part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/lipart.cpp}
  //====================================================================================================================
  inline constexpr auto ljpart  = extractor<6>{};

  //====================================================================================================================
  //!   @var lkpart
  //!   @brief Extracts the \f$lk\f$  part of a value.
  //!
  //!   **Defined in Header**
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
  //!     constexpr decltype(auto)  lkpart(concepts::cayley_dickson  auto&& v)  noexcept; // 1
  //!     constexpr auto            lkpart(concepts::quaternion      auto&& v)  noexcept; // 2
  //!     constexpr auto            lkpart(concepts::complex         auto&& v)  noexcept; // 2
  //!     constexpr auto            lkpart(concepts::real            auto&& v)  noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the \f$lk\f$ part of `v`.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/lipart.cpp}
  //====================================================================================================================

  //====================================================================================================================
  //! @}
  //====================================================================================================================
  inline constexpr auto lkpart  = extractor<7>{};
}
