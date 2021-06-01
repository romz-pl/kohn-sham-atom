#include <cassert>
#include <cstdio>
#include <stdexcept>
#include "clpmtxband.h"


extern "C"
{
void dsbevx_(char *jobz, char *range, char *uplo, int *n,
    int *kd, double *ab, int *ldab, double *q, int *
    ldq, double *vl, double *vu, int *il, int *iu,
    double *abstol, int *m, double *w, double *z__,
    int *ldz, double *work, int *iwork, int *ifail,
    int *info);

void dsbgvx_(char *jobz, char *range, char *uplo, int *n,
    int *ka, int *kb, double *ab, int *ldab, double *
    bb, int *ldbb, double *q, int *ldq, double *vl,
    double *vu, int *il, int *iu, double *abstol, int
    *m, double *w, double *z__, int *ldz, double *work,
    int *iwork, int *ifail, int *info);

void dpbsvx_(char *fact, char *uplo, int *n, int *kd,
    int *nrhs, double *ab, int *ldab, double *afb,
    int *ldafb, char *equed, double *s, double *b, int *
    ldb, double *x, int *ldx, double *rcond, double *ferr,
     double *berr, double *work, int *iwork, int *info);
}


//
// Default Constructor
//
ClpMtxBand::ClpMtxBand( )
    : m_zero( 0 )
{
    m_kl = 0;
    m_ku = 0;
}

//
// Constructor
// n - number of columns
// kl - number of subdiagonals
// ku - number of superdiagonals
//
ClpMtxBand::ClpMtxBand( size_t n, size_t ku, size_t kl )
    : m_zero( 0 )
{
    Assign( n, ku, kl, 0 );
}

void ClpMtxBand::Assign( size_t n, size_t ku, size_t kl, double val )
{
    m_mtx.Assign( kl + ku + 1, n, val );
    m_kl = kl;
    m_ku = ku;
}


//
// Returns element (row, col)
//
double ClpMtxBand::Get( size_t row, size_t col ) const
{
    if( InBand( row, col ) )
    {
        return m_mtx.Get( RowEx( row, col ), col );
    }

    return 0;
}

//
// Sets value of element (row, col)
//
double& ClpMtxBand::Set( size_t row, size_t col )
{
    if( InBand( row, col ) )
    {
        return m_mtx.Set( RowEx( row, col ), col );
    }

    return m_zero;
}


//
// Returns row id in rectangular matrix "m_mtx"
// for element (row, col) in band matrix "this"
//
size_t ClpMtxBand::RowEx( size_t row, size_t col ) const
{
    return m_ku + row - col;
}

//
// Returns "true", if element (row, col) belongs to band matrix "this"
//
bool ClpMtxBand::InBand( size_t row, size_t col ) const
{
    const bool b1 = ( col <= row + m_ku );
    const bool b2 = ( row <= col + m_kl );

    return ( b1 && b2 );
}

//
// returns number of columns in matrix
//
size_t ClpMtxBand::ColNo() const
{
    return m_mtx.ColNo();
}


//
// WRAPPER for "dsbevx" procedure from LAPACK
//
// Calculates a few the lowest eigenvalues and theis eigenvectors for following eigenproblem:
//
//		A x = \lambda x
//
//  where the matrix A is banded and symmetric.
// The matrix A is given as upper triangle and has $N$ columns.
//
// eigNo  - [IN] number of eigenvalues to be calculated
// abstol - [IN] The absolute error tolerance for the eigenvalues.
// w  - [OUT] vector of calculated eigenvalues. It must be of size $N$.
// z -  [OUT] vector of calculated eigenvectors. It must be of size $N x N$.
//
void ClpMtxBand::Eigen( size_t eigNo, double abstol, std::vector< double >& w, ClpMtx& z )
{
    int m;
    int n = static_cast< int >( m_mtx.ColNo() );

    // The leading dimension of the array Z.
    // LDZ >= 1, and if JOBZ = 'V', LDZ >= max(1,N).
    int ldz = n;

    // The leading dimension of the array Q.
    // If JOBZ = 'N', LDQ >= 1. If JOBZ = 'V', LDQ >= max(1,N)
    int ldq = n;

    int ku = static_cast< int >( m_ku );

    // The leading dimension of the array AB.  LDAB >= KA+1.
    int ldab = ku + 1;

    // If RANGE='I', the indice of the smallest eigenvalues to be returned.
    int il = 1;

    int iu = static_cast< int >( eigNo );

    // Not referenced if RANGE = 'A' or 'I'.
    double vl = 0, vu = 0;

    // Compute eigenvalues and eigenvectors
    char jobz = 'V';

    // the IL-th through IU-th eigenvalues will be found
    char range = 'I';

    // Upper triangles of A and B are stored;
    char uplo = 'U';

    std::vector< double > q, work;
    std::vector< int > iwork, ifail;
    int info;


    // Only upper diagonal is defined
    assert( m_kl == 0 );

    q.resize( n * n );
    work.resize( 7 * n );
    iwork.resize( 5 * n );
    ifail.resize( n );

    dsbevx_(&jobz, &range, &uplo, &n, &ku, m_mtx.Head(), &ldab, &q.front(), &ldq,
        &vl, &vu, &il, &iu, &abstol, &m,
        &w.front(),
        z.Head(), &ldz, &work.front(), &iwork.front(), &ifail.front(), &info);


    if( info != 0 )
    {
        throw std::runtime_error( "Error in 'ClpMtxBand::EigenGen'" );
    }

}

//
// WRAPPER for "dsbgvx" procedure from LAPACK
//
// Calculates a few the smallest eigenvalues and eigenvectors for generalized eigenvalue problem
//
//		A x = \lambda B x
//
//      where A, B are banded, symmetric and B is positive definite.
// matrices A, B are given as upper triangles
//
// eigNo  - [IN] number of the calculated smallest eigenvalues
// abstol - [IN] The absolute error tolerance for the eigenvalues.
// w - [OUT] vector of calculated einevalues. MUST be of size $N$.
// z - [OUT] vector of calculated eigenvectors. MUST be of size  $N x N$.
// b - [IN]  matrix B, banded, symetric, positive definite
//
void ClpMtxBand::EigenGen( size_t eigNo, double abstol, std::vector< double > &w, ClpMtx& z, ClpMtxBand& b )
{
    int m;

    int n = static_cast< int >( m_mtx.ColNo() );

    // The leading dimension of the array Z.
    // LDZ >= 1, and if JOBZ = 'V', LDZ >= max(1,N).
    int ldz = n;

    // The leading dimension of the array Q.
    // If JOBZ = 'N', LDQ >= 1. If JOBZ = 'V', LDQ >= max(1,N).
    int ldq = n;

    int ka = static_cast< int >( m_ku );

    // The leading dimension of the array AB.  LDAB >= KA+1.
    int ldab = ka + 1;

    int kb = static_cast< int >( b.m_ku );

    // The leading dimension of the array BB.  LDBB >= KB+1.
    int ldbb = kb + 1;

    // If RANGE='I', the indice of the smallest eigenvalues to be returned.
    int il = 1;

    // Not referenced if RANGE = 'A' or 'I'.
    double vl = 0, vu = 0;

    int iu = static_cast< int >( eigNo );

    // Compute eigenvalues and eigenvectors
    char jobz = 'V';

    // the IL-th through IU-th eigenvalues will be found
    char range = 'I';

    // Upper triangles of A and B are stored;
    char uplo = 'U';

    std::vector< double > q, work;
    std::vector< int > iwork, ifail;
    int info;

    // Only "upper triangular" is defined
    assert( m_kl == 0 );


    q.resize( n * n );
    work.resize( 7 * n );
    iwork.resize( 5 * n );
    ifail.resize( iu );

    dsbgvx_(&jobz, &range, &uplo, &n, &ka, &kb, m_mtx.Head(), &ldab,
        b.m_mtx.Head(), &ldbb, &q.front(), &ldq, &vl,
        &vu, &il, &iu, &abstol, &m,
        &w.front(),
        z.Head(), &ldz, &work.front(), &iwork.front(), &ifail.front(), &info);

    if( info != 0 )
    {
        throw std::runtime_error( "Error in 'ClpMtxBand::EigenGen'" );
    }
}

//
// WRAPPER for "dpbsvx" procedure from LAPACK
//
// It solves the set of linear equations:
//		A x = b
// $A$ is symmetric, positive definite.
// $A$ is stored as upper triangular.
//
void ClpMtxBand::SolveSymPos( const std::vector< double >& b, std::vector< double >& x )
{
    char fact = 'N';  // The matrix A will be copied to AFB and factored.
    char equed = 'N'; // Specifies the form of equilibration that was done.
    char uplo = 'U';  // Upper triangles of A and B are stored;

    int nrhs = 1; // The number of right-hand sides
    int info;

    int n = static_cast< int >( m_mtx.ColNo() );
    int ldb = n; // The leading dimension of the array B
    int ldx = n; // The leading dimension of the array X

    int kd = static_cast< int >( m_ku );
    int ldab = kd + 1; // The leading dimension of the array AB.  LDAB >= KA+1.
    int ldafb = kd + 1; // The leading dimension of the array AFB.

    double rcond; // The estimate of the reciprocal condition number
    double ferr[1]; // The estimated forward error bound
    double berr[1]; // The componentwise relative backward error

    std::vector< double > afb, work;
    std::vector< int > iwork;

    // Only "upper triangular" is defined
    assert( m_kl == 0 );


    afb.resize( ldafb * n );
    work.resize( 3 * n );
    iwork.resize( n );

    dpbsvx_(&fact, &uplo, &n, &kd,
        &nrhs, m_mtx.Head(), &ldab, &afb.front(), &ldafb,
        &equed, NULL,
        (double*)(&b.front()),
        &ldb,
        &x.front(),
        &ldx,
        &rcond, ferr, berr, &work.front(), &iwork.front(),
        &info);


    if( info != 0 )
    {
        throw std::runtime_error( "Error in 'ClpMtxBand::Solve'" );
    }
}


//
// Writes matrix into file "path"
//
void ClpMtxBand::Write(const char* path) const
{
FILE* out;
size_t kl, row, ku;

    out = fopen(path, "wt");
    fprintf(out, "DIAGONAL\n");
    for(row = 0; row < ColNo(); row++)
        fprintf(out, "%4lu %lf\n", static_cast<unsigned long>(row), Get(row, row));

    // Subdiagonals
    for(kl = 1; kl <= m_kl; kl++)
    {
        fprintf(out, "SUB-DIAGONAL %lu\n", static_cast<unsigned long>(kl));
        for(row = kl; row < ColNo(); row++)
            fprintf(out, "%4lu %lf\n", static_cast<unsigned long>(row), Get(row, row - kl));
    }

    // Superdiagonals
    for(ku = 1; ku <= m_ku; ku++)
    {
        fprintf(out, "SUPER-DIAGONAL %lu\n", static_cast<unsigned long>(ku));
        for(row = 0; row < ColNo(); row++)
        {
            if(row + ku < ColNo())
                fprintf(out, "%4lu %lf\n", static_cast<unsigned long>(row), Get(row, row + ku));
        }
    }

    fclose(out);
}



