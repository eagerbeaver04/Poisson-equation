#include "Sparse.h"

Sparse Sparse::ichol() {
    size_t n = size;
    Sparse new_sparse(*this);
    Iterator it1, it2, itJ, begin1, end1, begin2, end2;
    double val;
    for (size_t k = 0; k < size; k++) {
        begin1 = new_sparse.rows[k]->begin();
        end1 = new_sparse.rows[k]->end();
        val = 0;
        find_by_column(begin1, end1, it1, k);

        val = sqrt(it1->get_value());
        it1->get_value() = val;

        for (size_t i = k + 1; i < size; i++) {
            begin2 = new_sparse.rows[i]->begin();
            end2 = new_sparse.rows[i]->end();

            find_by_column(begin2, end2, it1, k);
            it1->get_value() /= val;
        }

        for (size_t j = k + 1; j < size; j++) {
            begin1 = new_sparse.rows[j]->begin();
            end1 = new_sparse.rows[j]->end();

            for (size_t i = j; i < size; i++) {
                begin2 = new_sparse.rows[i]->begin();
                end2 = new_sparse.rows[i]->end();

                find_by_column(begin2, end2, it1, j);
                itJ = it1;

                if (itJ != end2) {
                    find_by_column(begin1, end1, it1, k);
                    if (it1 != end1) {
                        find_by_column(begin2, end2, it2, k);
                        if (it2 != end2)
                            itJ->get_value() -= it1->get_value() * it2->get_value();
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < size; i++) {
        begin1 = new_sparse.rows[i]->begin();
        end1 = new_sparse.rows[i]->end();
        for (it1 = begin1; it1 != end1; it1++)
            if (it1->get_column() == i)
                new_sparse.rows[i]->reset_after_ptr(it1);
    }
    return new_sparse;
}

Sparse Sparse::chol() {
    size_t n = size;
    Sparse new_sparse(*this);
    Iterator it1, it2, itJ, begin1, end1, begin2, end2;
    double val;
    double current_val;
    for (size_t k = 0; k < size; k++) {
        begin1 = new_sparse.rows[k]->begin();
        end1 = new_sparse.rows[k]->end();
        val = 0;
        find_by_column(begin1, end1, it1, k);

        val = sqrt(it1->get_value());
        it1->get_value() = val;

        for (size_t i = k + 1; i < size; i++) {
            begin2 = new_sparse.rows[i]->begin();
            end2 = new_sparse.rows[i]->end();

            find_by_column(begin2, end2, it1, k);
            it1->get_value() /= val;
        }

        for (size_t j = k + 1; j < size; j++) {
            begin1 = new_sparse.rows[j]->begin();
            end1 = new_sparse.rows[j]->end();

            for (size_t i = j; i < size; i++) {
                current_val = 0;
                begin2 = new_sparse.rows[i]->begin();
                end2 = new_sparse.rows[i]->end();

                find_by_column(begin2, end2, it1, j);
                itJ = it1;

                find_by_column(begin1, end1, it1, k);
                if (it1 != end1) {
                    find_by_column(begin2, end2, it2, k);
                    if (it2 != end2) {
                        current_val -= it1->get_value() * it2->get_value();
                        if (itJ != end2)
                            itJ->get_value() += current_val;
                        else
                            new_sparse.add(i, j, current_val);
                    }
                }
            }
        }
    }
    for (size_t i = 0; i < size; i++) {
        begin1 = new_sparse.rows[i]->begin();
        end1 = new_sparse.rows[i]->end();
        for (it1 = begin1; it1 != end1; it1++)
            if (it1->get_column() == i)
                new_sparse.rows[i]->reset_after_ptr(it1);
    }
    return new_sparse;
}

Sparse Sparse::chol(double droptol) {
    size_t n = size;
    Sparse new_sparse(*this);
    Iterator it1, it2, itJ, begin1, end1, begin2, end2;
    double val;
    double current_val;
    for (size_t k = 0; k < size; k++) {
        begin1 = new_sparse.rows[k]->begin();
        end1 = new_sparse.rows[k]->end();
        val = 0;
        find_by_column(begin1, end1, it1, k);

        val = sqrt(it1->get_value());
        it1->get_value() = val;

        for (size_t i = k + 1; i < size; i++) {
            begin2 = new_sparse.rows[i]->begin();
            end2 = new_sparse.rows[i]->end();

            find_by_column(begin2, end2, it1, k);
            it1->get_value() /= val;
        }

        for (size_t j = k + 1; j < size; j++) {
            begin1 = new_sparse.rows[j]->begin();
            end1 = new_sparse.rows[j]->end();

            for (size_t i = j; i < size; i++) {
                current_val = 0;
                begin2 = new_sparse.rows[i]->begin();
                end2 = new_sparse.rows[i]->end();

                find_by_column(begin2, end2, it1, j);
                itJ = it1;

                find_by_column(begin1, end1, it1, k);
                if (it1 != end1) {
                    find_by_column(begin2, end2, it2, k);
                    if (it2 != end2) {
                        current_val -= it1->get_value() * it2->get_value();

                        if (itJ != end2) {
                            itJ->get_value() += current_val;
                            if (itJ->get_value() <= droptol)
                                itJ->get_value() = 0;
                        } else
                            new_sparse.add(i, j, current_val);

                    }
                }
            }
        }
    }
    for (size_t i = 0; i < size; i++) {
        begin1 = new_sparse.rows[i]->begin();
        end1 = new_sparse.rows[i]->end();
        for (it1 = begin1; it1 != end1; it1++)
            if (it1->get_column() == i)
                new_sparse.rows[i]->reset_after_ptr(it1);

    }
    return new_sparse;
}
