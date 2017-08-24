// Header file describing a class that describes multiple paths taken by a
// stochastic process at the same time.
//
// Author: Archit Gupta
// Date: Jan 03, 2017

#ifndef __MULTIPATH_RV_H__
#define __MULTIPATH_RV_H__

#include <vector>
#include <random>

class MultipathRV {
    protected:
        const int n_paths;
        std::vector<double> paths;
        static std::default_random_engine gen;    // Generator

    public:
        virtual ~MultipathRV();
        MultipathRV();
        MultipathRV(int _n_paths);
        MultipathRV(const MultipathRV &op);
        virtual std::vector<double> draw() = 0;
        virtual std::vector<double> draw(double dt) = 0;
        int getNPaths() { return n_paths; }
};

#endif
