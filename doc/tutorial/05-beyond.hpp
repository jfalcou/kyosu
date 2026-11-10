#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-beyond Octonions and higher algebras
//!
//! An [octonion](https://en.wikipedia.org/wiki/Octonion) is a number with eight real components,
//! whose product extends the quaternion product and is no longer associative. A
//! [sedenion](https://en.wikipedia.org/wiki/Sedenion) has sixteen components, and its product has
//! [zero divisors](https://en.wikipedia.org/wiki/Sedenion#Zero_divisors). In the
//! @ref math_background "Cayley-Dickson construction" each is a pair of values of the previous
//! algebra, in a sequence without end. **KYOSU** represents every dimension by
//! `kyosu::as_cayley_dickson_n_t<N, T>`, and the octonions by `kyosu::octonion_t<T>`.
//!
//! # Octonions
//!
//! An octonion, `kyosu::octonion_t<T>`, has eight components on the basis
//! \f$1, i, j, k, l, il, jl, kl\f$, and is built from them:
//!
//! @godbolt{doc/tut_beyond_types.cpp}
//!
//! The conjugate negates the seven imaginary components.
//!
//! # Higher algebras
//!
//! Only the basis elements up to dimension 8 have a letter. The type is
//! `kyosu::as_cayley_dickson_n_t<N, T>` with `N` the dimension. A component is read and written
//! through `kyosu::get<I>`. A value prints each component followed by its label, \f$z_0\f$ to
//! \f$z_{N-1}\f$:
//!
//! @godbolt{doc/tut_beyond_higher.cpp}
//!
//! The @ref agnostic "algebra-agnostic functions" apply in every dimension, `kyosu::exp` among
//! them.
//!
//! # Associativity
//!
//! From dimension 8, \f$(ab)c\f$ and \f$a(bc)\f$ differ for some triples. On the basis elements
//! \f$i\f$, \f$j\f$, and \f$l\f$, the two products are opposite, \f$(ij)l = -i(jl)\f$.
//!
//! `kyosu::associator` computes the [associator](https://en.wikipedia.org/wiki/Associator)
//! \f$(ab)c - a(bc)\f$. It is zero on the quaternions and below, which are associative. The
//! octonions are an
//! [alternative algebra](https://en.wikipedia.org/wiki/Alternative_algebra#The_associator), whose
//! associator is zero when two operands coincide or when the three lie in a quaternion
//! subalgebra:
//!
//! @godbolt{doc/tut_beyond_associativity.cpp}
//!
//! @warning An expression is evaluated with its parentheses as written and never re-associated:
//! moving a parenthesis changes the result.
//!
//! # Elementary functions
//!
//! In every dimension, an element \f$c\f$ with a nonzero pure part generates with \f$1\f$ a
//! subalgebra isomorphic to \f$\mathbb{C}\f$, as the @ref math_background "mathematics page"
//! shows. The powers, the exponential, the logarithm, and the functions built on them are
//! therefore defined on every algebra:
//!
//! @godbolt{doc/tut_beyond_functions.cpp}
//!
//! <div class="section_buttons">
//!
//! | Previous                                |                                Next |
//! |:----------------------------------------|------------------------------------:|
//! | [Quaternions](@ref tutorial-quaternion) | [Rotations](@ref tutorial-rotation) |
//!
//! </div>
