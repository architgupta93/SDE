// Extends the mutlipath random variable class to a class where random variables
// are drawn from a Gaussian distribution with a given mean and standard
// deviation
// Author: Archit Gupta
// Date: Jan 03, 2017

#ifndef __GAUSSIAN_MULTPATH_RV_H__
#define __GAUSSIAN_MULTPATH_RV_H__

#include "multipath_rv.h"
#include <random>
#include <vector>
#include <string>

class GaussianMultipathRV : public MultipathRV {
    private:
        static std::vector<std::normal_distribution<double>* > distro; // distribution

    public:
        ~GaussianMultipathRV();
        GaussianMultipathRV();
        GaussianMultipathRV(int _n_paths);
        GaussianMultipathRV(const GaussianMultipathRV &op)
            : MultipathRV(op) {};
        GaussianMultipathRV(int _n_paths, double mu, double sigma);
        GaussianMultipathRV(int _n_paths, std::vector<double> mu, std::vector<double> sigma);
        void clearDistro();
        void initializeDistro(double mu, double sigma);
        void initializeDistro(std::vector<double> mu, std::vector<double> sigma);
        std::vector<double> draw();
        std::vector<double> draw(double dt);
        std::string toStr() const;
};

#endif
