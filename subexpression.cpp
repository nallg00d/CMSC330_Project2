#include <iostream>
using namespace std;

#include "expression.h"
#include "subexpression.h"
#include "operand.h"
#include "plus.h"
#include "minus.h"
#include "times.h"
#include "divide.h"
#include "ge.h"
#include "geq.h"
#include "le.h"
#include "leq.h"
#include "eq.h"
#include "not.h"
#include "and.h"
#include "or.h"
#include "tern.h"

SubExpression::SubExpression(Expression* left, Expression* right)
{
    this->left = left;
    this->right = right;
}

Expression* SubExpression::parse()
{
    Expression* left;
    Expression* right;
    Expression *tern;
    char operation, paren, junk;

    left = Operand::parse(); // x
    cin >> operation;       // <
    right = Operand::parse();   // y

    cin >> ws;
    if(cin.peek() == '?') {

        // get rid of question mark
        cin >> junk;

        // get rid of paren
        cin >> paren;

        tern = SubExpression::parse();
    }

    cin >> paren;

    switch (operation)
    {
        case '+':
            return new Plus(left, right);
        case '-':
            return new Minus(left, right);
        case '*':
            return new Times(left, right);
        case '/':
            return new Divide(left, right);

        // Hnadling in the event it's greater than or equal
        case '>':
            if(cin.peek() == '=') {
                cin >> junk;    // get rid of =
                return new Geq(left, right);
            }
            else {
                return new Ge(left, right);
            }

            // handling if it's less than or less than or equal too
        case '<':
            if(cin.peek() == '=') {
                cin >> junk;    // Get rid of  =
                return new Leq(left, right);
            }
            else {
                return new Le(left, right);
            }
        case '=':
            return new Eq(left, right);
        case '&':
            return new And(left, right);
        case '|':
            return new Or(left, right);
        case '!':
            return new Not(left, right);
        case ':':
            // if Expr on the left is true, then value
            // need to do a check if literal or variable
            //tern = SubExpression::parse();
            return new Tern(left, right, tern);
    }

    //f
    return 0;
}
        