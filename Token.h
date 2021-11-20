#pragma once
#include "TokenType.h"

class Token {
private:
	Tokentype type;
	std::string token_interpretation; //нужно для неоднозначных трактовок токенов
					  //c0s(x) -> cos(x), asin(x) -> arcsin(x)
	std::string text;
	int pair_position = -1;
	int position;
public:
	Token() {
		type = Nothing;
		token_interpretation = "";
		text = "";
		position = -1;
	}
	Token(Tokentype a, std::string b, int c) {
		type = a;
		token_interpretation = a.Getinterpretation();
		text = b;
		position = c;
	}
	Token(Tokentype a, std::string b,  std::string c, int d) {//для токенов, с заранее неизветсным представлением. Например - Number
		type = a;
		token_interpretation = b;
		text = c;
		position = d;
	}

	Tokentype GetType() {
		return type;
	}

	std::string GetTokenInterpretation() {
		return token_interpretation;
	}

	std::string GetText() {
		return text;
	}

	int GetPairPosition() {
		return pair_position;
	}

	int GetPosition() {
		return position;
	}

	void SetPairPosition(int pos) {
		pair_position = pos;
	}

	void SetText(std::string token_text) {
		text = token_text;
	}

	friend bool operator == (Token &Token1, Tokentype &Token2);
};

bool operator==(Token  &Token1, Tokentype &type) {
	return (Token1.type == type);
}
