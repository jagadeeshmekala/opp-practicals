// Experiment 3 (part 2): Verify and visualize a memory leak
//
// Compile and check with:
//   g++ -g -fsanitize=address exp3_memory_leak_demo.cpp -o leak && ./leak
//   or:  valgrind --leak-check=full ./leak
//
// Visualization:
//   Stack            Heap
//   p  ------->      [ 5 ]   <- still reserved after leak() ends
//   (p destroyed)    nobody holds its address -> LEAKED
#include <iostream>
using namespace std;

void leak() {
    int* p = new int(5);       // box created in heap
    cout << "Leaking function: value = " << *p << endl;
    // no 'delete p;' here -> memory leak
}

void noLeak() {
    int* p = new int(5);
    cout << "Safe function: value = " << *p << endl;
    delete p;                  // memory returned -> no leak
}

int main() {
    leak();                    // leaks 4 bytes
    noLeak();                  // no leak
    return 0;
}
