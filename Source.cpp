#include "Sparse.h"

int main() {
    Sparse s1(4);
    s1.add(0, 1, 1);
    s1.add(0, 2, 2);
    s1.add(3, 3, 3);
    s1.add(0, 1, 1);
    s1.add(2, 0, 1);
    s1.print();
    auto s2 = s1.transpose();
    std::cout << "s2: " << std::endl;
    s2.print();
    auto s3 = s1 + s2;
    auto s4 = s3;
    std::cout << "s3: " << std::endl;
    s3.print();
    std::cout << "s4: " << std::endl;
    s4.print();
    auto s5 = s2 * s3;
    std::cout << "s5: " << std::endl;
    s5.print();
    return 0;
}