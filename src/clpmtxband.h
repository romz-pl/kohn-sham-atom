#ifndef RATOM_CLPMTXBAND_H
#define RATOM_CLPMTXBAND_H

//
// Wrapper for band matrix from LAPACK library
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//


#include "clpmtx.h"


class ClpMtxBand
{
public:
    ClpMtxBand();
    ClpMtxBand( size_t n, size_t ku, size_t kl );
    ~ClpMtxBand( ) = default;

    void Assign( size_t n, size_t ku, size_t kl, double val );

    double Get( size_t row, size_t col ) const;
    double& Set( size_t row, size_t col );

    void Eigen( size_t eigNo, double abstol, std::vector< double >& w, ClpMtx& z );
    void EigenGen( size_t eigNo, double abstol, std::vector< double >& w, ClpMtx& z, ClpMtxBand& b );

    void SolveSymPos( const std::vector< double >& b, std::vector< double >& x );

    size_t ColNo() const;


    void Write(const char* path) const;

private:
    size_t RowEx( size_t row, size_t col ) const;
    bool InBand( size_t row, size_t col ) const;

private:
    // Reactangular matrix used for string the band matrix
    ClpMtx m_mtx;

     // kl - number of subdiagonals
    size_t m_kl;

     // ku - number of superdiagonals
    size_t m_ku;

    // Auxiliary mememer, works as "zero".
    double m_zero;
};

#endif

