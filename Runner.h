#pragma once

class Preparing {
private:
	std::vector <Token> tokens_after_preparing;
public:
	Preparing(std::vector <Token> a) {
		tokens_after_preparing = a;
	}

	void Preparation(std::string variable_value) {//����� �������� �� ������ ������� ���� �� �������, ������ �� � ����� �����
		MultAdd();
		iterator();
		initializingConstant();
		initializingVariables(variable_value);
	}

	void initializingVariables(std::string x) {
		for (int i = 0; i < tokens_after_preparing.size(); i++) {
			if (tokens_after_preparing[i] == Variable) {
				tokens_after_preparing[i].SetText(x);
			}
		}
	}
	
	void MultAdd() {//�� ����� �������, �� ���������� ���� �� ��������
		
		std::vector <Tokentype> insert_multiplication = {Lpar, Pi_Constant, E_Constant, Variable, Sqrt, Sqrt, Sin, Cos, Tg, Arcsin, Arccos, Arctg, Ln, Exp};

		for (int i = 0; i < insert_multiplication.size(); i+=2) {
			insert_multiplication.insert(insert_multiplication.begin() + i, Number); //�������� ��� ���� �������, ����� �������� ����� ���� �������� ���� ���������
																					 //������: Number * Lpar, Number * Pi_Constant, Number * E_Constant...
																					 //� ������� ���� xcos(x) ������ ����� ��� ����� ������ ���� ���������, 
																					 //��� ��� ����� ��������� - xcos(x) - �� ����������
																					 //�� �������: � ����� ������� ����� �������� ��������������.
																					 //��� ������������� ���������� �� cos(x) ����� �������
		}
		//��� ���� ��������� �������� - )( - ������: (5+2)(6+8)
		insert_multiplication.push_back(Rpar);
		insert_multiplication.push_back(Lpar);

		for (int i = 0; i < tokens_after_preparing.size()-1; i++) {//���� ���������� ����� ����� ��������� ������� � ����� �������, ����� �������� ����� ������ ���� ���������
			for (int j = 0; j < insert_multiplication.size(); j += 2) {
				if (tokens_after_preparing[i] == insert_multiplication[j] && tokens_after_preparing[i + 1] == insert_multiplication[j + 1]) {
					Token multtoken = Token(Mult, "*", "*", i + 1);
					tokens_after_preparing.insert(tokens_after_preparing.begin() + i + 1, multtoken);
					i+=2;
					break;
				}
			}
		}
	}

	void iterator() {//������� ���� ��� ������ ������
		for (int i = 0; i < tokens_after_preparing.size(); i++) {
			if (tokens_after_preparing[i] == Rpar) {
				//���� �� ������ i �� 0 (� �������� �������)
				//��� ����� ������� ������ ������ � ���� ������������� ��������� ����� �����
				findPair(i, 0, i);
			}
		}

		//���� �������� ����� ������ ��� ���� - ������ ������
		//�������� ���� ��� ������ ������ �������������� � findPair()
		for (int i = 0; i < tokens_after_preparing.size(); i++) {
			if (tokens_after_preparing[i] == Lpar && tokens_after_preparing[i].GetPairPosition() == -1) {
				std::cout << " ��������� ������ ����������� ������ ";
				exit(1);
			}
		}

	}

	void findPair(int find_start, int find_end, int current_position) {
		int index = -1; //������� ����� ������
		for (int i = find_start; i >= find_end; i--) {
			if (tokens_after_preparing[i] == Lpar) {
				index = i;
				break;
			}
		}
		//���� ����� ������ �� �������
		if (index == -1) {
			std::cout << "��������� ����� ����������� ������ ";
			exit(1);
		}
		//���� � ����� ����� ��� ��� ���� - ��������� �� � ������ �������
		//����� ���� ������
		if (tokens_after_preparing[index].GetPairPosition() == -1) {
			tokens_after_preparing[index].SetPairPosition(current_position);
			tokens_after_preparing[current_position].SetPairPosition(index);
		}
		else {
			findPair(index - 1, find_end, current_position);
		}
	}

	void initializingConstant() {
		for (int i = 0; i < tokens_after_preparing.size(); i++) {
			if (tokens_after_preparing[i] == Pi_Constant) tokens_after_preparing[i].SetText("3,14159265358979323846");
			else if (tokens_after_preparing[i] == E_Constant) tokens_after_preparing[i].SetText("2,71828182845904523536");
		}
	}

	void SetTokensAterPreparing(std::vector <Token> tokens_vector) {
		tokens_after_preparing = tokens_vector;
	}

	std::vector <Token> GetTokensAfterPreparing() {
		return tokens_after_preparing;
	}

};

class Parser {
private:
	std::vector <Token> tokens;
	int current_position = 0;
	double x = 1;
	double temporary_result = 0;
public:

	Parser() {}
	Parser(std::vector <Token> a, double variable) {
		tokens = a;
		x = variable;
	}
	
	void match(Token Curr_Tok, Tokentype Expected_Token) {
		if (!(Curr_Tok == Expected_Token)) {
			std::cout << " ��������� ��������� " << Expected_Token.GetName() << " �� ������� " << current_position + 1;
			exit(1);
		}
	}

	void RunNumberorConstant(Token Curr_Tok) {
		temporary_result = atof(Curr_Tok.GetText().c_str());
		current_position += 1;
	}

	void RunVariable(Token Curr_Tok) {
		temporary_result = atof(Curr_Tok.GetText().c_str());
		current_position += 1;
	}
	
	void RunLParExp(Token Curr_Tok) {
		current_position += 1;
		temporary_result = Run(current_position, Curr_Tok.GetPairPosition());
	}

	void RunMathFunction(Token Curr_Tok) {

		current_position += 1;
		match(tokens[current_position], Lpar); //����� �������� ������� ������ ���� ����� ����� - sin(...)
		double local_result = Run(current_position, current_position);

		if (Curr_Tok == Sin) temporary_result = sin(local_result);

		else if (Curr_Tok == Cos) temporary_result = cos(local_result);

		else if (Curr_Tok == Tg) temporary_result = tan(local_result);

		else if (Curr_Tok == Arcsin) temporary_result = asin(local_result);

		else if (Curr_Tok == Arccos) temporary_result = acos(local_result);

		else if (Curr_Tok == Arctg) temporary_result = atan(local_result);

		else if (Curr_Tok == Ln) temporary_result = log(local_result);

		else if (Curr_Tok == Exp) temporary_result = exp(local_result);

		else if (Curr_Tok == Sqrt) temporary_result = sqrt(local_result);
	}

	void RunBinOp(Token Curr_Tok) {
		int end_parsing = current_position + 1;
		double local_LHS = temporary_result;//� temporary_result �������� �������� ������ ��������

		while (tokens[end_parsing].GetType().GetPrecedence() > Curr_Tok.GetType().GetPrecedence()) {//���� �������� �������� ������ ������, ��� � ��������� - ���� ������
																									//������ ����� ������ "�������������" ����� ��������
																									//������: (5+2*2^6*8)^5. ��� ��������� + ������ ������� - 2*2^6*8
																									//���� �� �������� ��������� ������ ����� ������ ������ ������
																									//� ������� � ������ ������� ^5, ��� �������� �������

														
			if (tokens[end_parsing] == Lpar) {//����� ���, ��� ��������� ������ ������
				end_parsing = tokens[end_parsing].GetPairPosition() + 1;
			}
			else end_parsing++;
			if (end_parsing >= tokens.size()) break;
		}
		end_parsing -= 1;

		local_LHS = temporary_result;

		if (Curr_Tok == Minus) {//��� �������� ������. �� ��������� ���� � ����� ������ ������, ���� �������� � ������
			if (current_position == 0 || tokens[current_position - 1] == Lpar) local_LHS = 0;
		}

		current_position += 1;
		double local_result = Run(current_position, end_parsing);

		if (Curr_Tok == Plus) temporary_result = local_LHS + local_result;
		else if (Curr_Tok == Minus) temporary_result = local_LHS - local_result;
		else if (Curr_Tok == Mult) temporary_result = local_LHS * local_result;
		else if (Curr_Tok == Div) temporary_result = local_LHS / local_result;
		else if (Curr_Tok == Power) temporary_result = pow(local_LHS, local_result);
	}

	double Run(int begin, int end) {
		for (int position = begin; position <= end; position++) {
			if (tokens[position] == Number || tokens[position] == E_Constant || tokens[position] == Pi_Constant) {
				RunNumberorConstant(tokens[position]);
			}

			else if (tokens[position] == Variable){
				RunVariable(tokens[position]);
			}

			else if (tokens[position] == Lpar) {
				RunLParExp(tokens[position]);
				position = current_position - 1;
			}
			//��������� ����� ������ ������� ��� ���������� � RunLParExp()
			else if (tokens[position] == Rpar) {
				current_position += 1;
			}

			else if (tokens[position] == Plus || tokens[position] == Minus || tokens[position] == Div || tokens[position] == Mult || tokens[position] == Power) {
				RunBinOp(tokens[position]);
				position = current_position - 1;
			}

			else {
				RunMathFunction(tokens[position]);
				position = current_position - 1;
			}
		}

		return temporary_result;
	}

	std::vector <Token> GetTokens() {
		return tokens;
	}

	int GetCurrentPosition() {
		return current_position;
	}

	double GetVariableValue() {
		return x;
	}

	double GetTemporarryResult() {
		return temporary_result;
	}

	void SetTokens(std::vector <Token> tokens_vector) {
		tokens = tokens_vector;
	}

	void SetCurrentPosition(int pos) {
		current_position = pos;
	}

	void SetVariablesValue(double value) {
		x = value;
	}

	void SetTemporaryResult(double result) {
		temporary_result = result;
	}
};