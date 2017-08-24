#include "integrator.h"
#include "stochastic_integrator.h"
#include <vector>
#include <iostream>

// Just some empty function definitions here... Nothing to do really
StochasticIntegrator::StochasticIntegrator() : Integrator() {

}

StochasticIntegrator::StochasticIntegrator(double _t_step, const std::vector<double> &_init_guess, double _t_init) : Integrator(_t_step, _init_guess, _t_init) {
#ifdef __DEBUG__
    std::cout << "Instantiated a Stochastic Integrator @ " << this << std::endl;
#endif
}

StochasticIntegrator::~StochasticIntegrator() {
#ifdef __DEBUG__
    std::cout << "Freeing up space for Stochastic integrator @ " << this << std::endl;
#endif
}
