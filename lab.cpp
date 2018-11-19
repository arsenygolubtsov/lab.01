#include <iostream>
	
	class Table {
	       double** _simplex_table; 
	       unsigned int** _variable;
	public:
	       Table(double*&, double**&, double*&, unsigned int); 
	       bool is_appropriate(unsigned int); 
	       unsigned int search_column(unsigned int); 
	       unsigned int search_second_column(unsigned int);
	       unsigned int search_row(unsigned int, unsigned int); 
	       void swap(unsigned int, unsigned int, unsigned int); 
	       bool is_optimal(unsigned int); 
	       double value(unsigned int, unsigned int); 
	       void search_appropriate_solution(unsigned int);
	       void search_optimal_solution(unsigned int); 
	       unsigned int appropriate_value(unsigned int); 
	       double function_value(unsigned int); 
	       ~Table();
	       void print(unsigned int); 
	};
	
	
	
	
	Table::Table(double*& c, double**& A, double*& b, unsigned int x) {
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
	       _variable = new unsigned int*[x + 1];
	       for (unsigned int i = 0; i < x + 1; i++) {
	              _variable[i] = new unsigned int[x + 1];
	       }
	       for (unsigned int j = 1; j < x + 1; j++)
	              _variable[0][j] = j;
	       for (unsigned int i = 1; i < x + 1; i++)
	              _variable[i][0] = i + 3;
	}
	
	bool Table::is_appropriate(unsigned int x) {
	       for (unsigned int i = 0; i < x; i++)
	              if (_simplex_table[i][0] < 0)
	                     return false;
	       return true;
	}
	unsigned int Table::search_column(unsigned int x) {
	       unsigned int i = 0;
	       for (i = 0; i < x; i++)
	              if (_simplex_table[i][0] < 0)
	                     break;
	       for (unsigned int j = 1; j < x + 1; j++)
	              if (_simplex_table[i][j] < 0)
	                     return j;
	       return 0;
	}
	
	unsigned int Table::search_second_column(unsigned int x) {
	       for (unsigned int j = 1; j < x + 1; j++)
	              if (_simplex_table[x][j] > 0)
	                     return j;
	       return 0;
	}
	
	unsigned int Table::search_row(unsigned int j, unsigned int x) {
	       unsigned int i_min = 0;
	       double min = 0;
	       for (unsigned int i = 0; i < x + 1; i++)
	              if ((_simplex_table[i][j] > 0) && (_simplex_table[i][0] / _simplex_table[i][j]> 0)) {
	                     min = _simplex_table[i][0] / _simplex_table[i][1];
	                     i_min = i;
	                     break;
	              }
	       for (unsigned int i = 0; i < x + 1; i++)
	              if ((_simplex_table[i][j] > 0) && (_simplex_table[i][0] / _simplex_table[i][j]< min) && (_simplex_table[i][0] / _simplex_table[i][j] > 0)) {
	                     min = _simplex_table[i][0] / _simplex_table[i][j];
	                     i_min = i;
	              }
	       return i_min;
	}
	
	void Table::swap(unsigned int i_const, unsigned int j_const, unsigned int x) {
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
	                            _simplex_table_curr[i][j] = _simplex_table[i][j] /_simplex_table[i_const][j_const];
	                     }
	                     if ((j == j_const) && (i != i_const)) {
	                            _simplex_table_curr[i][j] = -(_simplex_table[i][j] /_simplex_table[i_const][j_const]);
	                     }
	                     if ((i != i_const) && (j != j_const))
	                            _simplex_table_curr[i][j] = _simplex_table[i][j] - (_simplex_table[i][j_const] * _simplex_table[i_const][j] /_simplex_table[i_const][j_const]);
	              }
	       
	       for (unsigned int i = 0; i < x + 1; i++)
	              for (unsigned int j = 0; j < x + 1; j++) {
	                     _simplex_table[i][j] = _simplex_table_curr[i][j];
	                     if (_simplex_table_curr[i][j] == -0) _simplex_table[i][j] = 0;
	              }
	       delete[] _simplex_table_curr;
	}
	
	bool Table::is_optimal(unsigned int x) {
	       for (unsigned int j = 1; j < x + 1; j++)
	              if (_simplex_table[x][j] > 0)
	                     return false;
	       return true;
	}
	
	double Table::value(unsigned int i, unsigned int j) {
	       return _simplex_table[i][j];
	}
	
	void Table::search_appropriate_solution(unsigned int x) {
	       while (!this->is_appropriate(x)) {
	              unsigned int j = this->search_column(x);
	              unsigned int i = this->search_row(j, x);
	              this->swap(i, j, x);
	              unsigned int count = _variable[0][j];
	              _variable[0][j] = _variable[i + 1][0];
	              _variable[i + 1][0] = count;
	              this->print(x);
	              std::cout << std::endl;
	       }
	}
	
	void Table::search_optimal_solution(unsigned int x) {
	       while (!this->is_optimal(x)) {
	              unsigned int j = this->search_second_column(x);
	              unsigned int i = this->search_row(j, x);
	              this->swap(i, j, x);
	              unsigned int count = _variable[0][j];
	              _variable[0][j] = _variable[i + 1][0];
	              _variable[i + 1][0] = count;
	              this->print(x);
	              std::cout << std::endl;
	       }
	}
	
	unsigned int Table::appropriate_value(unsigned int i) {
	       if (_variable[i][0] == i)
	              return 1;
	       if (_variable[0][i] == i)
	              return 2;
	       return 0;
	}
	
	double Table::function_value(unsigned int x) {
	       return _simplex_table[x][0];
	}
	
	Table::~Table() {
	       delete[] _variable;
	       delete[] _simplex_table;
	}

	void Table::print(unsigned int x) {
	       std::cout << " Si0";
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
	                     std::cout << _simplex_table[i][j] << "";
	              }
	              std::cout << std::endl;
	       }
	}
	
	int main() {
	        
	       unsigned int x = 0;
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
