// Implementation for the basic function of a multipath random varible class
//
// Author: Archit Gupta
// Date: Jan 03, 2017
//

#include "multipath_rv.h"
#include <random>
#include <vector>
#include <chrono>

std::default_random_engine MultipathRV::gen( 
        std::chrono::system_clock::now().time_since_epoch().count() );

MultipathRV::MultipathRV(int _n_paths) : n_paths(_n_paths) {
    for (int i = 0; i < _n_paths; i++) {
        paths.push_back( (double) 0.0);
    }
}

MultipathRV::MultipathRV() : n_paths(0) {

}

MultipathRV::~MultipathRV() {
    paths.clear();
}

// Private/protected functions: Not checking the sizes everytime assuming that
// the sizes have been checked before this function is called

MultipathRV::MultipathRV(const MultipathRV &op) : n_paths(op.n_paths) {
    paths = op.paths;
}
