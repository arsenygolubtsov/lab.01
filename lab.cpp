#include <iostream>

class Table {
       double** _simplex_table; // Создаем массив коэффициентов
       int** _variable;// Создаем массив переменных
public:
       Table(double*&, double**&, double*&, int); // Конструктор симплекс-таблицы
       bool is_appropriate(int); // Проверяем решение на допустимость
       int serch_supporting_column_approptiate(int); // Ищем разрешающий столбец для 1 этапа
       int serch_supporting_string(int, int); // Ищем разрешающую строку
       int serch_supporting_column(int); // Ищем разрешающий столбец для 2 этапа
       void swap_x(int, int, int); // Меняем строку и столбец и расчитываем симплекс-таблицу
       bool is_optimal(int); // Проверяем решение на оптимальность
       void print(int); // Выводим симплекс-таблицу на экран
       double value(int, int); // Возвращаем значение нужного элемента таблицы
       void search_appropriate_solution(int); // Ищем допустимое решение
       void search_optimal_solution(int); // Ищем оптимальное решение
       int appropriate_value(int); // Возвращает сторону массива переменных
       double function_value(int); // Возвращаем значение функции
       ~Table();
};

Table::Table(double*& c, double**& A, double*& b, int x) {
_simplex_table = new double*[x + 1];
for (unsigned int i = 0; i < x + 1; i++)
_simplex_table[i] = new double[x + 1];
for (unsigned int i = 0; i < x; i++) {
_simplex_table[i][0] = b[i];
}
for (unsigned int i = 0; i < x; i++)
for (unsigned int j = 0; j < x; j++) {
_simplex_table[i][j + 1] = A[i][j];
}
for (unsigned int i = 0; i < x; i++) {
_simplex_table[x][i + 1] = c[i];
}  
//Creating an array of variables
_variable = new int*[x + 1];
for (unsigned int i = 0; i < x + 1; i++) {
_variable[i] = new int[x + 1];
}
for (unsigned int j = 1; j < x + 1; j++)
_variable[0][j] = j;
for (unsigned int i = 1; i < x + 1; i++)
_variable[i][0] = i + 3;

}
bool Table::is_appropriate(int x) {
for (unsigned int i = 0; i < x; i++)
if (_simplex_table[i][0] < 0)
return false;

return true;
}
int Table::serch_supporting_column_approptiate(int x) {

int i = 0;
for (i = 0; i < x; i++)
if (_simplex_table[i][0] < 0)
break;

for (unsigned int j = 1; j < x + 1; j++)
if (_simplex_table[i][j] < 0)
return j;

return 0;
}
int Table::serch_supporting_column(int x) {
for (unsigned int j = 1; j < x + 1; j++)
if (_simplex_table[x][j] > 0)
return j;

return 0;
}
int Table::serch_supporting_string(int j, int x) {
int i_min = 0;
double min = 0;
for (unsigned int i = 0; i < x + 1; i++)
if ((_simplex_table[i][j] > 0) && (_simplex_table[i][0] / _simplex_table[i][j]

> 0)) {

min = _simplex_table[i][0] / _simplex_table[i][1];
i_min = i;
break;
}
for (unsigned int i = 0; i < x + 1; i++)
if ((_simplex_table[i][j] > 0) && (_simplex_table[i][0] / _simplex_table[i][j]

< min) && (_simplex_table[i][0] / _simplex_table[i][j] > 0)) {
min = _simplex_table[i][0] / _simplex_table[i][j];
i_min = i;
}
return i_min;
}
void Table::swap_x(int i_const, int j_const, int x) {
double** _simplex_table_curr = new double*[x + 1];
for (unsigned int i = 0; i < x + 1; i++)
_simplex_table_curr[i] = new double[x + 1];
for (unsigned int i = 0; i < x + 1; i++)
for (unsigned int j = 0; j < x + 1; j++)
_simplex_table_curr[i][j] = _simplex_table[i][j];

_simplex_table_curr[i_const][j_const] = 1 / _simplex_table[i_const][j_const];
for (unsigned int i = 0; i < x + 1; i++)
for (unsigned int j = 0; j < x + 1; j++) {
if ((i == i_const) && (j != j_const)) {
_simplex_table_curr[i][j] = _simplex_table[i][j] /

_simplex_table[i_const][j_const];

}
if ((j == j_const) && (i != i_const)) {
_simplex_table_curr[i][j] = -(_simplex_table[i][j] /

_simplex_table[i_const][j_const]);

}
if ((i != i_const) && (j != j_const))
_simplex_table_curr[i][j] = _simplex_table[i][j] -

(_simplex_table[i][j_const] * _simplex_table[i_const][j] /
_simplex_table[i_const][j_const]);

}
for (unsigned int i = 0; i < x + 1; i++)
for (unsigned int j = 0; j < x + 1; j++) {
_simplex_table[i][j] = _simplex_table_curr[i][j];
if (_simplex_table_curr[i][j] == -0) _simplex_table[i][j] = 0;
}

delete[] _simplex_table_curr;
}
bool Table::is_optimal(int x) {
for (unsigned int j = 1; j < x + 1; j++)
if (_simplex_table[x][j] > 0)
return false;

return true;
}
void Table::print(int x) {
std::cout << " S";
for (unsigned int i = 1; i < x + 1; i++) {
std::cout.width(10);
std::cout << "x" << _variable[0][i];
}
std::cout << std::endl;
for (unsigned int i = 0; i < x + 1; i++) {
std::cout.width(10);
if (i != x) {
std::cout << "x" << _variable[i + 1][0];
}
else std::cout << " F";
for (unsigned int j = 0; j < x + 1; j++) {
std::cout.width(10);
std::cout.precision(4);
std::cout << _simplex_table[i][j] << " ";
}
std::cout << std::endl;
}
}
double Table::value(int i, int j) {
return _simplex_table[i][j];
}
void Table::search_appropriate_solution(int x) {
while (!this->is_appropriate(x)) {
int j = this->serch_supporting_column_approptiate(x);
int i = this->serch_supporting_string(j, x);
this->swap_x(i, j, x);
int count = _variable[0][j];
_variable[0][j] = _variable[i + 1][0];
_variable[i + 1][0] = count;
this->print(x);
std::cout << std::endl;
}
}
void Table::search_optimal_solution(int x) {
while (!this->is_optimal(x)) {
int j = this->serch_supporting_column(x);
int i = this->serch_supporting_string(j, x);
this->swap_x(i, j, x);
int count = _variable[0][j];
_variable[0][j] = _variable[i + 1][0];
_variable[i + 1][0] = count;
this->print(x);
std::cout << std::endl;
}
}
int Table::appropriate_value(int i) {
if (_variable[i][0] == i)
return 1;
if (_variable[0][i] == i)
return 2;

return 0;
}
double Table::function_value(int x) {
return _simplex_table[x][0];
}
Table::~Table() {
delete[] _variable;
delete[] _simplex_table;
}

int main() {
        
       int x = 0;
       std::cout << "Enter the number of variables: ";
       std::cin >> x;
        
       std::cout << "Enter c: ";
       double* c = new double[x];
       for (unsigned int i = 0; i < x; i++)
              std::cin >> c[i];
        
       std::cout << "Enter A: ";
       std::cout << std::endl;
       double** A = new double*[x];
       for (unsigned int i = 0; i < x; i++)
              A[i] = new double[x];
        
       for (unsigned int i = 0; i < x; i++)
              for (unsigned int j = 0; j < x; j++)
                     std::cin >> A[i][j];
        
       std::cout << "Enter b: ";
       double* b = new double[x];
       for (unsigned int i = 0; i < x; i++)
              std::cin >> b[i];
       std::cout << std::endl;
        
       Table table(c, A, b, x);
        
       table.print(x);
       std::cout << std::endl;
        
       table.search_appropriate_solution(x);
        
       table.search_optimal_solution(x);
        
       for (unsigned int i = 1; i < x + 1; i++) {
              if (table.appropriate_value(i) == 1)
                     std::cout << "x" << i << " = " << table.value(i - 1, 0) << std::endl;
              if (table.appropriate_value(i) == 2)
                     std::cout << "x" << i << " = " << 0 << std::endl;
       }
       std::cout << "F = " << table.function_value(x)*(-1) << std::endl;
       delete c;
       delete b;
       delete[] A; 
}
