#include "position.h"

CPos::CPos ( std::string_view str ) {}

CPos & CPos::copy ( const CPos & pos ) const {}

bool CPos::operator < ( CPos & pos ) const {}

std::ostream & operator << ( std::ostream os, CPos & pos ) {}