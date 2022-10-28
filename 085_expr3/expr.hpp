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
  virtual std::string toString() const = 0;
  virtual long evaluate() const = 0;
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
  virtual long evaluate() const { return value; }
};

class CalcExpression : public Expression {
 protected:
  Expression *lhs, *rhs;
  std::string calcSign;

 public:
  CalcExpression() : Expression() {}
  CalcExpression(Expression * lhs, Expression * rhs, long val, std::string s) :
      Expression(val), lhs(lhs), rhs(rhs), calcSign(s) {}
  virtual ~CalcExpression() {
    delete lhs;
    delete rhs;
  }
  virtual std::string toString() const {
    return "(" + lhs->toString() + " " + calcSign + " " + rhs->toString() + ")";
  }

  virtual long evaluate() const { return value; }
};

class PlusExpression : public CalcExpression {
 public:
  PlusExpression() : CalcExpression() {}
  PlusExpression(Expression * lhs, Expression * rhs) :
      CalcExpression(lhs, rhs, lhs->evaluate() + rhs->evaluate(), "+") {}
  virtual ~PlusExpression() {}
};

class MinusExpression : public CalcExpression {
 public:
  MinusExpression() : CalcExpression() {}
  MinusExpression(Expression * lhs, Expression * rhs) :
      CalcExpression(lhs, rhs, lhs->evaluate() - rhs->evaluate(), "-") {}
  virtual ~MinusExpression() {}
};

class TimesExpression : public CalcExpression {
 public:
  TimesExpression() : CalcExpression() {}
  TimesExpression(Expression * lhs, Expression * rhs) :
      CalcExpression(lhs, rhs, lhs->evaluate() * rhs->evaluate(), "*") {}
  virtual ~TimesExpression() {}
};

class DivExpression : public CalcExpression {
 public:
  DivExpression() : CalcExpression() {}
  DivExpression(Expression * lhs, Expression * rhs) :
      CalcExpression(lhs, rhs, lhs->evaluate() / rhs->evaluate(), "/") {}
  virtual ~DivExpression() {}
};

#endif
