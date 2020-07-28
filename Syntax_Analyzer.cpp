// Syntax_Analyzer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <iostream>
#include <vector>
#include "Syntax_Analyzer.h"

using namespace std;

int splitter = 0;
extern vector<string> resultLex;				//Lex에서 가져온 값들을 저장하는 Vector
extern vector<int> linenum;						//오류 검출을 위한 함수
vector<int> state;								//state 번호를 저장하는 스택
string temporary;

void syntax()									//main함수
{
	state.push_back(1);
	state1();
}

/******************************************
다음의 state들은 DFA transition graph의 vertex들을
형상화한 함수들로 정해진 입력들이 들어올 때 할 
행동들(Reduce, Goto, S&Goto)이 정의되어있다.
만약 예외 입력이 들어올 경우 에러 입력이 난
줄과 이유를 출력해준다.
*******************************************/

void state1()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		splitter++; state.push_back(5);  state5();
	}
	else if (input.compare("$") == 0)
	{
		reduce3();
	}
	else if (input.compare("CODE") == 0)
	{
		splitter++; state.push_back(2); state2();
	}
	else if (input.compare("VDECL") == 0)
	{
		splitter++; state.push_back(6);	state6();
	}
	else if (input.compare("FDECL") == 0)
	{
		splitter++; state.push_back(4); state4();
	}
	else if (input.compare("S") == 0)
	{
		printf("Success\n");
	}
	else
	{
		cout << "error!!!  :    " << line << "   line  " << input << "  is problem." << endl;
		cout << "State  1 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state2()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("$") == 0)
	{
		reduce0();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  2 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state3()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("$") == 0)
	{
		reduce2();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  3 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state4()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("vtype") == 0)
	{
		splitter++; state.push_back(5); state5();
	}
	else if (input.compare("$") == 0)
	{
		reduce3();
	}
	else if (input.compare("CODE") == 0)
	{
		splitter++; state.push_back(3); state3();
	}
	else if (input.compare("VDECL") == 0)
	{
		splitter++; state.push_back(6); state6();
	}
	else if (input.compare("FDECL") == 0)
	{
		splitter++; state.push_back(4); state4();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  4 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state5()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("id") == 0)
	{
		splitter++; state.push_back(9); state9();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(10); state10();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  5 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state6()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		splitter++; state.push_back(5); state5();
	}
	else if (input.compare("$") == 0)
	{
		reduce3();
	}
	else if (input.compare("CODE") == 0)
	{
		splitter++; state.push_back(7); state7();
	}
	else if (input.compare("VDECL") == 0)
	{
		splitter++; state.push_back(6); state6();
	}
	else if (input.compare("FDECL") == 0)
	{
		splitter++; state.push_back(4); state4();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  6 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state7()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("$") == 0)
	{
		reduce1();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  7 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state8()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("vtype") == 0)
	{
		reduce4();
	}
	else if (input.compare("id") == 0)
	{
		reduce4();
	}
	else if (input.compare("if") == 0)
	{
		reduce4();
	}
	else if (input.compare("while") == 0)
	{
		reduce4();
	}
	else if (input.compare("for") == 0)
	{
		reduce4();
	}
	else if (input.compare("return") == 0)
	{
		reduce4();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce4();
	}
	else if (input.compare("$") == 0)
	{
		reduce4();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  8 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state9()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("assign") == 0)
	{
		splitter++; state.push_back(20); state20();
	}
	else if (input.compare("semi") == 0)
	{
		splitter++; state.push_back(8); state8();
	}
	else if (input.compare("lparen") == 0)
	{
		splitter++; state.push_back(12); state12();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  10 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state10()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("semi") == 0)
	{
		splitter++; state.push_back(11); state11();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  11 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state11()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		reduce5();
	}
	else if (input.compare("id") == 0)
	{
		reduce5();
	}
	else if (input.compare("if") == 0)
	{
		reduce5();
	}
	else if (input.compare("while") == 0)
	{
		reduce5();
	}
	else if (input.compare("for") == 0)
	{
		reduce5();
	}
	else if (input.compare("return") == 0)
	{
		reduce5();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce5();
	}
	else if (input.compare("$") == 0)
	{
		reduce5();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  11 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state12()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		splitter++; state.push_back(13); state13();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce9();
	}
	else if (input.compare("ARG") == 0)
	{
		splitter++; state.push_back(36); state36();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  12 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state13()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("id") == 0)
	{
		splitter++; state.push_back(14); state14();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  13 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state14()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("comma") == 0)
	{
		splitter++; state.push_back(16); state16();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce11();
	}
	else if (input.compare("MOREARGS") == 0)
	{
		splitter++; state.push_back(15); state15();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  14 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state15()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("rparen") == 0)
	{
		reduce8();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  15 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state16()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		splitter++; state.push_back(8); state18();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  16 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state17()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("rparen") == 0)
	{
		reduce10();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  17 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state18()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("id") == 0)
	{
		splitter++; state.push_back(19); state19();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  18 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state19()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("comma") == 0)
	{
		splitter++; state.push_back(16); state16();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce11();
	}
	else if (input.compare("MOREARGS") == 0)
	{
		splitter++; state.push_back(17); state17();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  19 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state20()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("num") == 0)
	{
		splitter++; state.push_back(32); state32();
	}
	else if (input.compare("float") == 0)
	{
		splitter++; state.push_back(31); state31();
	}
	else if (input.compare("literal") == 0)
	{
		splitter++; state.push_back(23); state23();
	}
	else if (input.compare("id") == 0)
	{
		splitter++; state.push_back(30); state30();
	}
	else if (input.compare("lparen") == 0)
	{
		splitter++; state.push_back(33); state33();
	}
	else if (input.compare("RHS") == 0)
	{
		splitter++; state.push_back(21); state21();
	}
	else if (input.compare("EXPR") == 0)
	{
		splitter++; state.push_back(22); state22();
	}
	else if (input.compare("TERM") == 0)
	{
		splitter++; state.push_back(24); state24();
	}
	else if (input.compare("FACTOR") == 0)
	{
		splitter++; state.push_back(25); state25();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  20 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state21()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("semi") == 0)
	{
		reduce6();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce6();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  21 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state22()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("semi") == 0)
	{
		reduce21();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce21();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  22 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state23()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("semi") == 0)
	{
		reduce22();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce22();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  23 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state24()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("addsub") == 0)
	{
		splitter++; state.push_back(27); state27();
	}
	else if (input.compare("semi") == 0)
	{
		reduce24();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce24();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  24 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state25()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("addsub") == 0)
	{
		reduce26(); 
	}
	else if (input.compare("multdiv") == 0)
	{
		splitter++; state.push_back(28); state28();
	}
	else if (input.compare("semi") == 0)
	{
		reduce26();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce26();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  25 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state26()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("semi") == 0)
	{
		reduce23();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce23();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  26 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state27()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("num") == 0)
	{
		splitter++; state.push_back(32); state32();
	}
	else if (input.compare("float") == 0)
	{
		splitter++; state.push_back(31); state31();
	}
	else if (input.compare("id") == 0)
	{
		splitter++; state.push_back(30); state30();
	}
	else if (input.compare("lparen") == 0)
	{
		splitter++; state.push_back(33); state33();
	}
	else if (input.compare("EXPR") == 0)
	{
		splitter++;  state.push_back(26); state26();
	}
	else if (input.compare("TERM") == 0)
	{
		splitter++; state.push_back(24); state24();
	} 
	else if (input.compare("FACTOR") == 0)
	{
		splitter++; state.push_back(25); state25();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  27 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state28()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("num") == 0)
	{
		splitter++; state.push_back(32); state32();
	}
	else if (input.compare("float") == 0)
	{
		splitter++; state.push_back(31); state31();
	}
	else if (input.compare("id") == 0)
	{
		splitter++; state.push_back(30); state30();
	}
	else if (input.compare("TERM") == 0)
	{
		splitter++;  state.push_back(29); state29();
	}
	else if (input.compare("FACTOR") == 0)
	{
		splitter++;  state.push_back(25); state25();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  28 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state29()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("addsub") == 0)
	{
		reduce25();
	}
	else if (input.compare("semi") == 0)
	{
		reduce25();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce25();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  29 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state30()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("addsub") == 0)
	{
		reduce28();
	}
	else if (input.compare("multdiv") == 0)
	{
		reduce28();
	}
	else if (input.compare("comp") == 0)
	{
		reduce28();
	}
	else if (input.compare("semi") == 0)
	{
		reduce28();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce28();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  30 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state31()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("addsub") == 0)
	{
		reduce30();
	}
	else if (input.compare("multdiv") == 0)
	{
		reduce30();
	}
	else if (input.compare("comp") == 0)
	{
		reduce30();
	}
	else if (input.compare("semi") == 0)
	{
		reduce30();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce30();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  31 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state32()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("addsub") == 0)
	{
		reduce29();
	}
	else if (input.compare("multdiv") == 0)
	{
		reduce29();
	}
	else if (input.compare("comp") == 0)
	{
		reduce29();
	}
	else if (input.compare("semi") == 0)
	{
		reduce29();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce29();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  32 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void  state33()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("num") == 0)
	{
		splitter++;  state.push_back(32); state32();
	}
	else if (input.compare("float") == 0)
	{
		splitter++;  state.push_back(31); state31();
	}
	else if (input.compare("id") == 0)
	{
		splitter++;  state.push_back(30); state30();
	}
	else if (input.compare("lparen") == 0)
	{
		splitter++;  state.push_back(33); state33();
	}
	else if (input.compare("EXPR") == 0)
	{
		splitter++; state.push_back(34); state34();
	}
	else if (input.compare("TERM") == 0)
	{
		splitter++; state.push_back(24); state24();
	}
	else if (input.compare("FACTOR") == 0)
	{
		splitter++; state.push_back(25); state25();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  33 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void  state34()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rparen") == 0)
	{
		splitter++;  state.push_back(35); state35();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  34 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state35()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("addsub") == 0)
	{
		reduce27();
	}
	else if (input.compare("multdiv") == 0)
	{
		reduce27();
	}
	else if (input.compare("comp") == 0)
	{
		reduce27();
	}
	else if (input.compare("semi") == 0)
	{
		reduce27();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce27();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  35 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void  state36()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rparen") == 0)
	{
		splitter++;  state.push_back(37); state37();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  36 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state37()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("lbrace") == 0)
	{
		splitter++;  state.push_back(38); state38();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  37 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state38()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		splitter++;  state.push_back(50); state50();
	}
	else if (input.compare("id") == 0)
	{
		splitter++;  state.push_back(49); state49();
	}
	else if (input.compare("if") == 0)
	{
		splitter++;  state.push_back(53); state53();
	}
	else if (input.compare("while") == 0)
	{
		splitter++;  state.push_back(68); state68();
	}
	else if (input.compare("for") == 0)
	{
		splitter++;  state.push_back(75); state75();
	}
	else if (input.compare("return") == 0)
	{
		reduce13();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce13();
	}
	else if (input.compare("VDECL") == 0)
	{
		splitter++; state.push_back(42); state42();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(45); 
		state45();
	}
	else if (input.compare("BLOCK") == 0)
	{
		splitter++; state.push_back(39); state39();
	}
	else if (input.compare("STMT") == 0)
	{
		splitter++; state.push_back(43); state43();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  38 :  After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state39()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("return") == 0)
	{
		splitter++;  state.push_back(44); state44();
	}
	else if (input.compare("RETURN") == 0)
	{
		splitter++; state.push_back(40); state40();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  39 : After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state40()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rbrace") == 0)
	{
		splitter++;  state.push_back(41); state41();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  40 : " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state41()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		reduce7();
	}
	else if (input.compare("$") == 0)
	{
		reduce7();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  41 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state42()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		reduce14();
	}
	else if (input.compare("id") == 0)
	{
		reduce14();
	}
	else if (input.compare("if") == 0)
	{
		reduce14();
	}
	else if (input.compare("while") == 0)
	{
		reduce14();
	}
	else if (input.compare("for") == 0)
	{
		reduce14();
	}
	else if (input.compare("return") == 0)
	{
		reduce14();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce14();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  42 : After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state43()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	//cout <<"here"<< input << endl;
	//printAll();
	if (input.compare("vtype") == 0)
	{
		splitter++;  state.push_back(50); state50();
	}
	else if (input.compare("id") == 0)
	{
		splitter++;  state.push_back(49); state49();
	}
	else if (input.compare("if") == 0)
	{
		splitter++;  state.push_back(53); state53();
	}
	else if (input.compare("while") == 0)
	{
		splitter++;  state.push_back(68); state68();
	}
	else if (input.compare("for") == 0)
	{
		splitter++;  state.push_back(75); state75();
	}
	else if (input.compare("return") == 0)
	{
		reduce13();
	}
	else if (input.compare("rbrace") == 0)
	{
				reduce13();
	}
	else if (input.compare("VDECL") == 0)
	{
		splitter++; state.push_back(42); state42();
	}
	else if (input.compare("BLOCK") == 0)
	{
		splitter++; state.push_back(86); state52();
	}
	else if (input.compare("STMT") == 0)
	{
		splitter++; state.push_back(43); state43();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(45); state45();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  43 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state44()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("num") == 0)
	{
		splitter++;  state.push_back(32); state32();
	}
	else if (input.compare("float") == 0)
	{
		splitter++;  state.push_back(31); state31();
	}
	else if (input.compare("id") == 0)
	{
		splitter++;  state.push_back(30); state30();
	}
	else if (input.compare("lparen") == 0)
	{
		splitter++;  state.push_back(33); state33();
	}
	else if (input.compare("FACTOR") == 0)
	{
		splitter++; state.push_back(47); state47();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  44 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state45()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("semi") == 0)
	{
		splitter++;  state.push_back(46); state46();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  45 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state46()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		reduce15();
	}
	else if (input.compare("id") == 0)
	{
		reduce15();
	}
	else if (input.compare("if") == 0)
	{
		reduce15();
	}
	else if (input.compare("while") == 0)
	{
		reduce15();
	}
	else if (input.compare("for") == 0)
	{
		reduce15();
	}
	else if (input.compare("return") == 0)
	{
		reduce15();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce15();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  46 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state47()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("semi") == 0)
	{
		splitter++;  state.push_back(48); state48();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  47 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state48()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rbrace") == 0)
	{
		reduce32();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  48 : After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state49()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("assign") == 0)
	{
		splitter++;  state.push_back(20); state20();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  49 : After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state50()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("id") == 0)
	{
		splitter++;  state.push_back(51); state51();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(10); state10();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  50 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state51()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("assign") == 0)
	{
		splitter++; state.push_back(20); state20();
	}
	else if (input.compare("semi") == 0)
	{
		splitter++; state.push_back(52); state8();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  51 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state52()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);
	
	if (input.compare("rbrace") == 0)
	{
		reduce12();
	}
	else if (input.compare("return") == 0)
	{
		reduce12();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  52 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state53()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("lparen") == 0)
	{
		splitter++;  state.push_back(54); state54();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  53 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state54()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("num") == 0)
	{
		splitter++;  state.push_back(32); state32();
	}
	else if (input.compare("float") == 0)
	{
		splitter++;  state.push_back(31); state31();
	}
	else if (input.compare("id") == 0)
	{
		splitter++;  state.push_back(30); state30();
	}
	else if (input.compare("lparen") == 0)
	{
		splitter++;  state.push_back(33); state33();
	}
	else if (input.compare("FACTOR") == 0)
	{
		splitter++;  state.push_back(55); state55();
	}
	else if (input.compare("COND") == 0)
	{
		splitter++; state.push_back(56); state56();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  54 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state55()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("comp") == 0)
	{
		splitter++;  state.push_back(57); state57();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  55 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state56()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rparen") == 0)
	{
		splitter++;  state.push_back(59);  state59();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  56 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state57()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("num") == 0)
	{
		splitter++;  state.push_back(32);  state32();
	}
	else if (input.compare("float") == 0)
	{
		splitter++; state.push_back(31); state31();
	}
	else if (input.compare("id") == 0)
	{
		splitter++; state.push_back(30); state30();
	}
	else if (input.compare("lparen") == 0)
	{
		splitter++; state.push_back(33); state33();
	}
	else if (input.compare("FACTOR") == 0)
	{
		splitter++; state.push_back(58); state58();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  57 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state58()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("semi") == 0)
	{
		reduce31();
	}
	else if (input.compare("rparen") == 0)
	{
		reduce31();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  58 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state59()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("lbrace") == 0)
	{
		splitter++; state.push_back(60); state60();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  59 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state60()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		splitter++; state.push_back(50); state50();
	}
	else if (input.compare("id") == 0)
	{
		splitter++;  state.push_back(49); state49();
	}
	else if (input.compare("if") == 0)
	{
		splitter++; state.push_back(53); state53();
	}
	else if (input.compare("while") == 0)
	{
		splitter++; state.push_back(68); state68();
	}
	else if (input.compare("for") == 0)
	{
		splitter++; state.push_back(75); state75();
	}
	else if (input.compare("reture") == 0)
	{
		reduce13();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce13();
	}
	else if (input.compare("VDECL") == 0)
	{
		splitter++; state.push_back(42); state42();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(45); state45();
	}
	else if (input.compare("BLOCK") == 0)
	{
		splitter++; state.push_back(61); state61();
	}
	else if (input.compare("STMT") == 0)
	{
		splitter++; state.push_back(43);  state43();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  60 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state61()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rbrace") == 0)
	{
		splitter++; state.push_back(62); state62();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  61 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state62()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		reduce20();
	}
	else if (input.compare("id") == 0)
	{
		reduce20();
	}
	else if (input.compare("if") == 0)
	{
		reduce20();
	}
	else if (input.compare("else") == 0)
	{
		splitter++; state.push_back(64); state64();
	}
	else if (input.compare("while") == 0)
	{
		reduce20();
	}
	else if (input.compare("for") == 0)
	{
		reduce20();
	}
	else if (input.compare("return") == 0)
	{
		reduce20();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce20();
	}
	else if (input.compare("ELSE") == 0)
	{
		splitter++; state.push_back(63); state63();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  62 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state63()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		reduce16();
	}
	else if (input.compare("id") == 0)
	{
		reduce16();
	}
	else if (input.compare("if") == 0)
	{
		reduce16();
	}
	else if (input.compare("while") == 0)
	{
		reduce16();
	}
	else if (input.compare("for") == 0)
	{
		reduce16();
	}
	else if (input.compare("return") == 0)
	{
		reduce16();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce16();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  63 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state64()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("lbrace") == 0)
	{
		splitter++; state.push_back(65); state65();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  64 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state65()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		splitter++; state.push_back(50); state50();
	}
	else if (input.compare("id") == 0)
	{
		splitter++; state.push_back(49); state49();
	}
	else if (input.compare("if") == 0)
	{
		splitter++; state.push_back(53); state53();
	}
	else if (input.compare("while") == 0)
	{
		splitter++; state.push_back(68); state68();
	}
	else if (input.compare("for") == 0)
	{
		splitter++; state.push_back(75); state75();
	}
	else if (input.compare("return") == 0)
	{
		reduce13();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce13();
	}
	else if (input.compare("VDECL") == 0)
	{
		splitter++; state.push_back(42); state42();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(45); state45();
	}
	else if (input.compare("BLOCK") == 0)
	{
		splitter++; state.push_back(66); state66();
	}
	else if (input.compare("STMT") == 0)
	{
		splitter++; state.push_back(43); state43();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  65 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state66()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rbrace") == 0)
	{
		splitter++; state.push_back(67); state67();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  66 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}
void state67()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		reduce19();
	}
	else if (input.compare("id") == 0)
	{
		reduce19();
	}
	else if (input.compare("if") == 0)
	{
		reduce19();
	}
	else if (input.compare("while") == 0)
	{
		reduce19();
	}
	else if (input.compare("for") == 0)
	{
		reduce19();
	}
	else if (input.compare("return") == 0)
	{
		reduce19();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce19();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  67 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state68()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("lparen") == 0)
	{
		splitter++; state.push_back(69); state69();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  68 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state69()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("num") == 0)
	{
		splitter++;  state.push_back(32); state32();
	}
	else if (input.compare("float") == 0)
	{
		splitter++;  state.push_back(31); state31();
	}
	else if (input.compare("id") == 0)
	{
		splitter++; state.push_back(30); state30();
	}
	else if (input.compare("lparen") == 0)
	{
		splitter++; state.push_back(33); state33();
	}
	else if (input.compare("FACTOR") == 0)
	{
		splitter++; state.push_back(55); state55();
	}
	else if (input.compare("COND") == 0)
	{
		splitter++; state.push_back(70); state70();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  69 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state70()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rparen") == 0)
	{
		splitter++; state.push_back(71); state71();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  70 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state71()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("lbrace") == 0)
	{
		splitter++; state.push_back(72); state72();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  71 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state72()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		splitter++; state.push_back(50); state50();
	}
	else if (input.compare("id") == 0)
	{
		splitter++; state.push_back(49); state49();
	}
	else if (input.compare("if") == 0)
	{
		splitter++; state.push_back(53); state53();
	}
	else if (input.compare("while") == 0)
	{
		splitter++; state.push_back(68); state68();
	}
	else if (input.compare("for") == 0)
	{
		splitter++; state.push_back(75); state75();
	}
	else if (input.compare("return") == 0)
	{
		reduce13();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce13();
	}
	else if (input.compare("VDECL") == 0)
	{
		splitter++; state.push_back(42); state42();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(45); state45();
	}
	else if (input.compare("BLOCK") == 0)
	{
		splitter++; state.push_back(73); state73();
	}
	else if (input.compare("STMT") == 0)
	{
		splitter++; state.push_back(43); state43();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  72 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state73()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rbrace") == 0)
	{
		splitter++; state.push_back(74); state74();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  73 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state74()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		reduce17();
	}
	else if (input.compare("id") == 0)
	{
		reduce17();
	}
	else if (input.compare("if") == 0)
	{
		reduce17();
	}
	else if (input.compare("while") == 0)
	{
		reduce17();
	}
	else if (input.compare("for") == 0)
	{
		reduce17();
	}
	else if (input.compare("return") == 0)
	{
		reduce17();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce17();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  74 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state75()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("lparen") == 0)
	{
		splitter++; state.push_back(76); state76();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  75 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state76()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("id") == 0)
	{
		splitter++; state.push_back(49); state49();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(77); state77();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  76 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state77()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("semi") == 0)
	{
		splitter++; state.push_back(78); state78();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  77 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state78()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("num") == 0)
	{
		splitter++; state.push_back(32); state32();
	}
	else if (input.compare("float") == 0)
	{
		splitter++; state.push_back(31); state31();
	}
	else if (input.compare("id") == 0)
	{
		splitter++; state.push_back(30); state30();
	}
	else if (input.compare("lparen") == 0)
	{
		splitter++; state.push_back(33); state33();
	}
	else if (input.compare("FACTOR") == 0)
	{
		splitter++; state.push_back(55); state55();
	}
	else if (input.compare("COND") == 0)
	{
		splitter++; state.push_back(79); state79();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  78 : After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state79()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("semi") == 0)
	{
		splitter++; state.push_back(80); state80();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  79 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state80()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("id") == 0)
	{
		splitter++; state.push_back(49); state49();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(81); state81();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  80 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state81()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rparen") == 0)
	{
		splitter++; state.push_back(82); state82();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  81 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state82()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("lbrace") == 0)
	{
		splitter++; state.push_back(83); state83();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  82 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state83()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		splitter++; state.push_back(50); state50();
	}
	else if (input.compare("id") == 0)
	{
		splitter++; state.push_back(49); state49();
	}
	else if (input.compare("if") == 0)
	{
		splitter++; state.push_back(53); state53();
	}
	else if (input.compare("while") == 0)
	{
		splitter++; state.push_back(68); state68();
	}
	else if (input.compare("for") == 0)
	{
		splitter++; state.push_back(75); state75();
	}
	else if (input.compare("return") == 0)
	{
		reduce13();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce13();
	}
	else if (input.compare("VDECL") == 0)
	{
		splitter++; state.push_back(42); state42();
	}
	else if (input.compare("ASSIGN") == 0)
	{
		splitter++; state.push_back(45); state45();
	}
	else if (input.compare("BLOCK") == 0)
	{
		splitter++; state.push_back(84); state84();
	}
	else if (input.compare("STMT") == 0)
	{
		splitter++; state.push_back(43); state43();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  83 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state84()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("rbrace") == 0)
	{
		splitter++; state.push_back(85); state85();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  84 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}

void state85()
{
	string input = resultLex.at(splitter);
	int line = linenum.at(splitter);

	if (input.compare("vtype") == 0)
	{
		reduce18();
	}
	else if (input.compare("id") == 0)
	{
		reduce18();
	}
	else if (input.compare("if") == 0)
	{
		reduce18();
	}
	else if (input.compare("while") == 0)
	{
		reduce18();
	}
	else if (input.compare("for") == 0)
	{
		reduce18();
	}
	else if (input.compare("return") == 0)
	{
		reduce18();
	}
	else if (input.compare("rbrace") == 0)
	{
		reduce18();
	}
	else
	{
		cout << "error!!!  : " << line << "  line   " << input << "  is  problem." << endl;
		cout << "State  85 :After " << resultLex.at(splitter-1) << ", " << input << "  cannot come out" << endl;
	}
}


void gotoState(int n)								//Reduce 후 스택의 top값에 있는 상태로 가기 위한 함수
{
	for (int i = 0; i < n; i++)
	{
		state.pop_back();
	}
	int num = state.back();
	if (num == 1)
		state1();
	else if (num == 2)
		state2();
	else if (num == 3)
		state3();
	else if (num == 4)
		state4();
	else if (num == 5)
		state5();
	else if (num == 6)
		state6();
	else if (num == 7)
		state7();
	else if (num == 8)
		state8();
	else if (num == 9)
		state9();
	else if (num == 10)
		state10();
	else if (num == 11)
		state11();
	else if (num == 12)
		state12();
	else if (num == 13)
		state13();
	else if (num == 14)
		state14();
	else if (num == 15)
		state15();
	else if (num == 16)
		state16();
	else if (num == 17)
		state17();
	else if (num == 18)
		state18();
	else if (num == 19)
		state19();
	else if (num == 20)
		state20();
	else if (num == 21)
		state21();
	else if (num == 22)
		state22();
	else if (num == 23)
		state23();
	else if (num == 24)
		state24();
	else if (num == 25)
		state25();
	else if (num == 26)
		state26();
	else if (num == 27)
		state27();
	else if (num == 28)
		state28();
	else if (num == 29)
		state29();
	else if (num == 30)
		state30();
	else if (num == 31)
		state31();
	else if (num == 32)
		state32();
	else if (num == 33)
		state33();
	else if (num == 34)
		state34();
	else if (num == 35)
		state35();
	else if (num == 36)
		state36();
	else if (num == 37)
		state37();
	else if (num == 38)
		state38();
	else if (num == 39)
		state39();
	else if (num == 40)
		state40();
	else if (num == 41)
		state41();
	else if (num == 42)
		state42();
	else if (num == 43)
		state43();
	else if (num == 44)
		state44();
	else if (num == 45)
		state45();
	else if (num == 46)
		state46();
	else if (num == 47)
		state47();
	else if (num == 48)
		state48();
	else if (num == 49)
		state49();
	else if (num == 50)
		state50();
	else if (num == 51)
		state51();
	else if (num == 52)
		state52();
	else if (num == 53)
		state53();
	else if (num == 54)
		state54();
	else if (num == 55)
		state55();
	else if (num == 56)
		state56();
	else if (num == 57)
		state57();
	else if (num == 58)
		state58();
	else if (num == 59)
		state59();
	else if (num == 60)
		state60();
	else if (num == 61)
		state61();
	else if (num == 62)
		state62();
	else if (num == 63)
		state63();
	else if (num == 64)
		state64();
	else if (num == 65)
		state65();
	else if (num == 66)
		state66();
	else if (num == 67)
		state67();
	else if (num == 68)
		state68();
	else if (num == 69)
		state69();
	else if (num == 70)
		state70();
	else if (num == 71)
		state71();
	else if (num == 72)
		state72();
	else if (num == 73)
		state73();
	else if (num == 74)
		state74();
	else if (num == 75)
		state75();
	else if (num == 76)
		state76();
	else if (num == 77)
		state77();
	else if (num == 78)
		state78();
	else if (num == 79)
		state79();
	else if (num == 80)
		state80();
	else if (num == 81)
		state81();
	else if (num == 82)
		state82();
	else if (num == 83)
		state83();
	else if (num == 84)
		state84();
	else if (num == 85)
		state85();
}


/**************************************
Reduce행동을 수행하는 함수
각각의 번호마다 하나의 Reduce식을 담고 있다.
ex) BLOCK --> STMT BLOCK
***************************************/

void reduce0()
{
	resultLex.insert(resultLex.begin() + splitter, "S");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	
	resultLex.erase(resultLex.begin() + splitter - 1);			//splitter - 1 부터 지워야 하고 다 지운 후 n개 지우면 splitter - n에 넣으면 댐
	linenum.erase(linenum.begin() + splitter - 1);
	
	splitter--;
	gotoState(1);
}

void reduce1()
{
	resultLex.insert(resultLex.begin() + splitter, "CODE");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	
	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);

	splitter = splitter - 2;
	gotoState(2);
}

void reduce2()
{
	resultLex.insert(resultLex.begin() + splitter, "CODE");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	splitter = splitter - 2;
	gotoState(2);
}

void reduce3()
{
	resultLex.insert(resultLex.begin() + splitter, "CODE");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	gotoState(0);
}

void reduce4()
{
	resultLex.insert(resultLex.begin() + splitter, "VDECL");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	splitter = splitter - 3;
	gotoState(3);
}

void reduce5()
{
	resultLex.insert(resultLex.begin() + splitter, "VDECL");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	splitter = splitter - 3;
	gotoState(3);
}

void reduce6()
{
	resultLex.insert(resultLex.begin() + splitter, "ASSIGN");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	splitter = splitter - 3;
	gotoState(3);
}

void reduce7()
{
	resultLex.insert(resultLex.begin() + splitter, "FDECL");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	resultLex.erase(resultLex.begin() + splitter - 4);
	resultLex.erase(resultLex.begin() + splitter - 5);
	resultLex.erase(resultLex.begin() + splitter - 6);
	resultLex.erase(resultLex.begin() + splitter - 7);
	resultLex.erase(resultLex.begin() + splitter - 8);
	resultLex.erase(resultLex.begin() + splitter - 9);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 4);
	linenum.erase(linenum.begin() + splitter - 5);
	linenum.erase(linenum.begin() + splitter - 6);
	linenum.erase(linenum.begin() + splitter - 7);
	linenum.erase(linenum.begin() + splitter - 8);
	linenum.erase(linenum.begin() + splitter - 9);
	splitter = splitter - 9;
	gotoState(9);
}

void reduce8()
{
	resultLex.insert(resultLex.begin() + splitter, "ARG");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	splitter = splitter - 3;
	gotoState(3);
}

void reduce9()
{
	resultLex.insert(resultLex.begin() + splitter, "ARG");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	gotoState(0);
}

void reduce10()
{
	resultLex.insert(resultLex.begin() + splitter, "MOREARGS");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	resultLex.erase(resultLex.begin() + splitter - 4);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 4);
	splitter = splitter - 4;
	gotoState(4);
}

void reduce11()
{
	resultLex.insert(resultLex.begin() + splitter, "MOREARGS");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	gotoState(0);
}

void reduce12()
{
	resultLex.insert(resultLex.begin() + splitter, "BLOCK");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	splitter = splitter - 2;
	gotoState(2);
}

void reduce13()
{
	resultLex.insert(resultLex.begin() + splitter, "BLOCK");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	gotoState(0);
}

void reduce14()
{
	resultLex.insert(resultLex.begin() + splitter, "STMT");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);
	
	resultLex.erase(resultLex.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 1);
	splitter = splitter - 1;
	gotoState(1);
}

void reduce15()
{
	resultLex.insert(resultLex.begin() + splitter, "STMT");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);
	
	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	splitter = splitter - 2;
	gotoState(2);
}

void reduce16()
{
	resultLex.insert(resultLex.begin() + splitter, "STMT");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	resultLex.erase(resultLex.begin() + splitter - 4);
	resultLex.erase(resultLex.begin() + splitter - 5);
	resultLex.erase(resultLex.begin() + splitter - 6);
	resultLex.erase(resultLex.begin() + splitter - 7);
	resultLex.erase(resultLex.begin() + splitter - 8);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 4);
	linenum.erase(linenum.begin() + splitter - 5);
	linenum.erase(linenum.begin() + splitter - 6);
	linenum.erase(linenum.begin() + splitter - 7);
	linenum.erase(linenum.begin() + splitter - 8);
	splitter = splitter - 8;
	gotoState(8);
}

void reduce17()
{
	resultLex.insert(resultLex.begin() + splitter, "STMT");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	resultLex.erase(resultLex.begin() + splitter - 4);
	resultLex.erase(resultLex.begin() + splitter - 5);
	resultLex.erase(resultLex.begin() + splitter - 6);
	resultLex.erase(resultLex.begin() + splitter - 7);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 4);
	linenum.erase(linenum.begin() + splitter - 5);
	linenum.erase(linenum.begin() + splitter - 6);
	linenum.erase(linenum.begin() + splitter - 7);
	splitter = splitter - 7;
	gotoState(7);
}

void reduce18()
{

	resultLex.insert(resultLex.begin() + splitter, "STMT");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	resultLex.erase(resultLex.begin() + splitter - 4);
	resultLex.erase(resultLex.begin() + splitter - 5);
	resultLex.erase(resultLex.begin() + splitter - 6);
	resultLex.erase(resultLex.begin() + splitter - 7);
	resultLex.erase(resultLex.begin() + splitter - 8);
	resultLex.erase(resultLex.begin() + splitter - 9);
	resultLex.erase(resultLex.begin() + splitter - 10);
	resultLex.erase(resultLex.begin() + splitter - 11);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 4);
	linenum.erase(linenum.begin() + splitter - 5);
	linenum.erase(linenum.begin() + splitter - 6);
	linenum.erase(linenum.begin() + splitter - 7);
	linenum.erase(linenum.begin() + splitter - 8);
	linenum.erase(linenum.begin() + splitter - 9);
	linenum.erase(linenum.begin() + splitter - 10);
	linenum.erase(linenum.begin() + splitter - 11);
	splitter = splitter - 11;
	gotoState(11);
}

void reduce19()
{

	resultLex.insert(resultLex.begin() + splitter, "ELSE");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	resultLex.erase(resultLex.begin() + splitter - 4);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 4);
	splitter = splitter - 4;
	gotoState(4);
}

void reduce20()
{
	resultLex.insert(resultLex.begin() + splitter, "ELSE");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	gotoState(0);
}

void reduce21()
{

	resultLex.insert(resultLex.begin() + splitter, "RHS");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 1);
	splitter = splitter - 1;
	gotoState(1);
}

void reduce22()
{
	resultLex.insert(resultLex.begin() + splitter, "RHS");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 1);
	splitter = splitter - 1;
	gotoState(1);
}

void reduce23()
{
	resultLex.insert(resultLex.begin() + splitter, "EXPR");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	
	splitter = splitter - 3;
	gotoState(3);
}

void reduce24()
{
	resultLex.insert(resultLex.begin() + splitter, "EXPR");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 1);

	splitter = splitter - 1;
	gotoState(1);
}

void reduce25()
{
	resultLex.insert(resultLex.begin() + splitter, "TERM");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	splitter = splitter - 3;
	gotoState(3);
}

void reduce26()
{
	resultLex.insert(resultLex.begin() + splitter, "TERM");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 1);
	splitter = splitter - 1;
	gotoState(1);
}

void reduce27()
{
	resultLex.insert(resultLex.begin() + splitter, "FACTOR");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	splitter = splitter - 3;
	gotoState(3);
}

void reduce28()
{
	resultLex.insert(resultLex.begin() + splitter, "FACTOR");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 1);
	splitter = splitter - 1;
	gotoState(1);
}

void reduce29()
{
	resultLex.insert(resultLex.begin() + splitter, "FACTOR");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 1);
	splitter = splitter - 1;
	gotoState(1);
}

void reduce30()
{
	resultLex.insert(resultLex.begin() + splitter, "FACTOR");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 1);
	splitter = splitter - 1;
	gotoState(1);
}

void reduce31()
{
	resultLex.insert(resultLex.begin() + splitter, "COND");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);
	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	splitter = splitter - 3;
	gotoState(3);
}

void reduce32()
{
	resultLex.insert(resultLex.begin() + splitter, "RETURN");
	vector<int>::iterator it = linenum.begin() + splitter - 1;
	linenum.insert(linenum.begin() + splitter, *it);
	temporary = resultLex.at(splitter - 1);

	resultLex.erase(resultLex.begin() + splitter - 1);
	resultLex.erase(resultLex.begin() + splitter - 2);
	resultLex.erase(resultLex.begin() + splitter - 3);

	linenum.erase(linenum.begin() + splitter - 1);
	linenum.erase(linenum.begin() + splitter - 2);
	linenum.erase(linenum.begin() + splitter - 3);
	splitter = splitter - 3;
	gotoState(3);
}

void printAll()
{
	for (int i = 0; i < resultLex.size(); i++)
	{
		cout << resultLex.at(i)<<endl;
	}
}
