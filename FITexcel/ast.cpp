#include "ast.h"

std::ostream & operator << ( std::ostream& os, const ASTNode & node ) {
    node . print( os );
}

// BINARY OPERATIONS

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

CValue ASTAddition::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) + this->right->evaluate(map);
}

void ASTAddition::print(std::ostream& os) const {
    printParenthesies(os, "+");
}

CValue ASTSubtraction::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) - this->right->evaluate(map);
}

void ASTSubtraction::print(std::ostream& os) const {
    printParenthesies(os, "-");
}

CValue ASTMultiplication::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) * this->right->evaluate(map);
}

void ASTMultiplication::print(std::ostream& os) const {
    printParenthesies(os, "*");
}

CValue ASTDivision::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) / this->right->evaluate(map);
}

void ASTDivision::print(std::ostream& os) const {
    printParenthesies(os, "/");
}

CValue ASTPower::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) ^ this->right->evaluate(map);
}

void ASTPower::print(std::ostream& os) const {
    printParenthesies(os, "^");
}

CValue ASTEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) == this->right->evaluate(map);
}

void ASTEqual::print(std::ostream& os) const {
    printParenthesies(os, "==");
}

CValue ASTNotEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) != this->right->evaluate(map);
}

void ASTNotEqual::print(std::ostream& os) const {
    printParenthesies(os, "!=");
}

CValue ASTLess::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) < this->right->evaluate(map);
}

void ASTLess::print(std::ostream& os) const {
    printParenthesies(os, "<");
}

CValue ASTLessOrEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) <= this->right->evaluate(map);
}

void ASTLessOrEqual::print(std::ostream& os) const {
    printParenthesies(os, "<=");
}

CValue ASTGreater::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) > this->right->evaluate(map);
}

void ASTGreater::print(std::ostream& os) const {
    printParenthesies(os, ">");
}

CValue ASTGreaterOrEqual::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return this->left->evaluate( map ) >= this->right->evaluate(map);
}

void ASTGreaterOrEqual::print(std::ostream& os) const {
    printParenthesies(os, ">=");
}

// UNARY OPERATOR

ASTUnaryOperation::ASTUnaryOperation ( std::unique_ptr<ASTNode> node): 
    node(std::move(node)) {}

std::unique_ptr<ASTNode> ASTUnaryOperation::copy ( const CPos & pos ) const {
    return std::make_unique<ASTUnaryOperation>(this->node->copy( pos ));
}

CValue ASTNegative::evaluate(const std::map<CPos, std::unique_ptr<ASTNode>>& map) const {
    return -(this->node->evaluate(map));   // fix
}

void ASTNegative::print ( std::ostream & os ) const {
    os << "-";
    node->print( os );
}

// VAlUES

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

ASTDoubleValue::ASTDoubleValue ( const double val ):
    value ( val ) {}

CValue ASTDoubleValue::evaluate( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    return value;
}

void ASTDoubleValue::print( std::ostream & os ) const {
    os << value;
}

std::unique_ptr<ASTNode> ASTDoubleValue::copy( const CPos & pos ) const {
    return std::make_unique<ASTDoubleValue>( this->value );
}

// REFFERENCE

ASTRefference::ASTRefference ( std::string & str ):  // string / string_view?
    pos( str ) {}

CValue ASTRefference::evaluate( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const {
    return map.find( this->pos )->second->evaluate( map );
}

void ASTRefference::print( std::ostream & os ) const {
    os << pos;
}

// RANGE

ASTRange::ASTRange ( CPos & start, CPos & end ):  // implement split within expression method
    startPos ( start ),
    endPos ( end ) {}

std::unique_ptr<ASTNode> ASTRefference::copy( const CPos & pos ) const {
    return std::make_unique<ASTRefference>( this->pos.copy( pos ) );
}

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
    return std::make_unique<ASTRange>( startPos.copy(pos), endPos.copy(pos) );
}