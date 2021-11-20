#pragma once

#include "Token.h"
#include <vector>



class Lexer {
private:
	std::smatch result;
	std::string code;
	int position = 0;
	std::vector <Token> Token_list;
public:
	Lexer() {}
	Lexer(std::string a) {
		code = a;
	}

	void LexAnalisys() {
		std::string string_to_analysis = code;
		
		while (position < code.length()) {
			for (int i = 0; i < Tokens.size(); i++) {//поочередно сравниваем текущее выражение со списком всех поддерживаемых токенов
				Tokentype token_type = Tokens[i];
				std::regex regular(Tokens[i].GetRegax());
				std::regex_search(string_to_analysis, result, regular);
				if (result.length() != 0) {
					Token newToken;
					if (token_type == Number) {//дл€ всех токенок, кроме Number, интерпретаци€ известна заранее
											   //до анализа кода мы не знаем, какое именно число встретим
						newToken = Token(token_type, result.str(), result.str(), position);
					}
					else newToken = Token(token_type, result.str(), position);
					position += result.length();
					Token_list.push_back(newToken);
					i = -1;
				}
				string_to_analysis = string_to_analysis.substr(result.length());
				if (position >= code.length()) break;
			}

			if (result[0].length() == 0) {//если ни один из поддерживаемых токенок не подошел
				std::cout<<"Ќекорректное выражение"<< code[position]<<" в символе є" <<std::to_string(position);
				exit(1);
			}
		}
	}

	std::smatch GetResult() {
		return result;
	}

	std::string GetCode() {
		return code;
	}

	int Getposition() {
		return position;
	}

	std::vector <Token> GetTokenList() {
		return Token_list;
	}

	void SetResult(std::smatch res) {
		result = res;
	}

	void SetCode(std::string code_string) {
		code = code_string;
	}

	void SetPosition(int pos) {
		position = pos;
	}

	void SetTokenList(std::vector <Token> list) {
		Token_list = list;
	}
};

