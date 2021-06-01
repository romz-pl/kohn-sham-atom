#ifndef RATOM_CLPMTX_H
#define RATOM_CLPMTX_H

//
// Wrapper for the rectangular matrix from LAPACK library
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//


#include <cstddef>
#include <vector>


class ClpMtx
{
public:
    ClpMtx();
    ClpMtx( size_t rowNo, size_t colNo );
    ~ClpMtx() = default;

    void Assign( size_t rowNo, size_t colNo, double val );

    double Get( size_t row, size_t col ) const;
    double& Set( size_t row, size_t col );

    size_t ColNo() const { return m_colNo; }
    size_t RowNo() const { return m_rowNo; }

    void Dgesv( const std::vector< double >& b, std::vector< double >& x );
    void Dsysv( const std::vector< double >& b, std::vector< double >& x );

    void Write( const char* path, bool rowId = true ) const;

    double* Head( );

private:
    size_t Elt( size_t row, size_t col ) const;

private:
    // Number of columns
    size_t m_colNo;

    // Number of rows
    size_t m_rowNo;

    // Array with data
    std::vector< double > m_array;
};

#endif

