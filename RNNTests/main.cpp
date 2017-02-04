#include <iostream>
#include "MatrixOperationsTest.h"
//#include "cpptest-1.1.2/src/cpptest.h"
#include "cpptest-time.h"
//include </home/laura/cpptest-1.1.2/src/cpptest-textoutput.h>
using namespace std;

int main(int argc, char* argv[])
{
    Test::Suite tests;
    tests.add( auto_ptr<Test::Suite>( new MatrixOperationsTest ) );
    Test::TextOutput output(Test::TextOutput::Verbose);

    tests.run(output);
    cout << "Hello world!" << endl;
    return 0;
}
