#ifndef EXPRESSION_PARSER_H
#define EXPRESSION_PARSER_H

#include <string>
#include <cctype>
#include <cmath>
#include <stdexcept>

class ExpressionParser {
public: 
    ExpressionParser(const std::string& expression) : index(0) {
        expr.reserve(expression.size());
        for(char ch : expression) {
            if(!std::isspace(ch)) {
                expr += ch;
            }
        }
    }

    double parse() {
        return parseExpression();
    }
private:
    std::string expr;
    size_t index;

    double parseExpression() {
        double result = parseTerm();
        while(index < expr.length()) {
            if(expr[index] == '+') {
                index++;
                result += parseTerm();
            } else if(expr[index] == '-') {
                index++;
                result -= parseTerm();
            } else {
                break;
            }
        }
        return result;
    }
    double parseTerm() {
        double result = parseFactor();
        while(index < expr.length()) {
            if(expr[index] == '*') {
                index++;
                result *= parseFactor();
            } else if(expr[index] == '/') {
                index++;
                result /= parseFactor();
            } else if(expr[index] == '^') {
                index++;
                result = std::pow(result, parseFactor());
            } else {
                break;
            }
        }
        return result;
    }
    double parseFactor() {
        if(expr[index] == '+') {
            index++;
            return parseFactor();
        } else if(expr[index] == '-') {
            index++;
            return -parseFactor();
        } else if(expr[index] == '(') {
            index++;
            double result = parseExpression();
            if(expr[index] == ')') {
                index++;
            } else {
                throw std::runtime_error("Expected ')'");
            }
            return result;
        } else if(isdigit(expr[index]) or expr[index] == '.') {
            return parseNumber();
        } else if(isalpha(expr[index])) {
            return parseIdentifier();
        } else {
            throw std::runtime_error("Unexpected character");
        }
    }
    double parseNumber() {
        size_t start = index;
        while(index < expr.length() and (isdigit(expr[index]) or expr[index] == '.')) {
            index++;
        }
        double number = std::stod(expr.substr(start, index - start));

        if(index < expr.length() and isalpha(expr[index])) {
            size_t unitStart = index;
            while(index < expr.length() and isalpha(expr[index])) {
                index ++;
            }
            std::string unit = expr.substr(unitStart, index - unitStart);

            if(unit == "rad") {
                return number;
            } else if(unit == "deg") {
                return number * M_PI / 180;
            } else {
                throw std::runtime_error("Unknown unit: " + unit);
            }
        }
        return number;
    }
    double parseIdentifier() {
        size_t start = index;
        while(index < expr.length() and isalpha(expr[index])) {
            index++;
        }
        std::string identifier = expr.substr(start, index - start);
        
        if(identifier == "pi") {
            return M_PI;
        } else if(identifier == "rad") {
            return 1.0;
        } else if(identifier == "deg") {
            return M_PI / 180.0;
        } else {
            return parseFunction(identifier);
        }
    }
    double parseFunction(std::string& fnName) {
        if(expr[index] != '(') {
            throw std::runtime_error("Expected '(' after function name");
        }
        index++;

        double arg = parseExpression();
        
        if(expr[index] != ')') {
            throw std::runtime_error("Expected ')' after function argument");
        }
        index++;

        if(fnName == "sin") {
            return std::sin(arg);
        } else if(fnName == "cos") {
            return std::cos(arg);
        } else if(fnName == "tan") {
            return std::tan(arg);
        } else {
            throw std::runtime_error("Unknown function, either not implemented or incorrect: " + fnName);
        }
    }
};

#endif
