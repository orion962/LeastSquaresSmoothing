#include "../headers/System.h"

void System::solve() {
    // бинарное возведение в степень
    auto binPow = [](double a, int n) -> double
    {
        double res{1.0};
        while(n)
        {
            if(n & 1)
            {
                res *= a;
            }
            a *= a;
            n >>= 1;
        }
        return res;
    };

    // своя собственная функция сигнум
    auto signum = [](double a) -> double
    {
        if(a < 0.0)
        {
            return -1.0;
        }
        else if(a > 0.0)
        {
            return 1.0;
        }
        else
        {
            return 0.0;
        }
    };

    double sum;
    for(int i = 0; i < m_n; ++i)
    {
        sum = 0;
        for(int k = 0; k <= i-1; ++k)
        {
            sum += (binPow(m_s[k][i], 2) * m_d[k]);
        }
        m_d[i] = signum(m_a[i][i] - sum);
        m_s[i][i] = sqrt(abs(m_a[i][i] - sum));
        for(int j = i+1; j < m_n; ++j)
        {
            sum = 0;
            for(int k = 0; k <= i-1; ++k)
            {
                sum += (m_s[k][i] * m_d[k] * m_s[k][j]);
            }
            m_s[i][j] = (m_a[i][j] - sum) / (m_s[i][i] * m_d[i]);
        }
    }
    solveDown();
    solveUp();
}

void System::solveDown()
{
    double sum;
    for(int i = 0; i < m_n; ++i) // trpStimesD[i][j] = m_s[j][i] * m_d[j]
    {
        sum = 0;
        for(int j = 0; j < i; ++j)
        {
            sum += (m_s[j][i] * m_d[j] * m_y[j]);
        }
        m_y[i] = (m_b[i] - sum)/(m_s[i][i] * m_d[i]);
    }
}

void System::solveUp()
{
    double sum;
    for(int i = m_n - 1; i >= 0; --i) {
        sum = 0;
        for (int j = m_n - 1; j > i; --j) {
            sum += (m_s[i][j] * m_x[j]);
        }
        m_x[i] = (m_y[i] - sum) / m_s[i][i];
    }
}

double& System::operator[](int idx)
{
    assert(idx >= 0 && idx < m_n);
    return m_x[idx];
}

//void System::toTriangle() // прямой ход
//{
//    double maxElem;
//    double cur;
//    int curNum;
//    int i_0 = 0;
//    int j_0 = 0;
//    for (int m = 0; m < m_n; ++m)
//    {
//        maxElem = 0.0;
//        for(int i = m; i < m_n; ++i) // находим наибольший по модулю элемент
//        {
//            for(int j = m; j < m_n; ++j)
//            {
//                if(abs(m_a[i][j]) > abs(maxElem))
//                {
//                    maxElem = m_a[i][j];
//                    i_0 = i;
//                    j_0 = j;
//                }
//            }
//        }
//        for(int j = m; j < m_n; ++j) // меняем строки местами
//        {
//            cur = m_a[m][j];
//            m_a[m][j] = m_a[i_0][j];
//            m_a[i_0][j] = cur;
//
//        }
//        cur = m_b[m];
//        m_b[m] = m_b[i_0];
//        m_b[i_0] = cur;
//        for(int i = 0; i < m_n; i++) // меняем столбцы местами
//        {
//            cur = m_a[i][m];
//            m_a[i][m] = m_a[i][j_0];
//            m_a[i][j_0] = cur;
//        }
//        curNum = m_trueOrder[m]; // запоминаем правильный порядок
//        m_trueOrder[m] = m_trueOrder[j_0];
//        m_trueOrder[j_0] = curNum;
//        m_help[m_trueOrder[m]] = m;
//        m_help[m_trueOrder[j_0]] = j_0;
//        for (int i = m+1; i < m_n; ++i)
//        {
//            double k = m_a[i][m] / m_a[m][m]; // m_a[m][m] != 0
//            for (int j = m; j < m_n; ++j)
//            {
//                m_a[i][j] = m_a[i][j] - k * m_a[m][j];
//            }
//            m_b[i] = m_b[i] - k * m_b[m];
//        }
//    }
//}
//
//void System::calcX() // обратный ход
//{
//    vector<double> cur_x(m_n, 0.0);
//    for (int i = m_n - 1; i >= 0; --i)
//    {
//        double sum = 0;
//        for (int j = m_n - 1; j > i; --j)
//        {
//            sum += m_a[i][j] * cur_x[j];
//        }
//        cur_x[i] = (m_b[i] - sum) / m_a[i][i];
//    }
//    // восстановление правильного порядка
//    for(int i = 0; i < m_n; ++i)
//    {
//        m_x[i] = cur_x[m_help[i]];
//    }
//}