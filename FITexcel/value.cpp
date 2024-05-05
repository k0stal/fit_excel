#include "value.h"

CValue operator + (const CValue & a, const CValue & b ) {
    if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b)) {
        return std::get<double>(a) + std::get<double>(b);
    } else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b)) {
        return std::get<std::string>(a) + std::get<std::string>(b);
    } else if (std::holds_alternative<double>(a) && std::holds_alternative<std::string>(b)){
        std::string strA = std::to_string(std::get<double>(a));
        strA.erase ( strA.find_last_not_of('0') + 1, std::string::npos );
        strA.erase ( strA.find_last_not_of('.') + 1, std::string::npos );
        return strA + b;
    } else if (std::holds_alternative<std::string>(a) && std::holds_alternative<double>(b)) {
        std::string strB = std::to_string(std::get<double>(b));
        strB.erase ( strB.find_last_not_of('0') + 1, std::string::npos );
        strB.erase ( strB.find_last_not_of('.') + 1, std::string::npos );
        return a + strB;
    } else
        return std::monostate{};
}

CValue operator - ( const CValue & a, const CValue & b ) {
    if ( std::holds_alternative<double>(a) && std::holds_alternative<double>(b) )
        return std::get<double>(a) - std::get<double>(b);
    else
        return std::monostate{};
}

CValue operator - ( const CValue & a ) {
    if ( std::holds_alternative<double>(a) )
        return -std::get<double>(a);
    else
        return std::monostate{};
}

CValue operator * ( const CValue & a, const CValue & b ) {
    if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b))
        return std::get<double>(a) * std::get<double>(b);
    else
        return std::monostate{};
}

CValue operator / ( const CValue & a, const CValue & b ) {
    if ( std::holds_alternative<double>(a) && std::holds_alternative<double>(b) ) {
        double divisor = std::get<double>(b);
        if (divisor == 0.0)
            return std::monostate{};
        else {
            double dividend = std::get<double>(a);
            return dividend / divisor;
        }
    } else
        return std::monostate{};
}

CValue operator ^ ( const CValue & a, const CValue & b ) {
    if (std::holds_alternative<double>(a) && std::holds_alternative<double>(b)) {
        double baseValue = std::get<double>(a);
        double exponentValue = std::get<double>(b);
        return std::pow(baseValue, exponentValue);
    } else 
        return std::monostate{};
}

CValue operator < ( const CValue & a, const CValue & b ) {
    if ( std::holds_alternative<double>(a) && std::holds_alternative<double>(b) )
        return std::get<double>(a) < std::get<double>(b) ? 1.0 : 0.0;
    else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b))
        return std::get<std::string>(a) < std::get<std::string>(b) ? 1.0 : 0.0;
    else
        return std::monostate{};
}

CValue operator > ( const CValue & a, const CValue & b ) {
    if ( std::holds_alternative<double>(a) && std::holds_alternative<double>(b) )
        return std::get<double>(a) > std::get<double>(b) ? 1.0 : 0.0;
    else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b))
        return std::get<std::string>(a) > std::get<std::string>(b) ? 1.0 : 0.0;
    else
        return std::monostate{};
}

CValue operator == ( const CValue & a, const CValue & b ) {
    if ( std::holds_alternative<double>(a) && std::holds_alternative<double>(b) )
        return std::get<double>(a) == std::get<double>(b) ? 1.0 : 0.0;
    else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b))
        return std::get<std::string>(a) == std::get<std::string>(b) ? 1.0 : 0.0;
    else
        return std::monostate{};
}

CValue operator != ( const CValue & a, const CValue & b ) {
    if ( std::holds_alternative<double>(a) && std::holds_alternative<double>(b) )
        return std::get<double>(a) != std::get<double>(b) ? 1.0 : 0.0;
    else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b))
        return std::get<std::string>(a) != std::get<std::string>(b) ? 1.0 : 0.0;
    else
        return std::monostate{};
}

CValue operator <= ( const CValue & a, const CValue & b ) {
    if ( std::holds_alternative<double>(a) && std::holds_alternative<double>(b) )
        return std::get<double>(a) <= std::get<double>(b) ? 1.0 : 0.0;
    else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b))
        return std::get<std::string>(a) <= std::get<std::string>(b) ? 1.0 : 0.0;
    else
        return std::monostate{};
}

CValue operator >= ( const CValue & a, const CValue & b ) {
    if ( std::holds_alternative<double>(a) && std::holds_alternative<double>(b) )
        return std::get<double>(a) >= std::get<double>(b) ? 1.0 : 0.0;
    else if (std::holds_alternative<std::string>(a) && std::holds_alternative<std::string>(b))
        return std::get<std::string>(a) >= std::get<std::string>(b) ? 1.0 : 0.0;
    else
        return std::monostate{};
}


