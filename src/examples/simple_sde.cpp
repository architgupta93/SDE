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

// We will implement a simple function that takes in 2 input and gives out 2
// outputs. Since all the interfaces have already been set up, if the whole
// program has been designed well, this is the only non-trivial code that the
// user should be expected to write (and overload the () operator

class SimpleFun : public FunHandle {
    public:
        SimpleFun() : FunHandle(2, 2) {
        #ifdef  __DEBUG__
            std::cout << "Instantiating SimpleFun @ " << this << " with interface FunHandle" << std::endl; 
        #endif
        }

        ~SimpleFun() {

        }

        // In this case, the function takes in 2 values x1, x2 and produces [
        // sin(x1) + cos(x2); cos(x1) - sin(x2) ]
        std::vector<double> operator() (const std::vector<double> &v_in) {
        #ifdef __PRINT_DETAILS__
            std::cout << "Function Handle @ " << this <<  " called." << std::endl;
            std::cout << "Expecting " << n_in << " inputs, got " << v_in.size() << std::endl;
        #endif
            assert ( (unsigned int) v_in.size() == n_in );
            assert ( (unsigned int) calc.size() == n_out );
            calc[0] = sin(v_in[0]) + cos(v_in[1]);
            calc[1] = cos(v_in[0]) - sin(v_in[1]);
        #ifdef __PRINT_DETAILS__
            std::cout << "Calculated: (" << calc[0] << ", " << calc[1] << ")" << std::endl;
        #endif
            return calc;
        };
};

int main() {
    // Overall simulation parameters
    const int n_args = 2;
    const double T_STEP = pow(2, -8);
    const double STDDEV = sqrt( T_STEP );
    const int N_STEPS = pow(2, 8);

    ZeroFun<2,2> *no_fun = new ZeroFun<2,2>();
    SimpleFun *simple_fun = new SimpleFun();
    std::vector<double> init_guess(n_args, 1.0);
    
    // Simulating an ODE
    ODE *simple_ode = new ODE(simple_fun);
    ForwardEuler *fe = new ForwardEuler();  

    fe->setInitGuess(init_guess);
    fe->setTStep(T_STEP);
    fe->attachDE(simple_ode);
    fe->integrate(N_STEPS);
    fe->plot("Forward Euler - simple ODE");

    // Simulating and SODE with simple_fun as g (and an empty f)
    MultipathRV *dW = new GaussianMultipathRV(1, 0, STDDEV);
    SODE *simple_sode = new SODE(no_fun, simple_fun, dW);
    ItoIntegrator *ito = new ItoIntegrator();

    ito->setInitGuess(init_guess);
    ito->setTStep(T_STEP);
    ito->attachDE(simple_sode);
    ito->integrate(N_STEPS);
    ito->plot("Ito integral - simple SODE");

    delete fe;
    delete dW;
    delete ito;
    delete no_fun;
    delete simple_fun;
    delete simple_ode;
    delete simple_sode;
}
