#ifndef __VEC_OPS_H__
#define __VEC_OPS_H__

#include <cassert>
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <random>
#include <chrono>

// A small library for implementing some vectorization operations, like the
// addition of two vectors / arrays of the same size

namespace nn_utils {
    // Some of these functions are going to have pretty generic names, so thay
    // have been put inside this namespace to have some clarity
    template <typename T> 
    void printV(const std::vector<T> &v) {
        typename std::vector<T>::const_iterator it = v.begin();
        std::cout << *(it++);

        for( ; it != v.end(); it++) {
            std::cout << ", " << *it;
        }

        std::cout << std::endl;
    }
}

namespace vector_ops {
    template <typename T>
    std::vector<T> dot_times(const std::vector<T> &v, const std::vector<double> &s) {
        std::vector<T> result;
        result.reserve(v.size());
        typename std::vector<T>::const_iterator it_v = v.begin();
        typename std::vector<T>::const_iterator it_s = s.begin();
        for ( ; (it_v != v.end()) && (it_s != s.end()); ) {
            result.push_back((*it_v) * (*it_s));
            it_v++;
            it_s++;
        }
    
        return result;
    }

    std::vector<double> randomVector(int size, double mu, double stddev);
}

template <typename T>
std::vector<T> operator*(const std::vector<T> &v, const double s) {
    std::vector<T> result;
    result.reserve(v.size());
    
    for (typename std::vector<T>::const_iterator it = v.begin(); it != v.end(); it++) {
        result.push_back(*it * s);
    }

    return result;
}

template <typename T>
std::vector<T> operator*(const double s, const std::vector<T> &v) {
    return v*s;
}

template <typename T>
std::vector<T> operator*(const std::vector<T> &v, const std::vector<double> &s) {
    assert( v.size() == 1 || s.size() == 1 );
    if ( v.size() == 1 ) {
        return s * v[0];
    }
    return v * s[0];
}

template <typename T>
std::vector<T> operator+(const std::vector<T> &a, const std::vector<T> &b) {
    assert (a.size() == b.size());
    std::vector<T> result;

    result.reserve(a.size());
    typename std::vector<T>::const_iterator l_it = a.begin();
    typename std::vector<T>::const_iterator r_it = b.begin();
    while (l_it != a.end()) {
        result.push_back( (*l_it) + (*r_it) );
        l_it++;
        r_it++;
    }
    return result;
}

template <typename T>
void operator += (std::vector<T> &lhs, const std::vector<T> &rhs) {
    assert (lhs.size() == rhs.size());
    typename std::vector<T>::const_iterator r_it = rhs.begin();
    typename std::vector<T>::iterator l_it = lhs.begin();
    while (l_it != lhs.end()) {
        *l_it  = (*l_it) + (*r_it);
        l_it++;
        r_it++;
    }
    return;
}

template <typename T>
class StorageBase {
    protected:
        T* elements;
    public:
        T& operator[] (int& i) { return elements[i]; }
        StorageBase();
        StorageBase(const StorageBase &op);
        virtual ~StorageBase();
        typedef T* iterator;
        typedef const T* const_iterator;
        virtual const_iterator cbegin() = 0;
        virtual const_iterator cend() = 0;
        virtual iterator begin() = 0;
        virtual iterator end() = 0;
};

template <typename T, size_t n_elems>
class FixedStorage : public StorageBase<T> {
    using StorageBase<T>::elements;
    typedef typename StorageBase<T>::iterator iterator;
    typedef typename StorageBase<T>::const_iterator const_iterator; 

    public:
        FixedStorage();
        ~FixedStorage();
        FixedStorage(const FixedStorage &op);
        const_iterator cbegin() { return &elements[0]; }
        const_iterator cend() { return &elements[n_elems]; }
        iterator begin() { return &elements[0]; }
        iterator end() { return &elements[n_elems]; }
        FixedStorage<T, n_elems> operator + (const FixedStorage<T, n_elems> &rhs) const;
        FixedStorage<T, n_elems> &operator = (const FixedStorage<T, n_elems> &rhs);
        void operator += (const FixedStorage<T, n_elems> &rhs);
        void operator += (const T &rhs);

        // Multiplication by scalar operands or vector operands of the same size
        FixedStorage<T, n_elems> operator * (const FixedStorage<T, n_elems> &rhs) const;
        FixedStorage<T, n_elems> operator * (const T &rhs) const;
        void operator *= (const T &rhs); 
        // void operator .*= (const FixedStorage<T, n_elems> &rhs);
};

#endif
