#ifndef POS_H
#define POS_H

#include <cstdlib>
#include <string>
#include <vector>
#include <iostream>

/**
Class for storage and operation with cell positions.
*/
class CPos
{
    public:
        /**
         Construct empty CPos class. Initialize with non fixed position 0, 0.
        */
        CPos ();

        /**
         Construct CPos class based on positional information passed in string_view.  
        @param str String view in format {Fixed?}Column{Fixed?}Row, such as A$3.
        */
        CPos ( std::string_view str );

        /**
         Copy constructor for CPos class
        @param coo std::pair<int, int> with column and row index respectivley.
        @param p2 std::pair<int, int> with column and row fixation respectivley.
        */
        CPos ( std::pair<int, int> coo, std::pair<int, int> fixed );

        /**
         Copy method for CPos class, 
        @param delta Parameter description
        @param p2 Parameter description
        @return Return description
        */
        CPos copy ( const std::pair<int, int> & delta ) const;

        /**
         Empty constructor for 
        @param p1 Parameter description
        @param p2 Parameter description
        @return Return description
        */
        void addFixation ( std::pair<bool, bool> & fixation );

        /**
         Empty constructor for 
        @param p1 Parameter description
        @param p2 Parameter description
        @return Return description
        */
        CPos & operator = ( const CPos & arg );

        /**
         Empty constructor for 
        @param p1 Parameter description
        @param p2 Parameter description
        @return Return description
        */
        std::pair<int, int> operator - ( const CPos & arg);

        /**
         Empty constructor for 
        @param p1 Parameter description
        @param p2 Parameter description
        @return Return description
        */
        bool operator < ( const CPos & arg ) const;

        /**
         Empty constructor for 
        @param p1 Parameter description
        @param p2 Parameter description
        @return Return description
        */
        bool operator == ( const CPos & arg ) const;

        /**
         Empty constructor for 
        @param p1 Parameter description
        @param p2 Parameter description
        @return Return description
        */
        void getCellName (std::string & name) const;

        /**
         Empty constructor for 
        @param p1 Parameter description
        @param p2 Parameter description
        @return Return description
        */
        friend void rectIterationSize ( std::vector<CPos> & res, const CPos & start, int w, int h );

        /**
         Empty constructor for 
        @param p1 Parameter description
        @param p2 Parameter description
        @return Return description
        */
        friend std::ostream & operator << ( std::ostream & os, const CPos & pos );
        
  private:
        std::pair<int, int> coo;
        std::pair<bool, bool> fixed;
};

#endif // POS_H