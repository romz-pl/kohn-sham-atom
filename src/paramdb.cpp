#include "paramdb.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>

std::map< std::string, std::string > ParamDb::m_map;


//
// Constructor
//
ParamDb::ParamDb( const std::string& path )
{
    ReadParams( path );
    // WriteParams();
}

//
// Destructor
//
ParamDb::~ParamDb()
{
}

//
// Returns value of parameter "param"
//
std::string ParamDb::GetString( const std::string& param )
{
    std::map< std::string, std::string >::const_iterator iter = m_map.find( param );


    if( iter == m_map.end() )
    {
        const std::string str = "Parametr could not be found. Param = " + param;
        throw std::invalid_argument( str );
    }

    const std::string ret = iter->second;
    return ret;
}

//
// Returns size_t
//
size_t ParamDb::GetSize_t( const std::string& param )
{
    return static_cast< size_t >( GetLong( param ) );
}

//
// Returns double
//
double ParamDb::GetDouble( const std::string& param )
{
    return std::stod( GetString( param ) );
}

//
// Return long int
//
long int ParamDb::GetLong( const std::string& param )
{
    return std::stol( GetString( param ) );
}

//
// Returns bool
//
bool ParamDb::GetBool( const std::string& param )
{
    return ( GetString( param ) == "Yes" );
}




//
// Reads input parameters form file
//
void ParamDb::ReadParams( const std::string& path )
{
    std::string param, val;

    std::ifstream in( path, std::ios::in );
    if( !in )
    {
        const std::string str = "Cannot open file. Path = " + path;
        throw std::invalid_argument( str );
    }

    while( ReadOneParam( in, param, val ) )
    {
         m_map.insert( std::pair< std::string, std::string >( param, val ) );
    }

}

//
// Reads one parameter from file.
// Returns "true", if parameter is read.
// Returns "false", if end of file is found.
//
bool ParamDb::ReadOneParam( std::ifstream& in, std::string& param, std::string& val )
{

    std::string line;

    while( true )
    {
        std::getline( in, line );

        if( in.eof() )
        {
            return false;
        }

        if( line.empty() ) // Skip empty line
        {
            continue;
        }
        else if( std::all_of(line.begin(), line.end(), isspace) ) // Skip line with only whitespaces
        {
            continue;
        }
        else if( line[0] != '#' ) // If this line is not the comment
        {
            break;
        }
    }

    param.clear();
    val.clear();
    std::stringstream( line ) >> param >> val;

    if( param.empty() || val.empty() )
    {
        const std::string str = "Error during reading file. Line = " + line;
        throw std::invalid_argument( str );
    }

    return true;
}

//
// Writes input parameters and its values to standard output
// For dubuging purposes.
//
void ParamDb::WriteParams( )
{
    std::map< std::string, std::string >::const_iterator i;

    for( i = m_map.begin(); i != m_map.end(); ++i )
    {
        std::cout << i->first << "  " << i->second << std::endl;
    }
}
