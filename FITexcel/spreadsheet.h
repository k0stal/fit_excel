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

class CSpreadsheet
{
  public:
    static unsigned capabilities () {
      return SPREADSHEET_CYCLIC_DEPS | SPREADSHEET_FILE_IO | SPREADSHEET_SPEED ;
    }
    
    CSpreadsheet ();
    ~CSpreadsheet() = default;
    CSpreadsheet( CSpreadsheet & arg );
    CSpreadsheet & operator = ( CSpreadsheet & arg );                
    bool load ( std::istream & is );
    bool save ( std::ostream & os ) const;
    bool setCell ( CPos pos, std::string contents );
    CValue getValue ( CPos pos );
    void copyRect ( CPos dst, CPos src, int w = 1, int h = 1 );
  private:
    bool containsCycle ( const CPos & pos, const std::map<CPos, std::set<CPos>> & graph, std::set<CPos> & visited, std::set<CPos> & stack ) const;
    std::map<CPos, std::unique_ptr<ASTNode>> map;
};

#endif // SPREADSHEET_H