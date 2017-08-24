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
    const int n_args = 1;
    const double T_STEP = pow(2, -8);
    const double STDDEV = sqrt(T_STEP);
    const int N_STEPS = pow(2, 8);

    // Parameters required for describing the SDE
    double lambda = 2.0;
    double mu = 1.0;
    FxIsX<n_args> *_f = new FxIsX<1>(lambda);
    FxIsX<n_args> *_g = new FxIsX<1>(mu);

    // FIXME: The SDE should take in a Wiener Process and NOT a multipath
    // gaussian random variable. The latter has already been included in the
    // Wiener process class
    MultipathRV *dW = new GaussianMultipathRV(1, 0, STDDEV);
    SODE *black_scholes = new SODE(_f, _g, dW);
    ItoIntegrator *ito = new ItoIntegrator();

    // For this one, we need an initial guess, otherwise, the whole thing will
    // remain at 1
    std::vector<double> init_guess(n_args, 1.0);
    ito->setInitGuess(init_guess);
    ito->setTStep(T_STEP);
    ito->attachDE(black_scholes);
    ito->integrate(N_STEPS);
    ito->plot("Ito integral - simplified black scholes");

    delete _f, _g;
    delete dW;
    delete black_scholes;
    delete ito;
}
