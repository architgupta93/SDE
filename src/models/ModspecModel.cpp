#include "ModspecModel.h"
#include <vector>
#include <iostream>
#include <string>

// The deterministic Modspec Model class
ModspecModel::ModspecModel() : ModspecModel(0) {

}

ModspecModel::ModspecModel(int _n_unks) : n_unks(_n_unks) {
#ifdef __DEBUG__
    std::cout << "Instantiating MODSPEC Model with " << n_unks << " unknowns @ " << this;
    std::cout << std::endl;
#endif
}

ModspecModel::ModspecModel(int _n_unks, const std::vector<double> &in_parms) : n_unks(_n_unks) {
#ifdef __DEBUG__
#endif
}

ModspecModel::~ModspecModel() {
#ifdef __DEBUG__
#endif
}

// The stochastic Modspec Model class
ModspecModel__Sto::ModspecModel__Sto() : ModspecModel(0) {
#ifdef __DEBUG__
#endif
}

ModspecModel__Sto::ModspecModel__Sto(int _n_unks) : ModspecModel(_n_unks) {
#ifdef __DEBUG__
#endif
}

ModspecModel__Sto::ModspecModel__Sto(int _n_unks, const std::vector<double> &in_parms) : ModspecModel(_n_unks, in_parms) {
#ifdef __DEBUG__
#endif
}

ModspecModel__Sto::~ModspecModel__Sto() {
#ifdef __DEBUG__
#endif
}
