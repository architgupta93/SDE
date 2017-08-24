#include "SDE.h"
#include "integrator.h"
#include "stochastic_integrator.h"
#include "ito_integrator.h"
#include "multipath_rv.h"
#include "gaussian_multipath_rv.h"
#include "vec_ops.h"
#include <math.h>
#include <vector>
#include <cassert>
#include <iostream>

int main() {
    // Overall simulation parameters
    const int n_args = 2;
    const double lambda = -1e-1;
    const double T_STEP = pow(2, -2);
    const double STDDEV = sqrt( T_STEP );
    const int N_STEPS = pow(2, 8);

    ZeroFun<n_args,n_args> *no_fun = new ZeroFun<n_args,n_args>();
    FxIsX<n_args> *simple_fun = new FxIsX<n_args>(lambda);
    std::vector<double> init_guess = {1.0, -1.0};
    
    // Simulating an ODE
    ODE *simple_ode = new ODE(simple_fun);
    ForwardEuler *fe = new ForwardEuler();  

    fe->setInitGuess(init_guess);
    fe->setTStep(T_STEP);
    fe->attachDE(simple_ode);
    fe->integrate(N_STEPS);
    fe->plot("Forward Euler - simple ODE");

    delete fe;
    delete no_fun;
    delete simple_fun;
    delete simple_ode;
}
