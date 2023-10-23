//======================================================================================================================
/*
  Kyosu - Complex Without Complexes
  Copyright : KYOSU Contributors & Maintainers
  SPDX-License-Identifier: BSL-1.0
*/
//======================================================================================================================
#pragma once
#include <eve/module/core.hpp>
#include <eve/module/math.hpp>
#include <eve/module/special.hpp>
#include <kyosu/details/cayleyify.hpp>
#include <complex>

#include <kyosu/types/impl/detail/besselj0.hpp>
#include <kyosu/types/impl/detail/besselj1.hpp>
#include <kyosu/types/impl/detail/besseljn.hpp>
#include <kyosu/types/impl/detail/besseli0.hpp>
#include <kyosu/types/impl/detail/besseli1.hpp>
#include <kyosu/types/impl/detail/besselin.hpp>


//////////////////////////////////////////////////////////////////////////////////////////////////
//! This simd implementation of the cylindrical jn functions is inspired from
//! The codes and routines were developed and are updated by
//! <a href="https://www.researchgate.net/profile/Jhonas-de-Sarro">Jhonas O. de Sarro</a> ([@jodesarro]( https://github.com/jodesarro )).
//!
//! We repruce here the copyrith notice
//!
//!MIT License
//!
//!Copyright (c) 2021 Jhonas Olivati de Sarro
//!
//!Permission is hereby granted, free of charge, to any person obtaining a copy
//!of this software and associated documentation files (the "Software"), to deal
//!in the Software without restriction, including without limitation the rights
//!to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//!copies of the Software, and to permit persons to whom the Software is
//!furnished to do so, subject to the following conditions:
//!
//!The above copyright notice and this permission notice shall be included in all
//!copies or substantial portions of the Software.
//!
//!THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//!IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//!FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//!AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//!LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//!OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
//!SOFTWARE.
//!
//////////////////////////////////////////////////////////////////////////////////////////////////
