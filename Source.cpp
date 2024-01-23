#include "Sparse.h"
#include "PreconditionedConjugateGradientsMethod/PCG.h"
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
    s2 = s2 * s3;
    std::cout << "s2: " << std::endl;
    s2.print();

    std::vector<std::vector<double>> A = {{1.395367621832617, 1.793836757626301, 1.227868629033308, 0.521174654533141, 1.296203817908845},
                                {1.793836757626301, 2.964575485749597, 1.892472502016853, 1.308557881359714, 2.079159067654516 },
                                {1.227868629033308, 1.892472502016853,1.935905955356345, 1.035805712013819 ,1.768389255171490},
                                {0.521174654533141, 1.308557881359714, 1.035805712013819, 1.062148946273321 ,1.070186101501958},
                                {1.296203817908845, 2.079159067654516 ,1.768389255171490 ,1.070186101501958 ,1.728645295621314 } };
    Sparse sparse_A(A);
    std::cout << "s6: " << std::endl;
    sparse_A.print();
    auto l5 = sparse_A.ichol();
    std::cout << "l5: " << std::endl;
    l5.print();
    auto l6 = sparse_A.chol();
    std::cout << "l6: " << std::endl;
    l6.print();
    auto l5t = l5.transpose();
    auto s5_ = l5 * l5t;
    std::cout << "s5_: " << std::endl;
    s5_.print();
    auto l7 = sparse_A.chol(0.1);
    std::cout << "l7: " << std::endl;
    l7.print();

    std::cout << "pcg " << std::endl;
    size_t N = 5;
    std::vector<double> absolut_solution(N);
    for (int i = 0;i < N;i++)
        absolut_solution[i] = 1;
    std::vector<double> b = sparse_A*absolut_solution;
    std::vector<double> x_0(N, 10); x_0[0] = 1;
    double epsilon = 1e-5;
    Sparse L0 = sparse_A.chol();
    std::cout << "L0: " << std::endl;
    L0.print();
    std::cout << "L1: " << std::endl;
    L0.transpose().print();
    auto solution_pcg_pred = pcg_pred(sparse_A, b, x_0, epsilon, L0);
    std::cout <<"solution_pcg_pred: ";
    print(solution_pcg_pred);
    auto  solution_pcg = pcg(sparse_A, b, x_0, epsilon);
    std::cout <<"solution_pcg: ";
    print(solution_pcg);
    return 0;
}