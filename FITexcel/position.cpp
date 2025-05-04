#include "position.h"

CPos::CPos ():
    coo(0, 0),
    fixed(false, false) {}

CPos::CPos ( std::string_view str ):
    coo(0, 0),
    fixed(false, false) {
        
    if (str.empty())
        throw std::invalid_argument("Invalid cell identification.");

    auto it = str.begin();

    if (!std::isalpha(*it))
        throw std::invalid_argument("Invalid cell identification."); 

    for (; std::isalpha(*it); ++it)
        coo.first = coo.first * 26 + (std::tolower(*it) - 'a') + 1;

    if (!std::isdigit(*it)) {
        throw std::invalid_argument("Invalid cell identification.");
    }

    for (; std::isdigit(*it); ++it)
        coo.second = coo.second * 10 + (*it - '0');

    if (it != str.end()) {
        throw std::invalid_argument("Invalid cell identification.");
    }
}

CPos::CPos ( std::pair<int, int> coo, std::pair<int, int> fixed ):
    coo(coo),
    fixed(fixed) {}

CPos CPos::copy ( const std::pair<int, int> & delta ) const { 
    CPos res( *this );

    if ( !fixed.first )                        
        res.coo.first += delta.first;
    if ( !fixed.second )
        res.coo.second += delta.second;

    if ( res.coo.first < 1 || res.coo.second < 0 )
        throw std::invalid_argument("Invalid cell identification.");

    return res;
}

void CPos::addFixation ( std::pair<bool, bool> & fixation ) {
    this->fixed = fixation;
}

CPos & CPos::operator = ( const CPos & arg ) {
    if (*this == arg)
        return *this;
    
    this->coo = arg.coo;
    this->fixed = arg.fixed;
    return *this;
}

std::pair<int, int> CPos::operator - ( const CPos & arg ) {
    return std::make_pair( this->coo.first - arg.coo.first, this->coo.second - arg.coo.second);
}

bool CPos::operator < ( const CPos & arg ) const {
    if ( this->coo.first != arg.coo.first ) 
        return this->coo.first < arg.coo.first;
    else
        return this->coo.second < arg.coo.second;
}

bool CPos::operator == ( const CPos & arg ) const {
    return this->coo.first == arg.coo.first && this->coo.second == arg.coo.second;
}

void rectIterationSize ( std::vector<CPos> & res, const CPos & start, int w, int h ) {
    for ( int i = 0; i < w; i++ )
        for ( int j = 0; j < h; j++ )
            res . push_back( CPos( std::make_pair(start.coo.first + i, start.coo.second + j),
                                   std::make_pair(false, false)) );

}

void CPos::getCellName (std::string & name) const {
    std::string col = "";
    int colNum = coo.first; 

    if ( fixed.first )
        name += "$";

    while ( colNum >= 0 ) {            
        int modulo = (colNum - 1) % 26;
        char c = 'A' + modulo;
        col = c + col;
        colNum = (colNum - modulo) / 26;
        if ( !colNum )
            break;
    } 

    name += col;

    if ( fixed.second )
        name += "$";
    name += std::to_string(coo.second);
}

std::ostream & operator << ( std::ostream & os, const CPos & pos ) {
    std::string name = "";
    pos.getCellName(name);
    os << name;
    return os;
}