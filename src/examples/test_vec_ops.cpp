#define __DEBUG__
#include "../vec_ops.h"
#include <iostream>

void printArray (StorageBase<double> &b) {
    for (StorageBase<double>::const_iterator it = b.cbegin(); it != b.cend(); it++) {
        std::cout << *it << ", ";
    }
    std::cout << std::endl;
}

int main() {
    FixedStorage<double, 10> A = FixedStorage<double, 10>();
    FixedStorage<double, 10> B = FixedStorage<double, 10>();

    for (int i = 0; i < 10; i++) {
        A[i] = (double) i*i;
        B[i] = (double) 2*i + 1;
    }

    printArray(A);
    printArray(B);

    std::cout << "Running test function ..." << std::endl;
    FixedStorage<double, 10> C = FixedStorage<double, 10>();
    C = A + B;

    printArray(C);
    
    // Some testing with overloading: Basically stuff that won't work
    // std::cout << std::endl;
    // std::cout << "Repeating experiments with the base class" << std::endl;
    // std::cout << std::endl;

    // StorageBase<double> *X = new FixedStorage<double, 10>();
    // StorageBase<double> *Y = new FixedStorage<double, 10>();

    // for (int i = 0; i < 10; i++) {
    //     (*X)[i] = (double) i*i;
    //     (*Y)[i] = (double) 2*i + 1;
    // }

    // printArray(*X);
    // printArray(*Y);

    // StorageBase<double> *Z = new FixedStorage<double, 10>();
    // *Z = *X + *Y;

    // printArray(*Z);
    // delete X, Y, Z;
}
