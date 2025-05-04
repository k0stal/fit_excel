#include "expression.h"

ASTBuilder::ASTBuilder():
    stack() {}

void ASTBuilder::opAdd() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTAddition>(std::move(right), std::move(left)));
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
    stack.push(std::make_unique<ASTMultiplication>(std::move(right), std::move(left)));
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
    stack.push(std::make_unique<ASTEqual>(std::move(right), std::move(left))); 
}

void ASTBuilder::opNe() {
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;
    binaryOpSetUp(left, right);
    stack.push(std::make_unique<ASTNotEqual>(std::move(right), std::move(left))); 
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
    std::string mod = "";
    std::pair<bool, bool> fixation = extractFixation ( val, mod );
    CPos pos (mod);
    pos . addFixation ( fixation );
    stack.push(std::make_unique<ASTReference>(pos));
}

bool ASTBuilder::getLast ( std::unique_ptr<ASTNode> & root ) {
    if ( stack.size() != 1 || !validBuild ) {
        throw std::invalid_argument("Invalid heap size.");
        return false;
    }
    root = std::move(stack.top());
    stack.pop();
    return true;
}

std::pair<bool, bool> ASTBuilder::extractFixation ( std::string & valOrig, std::string & valMod ) {
    std::pair<bool, bool> fixation = {false, false};
    if (valOrig.empty())
        return fixation;

    auto it = valOrig.begin();

    if (*it == '$') {
        fixation.first = true;
        ++it;
    }

    for (; *it != '$' && it != valOrig.end(); ++it)
        valMod += *it;
    
    if (it == valOrig.end()) {
        return fixation;
    }

    if (*it == '$') {
        fixation.second = true;
        ++it;
    }    

    for (; it != valOrig.end(); ++it)
        valMod += *it;

    return fixation;
}

void ASTBuilder::binaryOpSetUp ( std::unique_ptr<ASTNode> & left, std::unique_ptr<ASTNode> & right ) {
    if ( stack.size() < 2 ) {
        throw std::invalid_argument("Invalid heap size.");
         validBuild = false;
    }
    left = std::move(stack.top());
    stack.pop();
    right = std::move(stack.top());
    stack.pop();
}