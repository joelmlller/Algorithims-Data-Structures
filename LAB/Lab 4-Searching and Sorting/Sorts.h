/*
 * Name: Joel Miller
 * Date Submitted: 02/15/2023
 * Lab Section: 004
 * Assignment Name: Searching and Sorting
 */


#pragma once

#include <vector>
#include <cstdlib>


template <class T>
std::vector<T> mergeSort(std::vector<T> lst) {
    if (lst.size() <= 1) {
        return lst;
    }

    // split the input vector
    std::vector<T> l, r, final;
    int m = (lst.size() + 1) / 2;
    for (int i = 0; i < m; i++) {
        l.push_back(lst[i]);
    }
    for (int i = m; i < lst.size(); i++) {
        r.push_back(lst[i]);
    }

    // recursively sort
    l = mergeSort(l);
    r = mergeSort(r);

    // merge the two
    int li = 0, ri = 0;
    while (li < l.size() && ri < r.size()) {
        if (l[li] < r[ri]) {
            final.push_back(l[li]);
            li++;
        }
        else {
            final.push_back(r[ri]);
            ri++;
        }
    }
    while (li < l.size()) {
        final.push_back(l[li]);
        li++;
    }
    while (ri < r.size()) {
        final.push_back(r[ri]);
        ri++;
    }

    return final;
}

template <class T>
std::vector<T> quickSort(std::vector<T> lst) {
    if (lst.size() <= 1) {
        return lst;
    }

    //random pivot value
    int next = rand() % lst.size();
    T val = lst[next];

    //vector into two halves based on the pivot value
    std::vector<T> lvar, rvar;
    for (int i = 0; i < lst.size(); i++) {
        if (i == next) {
            continue;
        }
        if (lst[i] < val) {
            lvar.push_back(lst[i]);
        }
        else {
            rvar.push_back(lst[i]);
        }
    }

    // recursively sort the two halves and merge them
    lvar = quickSort(lvar);
    rvar = quickSort(rvar);
    lvar.push_back(val);
    lvar.insert(lvar.end(), rvar.begin(), rvar.end());

    return lvar;
}
