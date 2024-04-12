#include "ast.h"

std::ostream & operator << ( std::ostream& os, const ASTNode & node ) {
    node . print( os );
}

// BINARY OPERATIONS ------------------------------------------------------------

ASTBinaryOperation::ASTBinaryOperation ( std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right): 
    left(std::move(left)), 
    right(std::move(right)) {}

std::unique_ptr<ASTNode> ASTBinaryOperation::copy ( const CPos & pos ) const {
    return std::make_unique<ASTBinaryOperation>( this->left->copy( pos ), this->right->copy( pos ) );
}

void ASTBinaryOperation::printParenthesies( std::ostream & os, const std::string & op ) const {
    os << "("; 
    this->left->print(os);
    os << op;
    this->right->print(os);
    os << ")"; 
}

// ADDITION ---------------------------------------------------------------------

CValue ASTAddition::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) + this->right->evaluate(map);
}

void ASTAddition::print(std::ostream& os) const {
    printParenthesies(os, "+");
}

// SUBTRACTION ------------------------------------------------------------------

CValue ASTSubtraction::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) - this->right->evaluate(map);
}

void ASTSubtraction::print(std::ostream& os) const {
    printParenthesies(os, "-");
}

// MULTIPLICATION ---------------------------------------------------------------

CValue ASTMultiplication::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) * this->right->evaluate(map);
}

void ASTMultiplication::print(std::ostream& os) const {
    printParenthesies(os, "*");
}

// DIVISION ---------------------------------------------------------------------

CValue ASTDivision::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) / this->right->evaluate(map);
}

void ASTDivision::print(std::ostream& os) const {
    printParenthesies(os, "/");
}

// POWER ------------------------------------------------------------------------

CValue ASTPower::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) ^ this->right->evaluate(map);
}

void ASTPower::print(std::ostream& os) const {
    printParenthesies(os, "^");
}

// EQUAL ------------------------------------------------------------------------

CValue ASTEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) == this->right->evaluate(map);
}

void ASTEqual::print(std::ostream& os) const {
    printParenthesies(os, "==");
}

// NOT EQUAL --------------------------------------------------------------------

CValue ASTNotEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) != this->right->evaluate(map);
}

void ASTNotEqual::print(std::ostream& os) const {
    printParenthesies(os, "!=");
}

// LESS THAN --------------------------------------------------------------------

CValue ASTLess::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) < this->right->evaluate(map);
}

void ASTLess::print(std::ostream& os) const {
    printParenthesies(os, "<");
}

// LESS THAN OR EQUAL TO ---------------------------------------------------------

CValue ASTLessOrEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) <= this->right->evaluate(map);
}

void ASTLessOrEqual::print(std::ostream& os) const {
    printParenthesies(os, "<=");
}

// GREATER THAN -----------------------------------------------------------------

CValue ASTGreater::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) > this->right->evaluate(map);
}

void ASTGreater::print(std::ostream& os) const {
    printParenthesies(os, ">");
}

// GREATER THAN OR EQUAL TO ------------------------------------------------------

CValue ASTGreaterOrEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) >= this->right->evaluate(map);
}

void ASTGreaterOrEqual::print(std::ostream& os) const {
    printParenthesies(os, ">=");
}

// UNARY OPERATOR ---------------------------------------------------------------

ASTUnaryOperation::ASTUnaryOperation ( std::unique_ptr<ASTNode> node): 
    node(std::move(node)) {}

std::unique_ptr<ASTNode> ASTUnaryOperation::copy ( const CPos & pos ) const {
    return std::make_unique<ASTUnaryOperation>(this->node->copy( pos ));
}

// NEGATIVE ---------------------------------------------------------------------

CValue ASTNegative::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return -(this->node->evaluate(map));  
}

void ASTNegative::print ( std::ostream & os ) const {
    os << "-";
    node->print( os );
}

// VALUES -----------------------------------------------------------------------
// STRING VALUE -----------------------------------------------------------------

ASTStringValue::ASTStringValue( const std::string & str ):
    value( str ) {}

CValue ASTStringValue::evaluate( const std::map<CPos, std::unique_ptr<ASTNode>>& map ) const {
    return this->value;
}

void ASTStringValue::print( std::ostream & os ) const {
    os << value;
}

std::unique_ptr<ASTNode> ASTStringValue::copy( const CPos& pos ) const {
    return std::make_unique<ASTStringValue> ( this->value );
}

// DOUBLE VALUE -----------------------------------------------------------------

ASTDoubleValue::ASTDoubleValue ( const double val ):
    value ( val ) {}

CValue ASTDoubleValue::evaluate( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    return this->value;
}

void ASTDoubleValue::print( std::ostream & os ) const {
    os << value;
}

std::unique_ptr<ASTNode> ASTDoubleValue::copy( const CPos & pos ) const {
    return std::make_unique<ASTDoubleValue>( this->value );
}

// REFFERENCE -------------------------------------------------------------------

ASTRefference::ASTRefference ( std::string & str ):  
    pos( str ) {}

CValue ASTRefference::evaluate( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    return map.find( this->pos )->second->evaluate( map );
}

void ASTRefference::print( std::ostream & os ) const {
    os << pos;
}

std::unique_ptr<ASTNode> ASTRefference::copy ( const CPos & pos ) const {
    return std::make_unique<ASTRefference>( this->pos.copy( pos ) );
}

// RANGE ------------------------------------------------------------------------

ASTRange::ASTRange ( CPos & start, CPos & end ):  
    startPos ( start ),
    endPos ( end ) {}

CValue ASTRange::evaluate( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    return std::monostate{};   // should not be called
}

std::vector<CValue> & ASTRange::evaluateRange ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    std::vector<CPos> positoins = rectItertion( startPos, endPos );
    std::vector<CValue> values = {};
    for ( const auto & pos : positoins )    
        values . push_back ( map.find(pos)->second->evaluate(map) );
    return values;
}

void ASTRange::print( std::ostream & os ) const {
    os << startPos << ":" << endPos;
}

std::unique_ptr<ASTNode> ASTRange::copy( const CPos & pos ) const {
    return std::make_unique<ASTRange>( this->startPos.copy(pos), this->endPos.copy(pos) );
}

// FUNCTIONS --------------------------------------------------------------------
// RANGE FUNCTION ---------------------------------------------------------------

ASTRangeFunction::ASTRangeFunction ( std::unique_ptr<ASTRange> range ):
    range(std::move(range)) {}

std::unique_ptr<ASTNode> ASTRangeFunction::copy ( const CPos & pos ) const {
    return std::make_unique<ASTRangeFunction>( this->range );
}

void ASTRangeFunction::printRangeFunction ( std::ostream & os, const std::string & func ) const {
    os << func << " (";
    this->range->print( os );
    os << ")";
}

// SUM --------------------------------------------------------------------------

CValue ASTSum::evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    std::vector<CValue> values = this->range->evaluateRange( map );
    CValue sum = values[0];
    for ( size_t i = 1; i < values.size(); i++ )
        sum = sum + values[i];
    return sum;
}

void ASTSum::print ( std::ostream & os ) const {
    printRangeFunction( os, "sum" );
}

// COUNT ------------------------------------------------------------------------

CValue ASTCount::evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    std::vector<CValue> values = this->range->evaluateRange( map );
    CValue count = 0.0;
    for( size_t i = 0; i < values.size(); i++ )
        if ( !std::holds_alternative<std::monostate>(values[i]) )
            count = count + 1.0;
    return count;
}

void ASTCount::print ( std::ostream & os ) const {
    printRangeFunction( os, "sum" );
}

// MIN --------------------------------------------------------------------------

CValue ASTMin::evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    std::vector<CValue> values = this->range->evaluateRange( map );
    CValue min = std::monostate{};
    bool init = true;
    for ( size_t i = 0; i < values.size(); i++ ) {
        if ( init && std::holds_alternative<bool>(values[i]) ) {
            min = values[i];
            continue;
        }

        if ( std::holds_alternative<bool>(values[i] < min) && std::get<double>(values[i] < min) )
            min = values[i];
    }
    return min;
}

void ASTMin::print ( std::ostream & os ) const {
    printRangeFunction( os, "sum" );
}

// MAX --------------------------------------------------------------------------

CValue ASTMax::evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    std::vector<CValue> values = this->range->evaluateRange( map );
    CValue max = std::monostate{};
    bool init = true;
    for ( size_t i = 0; i < values.size(); i++ ) {
        if ( init && std::holds_alternative<bool>(values[i]) ) {
            max = values[i];
            continue;
        }

        if ( std::holds_alternative<bool>(values[i] > max) && std::get<double>(values[i] > max) )
            max = values[i];
    }
    return max;
}

void ASTMax::print ( std::ostream & os ) const {
    printRangeFunction( os, "sum" );
}

// COUNT VALUE ------------------------------------------------------------------

ASTCountVal::ASTCountVal( std::unique_ptr<ASTNode> val, std::unique_ptr<ASTRange> range ):
    val(std::move(val)),
    range(std::move(range)) {}

std::unique_ptr<ASTNode> ASTCountVal::copy ( const CPos & pos ) const {
    return std::make_unique<ASTCountVal>( this->val->copy( pos ), this->range->copy ( pos ) );
}

CValue ASTCountVal::evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    std::vector<CValue> values = this->range->evaluateRange( map );
    CValue count = 0.0;
    for ( size_t i = 0; i < values.size(); i++ ) {
        CValue valEval = val->evaluate(map);
        if ( std::holds_alternative<bool>(values[i] == valEval) && std::get<double>(values[i] == valEval) )
            count = count + 1.0;
    }
    return count;
}

void ASTCountVal::print ( std::ostream & os ) const {
    os << "countval (";
    val->print(os);
    os << ", ";
    range->print(os);
    os << ")";
}

// IF ---------------------------------------------------------------------------

ASTIf::ASTIf( std::unique_ptr<ASTNode> cond, std::unique_ptr<ASTNode> ifTrue, std::unique_ptr<ASTNode> ifFalse ):
    cond(std::move(cond)),
    ifTrue(std::move(ifTrue)),
    ifFalse(std::move(ifFalse)) {}

std::unique_ptr<ASTNode> ASTIf::copy ( const CPos & pos ) const {
    return std::make_unique<ASTIf>( cond->copy( pos ), ifTrue->copy( pos ), ifFalse->copy( pos ) );
}

CValue ASTIf::evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    CValue condEval = cond->evaluate( map );
    if ( std::holds_alternative<bool>( condEval) )
        return ifTrue->evaluate ( map );
    else
        return ifFalse->evaluate ( map );
}

void ASTIf::print ( std::ostream & os ) const {
    os << "if (";
    cond->print(os);
    os << ", ";
    ifTrue->print(os);
    os << ", ";
    ifFalse->print(os);
    os << ")"; 
}
