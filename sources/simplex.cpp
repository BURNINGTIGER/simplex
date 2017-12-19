#include "simplex.hpp"

simplex::simplex()
{
	rows = 0;
	columns = 0;
	simplex_core = nullptr;

}

simplex::simplex(std::ifstream input)
{
	if (!input)
	{
		throw std::logic_error("Error! File not found!");
	}
	bool way;
	input >> rows;
	input >> columns;
	input >> way;
	simplex_core = new double*[rows];
	for (int i = 0; i < rows; i++)
	{
		simplex_core[i] = new double[columns];
	}

	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			input >> simplex_core[i][j];
		}
	}
	if (way)
	{
		for (int j = 2; j < columns; j++)
		{
			simplex_core[rows - 1][j] = simplex_core[rows - 1][j] * (-1);
		}
	}
	print();
}

simplex::~simplex()
{
	for (int i = 0; i < rows; i++)
		delete[] simplex_core[i];
	delete[] simplex_core;
	rows = 0;
	columns = 0;
}

bool simplex::is_negative() {
	for (int i = 1; i < columns; i++) {
		if (simplex_core[rows - 1][i] < 0) {
			return true;
		}
	}
	return false;
}

void simplex::compute()
{
	do
	{
		int allow_column = 2;
		int allow_row = 1;
		double min_element = 0;
		for (int j = 2; j < columns; j++) {
			if (simplex_core[rows - 1][j] < 0 && simplex_core[rows - 1][j] < min_element) {
				min_element = simplex_core[rows - 1][j];
				allow_column = j;
			}
		}
		if (min_element == 0) {
			throw std::logic_error("Error! System has no solution!");
		}
		double allow_element = simplex_core[1][1] / simplex_core[1][allow_column];
		for (int j = 1; j < rows - 1; j++) {
			if (simplex_core[j][1] / simplex_core[j][allow_column] < allow_element && simplex_core[j][allow_column] / simplex_core[j][1] > 0) {
				allow_row = j;
			}
		}
		allow_element = simplex_core[allow_row][allow_column];

		double** new_simplex_core = new double*[rows];
		for (int k = 0; k < rows; k++) {
			new_simplex_core[k] = new double[columns];
			for (int j = 0; j < rows; j++) {
				new_simplex_core[k][j] = simplex_core[k][j];
			}
		}
		new_simplex_core[allow_row][allow_column] = 1 / allow_element;
		for (int i = 1; i < columns; i++) {
			if (i != allow_column) {
				new_simplex_core[allow_row][i] = simplex_core[allow_row][i] / allow_element;

			}
		}
		for (int i = 1; i < rows; i++) {
			if (i != allow_row) {
				new_simplex_core[i][allow_column] = -1 * simplex_core[i][allow_column] / allow_element;
			}
		}

		for (int i = 1; i < rows; i++) {
			for (int j = 1; j < columns; j++) {
				if (j != allow_column && i != allow_row) {
					new_simplex_core[i][j] = simplex_core[i][j] - simplex_core[i][allow_column] * simplex_core[allow_row][j] / allow_element;
				}
			}
		}
		double temp = new_simplex_core[0][allow_column];
		new_simplex_core[0][allow_column] = new_simplex_core[allow_row][0];
		new_simplex_core[allow_row][0] = temp;
		for (int i = 1; i < rows; i++) {
			for (int j = 1; j < columns; j++) {
				simplex_core[i][j] = new_simplex_core[i][j];
			}
		}
		for (int i = 0; i < rows; i++)
			delete[] new_simplex_core[i];
		delete[] new_simplex_core;
		print();
	} while (is_negative());
}

void simplex::print()
{
	cout << setw(7) << "B " << setw(7) << "S ";
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			if (i == 0 && j < 2) {
				continue;
			}
			if (j == 0 && i == rows - 1) {
				cout << setw(7) << "F ";
				continue;
			}
			if ((i == 0 && j > 1) || (j == 0 && i > 0 && i != rows - 1)) {
				cout << setw(5) << "x" << simplex_core[i][j] << " ";
				continue;
			}
			cout << setw(6) << simplex_core[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n\n\n";
}

double simplex::show()
{
	double result = simplex_core[rows - 1][1];
	return result;
}

