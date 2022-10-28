#ifndef _EXPR_HPP
#define _EXPR_HPP

#include <cstdlib>
#include <sstream>
#include <string>

class Expression {
 protected:
  long value;

 public:
  Expression() : value(0) {}
  Expression(long val) : value(val) {}
  virtual ~Expression() {}
  long getValue() { return value; }
  virtual std::string toString() const = 0;
};

class NumExpression : public Expression {
 public:
  NumExpression() : Expression() {}
  NumExpression(long val) : Expression(val) {}
  virtual ~NumExpression() {}
  virtual std::string toString() const {
    std::stringstream ss;
    ss << this->value;
    return ss.str();
  }
};

class PlusExpression : public Expression {
 private:
  Expression *lhs, *rhs;

 public:
  PlusExpression() : Expression() {}
  PlusExpression(Expression * lhs, Expression * rhs) :
      Expression(lhs->getValue() + rhs->getValue()), lhs(lhs), rhs(rhs) {}
  virtual ~PlusExpression() {
    delete lhs;
    delete rhs;
  }
  virtual std::string toString() const {
    return "(" + lhs->toString() + " + " + rhs->toString() + ")";
  }
};

#endif
