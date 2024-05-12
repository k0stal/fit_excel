#ifndef __PROGTEST__
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

#include "position.h"
#include "spreadsheet.h"
#include "value.h"

#endif /* __PROGTEST__ */


#ifndef __PROGTEST__

bool                                   valueMatch                              ( const CValue                        & r,
                                                                                 const CValue                        & s )

{
  if ( r . index () != s . index () )
    return false;
  if ( r . index () == 0 )
    return true;
  if ( r . index () == 2 )
    return std::get<std::string> ( r ) == std::get<std::string> ( s );
  if ( std::isnan ( std::get<double> ( r ) ) && std::isnan ( std::get<double> ( s ) ) )
    return true;
  if ( std::isinf ( std::get<double> ( r ) ) && std::isinf ( std::get<double> ( s ) ) )
    return ( std::get<double> ( r ) < 0 && std::get<double> ( s ) < 0 )
           || ( std::get<double> ( r ) > 0 && std::get<double> ( s ) > 0 );
  return fabs ( std::get<double> ( r ) - std::get<double> ( s ) ) <= 1e8 * DBL_EPSILON * fabs ( std::get<double> ( r ) );
}
int main ()
{

  CSpreadsheet x0, x1;
  std::ostringstream oss;
  std::istringstream iss;
  std::string data;
  
  assert ( x0 . setCell ( CPos ( "A1" ), "10" ) );
  assert ( x0 . setCell ( CPos ( "A2" ), "20.5" ) );
  assert ( x0 . setCell ( CPos ( "A3" ), "3e1" ) );
  assert ( x0 . setCell ( CPos ( "A4" ), "=40" ) );
  assert ( x0 . setCell ( CPos ( "A5" ), "=5e+1" ) );
  assert ( x0 . setCell ( CPos ( "A6" ), "raw text with any characters, including a quote \" or a newline\n" ) );
  assert ( x0 . setCell ( CPos ( "A7" ), "=\"quoted string, quotes must be doubled: \"\". Moreover, backslashes are needed for C++.\"" ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "A1" ) ), CValue ( 10.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "A2" ) ), CValue ( 20.5 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "A3" ) ), CValue ( 30.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "A4" ) ), CValue ( 40.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "A5" ) ), CValue ( 50.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "A6" ) ), CValue ( "raw text with any characters, including a quote \" or a newline\n" ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "A7" ) ), CValue ( "quoted string, quotes must be doubled: \". Moreover, backslashes are needed for C++." ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "A8" ) ), CValue() ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "AAAA9999" ) ), CValue() ) );
  assert ( x0 . setCell ( CPos ( "B1" ), "=A1+A2*A3" ) );
  assert ( x0 . setCell ( CPos ( "B2" ), "= -A1 ^ 2 - A2 / 2   " ) );
  assert ( x0 . setCell ( CPos ( "B3" ), "= 2 ^ $A$1" ) );
  assert ( x0 . setCell ( CPos ( "B4" ), "=($A1+A$2)^2" ) );
  assert ( x0 . setCell ( CPos ( "B5" ), "=B1+B2+B3+B4" ) );
  assert ( x0 . setCell ( CPos ( "B6" ), "=B1+B2+B3+B4+B5" ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B1" ) ), CValue ( 625.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B2" ) ), CValue ( -110.25 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B3" ) ), CValue ( 1024.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B4" ) ), CValue ( 930.25 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B5" ) ), CValue ( 2469.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B6" ) ), CValue ( 4938.0 ) ) );
  assert ( x0 . setCell ( CPos ( "A1" ), "12" ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B1" ) ), CValue ( 627.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B2" ) ), CValue ( -154.25 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B4" ) ), CValue ( 1056.25 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B5" ) ), CValue ( 5625.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B6" ) ), CValue ( 11250.0 ) ) );
  x1 = x0;
  assert ( x0 . setCell ( CPos ( "A2" ), "100" ) );
  assert ( x1 . setCell ( CPos ( "A2" ), "=A3+A5+A4" ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B1" ) ), CValue ( 3012.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B2" ) ), CValue ( -194.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B4" ) ), CValue ( 12544.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B5" ) ), CValue ( 19458.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "B6" ) ), CValue ( 38916.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B1" ) ), CValue ( 3612.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B2" ) ), CValue ( -204.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B4" ) ), CValue ( 17424.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B5" ) ), CValue ( 24928.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B6" ) ), CValue ( 49856.0 ) ) );
  oss . clear ();
  oss . str ( "" );
  assert ( x0 . save ( oss ) );
  data = oss . str ();
  iss . clear ();
  iss . str ( data );
  assert ( x1 . load ( iss ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B1" ) ), CValue ( 3012.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B2" ) ), CValue ( -194.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B4" ) ), CValue ( 12544.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B5" ) ), CValue ( 19458.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B6" ) ), CValue ( 38916.0 ) ) );
  assert ( x0 . setCell ( CPos ( "A3" ), "4e1" ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B1" ) ), CValue ( 3012.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B2" ) ), CValue ( -194.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B3" ) ), CValue ( 4096.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B4" ) ), CValue ( 12544.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B5" ) ), CValue ( 19458.0 ) ) );
  assert ( valueMatch ( x1 . getValue ( CPos ( "B6" ) ), CValue ( 38916.0 ) ) );
  oss . clear ();
  oss . str ( "" );
  assert ( x0 . save ( oss ) );
  data = oss . str ();
  for ( size_t i = 0; i < std::min<size_t> ( data . length (), 10 ); i ++ )
    data[i] ^=0x5a;
  iss . clear ();
  iss . str ( data );
  assert ( ! x1 . load ( iss ) );
  assert ( x0 . setCell ( CPos ( "D0" ), "10" ) );
  assert ( x0 . setCell ( CPos ( "D1" ), "20" ) );
  assert ( x0 . setCell ( CPos ( "D2" ), "30" ) );
  assert ( x0 . setCell ( CPos ( "D3" ), "40" ) );
  assert ( x0 . setCell ( CPos ( "D4" ), "50" ) );
  assert ( x0 . setCell ( CPos ( "E0" ), "60" ) );
  assert ( x0 . setCell ( CPos ( "E1" ), "70" ) );
  assert ( x0 . setCell ( CPos ( "E2" ), "80" ) );
  assert ( x0 . setCell ( CPos ( "E3" ), "90" ) );
  assert ( x0 . setCell ( CPos ( "E4" ), "100" ) );
  assert ( x0 . setCell ( CPos ( "F10" ), "=D0+5" ) );
  assert ( x0 . setCell ( CPos ( "F11" ), "=$D0+5" ) );
  assert ( x0 . setCell ( CPos ( "F12" ), "=D$0+5" ) );
  assert ( x0 . setCell ( CPos ( "F13" ), "=$D$0+5" ) );
  x0 . copyRect ( CPos ( "G11" ), CPos ( "F10" ), 1, 4 );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F10" ) ), CValue ( 15.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F11" ) ), CValue ( 15.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F12" ) ), CValue ( 15.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F13" ) ), CValue ( 15.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F14" ) ), CValue() ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G10" ) ), CValue() ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G11" ) ), CValue ( 75.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G12" ) ), CValue ( 25.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G13" ) ), CValue ( 65.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G14" ) ), CValue ( 15.0 ) ) );
  x0 . copyRect ( CPos ( "G11" ), CPos ( "F10" ), 2, 4 );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F10" ) ), CValue ( 15.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F11" ) ), CValue ( 15.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F12" ) ), CValue ( 15.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F13" ) ), CValue ( 15.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "F14" ) ), CValue() ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G10" ) ), CValue() ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G11" ) ), CValue ( 75.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G12" ) ), CValue ( 25.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G13" ) ), CValue ( 65.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "G14" ) ), CValue ( 15.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "H10" ) ), CValue() ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "H11" ) ), CValue() ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "H12" ) ), CValue() ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "H13" ) ), CValue ( 35.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "H14" ) ), CValue() ) );
  assert ( x0 . setCell ( CPos ( "F0" ), "-27" ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "H14" ) ), CValue ( -22.0 ) ) );
  x0 . copyRect ( CPos ( "H12" ), CPos ( "H13" ), 1, 2 );
  assert ( valueMatch ( x0 . getValue ( CPos ( "H12" ) ), CValue ( 25.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "H13" ) ), CValue ( -22.0 ) ) );
  assert ( valueMatch ( x0 . getValue ( CPos ( "H14" ) ), CValue ( -22.0 ) ) );

  // cyclic detection ---------------------------------------------------------------------

  CSpreadsheet x2;
  assert ( x2 . setCell ( CPos ( "A1" ), "=B1" ) );
  assert ( x2 . setCell ( CPos ( "B1" ), "=C1" ) );
  assert ( x2 . setCell ( CPos ( "C1" ), "=A1" ) );
  assert ( valueMatch ( x2 . getValue ( CPos ( "A1" ) ), CValue() ) );
  assert ( valueMatch ( x2 . getValue ( CPos ( "B1" ) ), CValue() ) );
  assert ( valueMatch ( x2 . getValue ( CPos ( "C1" ) ), CValue() ) );

  CSpreadsheet x3;
  assert ( x3 . setCell ( CPos ( "A1" ), "=B1+C1+D1" ) );
  assert ( x3 . setCell ( CPos ( "C1" ), "=E1+F1" ) );
  assert ( x3 . setCell ( CPos ( "D1" ), "=G1+H1" ) );
  assert ( x3 . setCell ( CPos ( "F1" ), "=X1" ) );
  assert ( x3 . setCell ( CPos ( "X1" ), "=A1" ) );
  assert ( valueMatch ( x3 . getValue ( CPos ( "A1" ) ), CValue() ) );

  CSpreadsheet x4;
  assert ( x4 . setCell ( CPos ( "A1" ), "=B1+C1+D1+E1+F1+G1+H1" ) );
  assert ( x4 . setCell ( CPos ( "C1" ), "=I1+J1" ) );
  assert ( x4 . setCell ( CPos ( "I1" ), "=K1+M1" ) );
  assert ( x4 . setCell ( CPos ( "M1" ), "=N1" ) );
  assert ( x4 . setCell ( CPos ( "N1" ), "=M1" ) );
  assert ( valueMatch ( x4 . getValue ( CPos ( "A1" ) ), CValue() ) );

  CSpreadsheet x5;
  assert ( x5 . setCell ( CPos ( "A1" ), "=B1+C1" ) );
  assert ( x5 . setCell ( CPos ( "B1" ), "50" ) );
  assert ( x5 . setCell ( CPos ( "C1" ), "100" ) );
  assert ( x5 . setCell ( CPos ( "D1" ), "=E1+F1" ) );
  assert ( x5 . setCell ( CPos ( "E1" ), "20" ) );
  assert ( x5 . setCell ( CPos ( "F1" ), "=G5+H5+I5" ) );
  assert ( x5 . setCell ( CPos ( "G5" ), "10" ) );
  assert ( x5 . setCell ( CPos ( "H5" ), "60" ) );
  assert ( x5 . setCell ( CPos ( "I5" ), "70" ) );

  CSpreadsheet x6 ( x5 );
  CSpreadsheet x7;
  x7 = x5;

  assert ( valueMatch ( x5 . getValue ( CPos ( "A1" ) ), CValue(150.0) ) );
  assert ( valueMatch ( x6 . getValue ( CPos ( "A1" ) ), CValue(150.0) ) );
  assert ( valueMatch ( x7 . getValue ( CPos ( "A1" ) ), CValue(150.0) ) );
  
  assert ( x5 . setCell ( CPos ( "B1" ), "100" ) );

  assert ( valueMatch ( x5 . getValue ( CPos ( "A1" ) ), CValue(200.0) ) );
  assert ( valueMatch ( x6 . getValue ( CPos ( "A1" ) ), CValue(150.0) ) );
  assert ( valueMatch ( x7 . getValue ( CPos ( "A1" ) ), CValue(150.0) ) );

  CSpreadsheet x8;

  assert ( x8 . setCell ( CPos ( "A1" ), "=10>5" ) );
  assert ( x8 . setCell ( CPos ( "B1" ), "=5>10" ) );
  assert ( x8 . setCell ( CPos ( "C1" ), "=5>\"abc\"" ) );
  assert ( x8 . setCell ( CPos ( "D1" ), "=5<>10" ) );
  assert ( x8 . setCell ( CPos ( "E1" ), "=\"aaa\"<>\"aa\"" ) );
  assert ( x8 . setCell ( CPos ( "F1" ), "=\"aaa\"<>\"aaa\"" ) );
  assert ( x8 . setCell ( CPos ( "G1" ), "=\"aaa\"=\"aaa\"" ) );
  assert ( x8 . setCell ( CPos ( "H1" ), "=\"bbb\">\"aaa\"" ) );
  assert ( x8 . setCell ( CPos ( "I1" ), "=1000<>1000" ) );

  assert ( x8 . setCell ( CPos ( "A2" ), "=10>5" ) );
  assert ( x8 . setCell ( CPos ( "B2" ), "=5>10" ) );
  assert ( x8 . setCell ( CPos ( "C2" ), "=5>\"abc\"" ) );
  assert ( x8 . setCell ( CPos ( "D2" ), "=5<>10" ) );
  assert ( x8 . setCell ( CPos ( "E2" ), "=\"aaa\"<>\"aa\"" ) );
  assert ( x8 . setCell ( CPos ( "F2" ), "=\"aaa\"<>\"aaa\"" ) );
  assert ( x8 . setCell ( CPos ( "G2" ), "=\"aaa\"=\"aaa\"" ) );
  assert ( x8 . setCell ( CPos ( "H2" ), "=\"bbb\">\"aaa\"" ) );
  assert ( x8 . setCell ( CPos ( "I2" ), "=1000<>1000" ) );

  assert ( x8 . setCell ( CPos ( "A3" ), "=10>5" ) );
  assert ( x8 . setCell ( CPos ( "B3" ), "=5>10" ) );
  assert ( x8 . setCell ( CPos ( "C3" ), "=5>\"abc\"" ) );
  assert ( x8 . setCell ( CPos ( "D3" ), "=5<>10" ) );
  assert ( x8 . setCell ( CPos ( "E3" ), "=\"aaa\"<>\"aa\"" ) );
  assert ( x8 . setCell ( CPos ( "F3" ), "=\"aaa\"<>\"aaa\"" ) );
  assert ( x8 . setCell ( CPos ( "G3" ), "=\"aaa\"=\"aaa\"" ) );
  assert ( x8 . setCell ( CPos ( "H3" ), "=\"bbb\">\"aaa\"" ) );
  assert ( x8 . setCell ( CPos ( "I3" ), "=1000<>1000" ) );

  assert ( valueMatch ( x8 . getValue ( CPos ( "A1" ) ), CValue(1.0) ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "B1" ) ), CValue(0.0) ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "C1" ) ), CValue() ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "D1" ) ), CValue(1.0) ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "E1" ) ), CValue(1.0) ) );
  assert ( valueMatch ( x8 . getValue ( CPos ( "F1" ) ), CValue(0.0) ) ); 
  assert ( valueMatch ( x8 . getValue ( CPos ( "G1" ) ), CValue(1.0) ) ); 
  assert ( valueMatch ( x8 . getValue ( CPos ( "H1" ) ), CValue(1.0) ) ); 
  assert ( valueMatch ( x8 . getValue ( CPos ( "I1" ) ), CValue(0.0) ) );
 
  assert ( valueMatch ( x8 . getValue ( CPos ( "B2" ) ), CValue(0.0) ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "C2" ) ), CValue() ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "D2" ) ), CValue(1.0) ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "E2" ) ), CValue(1.0) ) );
  assert ( valueMatch ( x8 . getValue ( CPos ( "F2" ) ), CValue(0.0) ) );
  assert ( valueMatch ( x8 . getValue ( CPos ( "G2" ) ), CValue(1.0) ) ); 
  assert ( valueMatch ( x8 . getValue ( CPos ( "H2" ) ), CValue(1.0) ) );
  assert ( valueMatch ( x8 . getValue ( CPos ( "I2" ) ), CValue(0.0) ) ); 

  assert ( valueMatch ( x8 . getValue ( CPos ( "B3" ) ), CValue(0.0) ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "C3" ) ), CValue() ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "D3" ) ), CValue(1.0) ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "E3" ) ), CValue(1.0) ) );  
  assert ( valueMatch ( x8 . getValue ( CPos ( "F3" ) ), CValue(0.0) ) );
  assert ( valueMatch ( x8 . getValue ( CPos ( "G3" ) ), CValue(1.0) ) ); 
  assert ( valueMatch ( x8 . getValue ( CPos ( "H3" ) ), CValue(1.0) ) ); 
  assert ( valueMatch ( x8 . getValue ( CPos ( "I3" ) ), CValue(0.0) ) ); 

  CSpreadsheet x9;

  assert ( x9 . setCell ( CPos ( "A1" ), "1" ) );
  assert ( x9 . setCell ( CPos ( "A1" ), "1" ) );
  assert ( x9 . setCell ( CPos ( "B1" ), "2" ) );
  assert ( x9 . setCell ( CPos ( "C1" ), "3" ) );
  assert ( x9 . setCell ( CPos ( "D1" ), "4" ) );

  assert ( x9 . setCell ( CPos ( "A2" ), "5" ) );
  assert ( x9 . setCell ( CPos ( "B2" ), "6" ) );
  assert ( x9 . setCell ( CPos ( "C2" ), "7" ) );
  assert ( x9 . setCell ( CPos ( "D2" ), "8" ) );

  assert ( x9 . setCell ( CPos ( "A3" ), "=$A$1" ) );
  assert ( x9 . setCell ( CPos ( "B3" ), "=$B1" ) );
  assert ( x9 . setCell ( CPos ( "C3" ), "=C$1" ) );
  assert ( x9 . setCell ( CPos ( "D3" ), "=D1" ) );

  x9 . copyRect ( CPos ( "A4" ), CPos ( "A3" ), 4, 1 );

  assert ( valueMatch ( x9 . getValue ( CPos ( "A4" ) ), CValue(1.0) ) );  
  assert ( valueMatch ( x9 . getValue ( CPos ( "B4" ) ), CValue(6.0) ) );  
  assert ( valueMatch ( x9 . getValue ( CPos ( "C4" ) ), CValue(3.0) ) );  
  assert ( valueMatch ( x9 . getValue ( CPos ( "D4" ) ), CValue(8.0) ) );  
  
  CSpreadsheet x10(std::move(x9));

  assert ( valueMatch ( x10 . getValue ( CPos ( "A4" ) ), CValue(1.0) ) );  
  assert ( valueMatch ( x10 . getValue ( CPos ( "B4" ) ), CValue(6.0) ) );  
  assert ( valueMatch ( x10 . getValue ( CPos ( "C4" ) ), CValue(3.0) ) );  
  assert ( valueMatch ( x10 . getValue ( CPos ( "D4" ) ), CValue(8.0) ) ); 

  CSpreadsheet test1;
  assert ( test1 . setCell ( CPos ( "A1" ), "10" ) );
  assert ( test1 . setCell ( CPos ( "A3" ), "abcd" ) );
  assert ( test1 . setCell ( CPos ( "A4" ), "20" ) );
  assert ( test1 . setCell ( CPos ( "A5" ), "efgh" ) );
  
  assert ( test1 . setCell ( CPos ( "B1" ), "=A1 + A2" ) );
  assert ( test1 . setCell ( CPos ( "B2" ), "=A1 + A3" ) );
  assert ( test1 . setCell ( CPos ( "B3" ), "=A1 + A4" ) );
  assert ( test1 . setCell ( CPos ( "B4" ), "=A2 + A1" ) );
  assert ( test1 . setCell ( CPos ( "B5" ), "=A2 + A3" ) );
  assert ( test1 . setCell ( CPos ( "B6" ), "=A3 + A1" ) );
  assert ( test1 . setCell ( CPos ( "B7" ), "=A3 + A2" ) );
  assert ( test1 . setCell ( CPos ( "B8" ), "=A3 + A5" ) );

  assert(test1.setCell(CPos("C1"), "=A1*A3"));
  assert(test1.setCell(CPos("C2"), "=A3*A1"));
  assert(test1.setCell(CPos("C3"), "=A4*A1"));
  assert(test1.setCell(CPos("C4"), "=A3*A5"));
  assert(test1.setCell(CPos("C5"), "=A1*A4"));

  assert(test1.setCell(CPos("D1"), "=A1^2"));
  assert(test1.setCell(CPos("D2"), "=A3^2"));
  assert(test1.setCell(CPos("D3"), "=A4^2"));
  assert(test1.setCell(CPos("D4"), "=A5^2"));
  assert(test1.setCell(CPos("D5"), "=A2^2"));

  assert(test1.setCell(CPos("E1"), "=A4/A1"));
  assert(test1.setCell(CPos("E2"), "=A3/A1"));
  assert(test1.setCell(CPos("E3"), "=A1/A5"));
  assert(test1.setCell(CPos("E4"), "=A5/A3"));
  assert(test1.setCell(CPos("E5"), "=A1/A4"));

  assert(test1.setCell(CPos("F1"), "=A1-A3"));
  assert(test1.setCell(CPos("F2"), "=A3-A1"));
  assert(test1.setCell(CPos("F3"), "=A4-A1"));
  assert(test1.setCell(CPos("F4"), "=A3-A5"));
  assert(test1.setCell(CPos("F5"), "=A1-A4"));

  assert ( valueMatch ( test1 . getValue ( CPos ( "B1" ) ), CValue() ) );  
  assert ( valueMatch ( test1 . getValue ( CPos ( "B2" ) ), CValue("10abcd") ) );  
  assert ( valueMatch ( test1 . getValue ( CPos ( "B3" ) ), CValue(30.0) ) );  
  assert ( valueMatch ( test1 . getValue ( CPos ( "B4" ) ), CValue() ) ); 
  assert ( valueMatch ( test1 . getValue ( CPos ( "B5" ) ), CValue() ) );
  assert ( valueMatch ( test1 . getValue ( CPos ( "B6" ) ), CValue("abcd10") ) );
  assert ( valueMatch ( test1 . getValue ( CPos ( "B7" ) ), CValue() ) ); 
  assert ( valueMatch ( test1 . getValue ( CPos ( "B8" ) ), CValue("abcdefgh") ) ); 

  assert(valueMatch(test1.getValue(CPos("F1")), CValue()));
  assert(valueMatch(test1.getValue(CPos("F2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("F3")), CValue(10.0)));
  assert(valueMatch(test1.getValue(CPos("F4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("F5")), CValue(-10.0)));

  assert(valueMatch(test1.getValue(CPos("C1")), CValue()));
  assert(valueMatch(test1.getValue(CPos("C2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("C3")), CValue(200.0)));
  assert(valueMatch(test1.getValue(CPos("C4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("C5")), CValue(200.0)));

  assert(valueMatch(test1.getValue(CPos("D1")), CValue(100.0)));
  assert(valueMatch(test1.getValue(CPos("D2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("D3")), CValue(400.0)));
  assert(valueMatch(test1.getValue(CPos("D4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("D5")), CValue()));

  assert(valueMatch(test1.getValue(CPos("E1")), CValue(2.0)));
  assert(valueMatch(test1.getValue(CPos("E2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("E3")), CValue()));
  assert(valueMatch(test1.getValue(CPos("E4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("E5")), CValue(0.5)));

  assert(test1.setCell(CPos("G1"), "=0/0"));
  assert(test1.setCell(CPos("G2"), "=100/0"));
  assert(test1.setCell(CPos("G3"), "=5/2"));
  assert(test1.setCell(CPos("G4"), "=5^0"));
  assert(test1.setCell(CPos("G5"), "=0^1"));
  assert(test1.setCell(CPos("G6"), "=-10"));

  assert(valueMatch(test1.getValue(CPos("G1")), CValue()));
  assert(valueMatch(test1.getValue(CPos("G2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("G3")), CValue(2.5)));
  assert(valueMatch(test1.getValue(CPos("G4")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("G5")), CValue(0.0)));
  assert(valueMatch(test1.getValue(CPos("G6")), CValue(-10.0)));
  
// operators <>, =, <=, <, >, >= ---------------------------------------------------------------------

  assert(test1.setCell(CPos("H1"), "=AAAA5555<>10"));
  assert(test1.setCell(CPos("H2"), "=10<>uiop234"));
  assert(test1.setCell(CPos("H3"), "=10<>10"));
  assert(test1.setCell(CPos("H4"), "=10<>\"abc\""));
  assert(test1.setCell(CPos("H5"), "=\"abc\"<>10"));
  assert(test1.setCell(CPos("H6"), "=\"abc\"<>\"abc\""));
  assert(test1.setCell(CPos("H7"), "=\"abc\"<>\"abcd\""));
  assert(test1.setCell(CPos("H8"), "=11<>10"));

  assert(valueMatch(test1.getValue(CPos("H1")), CValue()));
  assert(valueMatch(test1.getValue(CPos("H2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("H3")), CValue(0.0)));
  assert(valueMatch(test1.getValue(CPos("H4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("H5")), CValue()));
  assert(valueMatch(test1.getValue(CPos("H6")), CValue(0.0)));
  assert(valueMatch(test1.getValue(CPos("H7")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("H8")), CValue(1.0)));
  
  assert(test1.setCell(CPos("X1"), "=10"));
  assert(test1.setCell(CPos("X2"), "=10=uiop234"));
  assert(test1.setCell(CPos("X3"), "=10=10"));
  assert(test1.setCell(CPos("X4"), "=10=\"abc\""));
  assert(test1.setCell(CPos("X5"), "=\"abc\"=10"));
  assert(test1.setCell(CPos("X6"), "=\"abc\"=\"abc\""));
  assert(test1.setCell(CPos("X7"), "=\"abc\"=\"abcd\""));
  assert(test1.setCell(CPos("X8"), "=11=10"));

  assert(valueMatch(test1.getValue(CPos("x1")), CValue(10.0)));
  assert(valueMatch(test1.getValue(CPos("x2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("x3")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("x4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("x5")), CValue()));
  assert(valueMatch(test1.getValue(CPos("x6")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("x7")), CValue(0.0)));
  assert(valueMatch(test1.getValue(CPos("x8")), CValue(0.0)));

  assert(test1.setCell(CPos("abcd1234"), "=100"));
  assert(valueMatch(test1.getValue(CPos("ABCD1234")), CValue(100.0)));
  assert(valueMatch(test1.getValue(CPos("aBcD1234")), CValue(100.0)));
  assert(valueMatch(test1.getValue(CPos("abcD1234")), CValue(100.0)));

  assert(test1.setCell(CPos("J1"), "=AAAA5555>abded123"));
  assert(test1.setCell(CPos("J2"), "=10>uiop234"));
  assert(test1.setCell(CPos("J3"), "=10>10"));
  assert(test1.setCell(CPos("j4"), "=10>\"abc\""));
  assert(test1.setCell(CPos("J5"), "=\"abc\">10"));
  assert(test1.setCell(CPos("j6"), "=\"abc\">\"abc\""));
  assert(test1.setCell(CPos("j7"), "=\"zzzz\">\"abcd\""));
  assert(test1.setCell(CPos("j8"), "=11>10"));

  assert(valueMatch(test1.getValue(CPos("j1")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j3")), CValue(0.0)));
  assert(valueMatch(test1.getValue(CPos("j4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j5")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j6")), CValue(0.0)));
  assert(valueMatch(test1.getValue(CPos("j7")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j8")), CValue(1.0)));

  assert(test1.setCell(CPos("J1"), "=AAAA5555>=abded123"));
  assert(test1.setCell(CPos("J2"), "=10>=uiop234"));
  assert(test1.setCell(CPos("J3"), "=10>=10"));
  assert(test1.setCell(CPos("j4"), "=10>=\"abc\""));
  assert(test1.setCell(CPos("J5"), "=\"abc\">=10"));
  assert(test1.setCell(CPos("j6"), "=\"abc\">=\"abc\""));
  assert(test1.setCell(CPos("j7"), "=\"zzzz\">=\"abcd\""));
  assert(test1.setCell(CPos("j8"), "=11>=10"));

  assert(valueMatch(test1.getValue(CPos("j1")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j3")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j5")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j6")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j7")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j8")), CValue(1.0)));

  assert(test1.setCell(CPos("J1"), "=AAAA5555>=abded123"));
  assert(test1.setCell(CPos("J2"), "=10>=uiop234"));
  assert(test1.setCell(CPos("J3"), "=10>=10"));
  assert(test1.setCell(CPos("j4"), "=10>=\"abc\""));
  assert(test1.setCell(CPos("J5"), "=\"abc\">=10"));
  assert(test1.setCell(CPos("j6"), "=\"abc\">=\"abc\""));
  assert(test1.setCell(CPos("j7"), "=\"zzzz\">=\"abcd\""));
  assert(test1.setCell(CPos("j8"), "=11>=10"));

  assert(valueMatch(test1.getValue(CPos("j1")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j3")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j5")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j6")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j7")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j8")), CValue(1.0)));

  assert(test1.setCell(CPos("J1"), "=AAAA5555<abded123"));
  assert(test1.setCell(CPos("J2"), "=10<uiop234"));
  assert(test1.setCell(CPos("J3"), "=10<10"));
  assert(test1.setCell(CPos("j4"), "=10<\"abc\""));
  assert(test1.setCell(CPos("J5"), "=\"abc\"<10"));
  assert(test1.setCell(CPos("j6"), "=\"abc\"<\"abc\""));
  assert(test1.setCell(CPos("j7"), "=\"aaaa\"<\"zzzz\""));
  assert(test1.setCell(CPos("j8"), "=11<12"));

  assert(valueMatch(test1.getValue(CPos("j1")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j3")), CValue(0.0)));
  assert(valueMatch(test1.getValue(CPos("j4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j5")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j6")), CValue(0.0)));
  assert(valueMatch(test1.getValue(CPos("j7")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j8")), CValue(1.0)));

  assert(test1.setCell(CPos("J1"), "=AAAA5555<=abded123"));
  assert(test1.setCell(CPos("J2"), "=10<=uiop234"));
  assert(test1.setCell(CPos("J3"), "=10<=10"));
  assert(test1.setCell(CPos("j4"), "=10<=\"abc\""));
  assert(test1.setCell(CPos("J5"), "=\"abc\"<=10"));
  assert(test1.setCell(CPos("j6"), "=\"abc\"<=\"abc\""));
  assert(test1.setCell(CPos("j7"), "=\"aaaa\"<=\"zzzz\""));
  assert(test1.setCell(CPos("j8"), "=11<=11"));

  assert(valueMatch(test1.getValue(CPos("j1")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j2")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j3")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j4")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j5")), CValue()));
  assert(valueMatch(test1.getValue(CPos("j6")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j7")), CValue(1.0)));
  assert(valueMatch(test1.getValue(CPos("j8")), CValue(1.0)));

  CSpreadsheet test2;

  assert(test2.setCell(CPos("A1"), "=A2"));
  assert(test2.setCell(CPos("A2"), "=A3+\"cccc\""));
  assert(test2.setCell(CPos("A3"), "=A4"));
  assert(test2.setCell(CPos("A4"), "=a5+\"bbbb\""));
  assert(test2.setCell(CPos("A5"), "=a6"));
  assert(test2.setCell(CPos("A6"), "=a7"));
  assert(test2.setCell(CPos("A7"), "=a8"));
  assert(test2.setCell(CPos("A8"), "=\"aaaa\""));

  assert(valueMatch(test2.getValue(CPos("A1")), CValue("aaaabbbbcccc")));

  assert(test2.setCell(CPos("aaa888"), "=100"));
    
  assert(valueMatch(test2.getValue(CPos("aaa888")), CValue(100.0)));
  assert(valueMatch(test2.getValue(CPos("AAA888")), CValue(100.0)));
  assert(valueMatch(test2.getValue(CPos("AAA888")), CValue(100.0)));
  assert(valueMatch(test2.getValue(CPos("Aaa888")), CValue(100.0)));

  assert(test2.setCell(CPos("A1"), "=((((1+10)^2-21)/(100-90))*(5^2))<(2500/10)"));
  assert(valueMatch(test2.getValue(CPos("A1")), CValue(0.0)));
  assert(test2.setCell(CPos("A1"), "=B1"));
  assert(valueMatch(test2.getValue(CPos("A1")), CValue()));  
  assert(test2.setCell(CPos("b1"), "=100"));
  assert(valueMatch(test2.getValue(CPos("A1")), CValue(100.0)));  
  assert(test2.setCell(CPos("A1"), "=C1"));
  assert(valueMatch(test2.getValue(CPos("A1")), CValue()));  
  assert(test2.setCell(CPos("C1"), "=\"abc\""));
  assert(valueMatch(test2.getValue(CPos("A1")), CValue("abc"))); 
  assert(test2.setCell(CPos("C1"), "=D1"));
  assert(test2.setCell(CPos("D1"), "=F1"));
  assert(test2.setCell(CPos("F1"), "10")); 
  assert(valueMatch(test2.getValue(CPos("A1")), CValue(10.0))); 
  assert(test2.setCell(CPos("D1"), "=WW1"));
  assert(valueMatch(test2.getValue(CPos("A1")), CValue())); 
  assert(test2.setCell(CPos("WW1"), "1400"));
  assert(valueMatch(test2.getValue(CPos("A1")), CValue(1400.0))); 

  CSpreadsheet test3;
  assert(test3.setCell(CPos("A1"), "1.23"));
  assert(test3.setCell(CPos("A2"), "abcd"));
  assert(test3.setCell(CPos("A3"), "=A1+A2"));

  assert(test3.setCell(CPos("A4"), "1"));
  assert(test3.setCell(CPos("A5"), "abcd"));
  assert(test3.setCell(CPos("A6"), "=A4+A5"));

  assert(valueMatch(test3.getValue(CPos("A3")), CValue("1.23abcd"))); 
  assert(valueMatch(test3.getValue(CPos("A6")), CValue("1abcd"))); 

  // CPos tests ---------------------------------------------------------------------

  CSpreadsheet test10;
  assert(test10.setCell(CPos("A0"), "0"));
  assert(test10.setCell(CPos("B0"), "1"));
  assert(test10.setCell(CPos("C0"), "2"));
  assert(test10.setCell(CPos("D0"), "3"));
  assert(test10.setCell(CPos("E0"), "4"));
  assert(test10.setCell(CPos("F0"), "5"));
  assert(test10.setCell(CPos("G0"), "6"));
  assert(test10.setCell(CPos("H0"), "7"));
  assert(test10.setCell(CPos("I0"), "8"));
  assert(test10.setCell(CPos("J0"), "9"));
  assert(test10.setCell(CPos("K0"), "10"));
  assert(test10.setCell(CPos("L0"), "11"));
  assert(test10.setCell(CPos("M0"), "12"));
  assert(test10.setCell(CPos("N0"), "13"));
  assert(test10.setCell(CPos("O0"), "14"));
  assert(test10.setCell(CPos("P0"), "15"));
  assert(test10.setCell(CPos("Q0"), "16"));
  assert(test10.setCell(CPos("R0"), "17"));
  assert(test10.setCell(CPos("S0"), "18"));
  assert(test10.setCell(CPos("T0"), "19"));
  assert(test10.setCell(CPos("U0"), "20"));
  assert(test10.setCell(CPos("V0"), "21"));
  assert(test10.setCell(CPos("W0"), "22"));
  assert(test10.setCell(CPos("X0"), "23"));
  assert(test10.setCell(CPos("Y0"), "24"));
  assert(test10.setCell(CPos("Z0"), "25"));
  assert(test10.setCell(CPos("AA0"), "26"));
  assert(test10.setCell(CPos("AB0"), "27"));
  assert(test10.setCell(CPos("AC0"), "28"));
  assert(test10.setCell(CPos("AD0"), "29"));
  assert(test10.setCell(CPos("AE0"), "30"));
  assert(test10.setCell(CPos("AF0"), "31"));
  assert(test10.setCell(CPos("AG0"), "32"));
  assert(test10.setCell(CPos("AH0"), "33"));
  assert(test10.setCell(CPos("AI0"), "34"));
  assert(test10.setCell(CPos("AJ0"), "35"));
  assert(test10.setCell(CPos("AK0"), "36"));
  assert(test10.setCell(CPos("AL0"), "37"));
  assert(test10.setCell(CPos("AM0"), "38"));
  assert(test10.setCell(CPos("AN0"), "39"));
  assert(test10.setCell(CPos("AO0"), "40"));
  assert(test10.setCell(CPos("AP0"), "41"));
  assert(test10.setCell(CPos("AQ0"), "42"));
  assert(test10.setCell(CPos("AR0"), "43"));
  assert(test10.setCell(CPos("AS0"), "44"));
  assert(test10.setCell(CPos("AT0"), "45"));
  assert(test10.setCell(CPos("AU0"), "46"));
  assert(test10.setCell(CPos("AV0"), "47"));
  assert(test10.setCell(CPos("AW0"), "48"));
  assert(test10.setCell(CPos("AX0"), "49"));
  assert(test10.setCell(CPos("AY0"), "50"));
  assert(test10.setCell(CPos("AZ0"), "51"));
  assert(test10.setCell(CPos("BA0"), "52"));
  assert(test10.setCell(CPos("BB0"), "53"));
  assert(test10.setCell(CPos("BC0"), "54"));
  assert(test10.setCell(CPos("BD0"), "55"));
  assert(test10.setCell(CPos("BE0"), "56"));
  assert(test10.setCell(CPos("BF0"), "57"));
  assert(test10.setCell(CPos("BG0"), "58"));
  assert(test10.setCell(CPos("BH0"), "59"));
  assert(test10.setCell(CPos("BI0"), "60"));
  assert(test10.setCell(CPos("BJ0"), "61"));
  assert(test10.setCell(CPos("BK0"), "62"));
  assert(test10.setCell(CPos("BL0"), "63"));
  assert(test10.setCell(CPos("BM0"), "64"));
  assert(test10.setCell(CPos("BN0"), "65"));
  assert(test10.setCell(CPos("BO0"), "66"));
  assert(test10.setCell(CPos("BP0"), "67"));
  assert(test10.setCell(CPos("BQ0"), "68"));
  assert(test10.setCell(CPos("BR0"), "69"));
  assert(test10.setCell(CPos("BS0"), "70"));
  assert(test10.setCell(CPos("BT0"), "71"));
  assert(test10.setCell(CPos("BU0"), "72"));
  assert(test10.setCell(CPos("BV0"), "73"));
  assert(test10.setCell(CPos("BW0"), "74"));
  assert(test10.setCell(CPos("BX0"), "75"));
  assert(test10.setCell(CPos("BY0"), "76"));
  assert(test10.setCell(CPos("BZ0"), "77"));
  assert(test10.setCell(CPos("CA0"), "78"));
  assert(test10.setCell(CPos("CB0"), "79"));
  assert(test10.setCell(CPos("CC0"), "80"));
  assert(test10.setCell(CPos("CD0"), "81"));
  assert(test10.setCell(CPos("CE0"), "82"));
  assert(test10.setCell(CPos("CF0"), "83"));
  assert(test10.setCell(CPos("CG0"), "84"));
  assert(test10.setCell(CPos("CH0"), "85"));
  assert(test10.setCell(CPos("CI0"), "86"));
  assert(test10.setCell(CPos("CJ0"), "87"));
  assert(test10.setCell(CPos("CK0"), "88"));
  assert(test10.setCell(CPos("CL0"), "89"));
  assert(test10.setCell(CPos("CM0"), "90"));
  assert(test10.setCell(CPos("CN0"), "91"));
  assert(test10.setCell(CPos("CO0"), "92"));
  assert(test10.setCell(CPos("CP0"), "93"));
  assert(test10.setCell(CPos("CQ0"), "94"));
  assert(test10.setCell(CPos("CR0"), "95"));
  assert(test10.setCell(CPos("CS0"), "96"));
  assert(test10.setCell(CPos("CT0"), "97"));
  assert(test10.setCell(CPos("CU0"), "98"));
  assert(test10.setCell(CPos("CV0"), "99"));
  assert(test10.setCell(CPos("CW0"), "100"));
  assert(test10.setCell(CPos("CX0"), "101"));
  assert(test10.setCell(CPos("CY0"), "102"));
  assert(test10.setCell(CPos("CZ0"), "103"));
  assert(test10.setCell(CPos("DA0"), "104"));
  assert(test10.setCell(CPos("DB0"), "105"));
  assert(test10.setCell(CPos("DC0"), "106"));
  assert(test10.setCell(CPos("DD0"), "107"));
  assert(test10.setCell(CPos("DE0"), "108"));
  assert(test10.setCell(CPos("DF0"), "109"));
  assert(test10.setCell(CPos("DG0"), "110"));
  assert(test10.setCell(CPos("DH0"), "111"));
  assert(test10.setCell(CPos("DI0"), "112"));
  assert(test10.setCell(CPos("DJ0"), "113"));
  assert(test10.setCell(CPos("DK0"), "114"));
  assert(test10.setCell(CPos("DL0"), "115"));
  assert(test10.setCell(CPos("DM0"), "116"));
  assert(test10.setCell(CPos("DN0"), "117"));
  assert(test10.setCell(CPos("DO0"), "118"));
  assert(test10.setCell(CPos("DP0"), "119"));
  assert(test10.setCell(CPos("DQ0"), "120"));
  assert(test10.setCell(CPos("DR0"), "121"));
  assert(test10.setCell(CPos("DS0"), "122"));
  assert(test10.setCell(CPos("DT0"), "123"));
  assert(test10.setCell(CPos("DU0"), "124"));
  assert(test10.setCell(CPos("DV0"), "125"));
  assert(test10.setCell(CPos("DW0"), "126"));
  assert(test10.setCell(CPos("DX0"), "127"));
  assert(test10.setCell(CPos("DY0"), "128"));
  assert(test10.setCell(CPos("DZ0"), "129"));
  assert(test10.setCell(CPos("EA0"), "130"));
  assert(test10.setCell(CPos("EB0"), "131"));
  assert(test10.setCell(CPos("EC0"), "132"));
  assert(test10.setCell(CPos("ED0"), "133"));
  assert(test10.setCell(CPos("EE0"), "134"));
  assert(test10.setCell(CPos("EF0"), "135"));
  assert(test10.setCell(CPos("EG0"), "136"));
  assert(test10.setCell(CPos("EH0"), "137"));
  assert(test10.setCell(CPos("EI0"), "138"));
  assert(test10.setCell(CPos("EJ0"), "139"));
  assert(test10.setCell(CPos("EK0"), "140"));
  assert(test10.setCell(CPos("EL0"), "141"));
  assert(test10.setCell(CPos("EM0"), "142"));
  assert(test10.setCell(CPos("EN0"), "143"));
  assert(test10.setCell(CPos("EO0"), "144"));
  assert(test10.setCell(CPos("EP0"), "145"));
  assert(test10.setCell(CPos("EQ0"), "146"));
  assert(test10.setCell(CPos("ER0"), "147"));
  assert(test10.setCell(CPos("ES0"), "148"));
  assert(test10.setCell(CPos("ET0"), "149"));
  assert(test10.setCell(CPos("EU0"), "150"));
  assert(test10.setCell(CPos("EV0"), "151"));
  assert(test10.setCell(CPos("EW0"), "152"));
  assert(test10.setCell(CPos("EX0"), "153"));
  assert(test10.setCell(CPos("EY0"), "154"));
  assert(test10.setCell(CPos("EZ0"), "155"));
  assert(test10.setCell(CPos("FA0"), "156"));
  assert(test10.setCell(CPos("FB0"), "157"));
  assert(test10.setCell(CPos("FC0"), "158"));
  assert(test10.setCell(CPos("FD0"), "159"));
  assert(test10.setCell(CPos("FE0"), "160"));
  assert(test10.setCell(CPos("FF0"), "161"));
  assert(test10.setCell(CPos("FG0"), "162"));
  assert(test10.setCell(CPos("FH0"), "163"));
  assert(test10.setCell(CPos("FI0"), "164"));
  assert(test10.setCell(CPos("FJ0"), "165"));
  assert(test10.setCell(CPos("FK0"), "166"));
  assert(test10.setCell(CPos("FL0"), "167"));
  assert(test10.setCell(CPos("FM0"), "168"));
  assert(test10.setCell(CPos("FN0"), "169"));
  assert(test10.setCell(CPos("FO0"), "170"));
  assert(test10.setCell(CPos("FP0"), "171"));
  assert(test10.setCell(CPos("FQ0"), "172"));
  assert(test10.setCell(CPos("FR0"), "173"));
  assert(test10.setCell(CPos("FS0"), "174"));
  assert(test10.setCell(CPos("FT0"), "175"));
  assert(test10.setCell(CPos("FU0"), "176"));
  assert(test10.setCell(CPos("FV0"), "177"));
  assert(test10.setCell(CPos("FW0"), "178"));
  assert(test10.setCell(CPos("FX0"), "179"));
  assert(test10.setCell(CPos("FY0"), "180"));
  assert(test10.setCell(CPos("FZ0"), "181"));
  assert(test10.setCell(CPos("GA0"), "182"));
  assert(test10.setCell(CPos("GB0"), "183"));
  assert(test10.setCell(CPos("GC0"), "184"));
  assert(test10.setCell(CPos("GD0"), "185"));
  assert(test10.setCell(CPos("GE0"), "186"));
  assert(test10.setCell(CPos("GF0"), "187"));
  assert(test10.setCell(CPos("GG0"), "188"));
  assert(test10.setCell(CPos("GH0"), "189"));
  assert(test10.setCell(CPos("GI0"), "190"));
  assert(test10.setCell(CPos("GJ0"), "191"));
  assert(test10.setCell(CPos("GK0"), "192"));
  assert(test10.setCell(CPos("GL0"), "193"));
  assert(test10.setCell(CPos("GM0"), "194"));
  assert(test10.setCell(CPos("GN0"), "195"));
  assert(test10.setCell(CPos("GO0"), "196"));
  assert(test10.setCell(CPos("GP0"), "197"));
  assert(test10.setCell(CPos("GQ0"), "198"));
  assert(test10.setCell(CPos("GR0"), "199"));
  assert(test10.setCell(CPos("GS0"), "200"));

  assert(valueMatch(test10.getValue(CPos("A0")), CValue(0.0)));
  assert(valueMatch(test10.getValue(CPos("B0")), CValue(1.0))); 
  assert(valueMatch(test10.getValue(CPos("C0")), CValue(2.0)));
  assert(valueMatch(test10.getValue(CPos("D0")), CValue(3.0)));
  assert(valueMatch(test10.getValue(CPos("E0")), CValue(4.0)));
  assert(valueMatch(test10.getValue(CPos("F0")), CValue(5.0)));
  assert(valueMatch(test10.getValue(CPos("G0")), CValue(6.0)));
  assert(valueMatch(test10.getValue(CPos("H0")), CValue(7.0)));
  assert(valueMatch(test10.getValue(CPos("I0")), CValue(8.0)));
  assert(valueMatch(test10.getValue(CPos("J0")), CValue(9.0)));
  assert(valueMatch(test10.getValue(CPos("K0")), CValue(10.0)));
  assert(valueMatch(test10.getValue(CPos("L0")), CValue(11.0)));
  assert(valueMatch(test10.getValue(CPos("M0")), CValue(12.0)));
  assert(valueMatch(test10.getValue(CPos("N0")), CValue(13.0)));
  assert(valueMatch(test10.getValue(CPos("O0")), CValue(14.0)));
  assert(valueMatch(test10.getValue(CPos("P0")), CValue(15.0)));
  assert(valueMatch(test10.getValue(CPos("Q0")), CValue(16.0)));
  assert(valueMatch(test10.getValue(CPos("R0")), CValue(17.0)));
  assert(valueMatch(test10.getValue(CPos("S0")), CValue(18.0)));
  assert(valueMatch(test10.getValue(CPos("T0")), CValue(19.0)));
  assert(valueMatch(test10.getValue(CPos("U0")), CValue(20.0)));
  assert(valueMatch(test10.getValue(CPos("V0")), CValue(21.0)));
  assert(valueMatch(test10.getValue(CPos("W0")), CValue(22.0)));
  assert(valueMatch(test10.getValue(CPos("X0")), CValue(23.0)));
  assert(valueMatch(test10.getValue(CPos("Y0")), CValue(24.0)));
  assert(valueMatch(test10.getValue(CPos("Z0")), CValue(25.0)));
  assert(valueMatch(test10.getValue(CPos("AA0")), CValue(26.0)));
  assert(valueMatch(test10.getValue(CPos("AB0")), CValue(27.0)));
  assert(valueMatch(test10.getValue(CPos("AC0")), CValue(28.0)));
  assert(valueMatch(test10.getValue(CPos("AD0")), CValue(29.0)));
  assert(valueMatch(test10.getValue(CPos("AE0")), CValue(30.0)));
  assert(valueMatch(test10.getValue(CPos("AF0")), CValue(31.0)));
  assert(valueMatch(test10.getValue(CPos("AG0")), CValue(32.0)));
  assert(valueMatch(test10.getValue(CPos("AH0")), CValue(33.0)));
  assert(valueMatch(test10.getValue(CPos("AI0")), CValue(34.0)));
  assert(valueMatch(test10.getValue(CPos("AJ0")), CValue(35.0)));
  assert(valueMatch(test10.getValue(CPos("AK0")), CValue(36.0)));
  assert(valueMatch(test10.getValue(CPos("AL0")), CValue(37.0)));
  assert(valueMatch(test10.getValue(CPos("AM0")), CValue(38.0)));
  assert(valueMatch(test10.getValue(CPos("AN0")), CValue(39.0)));
  assert(valueMatch(test10.getValue(CPos("AO0")), CValue(40.0)));
  assert(valueMatch(test10.getValue(CPos("AP0")), CValue(41.0)));
  assert(valueMatch(test10.getValue(CPos("AQ0")), CValue(42.0)));
  assert(valueMatch(test10.getValue(CPos("AR0")), CValue(43.0)));
  assert(valueMatch(test10.getValue(CPos("AS0")), CValue(44.0)));
  assert(valueMatch(test10.getValue(CPos("AT0")), CValue(45.0)));
  assert(valueMatch(test10.getValue(CPos("AU0")), CValue(46.0)));
  assert(valueMatch(test10.getValue(CPos("AV0")), CValue(47.0)));
  assert(valueMatch(test10.getValue(CPos("AW0")), CValue(48.0)));
  assert(valueMatch(test10.getValue(CPos("AX0")), CValue(49.0)));
  assert(valueMatch(test10.getValue(CPos("AY0")), CValue(50.0)));
  assert(valueMatch(test10.getValue(CPos("AZ0")), CValue(51.0)));
  assert(valueMatch(test10.getValue(CPos("BA0")), CValue(52.0)));
  assert(valueMatch(test10.getValue(CPos("BB0")), CValue(53.0)));
  assert(valueMatch(test10.getValue(CPos("BC0")), CValue(54.0)));
  assert(valueMatch(test10.getValue(CPos("BD0")), CValue(55.0)));
  assert(valueMatch(test10.getValue(CPos("BE0")), CValue(56.0)));
  assert(valueMatch(test10.getValue(CPos("BF0")), CValue(57.0)));
  assert(valueMatch(test10.getValue(CPos("BG0")), CValue(58.0)));
  assert(valueMatch(test10.getValue(CPos("BH0")), CValue(59.0)));
  assert(valueMatch(test10.getValue(CPos("BI0")), CValue(60.0)));
  assert(valueMatch(test10.getValue(CPos("BJ0")), CValue(61.0)));
  assert(valueMatch(test10.getValue(CPos("BK0")), CValue(62.0)));
  assert(valueMatch(test10.getValue(CPos("BL0")), CValue(63.0)));
  assert(valueMatch(test10.getValue(CPos("BM0")), CValue(64.0)));
  assert(valueMatch(test10.getValue(CPos("BN0")), CValue(65.0)));
  assert(valueMatch(test10.getValue(CPos("BO0")), CValue(66.0)));
  assert(valueMatch(test10.getValue(CPos("BP0")), CValue(67.0)));
  assert(valueMatch(test10.getValue(CPos("BQ0")), CValue(68.0)));
  assert(valueMatch(test10.getValue(CPos("BR0")), CValue(69.0)));
  assert(valueMatch(test10.getValue(CPos("BS0")), CValue(70.0)));
  assert(valueMatch(test10.getValue(CPos("BT0")), CValue(71.0)));
  assert(valueMatch(test10.getValue(CPos("BU0")), CValue(72.0)));
  assert(valueMatch(test10.getValue(CPos("BV0")), CValue(73.0)));
  assert(valueMatch(test10.getValue(CPos("BW0")), CValue(74.0)));
  assert(valueMatch(test10.getValue(CPos("BX0")), CValue(75.0)));
  assert(valueMatch(test10.getValue(CPos("BY0")), CValue(76.0)));
  assert(valueMatch(test10.getValue(CPos("BZ0")), CValue(77.0)));
  assert(valueMatch(test10.getValue(CPos("CA0")), CValue(78.0)));
  assert(valueMatch(test10.getValue(CPos("CB0")), CValue(79.0)));
  assert(valueMatch(test10.getValue(CPos("CC0")), CValue(80.0)));
  assert(valueMatch(test10.getValue(CPos("CD0")), CValue(81.0)));
  assert(valueMatch(test10.getValue(CPos("CE0")), CValue(82.0)));
  assert(valueMatch(test10.getValue(CPos("CF0")), CValue(83.0)));
  assert(valueMatch(test10.getValue(CPos("CG0")), CValue(84.0)));
  assert(valueMatch(test10.getValue(CPos("CH0")), CValue(85.0)));
  assert(valueMatch(test10.getValue(CPos("CI0")), CValue(86.0)));
  assert(valueMatch(test10.getValue(CPos("CJ0")), CValue(87.0)));
  assert(valueMatch(test10.getValue(CPos("CK0")), CValue(88.0)));
  assert(valueMatch(test10.getValue(CPos("CL0")), CValue(89.0)));
  assert(valueMatch(test10.getValue(CPos("CM0")), CValue(90.0)));
  assert(valueMatch(test10.getValue(CPos("CN0")), CValue(91.0)));
  assert(valueMatch(test10.getValue(CPos("CO0")), CValue(92.0)));
  assert(valueMatch(test10.getValue(CPos("CP0")), CValue(93.0)));
  assert(valueMatch(test10.getValue(CPos("CQ0")), CValue(94.0)));
  assert(valueMatch(test10.getValue(CPos("CR0")), CValue(95.0)));
  assert(valueMatch(test10.getValue(CPos("CS0")), CValue(96.0)));
  assert(valueMatch(test10.getValue(CPos("CT0")), CValue(97.0)));
  assert(valueMatch(test10.getValue(CPos("CU0")), CValue(98.0)));
  assert(valueMatch(test10.getValue(CPos("CV0")), CValue(99.0)));
  assert(valueMatch(test10.getValue(CPos("CW0")), CValue(100.0)));
  assert(valueMatch(test10.getValue(CPos("CX0")), CValue(101.0)));
  assert(valueMatch(test10.getValue(CPos("CY0")), CValue(102.0)));
  assert(valueMatch(test10.getValue(CPos("CZ0")), CValue(103.0)));
  assert(valueMatch(test10.getValue(CPos("DA0")), CValue(104.0)));
  assert(valueMatch(test10.getValue(CPos("DB0")), CValue(105.0)));
  assert(valueMatch(test10.getValue(CPos("DC0")), CValue(106.0)));
  assert(valueMatch(test10.getValue(CPos("DD0")), CValue(107.0)));
  assert(valueMatch(test10.getValue(CPos("DE0")), CValue(108.0)));
  assert(valueMatch(test10.getValue(CPos("DF0")), CValue(109.0)));
  assert(valueMatch(test10.getValue(CPos("DG0")), CValue(110.0)));
  assert(valueMatch(test10.getValue(CPos("DH0")), CValue(111.0)));
  assert(valueMatch(test10.getValue(CPos("DI0")), CValue(112.0)));
  assert(valueMatch(test10.getValue(CPos("DJ0")), CValue(113.0)));
  assert(valueMatch(test10.getValue(CPos("DK0")), CValue(114.0)));
  assert(valueMatch(test10.getValue(CPos("DL0")), CValue(115.0)));
  assert(valueMatch(test10.getValue(CPos("DM0")), CValue(116.0)));
  assert(valueMatch(test10.getValue(CPos("DN0")), CValue(117.0)));
  assert(valueMatch(test10.getValue(CPos("DO0")), CValue(118.0)));
  assert(valueMatch(test10.getValue(CPos("DP0")), CValue(119.0)));
  assert(valueMatch(test10.getValue(CPos("DQ0")), CValue(120.0)));
  assert(valueMatch(test10.getValue(CPos("DR0")), CValue(121.0)));
  assert(valueMatch(test10.getValue(CPos("DS0")), CValue(122.0)));
  assert(valueMatch(test10.getValue(CPos("DT0")), CValue(123.0)));
  assert(valueMatch(test10.getValue(CPos("DU0")), CValue(124.0)));
  assert(valueMatch(test10.getValue(CPos("DV0")), CValue(125.0)));
  assert(valueMatch(test10.getValue(CPos("DW0")), CValue(126.0)));
  assert(valueMatch(test10.getValue(CPos("DX0")), CValue(127.0)));
  assert(valueMatch(test10.getValue(CPos("DY0")), CValue(128.0)));
  assert(valueMatch(test10.getValue(CPos("DZ0")), CValue(129.0)));
  assert(valueMatch(test10.getValue(CPos("EA0")), CValue(130.0)));
  assert(valueMatch(test10.getValue(CPos("EB0")), CValue(131.0)));
  assert(valueMatch(test10.getValue(CPos("EC0")), CValue(132.0)));
  assert(valueMatch(test10.getValue(CPos("ED0")), CValue(133.0)));
  assert(valueMatch(test10.getValue(CPos("EE0")), CValue(134.0)));
  assert(valueMatch(test10.getValue(CPos("EF0")), CValue(135.0)));
  assert(valueMatch(test10.getValue(CPos("EG0")), CValue(136.0)));
  assert(valueMatch(test10.getValue(CPos("EH0")), CValue(137.0)));
  assert(valueMatch(test10.getValue(CPos("EI0")), CValue(138.0)));
  assert(valueMatch(test10.getValue(CPos("EJ0")), CValue(139.0)));
  assert(valueMatch(test10.getValue(CPos("EK0")), CValue(140.0)));
  assert(valueMatch(test10.getValue(CPos("EL0")), CValue(141.0)));
  assert(valueMatch(test10.getValue(CPos("EM0")), CValue(142.0)));
  assert(valueMatch(test10.getValue(CPos("EN0")), CValue(143.0)));
  assert(valueMatch(test10.getValue(CPos("EO0")), CValue(144.0)));
  assert(valueMatch(test10.getValue(CPos("EP0")), CValue(145.0)));
  assert(valueMatch(test10.getValue(CPos("EQ0")), CValue(146.0)));
  assert(valueMatch(test10.getValue(CPos("ER0")), CValue(147.0)));
  assert(valueMatch(test10.getValue(CPos("ES0")), CValue(148.0)));
  assert(valueMatch(test10.getValue(CPos("ET0")), CValue(149.0)));
  assert(valueMatch(test10.getValue(CPos("EU0")), CValue(150.0)));
  assert(valueMatch(test10.getValue(CPos("EV0")), CValue(151.0)));
  assert(valueMatch(test10.getValue(CPos("EW0")), CValue(152.0)));
  assert(valueMatch(test10.getValue(CPos("EX0")), CValue(153.0)));
  assert(valueMatch(test10.getValue(CPos("EY0")), CValue(154.0)));
  assert(valueMatch(test10.getValue(CPos("EZ0")), CValue(155.0)));
  assert(valueMatch(test10.getValue(CPos("FA0")), CValue(156.0)));
  assert(valueMatch(test10.getValue(CPos("FB0")), CValue(157.0)));
  assert(valueMatch(test10.getValue(CPos("FC0")), CValue(158.0)));
  assert(valueMatch(test10.getValue(CPos("FD0")), CValue(159.0)));
  assert(valueMatch(test10.getValue(CPos("FE0")), CValue(160.0)));
  assert(valueMatch(test10.getValue(CPos("FF0")), CValue(161.0)));
  assert(valueMatch(test10.getValue(CPos("FG0")), CValue(162.0)));
  assert(valueMatch(test10.getValue(CPos("FH0")), CValue(163.0)));
  assert(valueMatch(test10.getValue(CPos("FI0")), CValue(164.0)));
  assert(valueMatch(test10.getValue(CPos("FJ0")), CValue(165.0)));
  assert(valueMatch(test10.getValue(CPos("FK0")), CValue(166.0)));
  assert(valueMatch(test10.getValue(CPos("FL0")), CValue(167.0)));
  assert(valueMatch(test10.getValue(CPos("FM0")), CValue(168.0)));
  assert(valueMatch(test10.getValue(CPos("FN0")), CValue(169.0)));
  assert(valueMatch(test10.getValue(CPos("FO0")), CValue(170.0)));
  assert(valueMatch(test10.getValue(CPos("FP0")), CValue(171.0)));
  assert(valueMatch(test10.getValue(CPos("FQ0")), CValue(172.0)));
  assert(valueMatch(test10.getValue(CPos("FR0")), CValue(173.0)));
  assert(valueMatch(test10.getValue(CPos("FS0")), CValue(174.0)));
  assert(valueMatch(test10.getValue(CPos("FT0")), CValue(175.0)));
  assert(valueMatch(test10.getValue(CPos("FU0")), CValue(176.0)));
  assert(valueMatch(test10.getValue(CPos("FV0")), CValue(177.0)));
  assert(valueMatch(test10.getValue(CPos("FW0")), CValue(178.0)));
  assert(valueMatch(test10.getValue(CPos("FX0")), CValue(179.0)));
  assert(valueMatch(test10.getValue(CPos("FY0")), CValue(180.0)));
  assert(valueMatch(test10.getValue(CPos("FZ0")), CValue(181.0)));
  assert(valueMatch(test10.getValue(CPos("GA0")), CValue(182.0)));
  assert(valueMatch(test10.getValue(CPos("GB0")), CValue(183.0)));
  assert(valueMatch(test10.getValue(CPos("GC0")), CValue(184.0)));
  assert(valueMatch(test10.getValue(CPos("GD0")), CValue(185.0)));
  assert(valueMatch(test10.getValue(CPos("GE0")), CValue(186.0)));
  assert(valueMatch(test10.getValue(CPos("GF0")), CValue(187.0)));
  assert(valueMatch(test10.getValue(CPos("GG0")), CValue(188.0)));
  assert(valueMatch(test10.getValue(CPos("GH0")), CValue(189.0)));
  assert(valueMatch(test10.getValue(CPos("GI0")), CValue(190.0)));
  assert(valueMatch(test10.getValue(CPos("GJ0")), CValue(191.0)));
  assert(valueMatch(test10.getValue(CPos("GK0")), CValue(192.0)));
  assert(valueMatch(test10.getValue(CPos("GL0")), CValue(193.0)));
  assert(valueMatch(test10.getValue(CPos("GM0")), CValue(194.0)));
  assert(valueMatch(test10.getValue(CPos("GN0")), CValue(195.0)));
  assert(valueMatch(test10.getValue(CPos("GO0")), CValue(196.0)));
  assert(valueMatch(test10.getValue(CPos("GP0")), CValue(197.0)));
  assert(valueMatch(test10.getValue(CPos("GQ0")), CValue(198.0)));
  assert(valueMatch(test10.getValue(CPos("GR0")), CValue(199.0)));
  assert(valueMatch(test10.getValue(CPos("GS0")), CValue(200.0)));

  return EXIT_SUCCESS;
}
#endif /* __PROGTEST__ */
