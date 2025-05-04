#ifndef expression_h_09845924528375
#define expression_h_09845924528375

#include <cstdlib>
#include <string>
#include <stack>
#include <utility>
#include <memory>

#include "ast.h"

/**
* Tempate class for storing the contents of input expression.
*/
class CExprBuilder {
    public:
        virtual void                       opAdd                                   () = 0;
        virtual void                       opSub                                   () = 0;
        virtual void                       opMul                                   () = 0;
        virtual void                       opDiv                                   () = 0;
        virtual void                       opPow                                   () = 0;
        virtual void                       opNeg                                   () = 0;
        virtual void                       opEq                                    () = 0;
        virtual void                       opNe                                    () = 0;
        virtual void                       opLt                                    () = 0;
        virtual void                       opLe                                    () = 0;
        virtual void                       opGt                                    () = 0;
        virtual void                       opGe                                    () = 0;
        virtual void                       valNumber                               ( double                                val ) = 0;
        virtual void                       valString                               ( std::string                           val ) = 0;
        virtual void                       valReference                            ( std::string                           val ) = 0;
        virtual void                       valRange                                ( std::string                           val ) = 0;
        virtual void                       funcCall                                ( std::string                           fnName,
                                                                                 int                                   paramCount ) = 0;
};


/**
* Function for parsing string expression. Calls methods from CExprBuilder based on detected symbols. Using postfix notation.
* @param expr string expression.
* @param builder template class for storing the contents of input expession.
*/
void                                   parseExpression                         ( std::string                           expr,
                                                                                 CExprBuilder                        & builder );

/**
* Class for constructing Abstract syntax tree (AST) from input expression.
*/
class ASTBuilder : public CExprBuilder {
    public:
        /**
        * Construct empty builder object.
        */
        ASTBuilder();

        /**
        * Add addition operation to AST tree.
        */
        void opAdd () override;

        /**
        * Add subtraction operation to AST tree.
        */
        void opSub () override;

        /**
        * Add multiplication operation to AST tree.
        */
        void opMul () override;

        /**
        * Add division operation to AST tree.
        */
        void opDiv () override;

        /**
        * Add power operation to AST tree.
        */
        void opPow () override;

        /**
        * Add negation operation to AST tree.
        */
        void opNeg () override;

        /**
        * Add equal operation to AST tree.
        */
        void opEq () override;

        /**
        * Add not-equal operation to AST tree.
        */
        void opNe () override;

        /**
        * Add less-than operation to AST tree.
        */
        void opLt () override;

        /**
        * Add less-or-equal operation to AST tree.
        */
        void opLe () override;

        /**
        * Add greather-than operation to AST tree.
        */
        void opGt () override;

        /**
        * Add greather-or-equal operation to AST tree.
        */
        void opGe () override;

        /**
        * Add number value to AST tree.
        * @param val double number.
        */
        void valNumber ( double val ) override;

        /**
        * Add string value to AST tree.
        * @param val string.
        */
        void valString ( std::string val ) override;

        /**
        * Add cell refrence to AST tree.
        * @param val string contaning valid cell position.
        */
        void valReference ( std::string val ) override;

        /**
        * Add value range to AST tree. Not implemented.
        * @param val string contaning value range.
        */
        void valRange ( std::string val ) override {};

        /**
        * Add function to AST tree. Not implemented.
        * @param fnName string contaning function name.
        * @param paramCount number of function parameters.
        */
        void funcCall (std::string fnName, int paramCount ) override {}; 

        /**
        * Return root of the AST tree.
        * @param root unique ASTNode pointer.
        * @return boolean value whether build was succesful.
        */
        bool getLast ( std::unique_ptr<ASTNode> & root );

    private:
        /**
        * Extract fixation from string. Return if fixation was detected and position string without it.
        * @param valOrig source string.
        * @param valMod modified output string without fixation.
        * @return boolean pair whether fixation was detected for given index.
        */
        std::pair<bool, bool> extractFixation ( std::string & valOrig, std::string & valMod );

        /**
        * Set up unique pointer for binary operation.
        * @param left unique ASTNode pointer.
        * @param right unique ASTNode pointer.
        */
        void binaryOpSetUp ( std::unique_ptr<ASTNode> & left, std::unique_ptr<ASTNode> & right );
        
        bool validBuild = true;
        std::stack<std::unique_ptr<ASTNode>> stack;
};

#endif /* expression_h_09845924528375 */
