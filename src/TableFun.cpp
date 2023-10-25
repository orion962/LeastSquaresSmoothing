#include "../headers/TableFun.h"
#include "../headers/System.h"

void TableFun::calcValues()
{
    // бинарное возведение в степень (для оптимизации)
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

    vector<double> s(2 * m_deg + 1);
    vector<double> t(m_deg + 1);
    vector<vector<double>> data(m_deg + 1, vector<double>(m_deg + 1));
    for(int k = 0; k <= m_deg; ++k)
    {
        for (int i = 0; i <= m_n; ++i)
        {
            t[k] += (binPow(m_data[i].first, k) * m_data[i].second);
        }
    }

    s[0] = m_n + 1;
    for (int k = 1; k <= 2 * m_deg; ++k)
    {
        for (int i = 0; i <= m_n; ++i)
        {
            s[k] += binPow(m_data[i].first, k);
        }
    }

    for (int i = 0; i <= m_deg; ++i)
    {
        data[i][i] = s[2*i];
        for (int j = i+1, k = 2*i+1; j <= m_deg; ++j, ++k)
        {
            data[i][j] = data[j][i] = s[k];
        }
    }

    // далее идут вычисления по методу квадратного корня
    System a(data, t);
    for (int i = 0; i < m_points.size(); ++i)
    {
        double tmp {0.0};
        for (int k = 0; k <= m_deg; ++k)
        {
            tmp += (a[k] * binPow(m_points[i], k));
        }
        m_ans.emplace_back(tmp);
    }
}

ofstream& operator<<(ofstream& out, const TableFun& obj)
{
    for(double elem : obj.m_ans)
    {
        out << elem << "  ";
    }
    return out;
}

ifstream& operator>>(ifstream& in, TableFun& obj)
{
    in >> obj.m_n;
    --obj.m_n;
    obj.m_data.reserve(obj.m_n + 1);

    double tmp1;
    double tmp2; // вспомогательные переменные
    for(int i = 0; i < obj.m_n + 1; ++i)
    {
        in >> tmp1;
        in >> tmp2;
        obj.m_data.emplace_back(pair<double,double>(tmp1,tmp2));
    }

    in >> obj.m_m;
    obj.m_points.reserve(obj.m_m);
    obj.m_ans.reserve(obj.m_m);
    for(int i = 0; i < obj.m_m; ++i)
    {
        in >> tmp1;
        obj.m_points.emplace_back(tmp1);
    }
    in >> obj.m_deg;
    return in;
}