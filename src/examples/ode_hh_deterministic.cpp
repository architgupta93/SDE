#include "SDE.h"
#include "integrator.h"
#include "equation_system.h"
#include "vec_ops.h"
#include "models/ModspecModel.h"
#include "models/HodgkinHuxley.h"

int main() {
    ModspecModel *hh_model = new HodgkinHuxley__Det();
    DiffEqn *hh_ode = nn_dae::generateDE(hh_model);

    const int n_HH_unks = hh_model->n_unks;
    const double T_STEP = 4e-3;
    const int N_STEPS = 20000;

    // Creating an initial guess... It consists of 
    // 0) Membrane Potential (Set at the resting potential)
    // 1) Conductivity factor n -
    // 2) Conductivity factor m | - all set to 0 initially
    // 3) Conductivity factor h -
    std::vector<double> hh_init_guess = {-0.065, 0.1, 1.0, 1.0};

    ForwardEuler* fe = new ForwardEuler();
    fe->setInitGuess(hh_init_guess);
    fe->setTStep(T_STEP);
    fe->attachDE(hh_ode);
    fe->integrate(N_STEPS);
    fe->plot("HH Neuron simulation");

    delete hh_model;
    delete hh_ode;
    delete fe;
}
