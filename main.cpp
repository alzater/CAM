#include "tstr.h"
#include "solver.h"

#include <iostream>

#include <memory>
using std::unique_ptr;


int main()
{
    //std::string str = "<'1,'2>F";
    //std::string str = "\\(<'1,\\('2)E>S)E";
    //std::string str = "<\\(<\\(<<S,FS>E,'2>E),\\(S*)>E),'3>E";
    //std::string str = "<\\(<S,<'44,<\\(S),'2>E>>E),\\(S*)>E";
    //std::string str = "B('1)('2)";

    int factN = 5;
    std::string str = "<<Y(<<S,'0>=B(('1),(<S,<FS,<S,'1>->E>*)))>\\(<<S,'0>=B(('1),(<S,<FS,<S,'1>->E>*)))><S,'" + std::to_string(factN) + ">E";

    //std::cin >> str;
    //std::cout << str << std::endl;
    TStr* code = new TStr(str);
    Solver solver( code );
    solver.makeSteps(1000);

    return 0;
}
