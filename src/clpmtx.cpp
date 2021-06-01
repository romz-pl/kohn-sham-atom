#include "clpmtx.h"
#include <cassert>
#include <stdexcept>
#include <cstdio>

//
// From LAPACK library
//
extern "C"
{
    int dgesv_(int *n, int *nrhs, double *a, int *lda,
         int *ipiv, double *b, int *ldb, int *info);

    int dsysv_(char *uplo, int *n, int *nrhs, double *a,
    int *lda, int *ipiv, double *b, int *ldb,
        double *work, int *lwork, int *info);
}


//
// Default Constructor
//
ClpMtx::ClpMtx( )
{
    m_rowNo = 0;
    m_colNo = 0;
}

//
// Constructor
// rowNo - number of rows
// colNo - number of columns
//
ClpMtx::ClpMtx( size_t rowNo, size_t colNo )
{
    Assign( rowNo, colNo, 0 );
}

//
// Defines new size of the matrix.
// Previous date are destoyed.
// rowNo - new number of rows
// colNo - mew number of columns
//
void ClpMtx::Assign( size_t rowNo, size_t colNo, double val )
{
    m_rowNo = rowNo;
    m_colNo = colNo;
    m_array.assign( rowNo * colNo, val );
}

//
// Returns matrix element (row, col)
//
double ClpMtx::Get( size_t row, size_t col ) const
{
    return m_array[ Elt( row, col ) ];
}

//
// Sets value of matrix element (row, col)
//
double& ClpMtx::Set( size_t row, size_t col )
{
    return m_array[ Elt( row, col ) ];
}

//
// Returns index ath the "m_array"
//
size_t ClpMtx::Elt( size_t row, size_t col ) const
{
    assert( row < m_rowNo );
    assert( col < m_colNo );

    return col * m_rowNo + row;
}

//
// Returns pointer to the begining (head) of the matrix
//
double* ClpMtx::Head( )
{
    return &m_array.front();
}

//
// Solves set of linear equations
//	(*)	A x = b
// Matrix A must be squared
//
// b - [IN/OUT] right hand side of equation (*).
// The size of vector b must be equal to the number of columns (rows) of matric A.
// On return vector b holds the solution.
//
void ClpMtx::Dgesv( const std::vector< double > &b, std::vector< double > &x )
{
    int n = static_cast< int >( m_colNo );
    int nrhs = 1;
    int lda = n;
    std::vector< int > ipiv;
    int ldb = n;
    int info, ret;

    assert( m_colNo == m_rowNo );

    // Copying. Solution is returned in vector "x".
    x = b;

    ipiv.resize( n );
    ret = dgesv_( &n, &nrhs, Head(), &lda, &ipiv.front(), &x.front(), &ldb, &info );

    if( ret != 0 || info != 0 )
        throw std::runtime_error( "Error in 'ClpMtx::Solve'" );

}

//  DSYSV computes the solution to a real system of linear equations
//      A * X = B,
//  where A is an N-by-N symmetric matrix and X and B are vectors.
//  Matrix A must be upper triangular matrix
//
void ClpMtx::Dsysv( const std::vector< double > &b, std::vector< double > &x )
{
    // Upper triangle of A is stored
    char uplo = 'U';

    // The number of linear equations, i.e., the order of the matrix A
    int n = static_cast< int >( m_colNo );

    int nrhs = 1;
    int lda = n;
    int ldb = n;

    std::vector< int > ipiv;
    std::vector< double > work;
    double tmp[ 2 ];
    int lwork;
    int info, ret;

    // Copying. Solution is returned in vector "x".
    x = b;


    // Query for required memory
    lwork = -1;
    dsysv_( &uplo, &n, &nrhs, Head(), &lda, NULL, &x.front(), &ldb, tmp, &lwork, &info );
    lwork = static_cast< int >( tmp[ 0 ] );

    work.resize( lwork );
    ipiv.resize( n );

    ret = dsysv_( &uplo, &n, &nrhs, Head(), &lda, &ipiv.front(), &x.front(), &ldb, &work.front(), &lwork, &info );


    if( ret != 0 || info != 0 )
        throw std::runtime_error( "Error in 'ClpMtx::Dsysv'" );
}



//
// Saves the matric into the file.
// For debuging purposes.
// path - path to the output file.
// rowId - flag determing the output format
//
void ClpMtx::Write(const char* path, bool rowId) const
{
FILE* out;
size_t row, col;

    out = fopen(path, "wt");
    for(row = 0; row < RowNo(); row++)
    {
        if(rowId)
            fprintf(out, "ROW=%2lu ", static_cast<unsigned long>(row));

        for(col = 0; col < ColNo(); col++)
            fprintf(out, "%15.6E", Get(row, col));
        fprintf(out, "\n");
    }

    fclose(out);
}



