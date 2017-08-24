#include "ito_integrator.h"
#include "stochastic_integrator.h"
#include "vec_ops.h"
#include <vector>
#include <iostream>

// TODO: Find out how to inline a function. There is no real point in having
// this here as a separate function
std::vector<double> ItoIntegrator::getFVal(const std::vector<double> &x_in, double _t_step) {
    return de->operator()(x_in, _t_step);
}

ItoIntegrator::ItoIntegrator(double _t_step, const std::vector<double> &_init_guess, double _t_init) : StochasticIntegrator(_t_step, _init_guess, _t_init) {
#ifdef __DEBUG__
    std::cout << "Stochastic Integrator set up with Ito's integral @ " << this << std::endl;
#endif
}

ItoIntegrator::~ItoIntegrator() {
#ifdef __DEBUG__
    std::cout << "CLEAN UP: Freeing up space for Ito integrator @ " << this << std::endl;
#endif
}

ItoIntegrator::ItoIntegrator() : StochasticIntegrator() {

}

void ItoIntegrator::integrate(int n_steps) {
    checkInitGuessSize();
    integral.push_back(init_guess);
    #ifdef __DEBUG__
        std::cout << "Running Ito Integral on SDE @ " << de << " for " << n_steps 
            << " steps with dt = " << t_step << std::endl;
    #endif
    std::vector<double> sol = integral.back();

    double t = t_init;
    while (n_steps-- > 0) {
        std::vector<double> g_dW = vector_ops::dot_times(( de->getG(sol, t) ), ( de->getDW(t_step) ));
        std::vector<double> f_dt = de->operator()(sol, t) * t_step;
        sol += f_dt;
        sol += g_dW;
    
        #ifdef __PRINT_DETAILS__
            std::cout << "Obtained F*dt: " << f_dt[0] << ", ";
            std::cout << "G*dW: " << g_dW[0] << ", ";
            std::cout << "Updated sol: " << sol[0] << std::endl;
        #endif
        t += t_step;
        integral.push_back(sol);
    }
}
