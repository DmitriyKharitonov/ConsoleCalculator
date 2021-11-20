#pragma once

class Tokentype {
private:
	std::string name;
	std::string regax;
	std::string interpretation;
	int precedence; //подробнее в Runner.h функция RunBinOp()
public:
	Tokentype() {
		name = "";
		interpretation = "";
		regax = "";
		precedence = 1000;
	}
	Tokentype(std::string a, std::string b, std::string c, int d) {
		name = a;
		interpretation = b;
		regax = c;
		precedence = d;
	}

	std::string GetName() {
		return name;
	}

	std::string GetRegax() {
		return regax;
	}

	std::string Getinterpretation() {
		return interpretation;
	}

	int GetPrecedence() {
		return precedence;
	}

	friend bool operator==(Tokentype& type1, Tokentype& type2);
};

bool operator==(Tokentype& type1, Tokentype& type2) {
	return (type1.name == type2.name);
}

//подерживаются различные виды написания
//а также возможные ошибки
Tokentype Nothing = Tokentype();
Tokentype Pi_Constant = Tokentype("Pi_Constant", "pi", "^(pi)", 100);
Tokentype E_Constant = Tokentype("E_Constant", "e", "^([e^exp])", 100);
Tokentype Space = Tokentype("Space", " ", "^\\ ", 100);
Tokentype Number = Tokentype("Number", " Number" , "^([0-9]*\\,?[0-9]*)", 100);
Tokentype Variable = Tokentype("Variable", "x", "^(x)", 100);
Tokentype Plus = Tokentype("Math_operation_plus", "+","^([\+])", 10);
Tokentype Minus = Tokentype("Math_operation_minus","-", "^([\-])", 10);
Tokentype Mult = Tokentype("Math_operation_mult","*", "^([\*])", 20);
Tokentype Div = Tokentype("Math_operation_div","/", "^([\/])", 20);
Tokentype Power = Tokentype("Math_operation_power","^", "^([\\^])", 40);
Tokentype Sqrt = Tokentype("Math_function_sqrt","sqrt", "^((sqrt)?(sqr)?)", 100);
Tokentype Sin = Tokentype("Math_function_sin", "sin", "^((sin)?(Sin)?(sine)?)", 100);
Tokentype Cos = Tokentype("Math_function_cos","cos", "^((cos)?(c0s)?(Cos)?(cosine)?)", 100);
Tokentype Tg = Tokentype("Math_function_tg", "tg", "^((tg)?(tan)?(tangent)?)", 100);
Tokentype Arcsin = Tokentype("Math_function_arcsin", "arcsin", "^((arcsin)?(arsin)?(asin)?)", 100);
Tokentype Arccos = Tokentype("Math_function_arccos", "arccos", "^((arccos)?(arcos)?(arc0s)?(acos)?(ac0s)?)", 100); 
Tokentype Arctg = Tokentype("Math_function_arctg","arctg", "^((arctg)?(arctan)?(atan)?)", 100);
Tokentype Ln = Tokentype("Math_function_ln", "ln", "^((ln)?(log)?)", 100);
Tokentype Exp = Tokentype("Math_function_exp", "exp", "^(exp)", 100);
Tokentype Lpar = Tokentype("Lpar", "(", "^[\\(]", 100);
Tokentype Rpar = Tokentype("Rpar", ")", "^[\\)]", 0);

//список всех имеющихся токенов
std::vector <Tokentype> Tokens{Space, Number, Variable, Plus, Minus, Mult, Div, Power, Sqrt, Sin, Cos, Tg, Arcsin, Arccos, Arctg, Ln, Exp, Lpar,Rpar, Pi_Constant, E_Constant};
