#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cfloat>
#include <cassert>
#include <cmath>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
#include <stdexcept>
#include <variant>
#include <optional>
#include <compare>
#include <charconv>
#include <span>
#include <utility>

#include "expression.h"
#include "position.h"

constexpr unsigned                     SPREADSHEET_CYCLIC_DEPS                 = 0x01;
constexpr unsigned                     SPREADSHEET_FUNCTIONS                   = 0x02;
constexpr unsigned                     SPREADSHEET_FILE_IO                     = 0x04;
constexpr unsigned                     SPREADSHEET_SPEED                       = 0x08;
constexpr unsigned                     SPREADSHEET_PARSER                      = 0x10;

/**
* Class representing excel spreadsheet.
*/
class CSpreadsheet
{
    public:
        /**
        * Return unsigned representing implmeneted functionalities
        * @return Binary or of codes representing functionalities.
        */
        static unsigned capabilities () {
        return SPREADSHEET_CYCLIC_DEPS | SPREADSHEET_FILE_IO | SPREADSHEET_SPEED ;
        }
    
        /**
        * Construct empty spreadsheet object.
        */
        CSpreadsheet ();

        /**
        * Destruct spreadsheet object.
        */
        ~CSpreadsheet() = default;

        /**
        * Copy construct spreadsheet using reference.
        * @param arg CSpreadsheet reference.
        */
        CSpreadsheet( CSpreadsheet & arg );

        /**
        * Copy construct spreadsheet r-value reference.
        * @param arg CSpreadsheet r-value reference.
        */
        CSpreadsheet( CSpreadsheet && arg);

        /**
        * Assign values from argument spreadsheet to this spreadsheet object.
        * @param arg CSpreadsheet reference.
        * @return CSpreadsheet reference.
        */
        CSpreadsheet & operator = ( const CSpreadsheet & arg );   

        /**
        * Load spreadsheet based on the input stream. 
        * @param is input stream reference.
        * @return boolean value whether loading was succesful.
        */             
        bool load ( std::istream & is );

        /**
        * Save spreadsheet to the output stream.
        * @param os output stream reference.
        * @return boolean value whether saving was succesful.
        */
        bool save ( std::ostream & os ) const;

        /**
        * Set specified cell with certain value.
        * @param pos position of targeted cell.
        * @param contents string with certain value.
        * @return boolean value whether setting the value vas succesful.
        */
        bool setCell ( CPos pos, std::string contents );

        /**
        * Retrieve value of a specified cell.
        * @param pos position of targeted cell.
        * @return value of the targeted cell.
        */
        CValue getValue ( CPos pos );

        /**
        * Copy rectangle of cells with upper-left corner in src with width w and height h to destination position dst.
        * @param dst copy destination position.
        * @param src copy source position.
        * @param w rectangle width.
        * @param h rectangle height.
        */
        void copyRect ( CPos dst, CPos src, int w = 1, int h = 1 );
    
    private:
        std::map<CPos, std::unique_ptr<ASTNode>> map;
};

#endif // SPREADSHEET_H