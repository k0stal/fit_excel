#ifndef POS_H
#define POS_H

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

class CPos
{
  public:
        CPos ();
        CPos ( std::string_view str );
        CPos ( std::pair<int, int> coo, std::pair<int, int> fixed );
        CPos copy ( const std::pair<int, int> & delta ) const;
        void addFixation ( std::pair<bool, bool> & fixation );
        CPos & operator = ( const CPos & arg );
        std::pair<int, int> operator - ( const CPos & arg);
        bool operator < ( const CPos & arg ) const;
        bool operator == ( const CPos & arg ) const;
        void getCellName (std::string & name) const;
        friend void rectIterationSize ( std::vector<CPos> & res, const CPos & start, int w, int h );
        friend void rectIterationPos ( std::vector<CPos> & res, const CPos & start, const CPos & end );
        friend std::ostream & operator << ( std::ostream & os, const CPos & pos );
  private:
        std::pair<int, int> coo;
        std::pair<bool, bool> fixed;
};

#endif // POS_H