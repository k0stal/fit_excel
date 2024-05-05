#include "ast.h"

std::ostream & operator << ( std::ostream & os, ASTNode * node ) {
    node->print( os );
    return os;
}

// BINARY OPERATIONS ------------------------------------------------------------

ASTBinaryOperation::ASTBinaryOperation ( std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right): 
    left(std::move(left)), 
    right(std::move(right)) {}

bool ASTBinaryOperation::detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    if ( !this->left->detectCycle ( pos, visited, stack, map ) )
        return this->right->detectCycle ( pos, visited, stack, map );
    return true;
}

void ASTBinaryOperation::printParenthesies( std::ostream & os, const std::string & op ) const {
    os << "(";
    this->left->print( os ); 
    os << op;
    this->right->print( os );
    os << ")";
}

// ADDITION ---------------------------------------------------------------------

CValue ASTAddition::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate(map) + this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTAddition::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTAddition>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTAddition::print(std::ostream& os) const {
    printParenthesies(os, "+");
}

// SUBTRACTION ------------------------------------------------------------------

CValue ASTSubtraction::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) - this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTSubtraction::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTSubtraction>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTSubtraction::print(std::ostream& os) const {
    printParenthesies(os, "-");
}

// MULTIPLICATION ---------------------------------------------------------------

CValue ASTMultiplication::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) * this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTMultiplication::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTMultiplication>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTMultiplication::print(std::ostream& os) const {
    printParenthesies(os, "*");
}

// DIVISION ---------------------------------------------------------------------

CValue ASTDivision::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) / this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTDivision::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTDivision>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTDivision::print(std::ostream& os) const {
    printParenthesies(os, "/");
}

// POWER ------------------------------------------------------------------------

CValue ASTPower::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) ^ this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTPower::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTPower>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTPower::print(std::ostream& os) const {
    printParenthesies(os, "^");
}

// EQUAL ------------------------------------------------------------------------

CValue ASTEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) == this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTEqual::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTEqual>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTEqual::print(std::ostream& os) const {
    printParenthesies(os, "=");
}

// NOT EQUAL --------------------------------------------------------------------

CValue ASTNotEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) != this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTNotEqual::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTNotEqual>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTNotEqual::print(std::ostream& os) const {
    printParenthesies(os, "<>");
}

// LESS THAN --------------------------------------------------------------------

CValue ASTLess::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) < this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTLess::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTLess>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTLess::print(std::ostream& os) const {
    printParenthesies(os, "<");
}

// LESS THAN OR EQUAL TO ---------------------------------------------------------

CValue ASTLessOrEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) <= this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTLessOrEqual::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTLessOrEqual>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTLessOrEqual::print(std::ostream& os) const {
    printParenthesies(os, "<=");
}

// GREATER THAN -----------------------------------------------------------------

CValue ASTGreater::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) > this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTGreater::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTGreater>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTGreater::print(std::ostream& os) const {
    printParenthesies(os, ">");
}

// GREATER THAN OR EQUAL TO ------------------------------------------------------

CValue ASTGreaterOrEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return this->left->evaluate( map ) >= this->right->evaluate(map);
}

std::unique_ptr<ASTNode> ASTGreaterOrEqual::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTGreaterOrEqual>( this->left->copy( delta ), this->right->copy( delta ) ); 
}

void ASTGreaterOrEqual::print(std::ostream& os) const {
    printParenthesies(os, ">=");
}

// UNARY OPERATOR ---------------------------------------------------------------

ASTUnaryOperation::ASTUnaryOperation ( std::unique_ptr<ASTNode> node): 
    node(std::move(node)) {}

bool ASTUnaryOperation::detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    return this->node->detectCycle ( pos, visited, stack, map );
}    

// NEGATIVE ---------------------------------------------------------------------

CValue ASTNegative::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>> & map) const {
    return -(this->node->evaluate(map));  
}

std::unique_ptr<ASTNode> ASTNegative::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTNegative>(this->node->copy( delta ));
}

void ASTNegative::print ( std::ostream & os ) const {
    os << "(-";
    this->node->print( os );
    os << ")";
}

// VALUES -----------------------------------------------------------------------
// STRING VALUE -----------------------------------------------------------------

ASTStringValue::ASTStringValue( const std::string & str ):
    value( str ) {}

CValue ASTStringValue::evaluate( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    return this->value;
}

void ASTStringValue::print(std::ostream& os) const {
    os << "\"";
    for (char c : value) {
        if (c == '"')
            os << '"';
        os << c;
    }
    os << "\"";
    }

std::unique_ptr<ASTNode> ASTStringValue::copy( const std::pair<int, int> & delta ) const {
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

std::unique_ptr<ASTNode> ASTDoubleValue::copy( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTDoubleValue>( this->value );
}

// REFFERENCE -------------------------------------------------------------------

ASTRefference::ASTRefference ( const CPos & pos ):
    pos ( pos ) {}

CValue ASTRefference::evaluate( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    auto it = map.find( this->pos );
    if ( it != map.end() )
        return it->second->evaluate( map );
    return std::monostate{};
}

void ASTRefference::print( std::ostream & os ) const {
    os << pos;
}

std::unique_ptr<ASTNode> ASTRefference::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTRefference>( this->pos.copy( delta ) );
}

bool ASTRefference::detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const { 
    visited . emplace ( pos );
    stack . emplace ( pos );

    auto mIt = map . find ( this->pos );
    if ( mIt == map . end() )
        return false;

    auto vIt = visited . find ( mIt->first );
    auto sIt = stack . find ( mIt->first );
        
    if ( vIt == visited . end() && mIt->second->detectCycle( this->pos, visited, stack, map ) )
        return true;
    else if ( sIt != stack . end() )
        return true;

    stack . erase ( pos );
    return false;
}

// RANGE ------------------------------------------------------------------------

ASTRange::ASTRange ( const CPos & start, const CPos & end ):
    startPos( start ),
    endPos( end ) {} 

CValue ASTRange::evaluate( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    return std::monostate{};
}

void ASTRange::evaluateRange ( std::vector<CValue> & values, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    std::vector<CPos> positoins = {};
    rectIterationPos( positoins, startPos, endPos );
    for ( const auto & pos : positoins )    
        values . push_back ( map.find(pos)->second->evaluate(map) );
}

void ASTRange::print( std::ostream & os ) const {
    os << startPos << ":" << endPos;
}

std::unique_ptr<ASTNode> ASTRange::copy ( const std::pair<int, int> & delta ) const {
    return std::make_unique<ASTRange>( this->startPos.copy(delta), this->endPos.copy(delta) );
}

bool ASTRange::detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    return false; 
}
