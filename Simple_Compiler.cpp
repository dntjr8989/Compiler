#include "Simple_Compiler.h"
#define STATE_NUM WHITESPACE + 1
#include <vector>

vector<string> resultLex;
vector<int> linenum;
extern void syntax();

//각 Token들 정의
enum State
{
	VTYPE,
	KEYWORD,
	BOOLSTRING,
	INTEGER,
	INTEGERMINUS,
	LITERALSTRING,
	FLOATNUM,
	FLOATNUMMINUS,
	ID,
	IDMINUS,
	ARITHMETICOP,
	BITOP,
	ASSIGNMENT,
	COMPOP,
	TERMINATE,
	LBRACE,
	RBRACE,
	LPAREN,
	RPAREN,
	COMMA,
	WHITESPACE
};

struct Token								// 구조체 정의 
{   
	int type = -1;
	int location = 0;
	string output;
};

int state[STATE_NUM] = { 0, };
int accept[STATE_NUM] = { 0, };
ofstream foutput;

int line;

//class Compiler
//{
//public:
//	Compiler();
//	~Compiler();
//
//private:
//
//};
//
//Compiler::Compiler()
//{
//}
//
//Compiler::~Compiler()
//{
//}
int main(int argc, char*argv[])
{
	struct  Token token;
	string test;
	string temp;
	char input;
	int acceptType = -1;
	int flag = -1;

	ifstream finput;
	
	//입출력할 파일 열어놓기
	finput.open(argv[1], ifstream::binary);
	//finput.open("input.txt");
	foutput.open("output.txt");

	//파일 한줄 씩 입력받기
	line = 1;
	while (getline(finput, test))
	{
		foutput << "Line : " << line;
		for (int i = 0; i < test.length(); i++)
		{
			input = test[i];
			temp = temp + input;
			checkAllType(input);
			acceptType = checkOne();
			
			if (accept[WHITESPACE] == 1)							//공백일 경우
			{
				if (token.location == i-1)					//공백 전에 Token에 Accept할 확신을 가지지 않아 출력 안 햇을 때 출력하도록 명령
				{
					temp = "";
					makeToken(token);
					token.type = -1;
					token.location = i+1;
					token.output = "";
					resetState();
					resetAccept();
					continue;
				}
				temp = "";
				makeToken(token);
				i = token.location;
				token.type = -1;
				token.location = token.location+1;
				token.output = "";
				resetState();
				resetAccept();
				continue;
			}

			if (acceptType != -1)								//Accept할 의심이 있는 경우에 그 Token에 대한 정보 저장
			{
				token.type = acceptType;
				token.location = i;
				token.output = temp;
			}


			if (i == test.length() - 1 && token.type == -1)  //에러가 있는 경우
			{
				foutput << "< Error at " + temp + " >";
				temp = "";
				token.type = -1;
				token.output = "";
				resetState();
				resetAccept();
				continue;
			}
			if (!checkZero() && acceptType == -1 && token.type == -1)
			{
				foutput << "< Error at " + temp + " >";
				temp = "";
				token.type = -1;
				token.output = "";
				resetState();
				resetAccept();
				continue;
			}

			if (i != test.length()-1 && (checkZero() || checkOneNum()))								//확실히 Accept할 Token이 있는 지 확인
			{
				continue;
			}
			else
			{
				if (i == test.length() - 1 && acceptType != -1) makeToken(token);
				if (acceptType < 0)				
				{
					makeToken(token);
					temp = "";
					i = token.location;
					token.type = -1;
					token.location = i + 1;
					token.output = "";
					resetState();
					resetAccept();
				}
			}
			resetWhiteSpace();
		}

		foutput << endl;

		temp = "";
		token.type = -1;
		token.location = 0;
		token.output = "";
		resetState();
		resetAccept();
		resetWhiteSpace();
		line++;
	}
	finput.close();
	foutput.close();
	system("pause");

	resultLex.push_back("$");
	linenum.push_back(0);
	syntax();
	/*if (isRParen(*test.front()))
		cout << "Success";
	else
		cout << "fail";*/
	
}

//모든 Token에 입력받은 문자에 따른 DFA State 변화시키도록 명령
void checkAllType(char input)
{
	isVType(input);
	isKeyword(input);
	isBoolString(input);
	isInteger(input);
	isIntegerMINUS(input);
	isLiteralString(input);
	isFloatNum(input);
	isFloatNumMINUS(input);
	isID(input);
	isIDMINUS(input);
	isArithmeticOp(input);
	isBitOp(input);
	isAssignment(input);
	isCompOp(input);
	isTerminate(input);
	isLBrace(input);
	isRBrace(input);
	isLParen(input);
	isRParen(input);
	isComma(input);
	isWhiteSpace(input);
}

//Token들의 Accept의 값이 0인 경우가 있는 지 확인
bool checkZero()
{
	int check = 0;
	for (int i = 0; i < STATE_NUM; i++)
	{
		if (accept[i] == 0)
			return true;
	}
	return false;
}

//Token들의 Accept의 값이 1인 경우가 2번이상인지 확인
bool checkOneNum()
{
	int count = 0;
	for (int i = 0; i < STATE_NUM; i++)
	{
		if (accept[i] == 1)
			count++;
	}
	if (count > 1)
		return true;
	else
		return false;
}

//Token들의 Accept의 값이 1인 경우의 index를 알려주는 함수
int checkOne()
{
	for (int i = 0; i < STATE_NUM; i++)
	{
		if (accept[i] == 1)
			return i;
	}
	return -1;
}

//int saveState(char input)
//{
//	for (int i = 0; i < STATE_NUM; i++)
//	{
//		if (state[i] == 1)
//			return i;
//	}
//	return -1;
//}

//State 리셋
void resetState()
{
	for (int i = 0; i < STATE_NUM; i++)
	{
		state[i] = 0;
	}
}

//Accept 리셋
void resetAccept()
{
	for (int i = 0; i < STATE_NUM; i++)
	{
		accept[i] = 0;
	}
}

void resetWhiteSpace()
{
	accept[WHITESPACE] = 0;
}

//Token 출력
void makeToken(struct Token output)
{
	if (output.type == VTYPE) //vtype
	{
		resultLex.push_back("vtype");
		linenum.push_back(line);
		foutput << "< VTYPE, " + output.output + " >";
	}
	else if (output.type == KEYWORD)
	{
		string t(output.output);
		resultLex.push_back(t);
		linenum.push_back(line);
		foutput << "< KEYWORD, " + output.output + " >";
	}
	else if (output.type == BOOLSTRING)
		foutput << "< BOOLSTRING, " + output.output + " >";

	else if (output.type == INTEGER)
	{
		resultLex.push_back("num");
		linenum.push_back(line);
		foutput << "< INTEGER, " + output.output + " >";
	}
	else if (output.type == INTEGERMINUS)
	{
		resultLex.push_back("num");
		linenum.push_back(line);
		
		resultLex.push_back("addsub");
		linenum.push_back(line);

		output.output = output.output.substr(0, output.output.length() - 1);
		foutput << "< INTEGER " + output.output + " >";
		foutput << "< ARITHMETICOP, - >";
	}

	else if (output.type == LITERALSTRING)
	{
		resultLex.push_back("literal");
		linenum.push_back(line);
		foutput << "< LITERALSTRING , " + output.output + " >";
	}
	else if (output.type == FLOATNUM)
	{
		resultLex.push_back("float");
		linenum.push_back(line);
		foutput << "< FLOATNUM, " + output.output + " >";
	}

	else if (output.type == FLOATNUMMINUS)
	{
		resultLex.push_back("float");
		linenum.push_back(line);

		resultLex.push_back("addsub");
		linenum.push_back(line);

		output.output = output.output.substr(0, output.output.length() - 1);
		foutput << "< FLOATNUM, " + output.output + " >";
		foutput << "< ARITHMETICOP, - >";
	}

	else if (output.type == ID)
	{
		resultLex.push_back("id");
		linenum.push_back(line);
		foutput << "< ID, " + output.output + " >";
	}
	else if (output.type == IDMINUS)
	{
		resultLex.push_back("id");
		linenum.push_back(line);

		resultLex.push_back("addsub");
		linenum.push_back(line);
		
		output.output = output.output.substr(0, output.output.length() - 1);
		foutput << "< ID, " + output.output + " >";
		foutput << "< ARITHMETICOP, - >";
	}

	else if (output.type == ARITHMETICOP)
	{
		if (output.output == "+" || output.output == "-")
		{
			resultLex.push_back("addsub");
			linenum.push_back(line);
		}
		else
		{
			resultLex.push_back("multdiv");
			linenum.push_back(line);
		}
		foutput << "< ARITHMETICOP, " + output.output + " >";
	}

	else if (output.type == BITOP)
		foutput << "< BITOP,  " + output.output + " >";

	else if (output.type == ASSIGNMENT)
	{
		resultLex.push_back("assign");
		linenum.push_back(line);
		foutput << "< ASSIGNMENT, " + output.output + " >";
	}
	else if (output.type == COMPOP)
	{
		resultLex.push_back("comp");
		linenum.push_back(line);
		foutput << "< COMPOP, " + output.output + " >";
	}
	else if (output.type == TERMINATE)
	{
		resultLex.push_back("semi");
		linenum.push_back(line);
		foutput << "< TERMINATE, " + output.output + " >";
	}
	else if (output.type == LBRACE)
	{
		resultLex.push_back("lbrace");
		linenum.push_back(line);
		foutput << "< LBRACE, " + output.output + " >";
	}
	else if (output.type == RBRACE)
	{
		resultLex.push_back("rbrace");
		linenum.push_back(line);
		foutput << "< RBRACE, " + output.output + " >";
	}
	else if (output.type == LPAREN)
	{
		resultLex.push_back("lparen");
		linenum.push_back(line);
		foutput << "< LPAREN, " + output.output + " >";
	}
	else if (output.type == RPAREN)
	{
		resultLex.push_back("rparen");
		linenum.push_back(line);
		foutput << "< RPAREN, " + output.output + " >";
	}
	else if (output.type == COMMA)
	{
		resultLex.push_back("comma");
		linenum.push_back(line);
		foutput << "< COMMA " + output.output + " >";
	}

}

//Type DFA
void isVType(char input)												//accept state: 13
{
	switch (state[VTYPE])
	{
	case 0:
		if (input == 'i')
			state[VTYPE] = 1;

		else if (input == 'c')
			state[VTYPE] = 3;

		else if (input == 'b')
			state[VTYPE] = 6;

		else if (input == 'f')
			state[VTYPE] = 9;

		else
			state[VTYPE] = -1;

		break;

	case 1:
		if (input == 'n')
			state[VTYPE] = 2;

		else
			state[VTYPE] = -1;

		break;

	case 2:
		if (input == 't')
			state[VTYPE] = 13;

		else
			state[VTYPE] = -1;

		break;

	case 3:
		if (input == 'h')
			state[VTYPE] = 4;

		else
			state[VTYPE] = -1;

		break;

	case 4:
		if (input == 'a')
			state[VTYPE] = 5;

		else
			state[VTYPE] = -1;

		break;

	case 5:
		if (input == 'r')
			state[VTYPE] = 13;

		else
			state[VTYPE] = -1;

		break;

	case 6:
		if (input == 'o')
			state[VTYPE] = 7;

		else
			state[VTYPE] = -1;

		break;

	case 7:
		if (input == 'o')
			state[VTYPE] = 8;

		else
			state[VTYPE] = -1;

		break;

	case 8:
		if (input == 'l')
			state[VTYPE] = 13;

		else
			state[VTYPE] = -1;

		break;

	case 9:
		if (input == 'l')
			state[VTYPE] = 10;

		else
			state[VTYPE] = -1;

		break;

	case 10:
		if (input == 'o')
			state[VTYPE] = 11;

		else
			state[VTYPE] = -1;

		break;

	case 11:
		if (input == 'a')
			state[VTYPE] = 12;

		else
			state[VTYPE] = -1;

		break;

	case 12:
		if (input == 't')
			state[VTYPE] = 13;

		else
			state[VTYPE] = -1;

		break;

	case 13:
		state[VTYPE] = -1;
		break;
	}

	if (state[VTYPE] < 0)
		accept[VTYPE] = -1;
	else if (state[VTYPE] == 13)
		accept[VTYPE] = 1;
	else
		accept[VTYPE] = 0;
}

//Keyword DFA
void isKeyword(char input)									//accetp state: 16
{
	switch (state[KEYWORD])
	{
	case 0:
		if (input == 'i')
			state[KEYWORD] = 1;

		else if (input == 'e')
			state[KEYWORD] = 2;

		else if (input == 'w')
			state[KEYWORD] = 5;

		else if (input == 'f')
			state[KEYWORD] = 9;

		else if (input == 'r')
			state[KEYWORD] = 11;

		else
			state[KEYWORD] = -1;

		break;

	case 1:
		if (input == 'f')
			state[KEYWORD] = 16;

		else
			state[KEYWORD] = -1;

		break;

	case 2:
		if (input == 'l')
			state[KEYWORD] = 3;

		else
			state[KEYWORD] = -1;

		break;

	case 3:
		if (input == 's')
			state[KEYWORD] = 4;

		else
			state[KEYWORD] = -1;

		break;

	case 4:
		if (input == 'e')
			state[KEYWORD] = 16;

		else
			state[KEYWORD] = -1;

		break;

	case 5:
		if (input == 'h')
			state[KEYWORD] = 6;

		else
			state[KEYWORD] = -1;

		break;

	case 6:
		if (input == 'i')
			state[KEYWORD] = 7;

		else
			state[KEYWORD] = -1;

		break;

	case 7:
		if (input == 'l')
			state[KEYWORD] = 8;

		else
			state[KEYWORD] = -1;

		break;

	case 8:
		if (input == 'e')
			state[KEYWORD] = 16;

		else
			state[KEYWORD] = -1;

		break;

	case 9:
		if (input == 'o')
			state[KEYWORD] = 10;

		else
			state[KEYWORD] = -1;

		break;

	case 10:
		if (input == 'r')
			state[KEYWORD] = 16;

		else
			state[KEYWORD] = -1;

		break;

	case 11:
		if (input == 'e')
			state[KEYWORD] = 12;

		else
			state[KEYWORD] = -1;

		break;

	case 12:
		if (input == 't')
			state[KEYWORD] = 13;

		else
			state[KEYWORD] = -1;

		break;

	case 13:
		if (input == 'u')
			state[KEYWORD] = 14;

		else
			state[KEYWORD] = -1;

		break;

	case 14:
		if (input == 'r')
			state[KEYWORD] = 15;

		else
			state[KEYWORD] = -1;

		break;

	case 15:
		if (input == 'n')
			state[KEYWORD] = 16;

		else
			state[KEYWORD] = -1;

		break;

	case 16:
		state[KEYWORD] = -1;
		break;
	}

	if (state[KEYWORD] < 0)
		accept[KEYWORD] = -1;
	else if (state[KEYWORD] == 16)
		accept[KEYWORD] = 1;
	else
		accept[KEYWORD]=  0;
}

//BoolString DFA
void isBoolString(char input)									//accept state: 8
{
	switch (state[BOOLSTRING])
	{
	case 0:
		if (input == 't')
			state[BOOLSTRING] = 1;

		else if (input == 'f')
			state[BOOLSTRING] = 4;

		else
			state[BOOLSTRING] = -1;

		break;

	case 1:
		if (input == 'r')
			state[BOOLSTRING] = 2;

		else
			state[BOOLSTRING] = -1;

		break;

	case 2:
		if (input == 'u')
			state[BOOLSTRING] = 3;

		else
			state[BOOLSTRING] = -1;

		break;

	case 3:
		if (input == 'e')
			state[BOOLSTRING] = 8;

		else
			state[BOOLSTRING] = -1;

		break;

	case 4:
		if (input == 'a')
			state[BOOLSTRING] = 5;

		else
			state[BOOLSTRING] = -1;

		break;

	case 5:
		if (input == 'l')
			state[BOOLSTRING] = 6;

		else
			state[BOOLSTRING] = -1;

		break;

	case 6:
		if (input == 's')
			state[BOOLSTRING] = 7;

		else
			state[BOOLSTRING] = -1;

		break;

	case 7:
		if (input == 'e')
			state[BOOLSTRING] = 8;

		else
			state[BOOLSTRING] = -1;

		break;

	case 8:
		state[BOOLSTRING] = -1;
		break;
	}

	if (state[BOOLSTRING] < 0)
		accept[BOOLSTRING] = -1;
	else if (state[BOOLSTRING] == 8)
		accept[BOOLSTRING] = 1;
	else
		accept[BOOLSTRING] = 0;
}

//Integer DFA
void isInteger(char input)									//accept state 3
{
	switch (state[INTEGER])
	{
	case 0:
		if (input == '0')
			state[INTEGER] = 1;

		else if ('1' <= input && input <= '9')
			state[INTEGER] = 3;

		else if (input == '-')
			state[INTEGER] = 2;

		else
			state[INTEGER] = -1;

		break;

	case 1:
		state[INTEGER] = -1;

		break;

	case 2:
		if ('1' <= input && input <= '9')
			state[INTEGER] = 3;

		else
			state[INTEGER] = -1;

		break;

	case 3:
		if ('0' <= input && input <= '9')
			state[INTEGER] = 3;

		else
			state[INTEGER] = -1;

		break;

	}

	if (state[INTEGER] < 0)
		accept[INTEGER] = -1;
	else if (state[INTEGER] == 3 || state[INTEGER] == 1)
		accept[INTEGER] = 1;
	else
		accept[INTEGER] = 0;
}

//IntegerMINUS DFA
void isIntegerMINUS(char input)									//accept state 3
{
	switch (state[INTEGERMINUS])
	{
	case 0:
		if (input == '0')
			state[INTEGERMINUS] = 1;

		else if ('1' <= input && input <= '9')
			state[INTEGERMINUS] = 3;

		else if (input == '-')
			state[INTEGERMINUS] = 2;

		else
			state[INTEGERMINUS] = -1;

		break;

	case 1:
		if (input == '-')
			state[INTEGERMINUS] = 4;
		else
			state[INTEGERMINUS] = -1;

		break;

	case 2:
		if ('1' <= input && input <= '9')
			state[INTEGERMINUS] = 3;

		else
			state[INTEGERMINUS] = -1;

		break;

	case 3:
		if ('0' <= input && input <= '9')
			state[INTEGERMINUS] = 3;
		else if (input == '-')
			state[INTEGERMINUS] = 4;
		else
			state[INTEGERMINUS] = -1;

		break;
	case 4:
		state[INTEGERMINUS] = -1;

	}

	if (state[INTEGERMINUS] < 0)
		accept[INTEGERMINUS] = -1;
	else if (state[INTEGERMINUS] == 4)
		accept[INTEGERMINUS] = 1;
	else
		accept[INTEGERMINUS] = 0;
}

//LiteralString DFA
void isLiteralString(char input)
{
	switch (state[LITERALSTRING])
	{
	case 0:
		if (input == '"')
			state[LITERALSTRING] = 1;

		else
			state[LITERALSTRING] = -1;

		break;

	case 1:
		if (input == '"')
			state[LITERALSTRING] = 2;

		break;

	case 2:
		state[LITERALSTRING] = -1;

		break;

	}

	if (state[LITERALSTRING] < 0)
		accept[LITERALSTRING] = -1;
	else if (state[LITERALSTRING] == 2)
		accept[LITERALSTRING] = 1;
	else
		accept[LITERALSTRING] = 0;
}

//FloatNum DFA
void isFloatNum(char input)							//accept state: 4, 6       -1: 절대 안됨, 0: 될 수도 있음, 1: 됨
{
	switch (state[FLOATNUM])
	{
	case 0:
		if (input == '0')
			state[FLOATNUM] = 1;

		else if (input == '-')
			state[FLOATNUM] = 7;

		else if ('1' <= input && input <= '9')
			state[FLOATNUM] = 2;

		else
			state[FLOATNUM] = -1;

		break;
	
	case 1:
		if(input == '.')
			state[FLOATNUM] = 3;

		else
			state[FLOATNUM] = -1;

		break;

	case 2:
		if (input == '.')
			state[FLOATNUM] = 3;

		else if ('0' <= input && input <= '9')
			state[FLOATNUM] = 2;

		else
			state[FLOATNUM] = -1;

		break;

	case 3:
		if (input == '0')
			state[FLOATNUM] = 4;

		else if ('1' <= input && input <= '9')
			state[FLOATNUM] = 6;
			
		else
			state[FLOATNUM] = -1;

		break;

	case 4:
		if (input == '0')
			state[FLOATNUM] = 5;

		else if ('1' <= input && input <= '9')
			state[FLOATNUM] = 6;

		else
			state[FLOATNUM] = -1;

		break;

	case 5:
		if (input == '0')
			state[FLOATNUM] = 5;

		else if ('1' <= input && input <= '9')
			state[FLOATNUM] = 6;

		else
			state[FLOATNUM] = -1;

		break;

	case 6:
		if (input == '0')
			state[FLOATNUM] = 5;

		else if ('1' <= input && input <= '9')
			state[FLOATNUM] = 6;

		else
			state[FLOATNUM] = -1;

		break;
	case 7:
		if (input == '0')
			state[FLOATNUM] = 1;
		else if ('1' <= input && input <= '9')
			state[FLOATNUM] = 2;
		else
			state[FLOATNUM] = -1;

	}

	if (state[FLOATNUM] < 0)								
		accept[FLOATNUM] = -1;
	else if (state[FLOATNUM] == 4 || state[FLOATNUM] == 6)
		accept[FLOATNUM] = 1;
	else
		accept[FLOATNUM] = 0;
}

//FloatNumMinus DFA
void isFloatNumMINUS(char input)							//accept state: 4, 6       -1: 절대 안됨, 0: 될 수도 있음, 1: 됨
{
	switch (state[FLOATNUMMINUS])
	{
	case 0:
		if (input == '0')
			state[FLOATNUMMINUS] = 1;
		else if (input == '-')
			state[FLOATNUMMINUS] = 8;

		else if ('1' <= input && input <= '9')
			state[FLOATNUMMINUS] = 2;

		else
			state[FLOATNUMMINUS] = -1;

		break;

	case 1:
		if (input == '.')
			state[FLOATNUMMINUS] = 3;

		else
			state[FLOATNUMMINUS] = -1;

		break;

	case 2:
		if (input == '.')
			state[FLOATNUMMINUS] = 3;

		else if ('0' <= input && input <= '9')
			state[FLOATNUMMINUS] = 2;

		else
			state[FLOATNUMMINUS] = -1;

		break;

	case 3:
		if (input == '0')
			state[FLOATNUMMINUS] = 4;

		else if ('1' <= input && input <= '9')
			state[FLOATNUMMINUS] = 6;

		else
			state[FLOATNUMMINUS] = -1;

		break;

	case 4:
		if (input == '0')
			state[FLOATNUMMINUS] = 5;

		else if ('1' <= input && input <= '9')
			state[FLOATNUMMINUS] = 6;
		
		else if (input == '-')
			state[FLOATNUMMINUS] = 7;
		
		else
			state[FLOATNUMMINUS] = -1;

		break;

	case 5:
		if (input == '0')
			state[FLOATNUMMINUS] = 5;

		else if ('1' <= input && input <= '9')
			state[FLOATNUMMINUS] = 6;

		else
			state[FLOATNUMMINUS] = -1;

		break;

	case 6:
		if (input == '0')
			state[FLOATNUMMINUS] = 5;

		else if ('1' <= input && input <= '9')
			state[FLOATNUMMINUS] = 6;

		else if (input == '-')
			state[FLOATNUMMINUS] = 7;

		else
			state[FLOATNUMMINUS] = -1;

		break;
	case 7:
		state[FLOATNUMMINUS] = -1;
		break;

	case 8:
		if (input == '0')
			state[FLOATNUMMINUS] = 1;
		else if ('1' <= input && input <= '9')
			state[FLOATNUMMINUS] = 2;
		else
			state[FLOATNUMMINUS] = -1;
		break;
	}
	
	if (state[FLOATNUMMINUS] < 0)
		accept[FLOATNUMMINUS] = -1;
	else if (state[FLOATNUMMINUS] == 7)
		accept[FLOATNUMMINUS] = 1;
	else
		accept[FLOATNUMMINUS] = 0;
}

//ID DFA
void isID(char input)
{
	switch (state[ID])
	{
	case 0:
		if (input == '_' ||                     //글자가 _이거나 알파벳이나 Digit인지 확인 아닐 경우 break
			('A' <= input && input <= 'Z') ||
			('a' <= input && input <= 'z'))
			state[ID] = 1;

		else
			state[ID] = -1;

		break;

	case 1:
		if (input == '_' ||                     //글자가 _이거나 알파벳이나 Digit인지 확인 아닐 경우 break
			('A' <= input && input <= 'Z') ||
			('a' <= input && input <= 'z') ||
			('0' <= input && input <= '9'))
		state[ID] = 1;

		else
			state[ID] = -1;

		break;
	}

	if (state[ID] < 0)
		accept[ID] = -1;
	else if (state[ID] == 1)
		accept[ID] = 1;
	else
		accept[ID] = 0;
}

//IDMINUS DFA
void isIDMINUS(char input)
{
	switch (state[IDMINUS])
	{
	case 0:
		if (input == '_' ||                     //글자가 _이거나 알파벳이나 Digit인지 확인 아닐 경우 break
			('A' <= input && input <= 'Z') ||
			('a' <= input && input <= 'z'))
			state[IDMINUS] = 1;

		else
			state[IDMINUS] = -1;

		break;

	case 1:
		if (input == '_' ||                     //글자가 _이거나 알파벳이나 Digit인지 확인 아닐 경우 break
			('A' <= input && input <= 'Z') ||
			('a' <= input && input <= 'z') ||
			('0' <= input && input <= '9'))
			state[IDMINUS] = 1;
		if (input == '-') state[IDMINUS] = 2;

		else
			state[IDMINUS] = -1;

		break;
	
	case 2:
		state[IDMINUS] = -1;
		break;
	}

	if (state[IDMINUS] < 0)
		accept[IDMINUS] = -1;
	else if (state[IDMINUS] == 2)
		accept[IDMINUS] = 1;
	else
		accept[IDMINUS] = 0;
}

//BitOP DFA
void isBitOp(char input)						//accept state : 3
{
	switch (state[BITOP])
	{
	case 0:
		if (input == '<')
			state[BITOP] = 1;

		else if (input == '>')
			state[BITOP] = 2;

		else if (input == '|')
			state[BITOP] = 3;
		else if (input == '&')
			state[BITOP] = 3;
		else
			state[BITOP] = -1;

		break;

	case 1:
		if (input == '<')
			state[BITOP] = 3;

		else
			state[BITOP] = -1;

		break;

	case 2:
		if (input == '>')
			state[BITOP] = 3;

		else
			state[BITOP] = -1;

		break;

	case 3:
		state[BITOP] = -1;

		break;

	}

	if (state[BITOP] < 0)
		accept[BITOP] = -1;
	else if (state[BITOP] == 3)
		accept[BITOP] = 1;
	else
		accept[BITOP] = 0;
}

//ComOP DFA
void isCompOp(char input)
{
	switch (state[COMPOP])
	{
	case 0:
		if (input == '<')
			state[COMPOP] = 1;

		else if (input == '>')
			state[COMPOP] = 2;

		else if (input == '=')
			state[COMPOP] = 3;

		else if (input == '!')
			state[COMPOP] = 4;

		else
			state[COMPOP] = -1;

		break;

	case 1:
		if (input == '=')
			state[COMPOP] = 5;

		else
			state[COMPOP] = -1;

		break;

	case 2:
		if (input == '=')
			state[COMPOP] = 5;

		else
			state[COMPOP] = -1;

		break;

	case 3:
		if (input == '=')
			state[COMPOP] = 5;

		else
			state[COMPOP] = -1;

		break;

	case 4:
		if (input == '=')
			state[COMPOP] = 5;

		else
			state[COMPOP] = -1;

		break;

	case 5:
		state[COMPOP] = -1;
		break;
	}

	if (state[COMPOP] < 0)
		accept[COMPOP] = -1;
	else if (state[COMPOP] == 1 || state[COMPOP] == 2 || state[COMPOP] == 5)
		accept[COMPOP] = 1;
	else
		accept[COMPOP] = 0;
}

//ArithmeticOp DFA
void isArithmeticOp(char input)
{
	switch (state[ARITHMETICOP])
	{
	case 0:
		if (input == '+')
			state[ARITHMETICOP] = 1;
		
		else if (input == '-')
			state[ARITHMETICOP] = 1;

		else if (input == '*')
			state[ARITHMETICOP] = 1;

		else if (input == '/')
			state[ARITHMETICOP] = 1;

		else
			state[ARITHMETICOP] = -1;

		break;

	case 1:
		state[ARITHMETICOP] = -1;

		break;

	}

	if (state[ARITHMETICOP] < 0)
		accept[ARITHMETICOP] = -1;
	else if (state[ARITHMETICOP] == 1)
		accept[ARITHMETICOP] = 1;
	else
		accept[ARITHMETICOP] = 0;
}

//Assignment DFA
void isAssignment(char input)
{
	switch (state[ASSIGNMENT])
	{
	case 0:
		if (input == '=')
			state[ASSIGNMENT] = 1;

		else
			state[ASSIGNMENT] = -1;

		break;

	case 1:
		state[ASSIGNMENT] = -1;

		break;

	}

	if (state[ASSIGNMENT] < 0)
		accept[ASSIGNMENT] = -1;
	else if (state[ASSIGNMENT] == 1)
		accept[ASSIGNMENT] = 1;
	else
		accept[ASSIGNMENT] = 0;
}

//Terminate DFA
void isTerminate(char input)
{
	switch (state[TERMINATE])
	{
	case 0:
		if (input == ';')
			state[TERMINATE] = 1;

		else
			state[TERMINATE] = -1;

		break;

	case 1:
		state[TERMINATE] = -1;

		break;

	}

	if (state[TERMINATE] < 0)
		accept[TERMINATE] = -1;
	else if (state[TERMINATE] == 1)
		accept[TERMINATE] = 1;
	else
		accept[TERMINATE] = 0;
}

//LBrace DFA
void isLBrace(char input)
{
	switch (state[LBRACE])
	{
	case 0:
		if (input == '{')
			state[LBRACE] = 1;

		else
			state[LBRACE] = -1;

		break;

	case 1:
		state[LBRACE] = -1;

		break;

	}

	if (state[LBRACE] < 0)
		accept[LBRACE] = -1;
	else if (state[LBRACE] == 1)
		accept[LBRACE] = 1;
	else
		accept[LBRACE] = 0;
}

//RBrace DFA
void isRBrace(char input)
{
	switch (state[RBRACE])
	{
	case 0:
		if (input == '}')
			state[RBRACE] = 1;

		else
			state[RBRACE] = -1;

		break;

	case 1:
		state[RBRACE] = -1;

		break;

	}

	if (state[RBRACE] < 0)
		accept[RBRACE] = -1;
	else if (state[RBRACE] == 1)
		accept[RBRACE] = 1;
	else
		accept[RBRACE] = 0;
}

//LParen DFA
void isLParen(char input)
{
	switch (state[LPAREN])
	{
	case 0:
		if (input == '(')
			state[LPAREN] = 1;

		else
			state[LPAREN] = -1;

		break;

	case 1:
		state[LPAREN] = -1;

		break;

	}

	if (state[LPAREN] < 0)
		accept[LPAREN] = -1;
	else if (state[LPAREN] == 1)
		accept[LPAREN] = 1;
	else
		accept[LPAREN] = 0;
}

//RParen DFA
void isRParen(char input)
{
	switch (state[RPAREN])
	{
	case 0:
		if (input == ')')
			state[RPAREN] = 1;

		else
			state[RPAREN] = -1;

		break;

	case 1:
		state[RPAREN] = -1;

		break;

	}

	if (state[RPAREN] < 0)
		accept[RPAREN] = -1;
	else if (state[RPAREN] == 1)
		accept[RPAREN] = 1;
	else
		accept[RPAREN] = 0;
}

//Comma DFA
void isComma(char input)
{
	switch (state[COMMA])
	{
	case 0:
		if (input == ',')
			state[COMMA] = 1;

		else
			state[COMMA] = -1;

		break;

	case 1:
		state[COMMA] = -1;

		break;

	}

	if (state[COMMA] < 0)
		accept[COMMA] = -1;
	else if (state[COMMA] == 1)
		accept[COMMA] = 1;
	else
		accept[COMMA] = 0;
}

//White Space DFA
void isWhiteSpace(char input)
{
	switch (state[WHITESPACE])
	{
	case 0:
		if (input == ' ')
			state[WHITESPACE] = 1;

		else if (input == '\t')
			state[WHITESPACE] = 1;

		else if (input == 13)
			state[WHITESPACE] = 1;

		else
			state[WHITESPACE] = -1;

		break;

	case 1:
		state[WHITESPACE] = -1;

		break;

	}

	if (state[WHITESPACE] < 0)
		accept[WHITESPACE] = -1;
	else if (state[WHITESPACE] == 1)
		accept[WHITESPACE] = 1;
	else
		accept[WHITESPACE] = 0;
}
