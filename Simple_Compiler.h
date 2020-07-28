#pragma once
#ifndef SIMPLE_COMPILER_H
#define SIMPLE_COMPILER_H

#include <iostream>
#include <string>
#include <fstream>
#include <stdlib.h>

using namespace std;

void checkAllType(char input);

bool checkZero();

bool checkOneNum();

int checkOne();

void resetState();

void resetAccept();

void resetWhiteSpace();

void makeToken(struct Token output);

void isVType(char input);

void isKeyword(char input);

void isBoolString(char input);

void isInteger(char input);

void isIntegerMINUS(char input);

void isLiteralString(char input);

void isFloatNum(char input);

void isFloatNumMINUS(char input);

void isID(char input);

void isIDMINUS(char input);

void isBitOp(char input);

void isCompOp(char input);

void isArithmeticOp(char input);

void isAssignment(char input);

void isTerminate(char input);

void isLBrace(char input);

void isRBrace(char input);

void isLParen(char input);

void isRParen(char input);

void isComma(char input);

void isWhiteSpace(char input);



#endif // !SIMPLE_COMPILER_H


