/* lela/blas/level3-sw.h
 * Copyright 2011 Bradford Hovinen <hovinen@gmail.com>
 *
 * BLAS-interface to Strassen-Winograd implementation
 * ------------------------------------
 *
 * See COPYING for license information.
 */

#ifndef __BLAS_LEVEL3_SW_H
#define __BLAS_LEVEL3_SW_H

#include "lela/blas/context.h"
#include "lela/blas/level3-ll.h"
#include "lela/algorithms/strassen-winograd.h"

namespace LELA
{

/** This namespace contains the level 3 BLAS interface */
namespace BLAS3
{

template <class Ring, class ParentModule>
class _gemm<Ring, StrassenModuleTag<Ring, ParentModule> >
{
public:
	template <class Modules, class Matrix1, class Matrix2, class Matrix3>
	static Matrix3 &op (const Ring &F, Modules &M, const typename Ring::Element &a, const Matrix1 &A, const Matrix2 &B, const typename Ring::Element &b, Matrix3 &C)
		{ return ((StrassenModule<Ring, ParentModule> &) M).sw.gemm (F, M, a, A, B, b, C); }
};

} // namespace BLAS3

} // namespace LELA

#endif // __BLAS_LEVEL3_SW_H

// Local Variables:
// mode: C++
// tab-width: 8
// indent-tabs-mode: t
// c-basic-offset: 8
// End:

// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s:syntax=cpp.doxygen:foldmethod=syntax
