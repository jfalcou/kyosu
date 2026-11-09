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
  template<std::ptrdiff_t Index> struct extractor
  {
    template<concepts::cayley_dickson Z> KYOSU_ABI constexpr decltype(auto) operator()(Z&& z) const noexcept
    {
      using type = eve::element_type_t<std::remove_cvref_t<Z>>;
      if constexpr (Index < type::static_dimension) return get<Index>(KYOSU_FWD(z));
      else return as_real_type_t<std::remove_cvref_t<Z>>{0};
    }

    template<concepts::real V> KYOSU_ABI constexpr decltype(auto) operator()(V&& v) const noexcept
    {
      using type = std::remove_cvref_t<V>;
      if constexpr (Index == 0) return KYOSU_FWD(v);
      else return type{0};
    }
  };

  //====================================================================================================================
  //! @defgroup real kyosu::real
  //! @ingroup agnostic
  //! @brief Extracts the real part of a value.
  //! @{
  //====================================================================================================================
  //!   @var real
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
  inline constexpr auto real = extractor<0>{};

  //! @}

  //====================================================================================================================
  //! @defgroup ipart kyosu::ipart
  //! @ingroup agnostic
  //! @brief Extracts the imaginary part of a value.
  //! @{
  //====================================================================================================================
  //!   @var ipart
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
  inline constexpr auto ipart = extractor<1>{};

  //====================================================================================================================
  //! @defgroup imag kyosu::imag
  //! @ingroup agnostic
  //! @brief Alias of kyosu::ipart, the imaginary part of a value.
  //! @{
  //====================================================================================================================
  //!   @var imag
  //!
  //!   `kyosu::imag` is `kyosu::ipart` under the name of `std::imag`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/imag.cpp}
  //!
  //!   @see kyosu::ipart
  //====================================================================================================================
  inline constexpr auto imag = extractor<1>{};
  //! @}

  //! @}

  //====================================================================================================================
  //! @defgroup jpart kyosu::jpart
  //! @ingroup agnostic
  //! @brief Extracts the \f$j\f$ part of a value.
  //! @{
  //====================================================================================================================
  //!   @var jpart
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
  inline constexpr auto jpart = extractor<2>{};

  //! @}

  //====================================================================================================================
  //! @defgroup kpart kyosu::kpart
  //! @ingroup agnostic
  //! @brief Extracts the \f$k\f$  part of a value.
  //! @{
  //====================================================================================================================
  //!   @var kpart
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
  inline constexpr auto kpart = extractor<3>{};

  //! @}

  //====================================================================================================================
  //! @defgroup lpart kyosu::lpart
  //! @ingroup agnostic
  //! @brief Extracts the \f$l\f$  part of a value.
  //! @{
  //====================================================================================================================
  //!   @var lpart
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
  inline constexpr auto lpart = extractor<4>{};

  //! @}

  //====================================================================================================================
  //! @defgroup ilpart kyosu::ilpart
  //! @ingroup agnostic
  //! @brief Extracts the \f$il\f$ part of a value.
  //! @{
  //====================================================================================================================
  //!   @var ilpart
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
  //!     constexpr decltype(auto)  ilpart(concepts::cayley_dickson  auto&& v)  noexcept; // 1
  //!     constexpr auto            ilpart(concepts::quaternion      auto&& v)  noexcept; // 2
  //!     constexpr auto            ilpart(concepts::complex         auto&& v)  noexcept; // 2
  //!     constexpr auto            ilpart(concepts::real            auto&& v)  noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the \f$il\f$ part of `v`, the component
  //!      5 of an octonion.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/ilpart.cpp}
  //====================================================================================================================
  inline constexpr auto ilpart = extractor<5>{};

  //! @brief Deprecated name of kyosu::ilpart, which returns the same component.
  [[deprecated("lipart reads as the product li, the opposite of the component: use kyosu::ilpart")]]
  inline constexpr auto lipart = extractor<5>{};

  //! @}

  //====================================================================================================================
  //! @defgroup jlpart kyosu::jlpart
  //! @ingroup agnostic
  //! @brief Extracts the \f$jl\f$ part of a value.
  //! @{
  //====================================================================================================================
  //!   @var jlpart
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
  //!     constexpr decltype(auto)  jlpart(concepts::cayley_dickson  auto&& v)  noexcept; // 1
  //!     constexpr auto            jlpart(concepts::quaternion      auto&& v)  noexcept; // 2
  //!     constexpr auto            jlpart(concepts::complex         auto&& v)  noexcept; // 2
  //!     constexpr auto            jlpart(concepts::real            auto&& v)  noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the \f$jl\f$ part of `v`, the component
  //!      6 of an octonion.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/jlpart.cpp}
  //====================================================================================================================
  inline constexpr auto jlpart = extractor<6>{};

  //! @brief Deprecated name of kyosu::jlpart, which returns the same component.
  [[deprecated("ljpart reads as the product lj, the opposite of the component: use kyosu::jlpart")]]
  inline constexpr auto ljpart = extractor<6>{};

  //! @}

  //====================================================================================================================
  //! @defgroup klpart kyosu::klpart
  //! @ingroup agnostic
  //! @brief Extracts the \f$kl\f$ part of a value.
  //! @{
  //====================================================================================================================
  //!   @var klpart
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
  //!     constexpr decltype(auto)  klpart(concepts::cayley_dickson  auto&& v)  noexcept; // 1
  //!     constexpr auto            klpart(concepts::quaternion      auto&& v)  noexcept; // 2
  //!     constexpr auto            klpart(concepts::complex         auto&& v)  noexcept; // 2
  //!     constexpr auto            klpart(concepts::real            auto&& v)  noexcept; // 2
  //!   }
  //!   @endcode
  //!
  //!   **Parameters**
  //!
  //!   * `v`: Original value.
  //!
  //!   **Return value**
  //!
  //!   1. Returns a properly const-qualified reference to the \f$kl\f$ part of `v`, the component
  //!      7 of an octonion.
  //!   2. Returns `T{0}`.
  //!
  //!  @groupheader{Example}
  //!
  //!  @godbolt{doc/klpart.cpp}
  //====================================================================================================================
  inline constexpr auto klpart = extractor<7>{};

  //! @brief Deprecated name of kyosu::klpart, which returns the same component.
  [[deprecated("lkpart reads as the product lk, the opposite of the component: use kyosu::klpart")]]
  inline constexpr auto lkpart = extractor<7>{};

  //! @}
}
