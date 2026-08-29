#error This file is for documentation only - DO NOT INCLUDE
//! @page tutorial-rotation Rotations
//!
//! Quaternions are not a curiosity kept alive by mathematicians. They are the standard way to
//! represent rotations in three dimensions in graphics, robotics and aerospace, and the reason is
//! practical rather than elegant. This page is about that use, and it needs nothing from the
//! previous page beyond knowing that a quaternion has four components and does not commute.
//!
//! # Why not Euler angles
//!
//! Three angles around three axes are the obvious representation and they have two well-known
//! faults. They suffer *gimbal lock*: at certain orientations two of the three axes align and a
//! degree of freedom is lost. And interpolating between two sets of angles does not produce a
//! natural motion, because the angles are not independent of one another.
//!
//! A unit quaternion has neither problem. It covers every orientation without a singularity, it
//! composes by multiplication, and — the point of this page — two of them can be interpolated
//! along the shortest arc.
//!
//! # Rotating a vector
//!
//! Build the rotation from an angle and an axis, then apply it. The vector is an ordinary array of
//! three reals, handed over as a `std::span`:
//!
//! @godbolt{doc/tut_rot_apply.cpp}
//!
//! `kyosu::from_angle_axis` normalises the axis for you. If you know it is already a unit vector,
//! `[kyosu::assume_unitary]` skips that work.
//!
//! # Composing rotations
//!
//! Applying \f$p\f$ then \f$q\f$ is the single rotation \f$qp\f$ — in that order, because the
//! product does not commute. This is where the previous page pays off: getting the order wrong is
//! the classic bug, and the algebra is what tells you which order is right.
//!
//! @godbolt{doc/tut_rot_compose.cpp}
//!
//! # Interpolating between orientations
//!
//! kyosu::slerp — *spherical linear interpolation* — walks from one orientation to another along
//! the shortest arc, at constant angular speed. It is what makes quaternions worth the change of
//! representation in an animation or a trajectory:
//!
//! @godbolt{doc/tut_rot_slerp.cpp}
//!
//! # Converting to and from other representations
//!
//! You rarely control every piece of a pipeline, so the conversions are provided in both
//! directions: kyosu::to_rotation_matrix and kyosu::from_rotation_matrix,
//! kyosu::to_euler and kyosu::from_euler, kyosu::to_angle_axis and kyosu::from_angle_axis.
//!
//! @godbolt{doc/tut_rot_convert.cpp}
//!
//! One subtlety worth knowing: \f$q\f$ and \f$-q\f$ describe the *same* rotation. The
//! representation is a double cover of the rotations, so a round trip through a matrix or a set of
//! angles may hand you back the other of the two. Compare rotations by their effect, not by their
//! components.
//!
//! <div class="section_buttons">
//!
//! | Previous                                  |                                Next |
//! |:------------------------------------------|------------------------------------:|
//! | [Quaternions](@ref tutorial-quaternion)   | [Options](@ref tutorial-options)    |
//!
//! </div>
