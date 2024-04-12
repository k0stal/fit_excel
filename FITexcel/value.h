#ifndef VALUE_H
#define VALUE_H

#include <cmath>
#include <string>

using namespace std::literals;
using CValue = std::variant<std::monostate, double, std::string>;

CValue operator + ( const CValue & a, const CValue & b );
CValue operator - ( const CValue & a, const CValue & b );
CValue operator - ( const CValue & a );
CValue operator * ( const CValue & a, const CValue & b );
CValue operator / ( const CValue & a, const CValue & b );
CValue operator ^ ( const CValue & base, const CValue & exponent );
CValue operator < ( const CValue & a, const CValue & b );
CValue operator > ( const CValue & a, const CValue & b );
CValue operator == ( const CValue & a, const CValue & b );
CValue operator != ( const CValue & a, const CValue & b );
CValue operator <= ( const CValue & a, const CValue & b );
CValue operator >= ( const CValue & a, const CValue & b );

#endif // VALUE_H

