#ifndef AST_H
#define AST_H

#include <cstdlib>
#include <iostream>
#include <string>
#include <map>

#include "position.h"
#include "value.h"

using namespace std::literals;
using CValue = std::variant<std::monostate, double, std::string>;

class ASTNode {
    public:
        virtual ~ASTNode() = default;
        virtual CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const = 0;
        virtual std::unique_ptr<ASTNode> copy ( const CPos & pos ) const = 0;
        virtual void print ( std::ostream & os ) const = 0;
};

// OPERATORS

class ASTBinaryOperation : public ASTNode {
    public: 
        ASTBinaryOperation( std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right );
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;
        void ASTBinaryOperation::printParenthesies( std::ostream & os, const std::string & op ) const;
    protected:
        std::unique_ptr<ASTNode> left;
        std::unique_ptr<ASTNode> right;
};

class ASTUnaryOperation : public ASTNode {
    public: 
        ASTUnaryOperation( std::unique_ptr<ASTNode> node );
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;

    protected:
        std::unique_ptr<ASTNode> node;
};

// BINARY OPERATIONS

class ASTAddition : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTSubtraction : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTMultiplication : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTDivision : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTPower : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTPower : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTEqual : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTNotEqual : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTLess : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTLessOrEqual : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTGreater : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTGreaterOrEqual : public ASTBinaryOperation {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

// UNARY OPERATORS

class ASTNegative : public ASTUnaryOperation {
    public:
        ASTNegative( std::unique_ptr<ASTNode> node );
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;        
};

// VALUES

class ASTStringValue : public ASTNode {
    public:
        ASTStringValue ( const std::string & str );
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;
    private:
        std::string value;
};

class ASTDoubleValue : public ASTNode {
    public:
        ASTDoubleValue ( const double val );
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;
    private:
        double value;
};

// REFFERENCES

class ASTRefference : public ASTNode {
    public:
        ASTRefference ( std::string & str );   // might be issue with reffrence to str
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;
    private:
        CPos pos;
};

class ASTRange : public ASTNode {
    public:
        ASTRange ( CPos & start, CPos & end );
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::vector<CValue> & evaluateRange ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;
    private:
        CPos startPos;
        CPos endPos;
};

// FUNCTION

class ASTRangeFunction : public ASTNode {
    public:
        ASTRangeFunction ( std::unique_ptr<ASTRange> range );
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;
        void printRangeFunction ( std::ostream & os, const std::string & func ) const;
    protected:
        std::unique_ptr<ASTRange> range;
};

class ASTSum : public ASTRangeFunction {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTCount : public ASTRangeFunction {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;    
};

class ASTMin : public ASTRangeFunction {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;    
};

class ASTMax : public ASTRangeFunction {
    public:
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;    
};

class ASTCountVal : public ASTNode {
    public:
        ASTCountVal( std::unique_ptr<ASTNode> val, std::unique_ptr<ASTRange> range );
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;  
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
    private:
        std::unique_ptr<ASTNode> val;
        std::unique_ptr<ASTRange> range;
};

class ASTIf : public ASTNode {
    public:
        ASTIf( std::unique_ptr<ASTNode> cond, std::unique_ptr<ASTNode> ifTrue, std::unique_ptr<ASTNode> ifFalse );
        std::unique_ptr<ASTNode> copy ( const CPos & pos ) const override;  
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
    private:
        std::unique_ptr<ASTNode> cond;
        std::unique_ptr<ASTNode> ifTrue;
        std::unique_ptr<ASTNode> ifFalse;
};

#endif // AST_H