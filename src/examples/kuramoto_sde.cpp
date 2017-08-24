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

#define N_OSCILLATORS 4
#define PARM__K 0.15

class KuramotoFun : public FunHandle {
    private:
        std::vector<double> freqs;

    public:
        KuramotoFun(double common_freq) : FunHandle(N_OSCILLATORS, N_OSCILLATORS) {
            #ifdef __DEBUG__
                std::cout << "Instantiating Kuramoto Function @ " << this << " with interface FunHandle" << std::endl; 
            #endif
            freqs = std::vector<double>(N_OSCILLATORS, common_freq);
        }

        KuramotoFun(std::vector<double> common_freqs) : FunHandle(N_OSCILLATORS, N_OSCILLATORS) {
            #ifdef __DEBUG__
                std::cout << "Instantiating Kuramoto Function @ " << this << " with interface FunHandle" << std::endl; 
            #endif
            freqs = common_freqs;
        }

        ~KuramotoFun() {

        }

        // In this case, the function takes N_OSCILLATORS values and computes a
        // vector of size N_OSCILLATORS values via the function described here
        std::vector<double> operator() (const std::vector<double> &v_in) {
        #ifdef __PRINT_DETAILS__
            std::cout << "Function Handle @ " << this << " called." << std::endl;
            std::cout << "Expecting " << n_in << " inputs, got " << v_in.size() << std::endl;
        #endif
            assert( (unsigned int) v_in.size() == n_in );
            assert( (unsigned int) calc.size() == n_out );
            for (int osc_in = 0; osc_in < N_OSCILLATORS; osc_in++) 
            {
                calc[osc_in] = freqs[osc_in]; 
                for (int cont_in = 0; cont_in < N_OSCILLATORS; cont_in++)
                {
                    calc[osc_in] += (PARM__K/(M_PI*N_OSCILLATORS))*sin(M_PI*(v_in[osc_in] - v_in[cont_in]));
                }
            }
            return calc;
        }
};

int main() {
    const double T_STEP = pow(2, -10);
    const double STDDEV = sqrt(T_STEP);
    const int N_STEPS = pow(2, 15);

    // Parameters requried for describing the SDE
    double mu = 1.0;
    double noise_std = 0.1;
    // double osc_freq = pow(2,6);
    double osc_freq = 0.0;

    KuramotoFun *_f = new KuramotoFun(osc_freq);
    ConstFun<N_OSCILLATORS, N_OSCILLATORS> *_g = new ConstFun<N_OSCILLATORS,N_OSCILLATORS>(noise_std);
    MultipathRV *dW = new GaussianMultipathRV(N_OSCILLATORS, 0, STDDEV);
    SODE *kuramoto = new SODE(_f, _g, dW);
    ItoIntegrator *ito = new ItoIntegrator();

    // Generate initial guess and run the simulation
    std::vector<double> init_guess = vector_ops::randomVector(N_OSCILLATORS, 0, 1.0);
    ito->setInitGuess(init_guess);
    ito->setTStep(T_STEP);
    ito->attachDE(kuramoto);
    ito->integrate(N_STEPS);
    ito->plot("Kuramoto SDE");
    
    // Clearning up the allocated memory
    delete _f, _g;
    delete dW;
    delete kuramoto;
    delete ito;
}
