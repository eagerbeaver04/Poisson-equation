#include "PCG.h"

vector gauss(Sparse& L, Sparse& Lt, const vector& b)
{
    return Lt.gauss_up(L.gauss_down(b));
}

vector pcg(const Sparse& A,const vector& b,
           const vector& x_0, double epsilon)
{
    vector eps = sub(b , A*x_0);
    vector p = eps;
    vector q(eps.size(), 0);
    vector x = x_0;
    double alpha =0;
    double beta =0;
    double mistake = epsilon + 1;
    int k =0;
    while(mistake > epsilon)
    {
        q = A * p;
        alpha = scalar_mul(eps, p) / scalar_mul(q, p);
        x = sum(x, mul(p,alpha));
        eps = sub(eps, mul(q, alpha));
        mistake = norm(eps);
        beta = scalar_mul(eps,q) / scalar_mul(p, q);
        p = sub(eps, mul(p, beta));
        k++;
    }
    std::cout << "K: " << k <<std::endl;
    return x;
}

vector pcg_pred(const Sparse& A,const vector& b,
                const vector& x_0, double epsilon, Sparse& L)
{
    Sparse Lt = L.transpose();
    vector eps = sub(b , A*x_0);
    vector z = gauss(L,Lt, eps);
    vector prev_eps = eps;
    vector prev_z = z;
    double norm0 = norm(eps);
    vector p = z;
    vector q(eps.size(), 0);
    vector x = x_0;
    double alpha =0;
    double beta =0;
    double mistake = epsilon + 1;
    int k =0;
    while(mistake > epsilon)
    {
        q = A*p;
        alpha = scalar_mul(z,q) / scalar_mul(q,p);
        x = sum(x,  mul(p, alpha));
        eps = sub(eps,mul(q, alpha));
        z = gauss(L, Lt, eps);
        mistake = norm(eps) / norm0;
        beta = scalar_mul(z, eps) / scalar_mul(prev_eps, prev_z);
        p = sum(eps, mul(p ,beta));
        prev_z = z;
        prev_eps = eps;
        k++;
    }
    std::cout << "K_pred: " << k<<std::endl;
    return x;
}

vector pcg_pred(Sparse& A,const vector& b,
                const vector& x_0, double epsilon)
{
    Sparse L0 =A.chol();
    return pcg_pred(A, b, x_0, epsilon,  L0);
}