// Implementation file for the Gaussian Multipath Random variable class that
// extends the vanilla multipath random variable class (which basically defines
// the basic structure and operations for a multipath random variable
//
// Author: Archit Gupta
// Date: Jan 03, 2017

#include "gaussian_multipath_rv.h"
#include "multipath_rv.h"
#include "iostream"
#include <sstream>
#include <vector>

std::vector<std::normal_distribution<double>* > 
    GaussianMultipathRV::distro;

GaussianMultipathRV::GaussianMultipathRV() : MultipathRV() {

}

GaussianMultipathRV::GaussianMultipathRV(int _n_paths) : MultipathRV(_n_paths) {
#ifdef __DEBUG__
    std::cout << "Initializing " << _n_paths << "-path Gaussian RV @ " << this << std::endl;
#endif
    std::cout << "WARNING: Distribution parameters mu, sigma set to 0, 1 respectively" << std::endl;
    initializeDistro((double) 0, (double) 1);
}

GaussianMultipathRV::GaussianMultipathRV(int _n_paths, double mu, double sigma) : 
    MultipathRV(_n_paths) {
#ifdef __DEBUG__
    std::cout << "Initializing " << _n_paths << "-path Gaussian RV @ " << this << std::endl;
#endif
    initializeDistro(mu, sigma);
}

GaussianMultipathRV::GaussianMultipathRV(int _n_paths, std::vector<double> mu, std::vector<double> sigma) :
    MultipathRV(_n_paths) {
#ifdef __DEBUG__
    std::cout << "Initializing " << _n_paths << "-path Gaussian RV @ " << this << std::endl;
#endif
    initializeDistro(mu, sigma);
}

GaussianMultipathRV::~GaussianMultipathRV() {
    this->clearDistro();
}

void GaussianMultipathRV::clearDistro() {
    // Clear all the existing iterators
    for (std::vector<std::normal_distribution<double>* >::iterator it = distro.begin(); 
            it != distro.begin(); it++) {
        delete *it; 
    }
}

void GaussianMultipathRV::initializeDistro(double mu, double sigma) {
#ifdef __DEBUG__
    std::cout << "Initializing Gaussian distribution with mu = " << mu
        << ", sigma = " << sigma << std::endl;
#endif
    for (int i = 0; i < n_paths; i++) {
        std::normal_distribution<double>* n_dist = new std::normal_distribution<double>(mu, sigma);
        distro.push_back(n_dist);
    }
}

void GaussianMultipathRV::initializeDistro(std::vector<double> mu, std::vector<double> sigma) {
    int n_mu = mu.size();
    int n_sigma = sigma.size();
    if ( (n_mu != n_paths) || (n_sigma != n_paths) ) {
        std::cout << "ERROR: Mismatch in distribution parameteres and N_PATHS.\n";
        return;
    }

    paths.clear();
    for (int i = 0; i < n_paths; i++) {
        std::normal_distribution<double>* n_dist = new std::normal_distribution<double>(mu[i], sigma[i]);
        distro.push_back(n_dist);
    }
}

std::vector<double> GaussianMultipathRV::draw() {
    int inst = 0;
    for (std::vector<std::normal_distribution<double>* >::iterator it = distro.begin(); 
            it != distro.end(); it++) {
        paths[inst] = (*it)->operator()(gen);
        inst++;
    }
    return paths;
}

std::vector<double> GaussianMultipathRV::draw(double t_hat) {
#ifdef __DEBUG__
    std::cout << "WARNING: Variable time stepping is not allowed at the moment. ";
    std::cout << "Using initial distribution parameters" << std::endl;
#endif
    return draw(); // TODO: Fix this
}

std::string GaussianMultipathRV::toStr() const{
    std::stringstream converted;
    for (int i = 0; i < n_paths; i++) {
        converted << paths[i] << " ";
    }
    converted << std::endl;
    return converted.str();
}
