#ifndef __ITO_INTEGRATOR_H__
#define __ITO_INTEGRATOR_H__

#include "SDE.h"
#include "integrator.h"
#include "stochastic_integrator.h"
#include <vector>

class ItoIntegrator : public StochasticIntegrator {
    private:
        std::vector<double> getFVal(const std::vector<double> &x_in, double _t_step);

    public:
        ItoIntegrator();
        ItoIntegrator(double _t_step, const std::vector<double> &_init_guess, double _t_init);
        ~ItoIntegrator();
        void integrate(int n_steps);
};

#endif
