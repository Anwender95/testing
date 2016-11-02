// test_008.cpp: ���������� ����� ����� ��� ����������� ����������.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <iostream>
using namespace std;

// ������������ ����� �������
#define COM_MAX 10

// ����������� ������
#define ESCAPE 27
#define RETURN 13
#define BACKSPACE 8
#define DELETE 83
#define ARROWS -32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


// ������������ ���������� ��������
class Variables{
private:
	vector<string> _variables;
	vector<double> _values;

public:
	Variables() {
	}

	~Variables() {
		_variables.~vector();
		_values.~vector();
	}

	void addVar() {
		_variables.push_back("");
		_values.push_back(0.0);
	}

	void addVar(const string variable) {
		_variables.push_back(variable);
		_values.push_back(0.0);
	}

	void addVar(const string variable, const double value) {
		std::vector<string>::iterator it;
		
		it = find(_variables.begin(), _variables.end(), variable);

		if(it != _variables.end()) {
			//��������� ������ �� ���������� ��������� �� ����� ���������� �������
			vector<string> tmp(it, _variables.end());

			// ����� ���������� �������
			size_t size0 = _variables.size();
			// ����� ���������� �������
			size_t size1 = tmp.size();

			_values.at(size0 - size1) = value;

		} else {
			_variables.push_back(variable);
			_values.push_back(value);

		}

	}

	void setVar(const string variable, const double value){
		std::vector<string>::iterator it;

		it = find(_variables.begin(), _variables.end(), variable);

		//��������� ������ �� ���������� ��������� �� ����� ���������� �������
		vector<string> tmp(it, _variables.end());

		// ����� ���������� �������
		size_t size0 = _variables.size();
		// ����� ���������� �������
		size_t size1 = tmp.size();

		_values.at(size0 - size1) = value;

	}

	double getVar(const string variable) {
		//��������� ������ �� ���������� ��������� �� ����� ���������� �������
		vector<string> tmp(find(_variables.begin(), _variables.end(), variable), _variables.end());

		// ����� ���������� �������
		size_t size0 = _variables.size();
		// ����� ���������� �������
		size_t size1 = tmp.size();
		// �������� ���� - ����� �������� ����������
		return _values.at(size0 - size1);

	}

};

struct Brackets {
	unsigned int left, right, level;
};

class Operation : string {
private: 
	size_t priority;

public:
	Operation() : string() {
		priority = 0;
	}

	Operation(const char *ptr) : string(ptr){
		priority = 0;
	}

	Operation(const char *ptr, size_t priority0) : string(ptr) {
		priority = priority0;
	}

};


// ������, ���������� �������� � �������� ����������
Variables variables;

// ������ ��������������� �������� � ������������ �����������
vector<string> base;

bool getString(vector<string>& str) {
	char ch;
	string tmp; //��������� ������ ��� �������� � ������� �������
	str.push_back("\0");// ���������� ������� ������� � �����
	size_t k = str.size() - 1;//�������� ������� �����
	size_t c = 0;//��������� ������� ������������ ����� ������

	while(true) {
		ch = _getch();

		if(ch == ESCAPE) {
			return false;

		} else if(ch == RETURN) {
			std::cout << endl;
			return true;

		} else if(ch == BACKSPACE) {
			if(str.back().size()) {
				str.back().erase(str.back().end() - 1 - c);

				std::cout << "\r";

				for(size_t i = 0; i < (str.back().size() + 1); i++) {
					std::cout << " ";
				}

				std::cout << "\r" << str.back();

				// ��������� ������� ������������ ����� ������
				for(size_t i = 0; i < c; i++) {
					std::cout << "\b";
				}
			}

		} else if(ch == ARROWS) {
			ch = _getch();

			if(ch == DELETE) {
				if(c > 0) {
					str.back().erase(str.back().end() - c);
					c--;

					std::cout << "\r";

					for(size_t i = 0; i < (str.back().size() + 1); i++) {
						std::cout << " ";
					}

					std::cout << "\r" << str.back();

					// ��������� ������� ������������ ����� ������
					for(size_t i = 0; i < c; i++) {
						std::cout << "\b";
					}
				}

			} else if(ch == UP) {
				std::cout << "\r";
				for(size_t i = 0; i<str.back().length(); i++) {
					std::cout << " ";
				}
				std::cout << "\r";

				if(k == (str.size() - 1)) {
					tmp = str.back();
				}

				if((k > 0) && (k < str.size())) {
					k--;
					str.back() = str.at(k);

				}

				std::cout << str.back();

			} else if(ch == DOWN) {
				std::cout << "\r";
				for(size_t i = 0; i<str.back().length(); i++) {
					std::cout << " ";
				}
				std::cout << "\r";

				if(k < (str.size() - 1)) {
					k++;

					if(k < (str.size() - 1)) {
						str.back() = str.at(k);

					} else if(k == (str.size() - 1)) {
						str.back() = tmp;
					}

				}

				std::cout << str.back();

			} else if(ch == LEFT) {
				if(c < (str.back().size())) {
					c++;
					std::cout << "\b";
				}

			} else if(ch == RIGHT) {
				if(c > 0) {
					c--;
					std::cout << "\r" << str.back();
					for(size_t i = 0; i < c; i++) {
						std::cout << "\b";
					}
				}
			}

		} else {
			// ������� ������� � ��������� �������
			str.back().insert((str.back().end() - c), ch);

			// ������� ������� � ������ � ��������� ������
			std::cout << "\r" << str.back();

			// ��������� ������� ������������ ����� ������
			for(size_t i = 0; i < c; i++) {
				cout << "\b";
			}
		}

	}
}

int factorial(int n) {
	return (n == 1 || n == 0) ? 1 : factorial(n - 1) * n;
}

double computeUnaryOperation(double a, string op) {
	if(op.compare("sqrt") == 0){
		return sqrt(a);

	} else if(op.compare("sin") == 0) {
		return (sin(a));

	} else if(op.compare("cos") == 0) {
		return (cos(a));

	} else if((op.compare("tan") == 0) || (op.compare("tg") == 0)) {
		return (tan(a));

	} else if((op.compare("cot") == 0) || (op.compare("ctg") == 0)) {
		return (pow(tan(a), -1.0));

	} else if(op.compare("!") == 0) {
		return (factorial(size_t(a)));

	}

	return a;
}

// ���������� �������� ��������
double computeBinaryOperation(double a, double b, string op) {
	if(op.compare("+") == 0) {
		return (a + b);

	} else if(op.compare("-") == 0) {
		return (a - b);

	} else if(op.compare("*") == 0) {
		return (a * b);

	} else if(op.compare("/") == 0) {
		return (a / b);

	} else if(op.compare("^") == 0) {
		return pow(a,b);

	}

	return a;
}

//������������ ��������� ���������
size_t  getPriority(string op) {
	if(op.compare("=") == 0) {
		return 0;//��������� ��������� � ������������
	} else if(op.compare("+") == 0) {
		return 2;
	} else if(op.compare("-") == 0) {
		return 3;
	} else if(op.compare("^") == 0) {
		return 4;
	} else if(op.compare("*") == 0) {
		return 5;
	} else if(op.compare("/") == 0) {
		return 6;
	} else {
		if(op.compare("!") == 0) {
			return 7;
		}

		for(size_t i = 0; i < base.size(); i++) {
			if(op.compare(base[i]) == 0) {
				return 7;
			}
		}

	}
	return 1;
}

//���������� ������� ��������� ������ ������
double solveSimple(vector<double> params, vector<string> ops) {
	size_t prior = 0;
	size_t numOp = 0;
	double result = 0;

	while((params.size()) > 1) {
		prior = 0;
		for(size_t i = 0; i < (ops.size() - 1); i++) {
			if(getPriority(ops[i]) > prior) {
				prior = getPriority(ops[i]);
				numOp = i;
			}
		}

		// ���� �������� ������ "=", �� ��������� ���������� ���� � ����� ����������
		if(ops[numOp + 1].compare("=") == 0) {
			variables.addVar(ops[numOp], params.back());

			return params.back();

		} else {
			if(prior < 6) {
				//���������� ���������� �� ��������� ����������
				result = computeBinaryOperation(params[numOp - 1], params[numOp + 1], ops[numOp]);

				// ���������� ������� ��������� �����������
				params[numOp - 1] = result;

				// �������� ������� ��������� � �������� �������� �� ������� ����������
				params.erase(params.begin() + numOp);
				params.erase(params.begin() + numOp);

				// �������� �������� � �������� ������� ��������� �� ������� ��������
				ops.erase(ops.begin() + numOp);
				ops.erase(ops.begin() + numOp);

			} else {
				result = computeUnaryOperation(params[numOp + 1], ops[numOp]);

				// ���������� ��������� �����������
				params[numOp] = result;

				// �������� ��������� �� ������� ����������
				params.erase(params.begin() + numOp + 1);

				// �������� �������� �� ������� ��������
				ops.erase(ops.begin() + numOp + 1);
			}


		}

	}

	return params.back();

}

// ���������� ������� ����� ��������� ��� ��������
double solveBrackets(vector<double> params, vector<string> ops, vector<Brackets> brkts) {
	size_t level = 0;//������� ���������
	size_t numBr;//����� ���� ������ � �������

	// ���� ������ ����, ����������� ���������� � �������
	while(!brkts.empty()) {
		level = 0;
		//����� ���� ������ � ������������ �������
		for(size_t i = 0; i < brkts.size(); i++) {
			if(brkts[i].level > level) {
				level = brkts[i].level;
				numBr = i;
			}
		}

		vector<double> paramsTmp((params.begin() + brkts[numBr].left + 1), (params.begin() + brkts[numBr].right));
		vector<string> opsTmp((ops.begin() + brkts[numBr].left + 1), (ops.begin() + brkts[numBr].right));
		// ������� ����� ������, � ������� ����� �������� ������� ��������� � �������
		size_t numPar = brkts[numBr].left;

		// ���������� ������� ��������� � ������� � ������� ����� ������ � ������� ����������
		params[numPar] = solveSimple(paramsTmp, opsTmp);

		// �������� �������� ����� �� �������� ���������� � ����������
		params.erase((params.begin() + brkts[numBr].left + 1), (params.begin() + brkts[numBr].right + 1));
		ops.erase((ops.begin() + brkts[numBr].left + 1), (ops.begin() + brkts[numBr].right + 1));

		// �������� ���� ������
		brkts.erase(brkts.begin() + numBr);

		// ����� ���������� ��� ������
		for(size_t i = 0; i < brkts.size(); i++) {
			if(brkts[i].left > numPar) {
				brkts[i].left -= (paramsTmp.size() + 1);// ����� ��������� + ������ ������

			}

			if(brkts[i].right > numPar) {
				brkts[i].right -= (paramsTmp.size() + 1);

			}

		}

		// �������� ��������� ��������
		paramsTmp.~vector();
		opsTmp.~vector();

	}

	return solveSimple(params, ops);
	
}

// ���������� ������� ����� ��������� � ��������� ������ 
double parceString(string str) {
	string symbols;
	symbols = "0123456789,.+-^*/!()[]{}abcdefghijklmnopqrstuvwxyz=";
	size_t level = 0;//������� ���������
	int power = -1;//������� 10

	// ������ ����������
	vector<double> params;

	// ������ ����������
	vector<string> ops;
	string tmpOp;

	// ������  ��� ������
	vector<Brackets> brkts;
	Brackets tmpBr;

	// �������� ������� � ������
	size_t k = 0;

	bool isLeft = false;//Left from digit
	bool isRight = false;//Right from digit

	bool isOp = false;// ���� ��������������� ��� ��������� ��������������� ��������� ����������. e.g.: sin, cos

	// ���� ������������ ����� ������� �������. ����� ������ ����� ����� ���������� �� ���������.
	bool isFirst = true;

	// ���� ��������������� �� ����� ������������ �������� ����� ����������
	bool isAssignment = false;

	//��������� �� ������ ���������� � ����������
	for(size_t j = 0; j < str.length(); j++) {
		for(size_t i = 0; i < symbols.length(); i++) {
			if(isFirst != false) {

			}

			if(str[j] == symbols[i]) {
				if(i < 10) {//Decimal max - 10 symbols by digit
					if(isLeft != 0) {// ��������� ����� ����� �� �������\�����
						params.back() = (params.back() * 10.0) + double(i);

					} else if(isRight != 0) {//��������� ����� ������ �� �������\�����
						params.back() = params.back() + double(i)*pow(10, power);
						power--;

					} else {//��������� ������ �����
						params.push_back(double(i));
						isLeft = true;//������������ ����� ������ 9
						ops.push_back(tmpOp);

					}

					isOp = false;
					
				} else if((str[j] == ',') || (str[j] == '.')) {// ��������� ����� � ��������� ������
					isLeft = false;
					isRight = true;
					power = -1;

				} else {
					if((str[j] == '+') ||
					   (str[j] == '-') ||
					   (str[j] == '*') ||
					   (str[j] == '/') ||
					   (str[j] == '^') ||
					   (str[j] == '=')) {// ��������� �������������� ����������
						ops.push_back(tmpOp);
						ops.back().push_back(str[j]);

						params.push_back(0.0);
						isOp = false;

					} else if((str[j] == '(') ||
							  (str[j] == '[') ||
							  (str[j] == '{')) {
						// ������� ������ ���������� � ����������
						ops.push_back(tmpOp);
						params.push_back(0.0);

						isOp = false;

						level++;
						brkts.push_back(tmpBr);
						brkts.back().left = (ops.size() - 1);
						brkts.back().level = level;

					} else if((str[j] == ')') ||
							  (str[j] == ']') ||
							  (str[j] == '}')) {
						// ������� ������ ���������� � ����������
						ops.push_back(tmpOp);
						params.push_back(0.0);

						isOp = false;

						if(brkts.back().level == level) {
							brkts.back().right = (ops.size() - 1);

						} else {
							brkts[brkts.size() - 1 - (brkts.back().level - level)].right = (ops.size() - 1);

						}
						level--;

					} else {// ��������� ��������������� ���������� � ����������
							//������� ������ ������ 
						if(isOp == false) {
							ops.push_back(tmpOp);
							params.push_back(0.0);

							isOp = true;

						}

						// ������� ������� � ����� ������
						ops.back().push_back(str[j]);


					}

					isLeft = false;
					isRight = false;
				}

				break;//����� �� ����� for

				isFirst = false;
			}
		}
	}

	return solveBrackets(params, ops, brkts);

}

void main() {
	vector<string> str;

	base.push_back("sin");
	base.push_back("cos");
	base.push_back("tg");
	base.push_back("tan");
	base.push_back("ctg");
	base.push_back("cot");
	base.push_back("ln");
	base.push_back("lg");
	base.push_back("log");
	base.push_back("exp");

	variables.addVar("pi", (atan(1) * 4));
	variables.addVar("e", 2.71828182845904523536);
	variables.addVar("c", 299792458);

	std::cout << "Insert your math's expression:\n";

	while(getString(str)) {
		std::cout << parceString(str.back()) << endl << endl;

	}

}
