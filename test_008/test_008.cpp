// test_008.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <string>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <iostream>
using namespace std;

// Максимальная длина команды
#define COM_MAX 10

// Определения клавиш
#define ESCAPE 27
#define RETURN 13
#define BACKSPACE 8
#define DELETE 83
#define ARROWS -32
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77


// Соответствие переменной значению
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
			//Временный вектор от найденного итератора до конца начального вектора
			vector<string> tmp(it, _variables.end());

			// Длина начального вектора
			size_t size0 = _variables.size();
			// Длина временного вектора
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

		//Временный вектор от найденного итератора до конца начального вектора
		vector<string> tmp(it, _variables.end());

		// Длина начального вектора
		size_t size0 = _variables.size();
		// Длина временного вектора
		size_t size1 = tmp.size();

		_values.at(size0 - size1) = value;

	}

	string getVar(const size_t address) {
		return _variables.at(address);

	}

	double getVal(const size_t address) {
		return _values.at(address);
	}

	double getVal(const string variable) {
		//Временный вектор от найденного итератора до конца начального вектора
		vector<string> tmp(find(_variables.begin(), _variables.end(), variable), _variables.end());

		// Длина начального вектора
		size_t size0 = _variables.size();
		// Длина временного вектора
		size_t size1 = tmp.size();
		// Разность длин - адрес значения переменной
		return _values.at(size0 - size1);

	}

	size_t getLength() {
		return _variables.size();
	}

	void deleteVar(const string variable) {
		//Временный вектор от найденного итератора до конца начального вектора
		vector<string> tmpVector(find(_variables.begin(), _variables.end(), variable), _variables.end());

		// Длина начального вектора
		size_t size0 = _variables.size();
		// Длина временного вектора
		size_t size1 = tmpVector.size();

		_variables.erase(_variables.begin()+ (size0 - size1));
		_values.erase(_values.begin() + (size0 - size1));

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


// Вектор, содержащий названия и значения переменных
Variables variables;

// Вектор многосимвольных операций с максимальным приоритетом
vector<string> baseOperators;

// Вектор команд 
vector<string> commands;

bool getString(vector<string>& str) {
	char ch;
	string tmp; //Временная строка для возврата к прошлым строкам
	str.push_back("\0");// Добавление пустого вектора в конец
	size_t k = str.size() - 1;//Итератор вектора строк
	size_t c = 0;//Положение курсора относительно конца строки

	while(true) {
		ch = _getch();

		if(ch == ESCAPE) {
			return false;

		} else if(ch == RETURN) {
			std::vector<string>::iterator it;

			it = find(commands.begin(), commands.end(), str.back());

			if(it != commands.end()){
				if(str.back().compare("help") == 0) {
					cout << "\n\n";
					for(size_t i = 0; i < commands.size(); i++) {
						cout << commands.at(i) << "\n";
					}
					cout << "\n";

				} else if(str.back().compare("list") == 0) {
					cout << "\n\n";
					for(size_t i = 0; i < variables.getLength(); i++) {
						cout << variables.getVar(i) << "\t" << variables.getVal(i) << "\n";
					}
					cout << "\n";
				}

				str.push_back("\0");

			} else {
				std::cout << endl;
				return true;

			}

		} else if(ch == BACKSPACE) {
			if(str.back().size()) {
				str.back().erase(str.back().end() - 1 - c);

				std::cout << "\r";

				for(size_t i = 0; i < (str.back().size() + 1); i++) {
					std::cout << " ";
				}

				std::cout << "\r" << str.back();

				// Положение каретки относительно конца строки
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

					// Положение каретки относительно конца строки
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
			// Вставка символа в положение каретки
			str.back().insert((str.back().end() - c), ch);

			// Перевод каретки в начало и отрисовка строки
			std::cout << "\r" << str.back();

			// Положение каретки относительно конца строки
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

// Вычисление бинарной операции
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

//Возвращающет приоритет оператора
size_t  getPriority(string op) {
	if(op.compare("=") == 0) {
		return 0;//Наинизший приоритет у присваивания
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

		for(size_t i = 0; i < baseOperators.size(); i++) {
			if(op.compare(baseOperators[i]) == 0) {
				return 7;
			}
		}
		
		for(size_t i = 0; i < variables.getLength(); i++) {
			if(op.compare(variables.getVar(i)) == 0) {
				return 8;// Наивысший приоритет у переменных
			}
		}

	}
	return 1;
}

//Возвращает решение выражения внутри скобок
double solveSimple(vector<double> params, vector<string> ops) {
	size_t prior = 0;
	size_t numOp = 0;
	double result = 0;

	while(((params.size()) > 1) || (ops.back().compare("\0") != 0)) {
		prior = 0;
		for(size_t i = 0; i < (ops.size()); i++) {
			if(getPriority(ops[i]) > prior) {
				prior = getPriority(ops[i]);
				numOp = i;

			}
		}


		// Если операция справа "=", то результат вычисления идет в новую переменную
		if((ops.size() > 1) && (numOp == 0)) {
			// Если переменная объявлена и инициализирована, но происходит переприсваивание, то извлекаем(pop) переменную, для последующей первичной инициализации
			if((prior == 8) && (ops[numOp + 1].compare("=") == 0)) {
				variables.deleteVar(ops[numOp]);
				//ops.erase(ops.begin() + numOp);
				//params.erase(params.begin() + numOp);

				// Повторный поиск операции, наивысшей по приоритету
				prior = 0;
				for(size_t i = 0; i < (ops.size()); i++) {
					if(getPriority(ops[i]) > prior) {
						prior = getPriority(ops[i]);
						numOp = i;

					}
				}

			}

			if(ops[numOp + 1].compare("=") == 0) {
				variables.addVar(ops[numOp], params.back());

				return params.back();

			}
		} 

		if(prior < 6) {
			//Сохранение результата во временной переменной
			result = computeBinaryOperation(params[numOp - 1], params[numOp + 1], ops[numOp]);

			// Перезапись первого параметра результатом
			params[numOp - 1] = result;
			ops[numOp - 1] = "\0";

			// Удаление второго параметра и заглушки операции из вектора параметров
			params.erase(params.begin() + numOp);
			params.erase(params.begin() + numOp);

			// Удаление операции и заглушки второго параметра из вектора операций
			ops.erase(ops.begin() + numOp);
			ops.erase(ops.begin() + numOp);

		} else if(prior == 7) {
			result = computeUnaryOperation(params[numOp + 1], ops[numOp]);

			// Перезапись оператора результатом
			params[numOp] = result;
			ops[numOp] = "\0";

			// Удаление параметра из вектора параметров
			params.erase(params.begin() + numOp + 1);

			// Удаление операции из вектора операций
			ops.erase(ops.begin() + numOp + 1);

		} else if(prior == 8) {
			params[numOp] = variables.getVal(ops[numOp]);
			ops[numOp] = "\0";

		}

	}

	return params.back();

}

// Возвращает решение всего выражения без парсинга
double solveBrackets(vector<double> params, vector<string> ops, vector<Brackets> brkts) {
	size_t level = 0;//Уровень выражения
	size_t numBr;//Номер пары скобок в векторе

	// Пока скобки есть, производить вычисления в скобках
	while(!brkts.empty()) {
		level = 0;

		//Поиск пары скобок с максимальным уровнем
		for(size_t i = 0; i < brkts.size(); i++) {
			if(brkts[i].level > level) {
				level = brkts[i].level;
				numBr = i;

			}
		}

		vector<double> paramsTmp((params.begin() + brkts[numBr].left + 1), (params.begin() + brkts[numBr].right));
		vector<string> opsTmp((ops.begin() + brkts[numBr].left + 1), (ops.begin() + brkts[numBr].right));
		// Позиция левой скобки, в которую будет записано решение выражения в скобках
		size_t numPar = brkts[numBr].left;

		// Перезапись решения выражения в скобках в позицию левой скобки в векторе параметров
		params[numPar] = solveSimple(paramsTmp, opsTmp);

		// Удаление решенной части из векторов параметров и операторов
		params.erase((params.begin() + brkts[numBr].left + 1), (params.begin() + brkts[numBr].right + 1));
		ops.erase((ops.begin() + brkts[numBr].left + 1), (ops.begin() + brkts[numBr].right + 1));

		// Удаление пары скобок
		brkts.erase(brkts.begin() + numBr);

		// Сдвиг оставшихся пар скобок
		for(size_t i = 0; i < brkts.size(); i++) {
			if(brkts[i].left > numPar) {
				brkts[i].left -= (paramsTmp.size() + 1);// Длина выражения + правая скобка

			}

			if(brkts[i].right > numPar) {
				brkts[i].right -= (paramsTmp.size() + 1);

			}

		}

		// Удаление временных векторов
		paramsTmp.~vector();
		opsTmp.~vector();

	}

	return solveSimple(params, ops);
	
}

// Возвращает решение всего выражения с парсингом строки 
double parseString(string str) {
	string symbols;
	symbols = "0123456789,.+-^*/!()[]{}abcdefghijklmnopqrstuvwxyz=";
	size_t level = 0;//Уровень выражения
	int power = -1;//Степень 10

	// Вектор параметров
	vector<double> params;

	// Вектор операторов
	vector<string> ops;
	string tmpOp;

	// Вектор  пар скобок
	vector<Brackets> brkts;
	Brackets tmpBr;

	// Итератор символа в строке
	size_t k = 0;

	bool isLeft = false;//Left from digit
	bool isRight = false;//Right from digit

	bool isOperator = false;// Флаг устанавливается при обработке многосимвольных буквенных операторов. e.g.: sin, cos

	// Флаг сбрасывается после первого символа. После сброса флага новые переменные не создаются.
	bool isFirst = true;

	// Флаг устанавливается во время присваивания значения новой переменной
	bool isAssignment = false;

	// Удаление пробелов
	for(size_t i = 0; i < str.length(); i++) {
		if(str.at(i) == ' ') {
			str.erase(str.begin() + i);
		}

	}
	
	//Выделение из строки операторов и параметров
	for(size_t j = 0; j < str.length(); j++) {
		for(size_t i = 0; i < symbols.length(); i++) {
			if(isFirst != false) {

			}

			if(str[j] == symbols[i]) {
				if(i < 10) {//Decimal max - 10 symbols by digit
					if(isLeft != 0) {// Обработка чисел слева от запятой\точки
						params.back() = (params.back() * 10.0) + double(i);

					} else if(isRight != 0) {//Обработка чисел справа от запятой\точки
						params.back() = (params.back() + double(i)*pow(10, power));
						power--;

					} else {//Обработка первой цифры
						params.push_back(double(i));
						isLeft = true;//Отслеживание чисел больше 9
						ops.push_back(tmpOp);

					}

					isOperator = false;
					
				} else if((str[j] == ',') || (str[j] == '.')) {// Обработка чисел с плавающей точкой
					isLeft = false;
					isRight = true;
					power = -1;

				} else {
					if((str[j] == '+') ||
					   (str[j] == '-') ||
					   (str[j] == '*') ||
					   (str[j] == '/') ||
					   (str[j] == '^') ||
					   (str[j] == '=')) {// Обработка односимвольных операторов
						ops.push_back(tmpOp);
						ops.back().push_back(str[j]);

						params.push_back(0.0);
						isOperator = false;

					} else if((str[j] == '(') ||
							  (str[j] == '[') ||
							  (str[j] == '{')) {
						// Вставка пустых операторов и параметров
						ops.push_back(tmpOp);
						params.push_back(0.0);

						isOperator = false;

						level++;
						brkts.push_back(tmpBr);
						brkts.back().left = (ops.size() - 1);
						brkts.back().level = level;

					} else if((str[j] == ')') ||
							  (str[j] == ']') ||
							  (str[j] == '}')) {
						// Вставка пустых операторов и параметров
						ops.push_back(tmpOp);
						params.push_back(0.0);

						isOperator = false;

						if(brkts.back().level == level) {
							brkts.back().right = (ops.size() - 1);

						} else {
							brkts[brkts.size() - 1 - (brkts.back().level - level)].right = (ops.size() - 1);

						}
						level--;

					} else {// Обработка многосимвольных операторов и переменных
							//Вставка пустой строки 
						if(isOperator == false) {
							ops.push_back(tmpOp);
							params.push_back(0.0);

							isOperator = true;

						}

						// Вставка символа в конец строки
						ops.back().push_back(str[j]);


					}

					isLeft = false;
					isRight = false;
				}

				break;//Выход из цикла for

				isFirst = false;
			}
		}
	}

	return solveBrackets(params, ops, brkts);

}

int main() {
	vector<string> str;

	baseOperators.push_back("sin");
	baseOperators.push_back("cos");
	baseOperators.push_back("tg");
	baseOperators.push_back("tan");
	baseOperators.push_back("ctg");
	baseOperators.push_back("cot");
	baseOperators.push_back("ln");
	baseOperators.push_back("lg");
	baseOperators.push_back("log");
	baseOperators.push_back("exp");

	commands.push_back("help");//Выводит список команд
	commands.push_back("list");//Выводит список переменных с их значением

	variables.addVar("pi", (atan(1) * 4));
	variables.addVar("e", 2.71828182845904523536);
	variables.addVar("c", 299792458);

	std::cout << "Insert your math's expression:\n";

	while(getString(str)) {
		std::cout << parseString(str.back()) << endl << endl;

	}

	return 0;
}

