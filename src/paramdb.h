#ifndef RATOM_PARAMDB_H
#define RATOM_PARAMDB_H


//
// Database of input parameters.
//
// The database is represented as a hash table of pairs.
// The first element of pair is "parameter". The second element of pair is "parameter's value".
// Both, parameter and value are strings.
// The conversion from string into required type is done after parsing and reading from file.
// Hence, the user of this database must know the type of the parameter.
//
// Zbigniew Romanowski [ROMZ@wp.pl]
//
//


#include <cstddef>
#include <string>
#include <map>

class ParamDb
{
public:
    ParamDb( const std::string& path );
    ~ParamDb( );


    static std::string GetString( const std::string& param );
    static size_t      GetSize_t( const std::string& param );
    static double      GetDouble( const std::string& param );
    static long int    GetLong  ( const std::string& param );
    static bool        GetBool  ( const std::string& param );

private:
    static void ReadParams( const std::string& path );
    static void WriteParams();
    static bool ReadOneParam( std::ifstream &in, std::string &param, std::string &val );

private:

    static std::map< std::string, std::string > m_map;

};

#endif

