#pragma once
#include <vector>
#include <iostream>

using vector = std::vector<double>;
void print(const vector& a);
double scalar_mul(const vector& a,const vector& b);
vector sum(const vector& a, const vector& b);
vector sub(const vector& a, const vector& b);
vector mul(const vector& a, double f);
vector mul(double f, const vector& a);