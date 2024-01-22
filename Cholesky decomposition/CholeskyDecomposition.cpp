#include "Sparse.h"

Sparse Sparse::ichol() {
    size_t n = size;
    Sparse new_sparse(*this);
    Iterator it1, it2, itJ, begin1, end1, begin2, end2;
    double val;
    for (size_t k = 0; k < size; k++)
    {
        begin1 = new_sparse.rows[k]->begin();
        end1 = new_sparse.rows[k]->end();
        val = 0;
        for (it1 = begin1; it1 != end1; it1++)
        {
            if (it1->get_column() > k)
                break;
            if (it1->get_column() == k)
            {
                val = sqrt(it1->get_value());
                it1->get_value() = val;
                std::cout << it1->get_column() << " " << val << std::endl;
                break;
            }
        }

        for (size_t i = k + 1; i < size; i++)
        {
            begin2 = new_sparse.rows[i]->begin();
            end2 = new_sparse.rows[i]->end();
            for (it1 = begin2; it1 != end2; it1++)
            {
                if (it1->get_column() > k)
                    break;
                if (it1->get_column() == k)
                {
                    it1->get_value() /= val;
                    break;
                }
            }
        }

        for (size_t j = k + 1; j < size; j++)
        {
            begin1 = new_sparse.rows[j]->begin();
            end1 = new_sparse.rows[j]->end();

            for (size_t i = j; i < size; i++)
            {
                begin2 = new_sparse.rows[i]->begin();
                end2 = new_sparse.rows[i]->end();
                itJ = end2;
                for (it1 = begin2; it1 != end2; it1++)
                {
                    if (it1->get_column() > j)
                        break;
                    if (it1->get_column() == j)
                    {
                        itJ = it1;
                        break;
                    }
                }
                if (itJ != end2)
                {
                    for (it1 = begin1; it1 != end1; it1++)
                    {
                        if (it1->get_column() > k)
                        {
                            it1 = end1;
                            break;
                        }
                        if (it1->get_column() == k)
                            break;
                    }
                    if (it1 != end1)
                    {
                        for (it2 = begin2; it2 != end2; it2++)
                        {
                            if (it2->get_column() > k)
                            {
                                it2 = end2;
                                break;
                            }
                            if (it2->get_column() == k)
                                break;
                        }
                        if (it2 != end2) {
                            itJ->get_value() -= it1->get_value() * it2->get_value();
                        }
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < size; i++)
    {
        begin1 = new_sparse.rows[i]->begin();
        end1 = new_sparse.rows[i]->end();
        for (it1 = begin1; it1 != end1; it1++)
            if (it1->get_column() == i)
                it1.reset_after_this();
    }
    return new_sparse;
}