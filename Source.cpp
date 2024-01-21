#include "Sparse.h"

int main()
{
	Sparse<int> s1(4);
	s1.add(0, 1, 1);
	s1.add(0, 2, 2);
	s1.add(3, 3, 3);
	s1.add(0, 1, 1);
	s1.add(2, 0, 1);
	s1.print();
	return 0;
}