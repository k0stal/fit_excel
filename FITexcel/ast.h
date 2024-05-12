#ifndef AST_H
#define AST_H

#include <cstdlib>
#include <variant>
#include <iostream>
#include <string>
#include <set>
#include <map>

#include "position.h"
#include "value.h"

using namespace std::literals;
using CValue = std::variant<std::monostate, double, std::string>;

class ASTNode {
    public:
        virtual ~ASTNode() = default;
        virtual CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const = 0;
        virtual std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const = 0;
        virtual void print ( std::ostream & os ) const = 0;
        virtual bool detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const = 0;
        friend std::ostream & operator << ( std::ostream & os, const ASTNode & node );
};

// OPERATORS ---------------------------------------------------------------------

class ASTBinaryOperation : public ASTNode {
    public: 
        ASTBinaryOperation( std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right );
        bool detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void printParenthesies( std::ostream & os, const std::string & op ) const;
    protected:
        std::unique_ptr<ASTNode> left;
        std::unique_ptr<ASTNode> right;
};

class ASTUnaryOperation : public ASTNode {
    public: 
        ASTUnaryOperation( std::unique_ptr<ASTNode> node );
        bool detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
    protected:
        std::unique_ptr<ASTNode> node;
};

// BINARY OPERATIONS ---------------------------------------------------------------------

class ASTAddition : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTSubtraction : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTMultiplication : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTDivision : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTPower : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTEqual : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTNotEqual : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTLess : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTLessOrEqual : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTGreater : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

class ASTGreaterOrEqual : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

// UNARY OPERATORS ---------------------------------------------------------------------

class ASTNegative : public ASTUnaryOperation {
    public:
        using ASTUnaryOperation::ASTUnaryOperation;
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;     
};

// VALUES ---------------------------------------------------------------------

class ASTStringValue : public ASTNode {
    public:
        ASTStringValue ( const std::string & str );
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        bool detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override { return false; }
    private:
        std::string value;
};

class ASTDoubleValue : public ASTNode {
    public:
        ASTDoubleValue ( const double val );
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        bool detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override { return false; }
    private:
        double value;
};

// REFFERENCES ---------------------------------------------------------------------

class ASTRefference : public ASTNode {
    public:
        ASTRefference ( const CPos & pos ); 
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        bool detectCycle( const CPos & pos, std::set<CPos> & visited, std::set<CPos> & stack, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
    private:
        CPos pos;
};

#endif // AST_H