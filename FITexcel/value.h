#ifndef VALUE_H
#define VALUE_H

#include <cstdlib>
#include <cmath>
#include <string>
#include <variant>

/**
 * Type alias for supported cell values.
 * - std::monostate: Represents an empty or invalid value.
 * - double: Represents numeric values.
 * - std::string: Represents string values.
 */
using CValue = std::variant<std::monostate, double, std::string>;

using namespace std::literals;

/**
 * Arithmetic and comparison operators overloaded for CValue.
 * All operations return std::monostate if operands are invalid/incompatible.
 */

/**
 * Add two CValue values (numeric or string concatenation).
 * @param a First operand.
 * @param b Second operand.
 * @return Result of addition or std::monostate on error.
 */
CValue operator + ( const CValue & a, const CValue & b );

/**
 * Subtract one CValue from another.
 * @param a First operand.
 * @param b Second operand.
 * @return Result or std::monostate if invalid.
 */
CValue operator - ( const CValue & a, const CValue & b );

/**
 * Unary negation for numeric CValue.
 * @param a Operand.
 * @return -a or std::monostate if not numeric.
 */
CValue operator - ( const CValue & a );

/**
 * Multiply two CValues.
 * @param a First operand.
 * @param b Second operand.
 * @return Result or std::monostate on error.
 */
CValue operator * ( const CValue & a, const CValue & b );

/**
 * Divide two CValues.
 * @param a Numerator.
 * @param b Denominator.
 * @return Result or std::monostate if invalid or division by zero.
 */
CValue operator / ( const CValue & a, const CValue & b );

/**
 * Raise one CValue to the power of another.
 * @param a Base.
 * @param b Exponent.
 * @return Result or std::monostate on invalid types.
 */
CValue operator ^ ( const CValue & a, const CValue & b );

/**
 * Compare two CValues for less-than.
 * @param a First operand.
 * @param b Second operand.
 * @return true or false as CValue, or std::monostate if incomparable.
 */
CValue operator < ( const CValue & a, const CValue & b );

/**
 * Compare two CValues for greater-than.
 * @param a First operand.
 * @param b Second operand.
 * @return true or false as CValue, or std::monostate if incomparable.
 */
CValue operator > ( const CValue & a, const CValue & b );

/**
 * Compare two CValues for equality.
 * @param a First operand.
 * @param b Second operand.
 * @return true or false as CValue.
 */
CValue operator == ( const CValue & a, const CValue & b );

/**
 * Compare two CValues for inequality.
 * @param a First operand.
 * @param b Second operand.
 * @return true or false as CValue.
 */
CValue operator != ( const CValue & a, const CValue & b );

/**
 * Compare two CValues for less-than-or-equal.
 * @param a First operand.
 * @param b Second operand.
 * @return true or false as CValue.
 */
CValue operator <= ( const CValue & a, const CValue & b );

/**
 * Compare two CValues for greater-than-or-equal.
 * @param a First operand.
 * @param b Second operand.
 * @return true or false as CValue.
 */
CValue operator >= ( const CValue & a, const CValue & b );

#endif // VALUE_H
