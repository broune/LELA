/* lela/algorithms/faugere-lachartre.h
 * Copyright 2010 Bradford Hovinen
 *
 * Written by Bradford Hovinen <hovinen@math.uni-hannover.de>
 *
 * Implementation of algorithm for computing reduced row-echelon form
 * of a matrix coming from the F4-algorithm
 *
 * ------------------------------------
 * 
 * This file is part of LELA, licensed under the GNU General Public
 * License version 3. See COPYING for more information.
 */

#ifndef __LELA_ALGORITHMS_FAUGERE_LACHARTRE_H
#define __LELA_ALGORITHMS_FAUGERE_LACHARTRE_H

#include "lela/blas/context.h"
#include "lela/algorithms/gauss-jordan.h"
#include "lela/util/splicer.h"

namespace LELA
{

// Forward-declaration
template <class Ring, class Modules>
class EchelonForm;

/**
 * \brief Implementation of algorithm for computing reduced row-echelon form
 * of a matrix coming from the F4-algorithm
 *
 * The algorithm used is based loosely on the algorithm
 * described in J.C. Faugère's paper "Parallel Gaussian
 * Elimination for Gröbner bases computations in finite
 * fields", PASCO 2010.
 *
 * \ingroup algorithms
 */
template <class Ring, class Modules = AllModules<Ring> >
class FaugereLachartre {
	Context<Ring, Modules> &ctx;
	EchelonForm<Ring, Modules> EF;

	template <class Matrix>
	void setup_splicer (Splicer &splicer, Splicer &reconst_splicer, const Matrix &A, size_t &num_pivot_rows, typename Ring::Element &det) const;

public:
	/**
	 * \brief Construct a new FaugereLachartre
	 *
	 * @param _ctx Context-object for matrix-calculations
	 */
	FaugereLachartre (Context<Ring, Modules> &_ctx);

	/** 
	 * \brief Convert the matrix X into reduced
	 * row-echelon form
	 *
	 * The input matrix X must have jagged upper diagonal shape,
	 * which is to say that if a pivot appears in row r and column
	 * c, then all rows below r must be 0 in all columns before
	 * c. This is OK:
	 *
	 *  11111
	 *  00001
	 *  00001
	 *
	 * This is not OK:
	 *
	 *  11111
	 *  00001
	 *  00010
	 *
	 * To understand the function of option only_D, you need to
	 * know that the matrix is split into sub-matrices A, B, C and
	 * D in the shape
	 *
	 *   AB
	 *   CD
	 *
	 * where A is an upper-triangular matrix that is as large as
	 * possible. Rows and columns are permuted to achieve this,
	 * though the columns of the output are put back into the
	 * original order before the method returns. 
	 *
	 * @param R Matrix into which to store the reduced
	 * row-echelon form. Should have the same dimensions
	 * as A. May be the same matrix as A, in which case A
	 * is replaced by its reduced row-echelon form.
	 *
	 * @param X Matrix to be converted to row-echelon
	 * form. Not altered, unless R is the same matrix.
	 *
	 * @param rank Integer-reference into which to store
	 * computed rank
	 *
	 * @param det Ring-element-reference into which to
	 * store computed determinant of pivot-submatrix
	 *
	 * @param reduced Whether to compute the reduced
	 * row-echelon form (default true)
	 *
	 * @param only_D Whether to return only the rows of the lower
	 * block (default false). Here C will be zero and D will be
	 * the schur complement of A, which is D-C*inv(A)*B. Note that
	 * this is before the columns are permuted back to their
	 * original order.
	 */
	template <class Matrix>
	void echelonize (Matrix &R, const Matrix &X, size_t &rank, typename Ring::Element &det, bool reduced = true, bool only_D = false);
};

} // namespace LELA

#include "lela/algorithms/faugere-lachartre.tcc"

#endif // __LELA_ALGORITHMS_FAUGERE_LACHARTRE_H

// Local Variables:
// mode: C++
// tab-width: 8
// indent-tabs-mode: t
// c-basic-offset: 8
// End:

// vim:sts=8:sw=8:ts=8:noet:sr:cino=>s,f0,{0,g0,(0,\:0,t0,+0,=s:syntax=cpp.doxygen:foldmethod=syntax
