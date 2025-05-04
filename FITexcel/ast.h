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

/**
 * Base class representing a node in an Abstract Syntax Tree (AST).
 */
class ASTNode {
    public:
        /**
         * Virtual destructor for ASTNode.
         */
        virtual ~ASTNode() = default;

        /**
         * Evaluate the ASTNode and compute its value.
         * @param map Map of stored cells in spreadsheet.
         * @return Computed value of the node.
         */
        virtual CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const = 0;

        /**
         * Create a deep copy of the ASTNode with a positional delta applied.
         * @param delta Pair of integers representing the positional delta.
         * @return Unique pointer to the copied node.
         */
        virtual std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const = 0;

        /**
         * Print the ASTNode to the specified output stream.
         * @param os Output stream reference.
         */
        virtual void print ( std::ostream & os ) const = 0;

        /**
         * Detect if the AST contains a cyclic dependency starting from the given position. Using DFS algorithm.
         * @param visited Set of visited positions.
         * @param map Map of stored cells in spreadsheet.
         * @return True if a cycle is detected, false otherwise.
         */
        virtual bool detectCycle( std::set<CPos> & visited, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const = 0;

        /**
         * Output operator for printing ASTNode to an output stream.
         * @param os Output stream reference.
         * @param node ASTNode reference.
         * @return Output stream reference.
         */
        friend std::ostream & operator << ( std::ostream & os, const ASTNode & node );
};

/**
 * Base class for binary operations in the AST.
 */
class ASTBinaryOperation : public ASTNode {
    public: 
        /**
         * Constructor for a binary operation node.
         * @param left Left operand node.
         * @param right Right operand node.
         */
        ASTBinaryOperation( std::unique_ptr<ASTNode> left, std::unique_ptr<ASTNode> right );

        /**
         * Detect cycles in a binary operation node.
         * @param visited Set of visited positions.
         * @param map Map of stored cells in spreadsheet.
         * @return True if a cycle is detected, false otherwise.
         */
        bool detectCycle( std::set<CPos> & visited, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;

        /**
         * Print the binary operation with parentheses and operator.
         * @param os Output stream reference.
         * @param op Operator string.
         */
        void printParenthesies( std::ostream & os, const std::string & op ) const;

    protected:
        std::unique_ptr<ASTNode> left; 
        std::unique_ptr<ASTNode> right;
};

/**
 * Base class for unary operations in the AST.
 */
class ASTUnaryOperation : public ASTNode {
    public: 
        /**
         * Constructor for a unary operation node.
         * @param node Operand node.
         */
        ASTUnaryOperation( std::unique_ptr<ASTNode> node );

        /**
         * Detect cycles in a unary operation node.
         * @param visited Set of visited positions.
         * @param map Mapping of positions to ASTNode pointers.
         * @return True if a cycle is detected, false otherwise.
         */
        bool detectCycle( std::set<CPos> & visited, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;

    protected:
        std::unique_ptr<ASTNode> node; ///< Operand.
};

/**
 * Represents addition operation in the AST.
 */
class ASTAddition : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        /**
         * Evaluate the addition operation.
         * @param map Mapping of positions to ASTNode pointers.
         * @return Result of the addition.
         */
        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;

        /**
         * Create a copy of the addition node with a positional delta.
         * @param delta Pair of integers representing the positional delta.
         * @return Unique pointer to the copied node.
         */
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;

        /**
         * Print the addition operation.
         * @param os Output stream reference.
         */
        void print ( std::ostream & os ) const override;
};

/**
 * Represents subtraction operation in the AST.
 */
class ASTSubtraction : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents multiplication operation in the AST.
 */
class ASTMultiplication : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents division operation in the AST.
 */
class ASTDivision : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents power operation in the AST.
 */
class ASTPower : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents equality operation in the AST.
 */
class ASTEqual : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents inequality operation in the AST.
 */
class ASTNotEqual : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents less-than comparison operation in the AST.
 */
class ASTLess : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents less-than-or-equal-to comparison in the AST.
 */
class ASTLessOrEqual : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents greater-than comparison operation in the AST.
 */
class ASTGreater : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents greater-than-or-equal-to comparison in the AST.
 */
class ASTGreaterOrEqual : public ASTBinaryOperation {
    public:
        using ASTBinaryOperation::ASTBinaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents negation operation in the AST.
 */
class ASTNegative : public ASTUnaryOperation {
    public:
        using ASTUnaryOperation::ASTUnaryOperation;

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        void print ( std::ostream & os ) const override;
};

/**
 * Represents a string value node in the AST.
 */
class ASTStringValue : public ASTNode {
    public:
        /**
         * Constructor for a string value node.
         * @param str String value.
         */
        ASTStringValue ( const std::string & str );

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;

        /**
         * Detect cycles in a string value node (always false).
         * @return False (string values cannot have cycles).
         */
        bool detectCycle( std::set<CPos> & visited, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override { return false; };

    private:
        std::string value;
};

/**
 * Represents a number value node in the AST.
 */
class ASTDoubleValue : public ASTNode {
    public:
        /**
         * Constructor for a number value node.
         * @param val Numeric value.
         */
        ASTDoubleValue ( const double val );

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;

        /**
         * Detect cycles in a number value node (always false).
         * @return False (number values cannot have cycles).
         */
        bool detectCycle( std::set<CPos> & visited, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override { return false; };

    private:
        double value;
};

/**
 * Represents a reference node in the AST.
 */
class ASTReference : public ASTNode {
    public:
        /**
         * Constructor for a reference node.
         * @param pos Position reference.
         */
        ASTReference ( const CPos & pos );

        CValue evaluate ( const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;
        void print ( std::ostream & os ) const override;
        std::unique_ptr<ASTNode> copy ( const std::pair<int, int> & delta ) const override;
        bool detectCycle( std::set<CPos> & visited, const std::map<CPos, std::unique_ptr<ASTNode>> & map ) const override;

    private:
        CPos pos;
};
#endif // AST_H
