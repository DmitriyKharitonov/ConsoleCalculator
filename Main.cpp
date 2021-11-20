#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <regex>
#include <locale>
#include <windows.h>
#include "Lexer.h"
#include "Runner.h"
#include "Token.h"

void UnitTest() {
	std::string input;
	std::string x = "0,5463";
	std::vector <std::string> Test;
	std::vector <std::string> Expetced_result;
	Test.push_back("5*(2+2)");
	Expetced_result.push_back("20");
	Test.push_back("5(2+2*2*2)");
	Expetced_result.push_back("50");
	Test.push_back("6(2+2*2*2)/5"); 
	Expetced_result.push_back("12");
	Test.push_back("5exp(5x-6)^2");
	Expetced_result.push_back("0.00724414");
	Test.push_back("32.5exp(-cos(tg(2x/6^2)))^2-10");
	Expetced_result.push_back("-5.59755");
	Test.push_back("5sin(cos(x^2))/5+ln(25)-34tg(x^3)-4");
	Expetced_result.push_back("-5.55735");
	Test.push_back("5*(tg(x^4-0.3489)/5-15)/25^5+exp(exp(x^2))");
	Expetced_result.push_back("3.84879");
	Test.push_back("5*(25*5-5)^2");
	Expetced_result.push_back("72000");
	Test.push_back("cos(cos(cos(cos(cos(cos(pi)))*2tg(0.76pi))-0.324))*x*e");
	Expetced_result.push_back("0.882348");

	for (int i = 0; i < Test.size(); i++) {
		input = std::regex_replace(Test[i], std::regex("\\."), ",");

		Lexer l = Lexer(input);
		l.LexAnalisys();

		Preparing p = Preparing(l.GetTokenList());

		p.Preparation(x);

		Parser final = Parser(p.GetTokensAfterPreparing(), 0);

		std::cout << " Распознано как ";
		for (int i = 0; i < final.GetTokens().size(); i++) {
			std::cout << final.GetTokens()[i].GetTokenInterpretation();
		}
		std::cout << std::endl;

		double result = final.Run(0, final.GetTokens().size() - 1);
		std::cout << " Ответ " << result << " Ожидаемый результат " << Expetced_result[i]<<std::endl<<std::endl;
	}
}

int main() {
	setlocale(LC_ALL, "Russian");
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	UnitTest();

	/*std::string input;
	std::string x;
	std::cout << " Введите функцию " << std::endl;
	std::getline(std::cin, input);

	input = std::regex_replace(input, std::regex("\\."), ",");

	std::cout << " Введите значение переменной х " << std::endl;
	std::getline(std::cin, x);
	x = std::regex_replace(x, std::regex("\\."), ",");

	Lexer l = Lexer(input);
	l.LexAnalisys();

	Preparing p = Preparing(l.GetTokenList());

	p.Preparation(x);

	Parser final = Parser(p.GetTokensToPreparing(), 0);

	std::cout << " Распознано как ";
	for (int i = 0; i < final.GetTokens().size(); i++) {
		std::cout << final.GetTokens()[i].GetTokenInterpretation();
	}
	std::cout << std::endl;

	double result = final.Run(0, final.GetTokens().size() - 1);
	std::cout << " Ответ " << result;*/

	return 0;
}
