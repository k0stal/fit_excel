#include "expression.h"

ASTBuilder::ASTBuilder( const std::string & expr ):
    stack() {
    parseExpression( expr, *this );
}

void ASTBuilder::opAdd() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTAddition>(std::move(left), std::move(right)));
}

void ASTBuilder::opSub() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTSubtraction>(std::move(right), std::move(left)));
}

void ASTBuilder::opMul() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTMultiplication>(std::move(left), std::move(right)));
}

void ASTBuilder::opDiv() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTDivision>(std::move(right), std::move(left)));
}

void ASTBuilder::opPow() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTPower>(std::move(right), std::move(left)));
}

void ASTBuilder::opNeg() {
    std::unique_ptr<ASTNode> node = std::move(stack.top());
    stack.pop();
    stack.push(std::make_unique<ASTNegative>(std::move(node)));
}

void ASTBuilder::opEq() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTEqual>(std::move(left), std::move(right))); 
}

void ASTBuilder::opNe() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTNotEqual>(std::move(left), std::move(right))); 
}

void ASTBuilder::opLt() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTLess>(std::move(right), std::move(left))); 
}

void ASTBuilder::opLe() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTLessOrEqual>(std::move(right), std::move(left))); 
}

void ASTBuilder::opGt() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTGreater>(std::move(right), std::move(left))); 
}

void ASTBuilder::opGe() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTGreaterOrEqual>(std::move(right), std::move(left))); 
}

void ASTBuilder::valNumber( double val ) {
    stack.push(std::make_unique<ASTDoubleValue>(val));
}

void ASTBuilder::valString(std::string val) {
    stack.push(std::make_unique<ASTStringValue>(val));  
}

void ASTBuilder::valReference(std::string val) {
    CPos pos (val);
    stack.push(std::make_unique<ASTRefference>(pos));
}

/*

void ASTBuilder::valRange(std::string val) {
    size_t pos = val.find(':');
    if (pos == std::string::npos) {
        throw std::invalid_argument("Invalid cell range identification");
    }
    stack.push(std::make_unique<ASTRange>(val.substr(0, pos), val.substr(pos + 1)));
}

void ASTBuilder::funcCall(std::string fnName, int paramCount) {
    if (fnName == "sum") {
        validStack(1);
        std::shared_ptr<ASTNode> range = std::move(stack.top());
        stack.pop();
        stack.push(std::make_unique<ASTSum>(std::move(range)));
    } else if (fnName == "count") {
        validStack(1);
        std::shared_ptr<ASTNode> range = std::move(stack.top());
        stack.pop();
        stack.push(std::make_unique<ASTCount>(std::move(range)));
    } else if (fnName == "min") {
        validStack(1);
        std::shared_ptr<ASTNode> range = std::move(stack.top());
        stack.pop();
        stack.push(std::make_unique<ASTMin>(std::move(range)));
    } else if (fnName == "max") {
        validStack(1);
        std::shared_ptr<ASTNode> range = std::move(stack.top());
        stack.pop();
        stack.push(std::make_unique<ASTMax>(std::move(range)));
    } else if (fnName == "countval") {
        validStack(2);
        std::shared_ptr<ASTNode> value = std::move(stack.top());
        stack.pop();
        std::shared_ptr<ASTNode> range = std::move(stack.top());
        stack.pop();
        stack.push(std::make_unique<ASTCountVal>(std::move(value), std::move(range)));
    } else if (fnName == "if") {
        validStack(3);
        std::shared_ptr<ASTNode> cond = std::move(stack.top());
        stack.pop();
        std::shared_ptr<ASTNode> ifTrue = std::move(stack.top());
        stack.pop();
        std::shared_ptr<ASTNode> ifFalse = std::move(stack.top());
        stack.pop();
        stack.push(std::make_unique<ASTIf>(std::move(cond), std::move(ifTrue), std::move(ifFalse)));
    } else {
        throw std::invalid_argument("Unsupported function: " + fnName);
    }
}

*/

void ASTBuilder::getLast ( std::unique_ptr<ASTNode> & root ) {
    validStack ( 1 );
    root = std::move(stack.top());
//    root->print( std::cout );
//    std::cout << std::endl;
    stack.pop();
}

void ASTBuilder::binaryOpSetUp ( std::unique_ptr<ASTNode> & left, std::unique_ptr<ASTNode> & right ) {
    //validStack ( 2 );
    left = std::move(stack.top());
    stack.pop();
    right = std::move(stack.top());
    stack.pop();
}

void ASTBuilder::validStack( size_t size ) {
    if ( stack.size() != size )
        throw std::invalid_argument("");
}