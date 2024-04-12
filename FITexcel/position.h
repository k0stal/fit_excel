#ifndef POS_H
#define POS_H

#include <string>
#include <vector>
#include <iostream>

class CPos
{
  public:
        CPos ( std::string_view str );
        CPos & copy ( const CPos & pos ) const;  // reffrence might not work, stack
        bool operator < ( CPos & pos ) const;
        friend std::vector<CPos> & rectItertion ( const CPos & start, const CPos & end );
        friend std::ostream & operator << ( std::ostream & os, const CPos & pos );
  private:
        std::pair<int, int> pos;
        std::pair<bool, bool> fixed;
};

#endif // POS_H