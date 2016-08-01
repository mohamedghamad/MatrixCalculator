#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <math.h>
using namespace std;
#define ERROR cout << "ERROR"; exit(0);

int RowsNO(string strMAT) //This function returns the number of rows.
{
	int j = 0;
	for (int i = 0; i < (int)strMAT.length(); i++)
	{
		if (strMAT[i] == ';')
		{
			j++;
		}
	}
	return ++j;
}

int ColumnsNO(string strMAT) //This function returns the number of columns.
{
	int x = 0;
	int i = 0;
	while (strMAT[i] != ';' && i < (int)strMAT.length())
	{
		if (strMAT[i] == ' ')
		{
			x++;
		}
		i++;
	}

	int j; //This part checks if all rows have equal number of elements
	for (int i = 0; i < (int)strMAT.length(); i++)
	{
		j = 0;
		while (strMAT[i] != ';' && i < (int)strMAT.length())
		{
			if (strMAT[i] == ' ')
			{
				j++;
			}
			i++;
		}
		if (j != x)
		{
			return -1;
		}
	}
	return ++x;
}

int CheckInput(string strMAT, int m, int n) //This function checks the input.
{
	if (n > 100 || m > 100 || n == -1 || strMAT[0] != '[' || strMAT[strMAT.length() - 1] != ']' || (int)strMAT[strMAT.length() - 2] < 48 || ((int)strMAT[strMAT.length() - 2] > 57 && (int)strMAT[strMAT.length() - 2] != 'i'))
	{
		return 0;
	}
	for (int i = 1; i < (int)strMAT.length() - 1; i++)
	{
		if (!(strMAT[i] == ' ' || strMAT[i] == '+' || strMAT[i] == '-' || strMAT[i] == '.' || strMAT[i] == ';' || strMAT[i] == 'i' || ((int)strMAT[i] > 47 && (int)strMAT[i] < 58)))
			return 0;
	}
	for (int j = 0; j < (int)strMAT.length(); j++)
	{
		if (strMAT[j] == '[' || strMAT[j] == ';' || strMAT[j] == ' ')
		{
			j++;
			if (((int)strMAT[j] < 48 && (int)strMAT[j] != '-') || ((int)strMAT[j] > 57) && strMAT[j] != 'i')
			{
				return 0;
			}
			j--;
		}
		if (strMAT[j] == '-' || strMAT[j] == '+')
		{
			j++;
			if ((int)strMAT[j] < 48 || ((int)strMAT[j] > 57 && strMAT[j] != 'i'))
			{
				return 0;
			}
			j--;
		}
		if (strMAT[j] == '.')
		{
			j++;
			if ((int)strMAT[j] < 48 || (int)strMAT[j] > 57)
			{
				return 0;
			}
			j--;
		}
		if (strMAT[j] == 'i')
		{
			j++;
			if (strMAT[j] != ' ' && strMAT[j] != ';' && strMAT[j] != ']')
			{
				return 0;
			}
			j -= 2;
			if (((int)strMAT[j] < 48 && strMAT[j] != '+' && strMAT[j] != '-' && strMAT[j] != ' ') || (int)strMAT[j] > 57)
			{
				return 0;
			}
			j++;
		}

	}
	for (int k = 0; k < (int)strMAT.length() - 1; k++)
	{
		if (strMAT[k] == 'i')
		{
			return 2;
		}
	}
	return 1;
}

void StringToArray(string strMAT, float(&MAT)[100][100], float(&MATI)[100][100], int m, int n) //This function converts from a string to an array.
{
	int pos1 = 1;
	int pos2 = 0;
	int p = 1;
	int is2Elements, negCounter;
	string element;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			while (strMAT[pos2] != ' ' && strMAT[pos2] != ']' && strMAT[pos2] != ';')
			{
				pos2++;
			}
			element = strMAT.substr(pos1, pos2 - pos1);
			is2Elements = 0;
			negCounter = 0;
			for (int k = 0; k < (int)element.length(); k++)
			{
				if (element[k] == '+')
				{
					is2Elements = 1;
					break;
				}
				if (element[k] == '-' && k != 0)
				{
					is2Elements = 1;
					break;
				}
				if (element[k] == '-')
				{
					negCounter++;
				}
				if (negCounter == 2)
				{
					is2Elements = 1;
					break;
				}
			}
			if (is2Elements == 0)
			{
				if (element[element.length() - 1] == 'i')
				{
					if ((int)element.length() == 1)
					{
						MAT[i][j] = 0;
						MATI[i][j] = 1;
					}
					else if ((int)element.length() == 2 && element[0] == '-')
					{
						MAT[i][j] = 0;
						MATI[i][j] = -1;
					}
					else
					{
						MAT[i][j] = 0;
						MATI[i][j] = (float)atof(element.substr(0, element.length() - 2).c_str());
					}	
				}
				else
				{
					MAT[i][j] = (float)atof(element.c_str());
					MATI[i][j] = 0;
				}
			}
			else
			{
				p = 1;
				while (element[p] != '+' && element[p] != '-')
				{
					p++;
				}
				MAT[i][j] = (float)atof(element.substr(0, p).c_str());
				if ((int)element.length() - p == 2)
				{
					if (element[p] == '+')
					{
						MATI[i][j] = 1;
					}
					else if (element[p] == '-')
					{
						MATI[i][j] = -1;
					}
				}
				else
				{
					if (element[p] == '+')
					{
						MATI[i][j] = (float)atof(element.substr(++p, (int)(element.length()) - p - 1).c_str());
					}
					else if (element[p] == '-')
					{
						MATI[i][j] = (float)atof(element.substr(p, (int)(element.length()) - p - 1).c_str());
					}
				}
			}
			pos1 = ++pos2;
		}
	}
}

string ArrayToString(float MAT[100][100], float MATI[100][100], int m, int n) //This function converts from an array to a string.
{
	float element;
	string strMAT = "[";
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (MAT[i][j] == 0 && MATI[i][j] == 0)
			{
				strMAT += "0";
			}
			else
			{
				if (MAT[i][j] != 0)
				{
					element = MAT[i][j];
					ostringstream ss;
					ss << element;
					strMAT += ss.str();
				}
				if (MATI[i][j] != 0)
				{
					if (MATI[i][j] == 1 || MATI[i][j] == -1)
					{
						if (MATI[i][j] == 1)
						{
							strMAT += "+i";
						}
						else
						{
							strMAT += "-i";
						}
					}
					else
					{
						if (MATI[i][j] > 0 && MAT[i][j] != 0)
						{
							strMAT += "+";
						}
						element = MATI[i][j];
						ostringstream ss;
						ss << element;
						strMAT += ss.str();
						strMAT += "i";
					}
				}
			}
			if (j != n - 1)
			{
				strMAT += " ";
			}
		}
		if (i != m - 1)
		{
			strMAT += ";";
		}
	}
	strMAT += "]";
	return strMAT;
}

int AddorSubtract(float MAT1[100][100], float MAT1I[100][100], float MAT2[100][100], float MAT2I[100][100], float(&MATRES)[100][100], float(&MATRESI)[100][100], int m, int n, int p, int q, char operation) //This function adds or subtracts two arrays.
{
	if (m != p || n != q)
	{
		return 0;
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (operation == '+')
			{
				MATRES[i][j] = MAT1[i][j] + MAT2[i][j];
				MATRESI[i][j] = MAT1I[i][j] + MAT2I[i][j];
			}
			else
			{
				MATRES[i][j] = MAT1[i][j] - MAT2[i][j];
				MATRESI[i][j] = MAT1I[i][j] - MAT2I[i][j];
			}
		}
	}
	return 1;
}

int Multiply(float MAT1[100][100], float MAT1I[100][100], float MAT2[100][100], float MAT2I[100][100], float(&MATRES)[100][100], float(&MATRESI)[100][100], int m, int n, int p, int q) //This function multiplies two arrays.
{
	if (n != p)
	{
		return 0;
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < q; j++)
		{
			MATRES[i][j] = 0;
			for (int k = 0; k < n; k++)
			{
				MATRES[i][j] += MAT1[i][k] * MAT2[k][j] - MAT1I[i][k] * MAT2I[k][j];
				MATRESI[i][j] += MAT1[i][k] * MAT2I[k][j] + MAT1I[i][k] * MAT2[k][j];
			}
		}
	}
	return 1;
}

void Transpose(float MAT1[100][100], float(&MATRES)[100][100], int m, int n) //This function returns the transpose of an array.
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
		{
			MATRES[i][j] = MAT1[j][i];
		}
	}
}

int Determinant(float MAT1[100][100], int m, int n, float &determinant) //This function returns the determinant of a matrix using Chio's condensation method
{
	if (m != n)
	{
		return 0;
	}
	float MAT2[100][100], partial = 1;
	for (int i = m; i > 2; i--)
	{
		if (MAT1[0][0] == 0)
		{
			return 0;
		}
		partial /= pow(MAT1[0][0], i - 2);
		for (int j = 0; j < i - 1; j++)
		{
			for (int k = 0; k < i - 1; k++)
			{
				MAT2[j][k] = MAT1[0][0] * MAT1[j + 1][k + 1] - MAT1[0][k + 1] * MAT1[j + 1][0];
			}
		}
		for (int p = 0; p < i - 1; p++)
		{
			for (int q = 0; q < i - 1; q++)
			{
				MAT1[p][q] = MAT2[p][q];
			}
		}
	}
	determinant = (MAT1[0][0] * MAT1[1][1] - MAT1[0][1] * MAT1[1][0]) * partial;
	return 1;
}

int CoFactor(float MAT1[100][100], float(&MATRES)[100][100], int m, int n) //This function returns the co-factor matrix
{
	if (m != n)
	{
		return 0;
	}
	int checkoperation, z = 0, y = 0;
	float MAT[100][100];
	for (int i = 0; i < m; i++) //This part calculates the minor matrix
	{
		for (int j = 0; j < n; j++)
		{
			for (int p = 0; p < m - 1; p++)
			{
				if (z == i)
				{
					z++;
				}
				for (int q = 0; q < m - 1; q++)
				{
					if (y == j)
					{
						y++;
					}
					MAT[p][q] = MAT1[z][y];
					y++;
				}
				z++;
				y = 0;
			}
			z = 0;
			checkoperation = Determinant(MAT, m - 1, n - 1, MATRES[i][j]);
			if (checkoperation == 0)
			{
				return 0;
			}
		}
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if ((i % 2 == 0 && j % 2 != 0) || (i % 2 != 0 && j % 2 == 0))
			{
				MATRES[i][j] *= -1;
			}
		}
	}
	return 1;
}

int Inverse(float MAT1[100][100], float(&MATRES)[100][100], int m, int n) //This function returns the inverse matrix
{
	if (m != n)
	{
		return 0;
	}
	float determinant;
	int checkoperation = 0;
	float MAT2[100][100];
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			MAT2[i][j] = MAT1[i][j];
		}
	}
	checkoperation = Determinant(MAT2, m, n, determinant);
	if (m == 2)
	{
		MATRES[0][0] = MAT1[1][1];
		MATRES[0][1] = MAT1[0][1] * -1;
		MATRES[1][0] = MAT1[1][0] * -1;
		MATRES[1][1] = MAT1[0][0];
	}
	else
	{
		if (checkoperation == 0 || determinant == 0)
		{
			return 0;
		}
		checkoperation = CoFactor(MAT1, MAT2, m, n);
		if (checkoperation == 0)
		{
			return 0;
		}
		Transpose(MAT2, MATRES, m, n);
	}
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < m; j++)
		{
			MATRES[i][j] /= determinant;
		}
	}
	return 1;
}

int Divide(float MAT1[100][100], float MAT2[100][100], float(&MATRES)[100][100], int m, int n, int p, int q)
{
	if (n != p || p != q)
	{
		return 0;
	}
	float MAT3[100][100], MAT3I[100][100];
	int checkoperation = Inverse(MAT2, MAT3, p, q);
	if (checkoperation == 0)
	{
		return 0;
	}
	checkoperation = Multiply(MAT1, 0, MAT3, 0, MATRES, MAT3I, m, n, p, q);
	return 1;
}

int main()
{
	float MAT1[100][100], MAT2[100][100], MATRES[100][100], MAT1I[100][100], MAT2I[100][100], MATRESI[100][100]; //MAT1 is a matrix with m rows & n columns, MAT2 is a matrix with p rows and q columns
	string strMAT1, strMAT2, strMATRES, operation;
	int m, n, p, q, checkinp, checkoperation, isComplex;
	float determinant;
	getline(cin, strMAT1);
	m = RowsNO(strMAT1);
	n = ColumnsNO(strMAT1);
	checkinp = CheckInput(strMAT1, m, n);
	if (checkinp == 0)
	{
		ERROR
	}
	if (checkinp == 2)
	{
		isComplex = 1;
	}
	StringToArray(strMAT1, MAT1, MAT1I, m, n);
	getline(cin, operation);
	if (operation.length() != 1)
	{
		ERROR
	}
	switch (operation[0])
	{
	case '+':
		getline(cin, strMAT2);
		p = RowsNO(strMAT2);
		q = ColumnsNO(strMAT2);
		checkinp = CheckInput(strMAT2, p, q);
		StringToArray(strMAT2, MAT2, MAT2I, p, q);
		checkoperation = AddorSubtract(MAT1, MAT1I, MAT2, MAT2I, MATRES, MATRESI, m, n, p, q, operation[0]);
		if (checkinp == 0 || checkoperation == 0)
		{
			ERROR
		}
		strMATRES = ArrayToString(MATRES, MATRESI, m, n);
		cout << strMATRES;
		break;
	case '-':
		getline(cin, strMAT2);
		p = RowsNO(strMAT2);
		q = ColumnsNO(strMAT2);
		checkinp = CheckInput(strMAT2, p, q);
		StringToArray(strMAT2, MAT2, MAT2I, p, q);
		checkoperation = AddorSubtract(MAT1, MAT1I, MAT2, MAT2I, MATRES, MATRESI, m, n, p, q, operation[0]);
		if (checkinp == 0 || checkoperation == 0)
		{
			ERROR
		}
		strMATRES = ArrayToString(MATRES, MATRESI, m, n);
		cout << strMATRES;
		break;
	case '*':
		getline(cin, strMAT2);
		p = RowsNO(strMAT2);
		q = ColumnsNO(strMAT2);
		checkinp = CheckInput(strMAT2, m, n);
		StringToArray(strMAT2, MAT2, MAT2I, p, q);
		checkoperation = Multiply(MAT1, MAT1I, MAT2, MAT2I, MATRES, MATRESI, m, n, p, q);
		if (checkinp == 0 || checkoperation == 0)
		{
			ERROR
		}
		strMATRES = ArrayToString(MATRES, MATRESI, m, q);
		cout << strMATRES;
		break;
	case '^':
		if (m != n)
		{
			ERROR
		}
		float power;
		cin >> power;
		if (power < 0 || power - (int)power != 0 || isComplex == 1)
		{
			ERROR
		}
		for (int i = 0; i < m; i++)
		{
			for (int j = 0; j < n; j++)
			{
				MAT2[i][j] = MAT1[i][j];
			}
		}
		for (int i = 2; i <= power; i++)
		{
			Multiply(MAT2, MAT2I, MAT1, MAT1I, MATRES, MATRESI, m, m, m, m);
			for (int i = 0; i < m; i++)
			{
				for (int j = 0; j < m; j++)
				{
					MAT2[i][j] = MATRES[i][j];
				}
			}
		}
		strMATRES = ArrayToString(MATRES, MAT1I, m, m);
		cout << strMATRES;
		break;
	case 'T':
		if (isComplex == 1)
		{
			ERROR
		}
		Transpose(MAT1, MATRES, m, n);
		strMATRES = ArrayToString(MATRES, MAT1I, n, m);
		cout << strMATRES;
		break;
	case 'D':
		checkoperation = Determinant(MAT1, m, n, determinant);
		if (checkoperation == 0 || isComplex == 1)
		{
			ERROR
		}
		cout << determinant;
		break;
	case 'I':
		checkoperation = Inverse(MAT1, MATRES, m, n);
		if (checkoperation == 0 || isComplex == 1)
		{
			ERROR
		}
		strMATRES = ArrayToString(MATRES, MAT1I, m, n);
		cout << strMATRES;
		break;
	case '/':
		getline(cin, strMAT2);
		p = RowsNO(strMAT2);
		q = ColumnsNO(strMAT2);
		checkinp = CheckInput(strMAT2, p, q);
		StringToArray(strMAT2, MAT2, MAT2I, p, q);
		checkoperation = Divide(MAT1, MAT2, MATRES, m, n, p, q);
		if (checkinp == 0 || checkoperation == 0 || isComplex == 1)
		{
			ERROR
		}
		strMATRES = ArrayToString(MATRES, MAT1I, m, q);
		cout << strMATRES;
		break;
	default: ERROR
	}
	return 0;
}