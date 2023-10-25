#ifndef LEASTSQUARESSMOOTHING_TABLEFUN_H
#define LEASTSQUARESSMOOTHING_TABLEFUN_H

#include <fstream>
#include <vector>
#include <utility>

using namespace std;

class TableFun
{
private:
    int m_n; // число столбцов таблично заданной функции
    int m_m; // число точек, в которых надо найти значение функции
    int m_deg; // степень многочлена
    vector<pair<double, double>> m_data; // таблица значений функции
    // (x_i, g(x_i)) = (m_data[i].first, m_data[i].second)
    vector<double> m_points;
    vector<double> m_ans;
public:
    TableFun():
    m_n{0}, m_m{0}, m_deg{0}
    {}

    TableFun(int n, const vector<pair<double, double>>& data, int m, const vector<double>& points, int deg) :
    m_n{n}, m_data{data}, m_m{m}, m_points{points}, m_deg{deg}
    {
        m_ans.reserve(m);
    }

    void calcValues(); // вычислим значения, используя сглаживание по методу наименьших квадратов

    friend ofstream& operator<<(ofstream&, const TableFun&); // перегрузка оператора вывода

    friend ifstream& operator>>(ifstream&, TableFun&); // перегрузка оператора ввода

};

#endif