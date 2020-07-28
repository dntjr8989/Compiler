우선 저희는 lexical_Analyzer와 Syntax_Analyzer 코드가 연결 되어 있습니다.

extern을 이용해서 두 소스 코드를 엮었씁니다.

main함수는 lexical_Analyzer 코드가 있는 Simple_Compiler.cpp에 있으며
Syntax_Analyzer.cpp에 코드를 보내면 코드들을 Token으로 분류하고, 그 중에서
과제에 나와있는 non-terminal들을 토대로 Syntax_Analyzer코드에 non-terminal들을 보냅니다.

그러므로 입력하고 싶은 코드가 있는 텍스트파일만 입력한다면 바로 Syntax까지 한 결과가 console로 나옵니다.
