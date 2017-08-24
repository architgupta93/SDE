#ifndef __STOCHASTIC_INTEGRATOR_H__
#define __STOCHASTIC_INTEGRATOR_H__

#include "SDE.h"
#include "integrator.h"
#include "wiener_process.h"
#include <vector>

class StochasticIntegrator : public Integrator {
    protected:
        WienerProcess<double> dw;
        virtual std::vector<double> getFVal(const std::vector<double> &x_in, double _t_step) = 0;

    public:
        StochasticIntegrator();
        StochasticIntegrator(double _t_step, const std::vector<double> &_init_guess, double _t_init);
        virtual ~StochasticIntegrator();
};

#endif
