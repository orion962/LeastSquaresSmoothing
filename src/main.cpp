#include "../headers/TableFun.h"

int main()
{
    ifstream inf("input.txt");
    ofstream outf("output.txt");
    TableFun task;
    inf >> task;
    task.calcValues();
    outf << task;
    return 0;
}