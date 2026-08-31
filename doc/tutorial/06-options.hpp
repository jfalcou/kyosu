#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-options Options
//!
//! You have already used one option, `kyosu::real_only`, without much explanation. This page
//! collects the mechanism and the options worth knowing early.
//!
//! # The mechanism
//!
//! A function is followed by square brackets naming a behaviour:
//!
//! @code
//! kyosu::sqrt[kyosu::real_only](-1.0)
//! @endcode
//!
//! This is not a call. `kyosu::sqrt[opt]` produces a *new callable* that behaves differently, and
//! that callable is then applied. The consequence is that options compose, and that no function
//! name has to be invented for each combination — there is no `sqrt_raw_real_only`.
//!
//! Options are inherited from EVE and behave identically there, so anything learnt here transfers.
//!
//! # Accuracy against speed
//!
//! By default a function is as accurate as possible over its whole domain and guards its edges. `raw`
//! asks for the fastest formula instead, and the price is paid in two places at once: the answer
//! loses accuracy on ordinary input, and the edges stop being handled.
//!
//! The example below shows both on `kyosu::log`. The argument differs in the third decimal on a
//! perfectly well-behaved value, and at the origin the guarded version still names an imaginary
//! part where the raw one produces a NaN. `raw` is for the inner loop a profiler pointed at, not
//! a default.
//!
//! @godbolt{doc/tut_opt_raw.cpp}
//!
//! # Angles in half-turns
//!
//! Trigonometry in radians forces \f$\pi\f$ into the arithmetic, and \f$\pi\f$ is not exactly representable
//! as an *IEEE* floating number.
//! `kyosu::radpi` reads and returns angles as multiples of \f$\pi\f$ instead, which removes that
//! error at the source. Where a plain call needs `pi/2`, the option form takes `0.5`:
//!
//! @godbolt{doc/tut_opt_radpi.cpp}
//!
//! # Real answers
//!
//! Met on the first page: `kyosu::real_only` asks for the real function and its NaN rather than
//! for a complex answer.
//!
//! @godbolt{doc/tut_opt_real_only.cpp}
//!
//! # Skipping a normalisation
//!
//! The rotation functions normalise their argument, since a rotation must be a unit quaternion.
//! When you already know it is one, `kyosu::assume_unitary` skips the work. It is a promise, not a
//! request: pass a quaternion that is not unitary and the answer is simply wrong.
//!
//! @godbolt{doc/tut_opt_assume_unitary.cpp}
//!
//! <div class="section_buttons">
//!
//! | Previous                            |                                              Next |
//! |:------------------------------------|--------------------------------------------------:|
//! | [Rotations](@ref tutorial-rotation) | [Mathematical background]( @ref math_background)  |
//!
//! </div>
