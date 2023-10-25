#ifndef LEASTSQUARESSMOOTHING_SYSTEM_H
#define LEASTSQUARESSMOOTHING_SYSTEM_H

#include <vector>
#include <cmath>
#include <cassert>
#include <utility>
using namespace std;

class System
{
private:
    int m_n;
    vector<vector<double>> m_a;
    vector<vector<double>> m_s;
    vector<double> m_b;
    vector<double> m_x;
    vector<double> m_y;
    vector<double> m_d;
public:
    System(const vector<vector<double>>& data, const vector<double>& f):
            m_n{(int)data.size()}, m_b{move(f)}, m_a{move(data)}, m_s(m_n, vector<double>(m_n)),
            m_d(m_n), m_x(m_n), m_y(m_n)
    {
        solve();
    }

    void solve();

    void solveDown();

    void solveUp();

    double& operator[](int);
};

#endif

//class System
//{
//private:
//    int m_n;
//    vector<vector<double>> m_a;
//    vector<double> m_b;
//    vector<double> m_x;
//    vector<int> m_trueOrder;
//    vector<int> m_help;
//public:
//    System(const vector<vector<double>>& data, const vector<double>& f):
//            m_n{(int)data.size()}, m_b{move(f)}, m_a{move(data)}
//    {
//        for (int i = 0; i < m_n; ++i)
//        {
//            m_trueOrder.emplace_back(i);
//            m_help.emplace_back(i);
//            m_x.emplace_back(0.0);
//
//        }
//        // решаем методом Гаусса с выбором главного элемента
//        toTriangle();
//        calcX();
//    }
//
//    void toTriangle();
//
//    void calcX();
//
//    double& operator[](int);
//};