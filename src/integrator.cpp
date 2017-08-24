#include "integrator.h"
#include "vec_ops.h"
#include "SDE.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>

// Helper Utilities go first

void Integrator::plot() {
    plot("Time-Integration plot");
}

void Integrator::plot(const std::string &title) {
    const std::string PLOT_FNAME = title + "_integration_data.tmp";
    std::cout << "Plotting time-integration data ...\n";
    std::vector<std::string> commands_for_GnuPlot = {
        "set grid\n",
        "set title \"", title, " \"\n", 
        "set xlabel \"Time (in s)\"\n",
        "set ylabel \"W(t)\"\n",
    };
    std::fstream data;
    data.open(PLOT_FNAME, std::fstream::out);
    data.precision(3);

    std::stringstream conv;
    conv << "plot for [col=2:" << 1 + integral.begin()->size() << "]'" << PLOT_FNAME;
    conv << "'using 1:col with linespoints notitle" << std::endl;

    commands_for_GnuPlot.push_back(conv.str());

    FILE* gnuplot_pipe = popen("gnuplot -persistent", "w");
    double t_val = t_init;
    for (std::vector<std::vector<double> >::const_iterator it = integral.begin(); it != integral.end(); it++) {
        data << t_val << " ";
        for (std::vector<double>::const_iterator jt = it->begin(); jt != it->end(); jt++) {
            data << *jt << " ";
        }
        data << std::endl;
        t_val += t_step;
    }
    data.close();

    // TODO: Complete this using code from WienerProcess.h. It would be better
    // to create a new helper class for taking care of this stuff instead of
    // copying this all over the place
    for (std::vector<std::string>::iterator it = commands_for_GnuPlot.begin(); 
            it != commands_for_GnuPlot.end(); it++) {
        fprintf(gnuplot_pipe, "%s", it->c_str());
    }
}

Integrator::Integrator() {
    t_step = DEFAULT_TIME_STEP;
    t_init = (double) 0.0;
    init_guess = std::vector<double>(0);
}

Integrator::~Integrator() {
    integral.clear();
    init_guess.clear();
}

Integrator::Integrator(double _t_step, const std::vector<double> &_init_guess, double _t_init) {
    t_step = _t_step;
    t_init = _t_init;
    init_guess = init_guess;
}

void Integrator::checkInitGuessSize() {
    // Make sure that the initial guess has been set appropriately
    if( de->getNUnks() != init_guess.size() ) {
        std::cout << "WARNING: Initial guess sized inappropriately. Starting with all zeros" << std::endl;
        init_guess.assign(de->getNUnks(), (double) 0.0);
    }
}

// Functions described for the Forward Euler integration method

ForwardEuler::ForwardEuler() : Integrator() {
#ifdef __DEBUG__
    std::cout << "Initializing empty FE class object @ " << this << std::endl;
#endif
}

ForwardEuler::ForwardEuler(double _t_step, const std::vector<double> &_init_guess, double _t_init) : Integrator(_t_step, _init_guess, _t_init) {
#ifdef __DEBUG__
    std::cout << "Initialized FE class object @ " << this << std::endl;
    std::cout << "With t_step = " << t_step << " t_init = " << t_init << std::endl;
#endif
}

ForwardEuler::~ForwardEuler() {
#ifdef __DEBUG__
    std::cout << "Freeing up FE Object @ " << this << std::endl;
#endif
}

void ForwardEuler::integrate (int n_steps) {
    checkInitGuessSize();
    integral.push_back(init_guess);
    std::cout << "Running FE for " << n_steps << " steps ..." << std::endl;
    std::cout << "Time step for integration (constant) " << t_step << std::endl;
    std::vector<double> sol = integral.back();
    std::vector<double> update(init_guess);

    double t = t_init; 
    while (n_steps-- > 0) {
        update = ( de->operator()(sol, t) * t_step );    
        sol += update;
        integral.push_back(sol);
        t += t_step;
    }
}

// Function described for the Backward Euler integration method

BackwardEuler::BackwardEuler() : Integrator() {
#ifdef __DEBUG__
    std::cout << "Initializing empty BE class object @ " << this << std::endl;
#endif
}

BackwardEuler::BackwardEuler(double _t_step, const std::vector<double> &_init_guess, double _t_init) : Integrator(_t_step, _init_guess, _t_init) {
#ifdef __DEBUG__
    std::cout << "Initialized BE class object @ " << this << std::endl;
    std::cout << "With t_step = " << t_step << " t_init = " << t_init << std::endl;
#endif
}

void BackwardEuler::integrate (int n_steps) {
    integral.push_back(init_guess);
    std::cout << "ERROR: BE is not supported at the moment!\n";
}

BackwardEuler::~BackwardEuler() {
#ifdef __DEBUG__
    std::cout << "Freeing up BE Object @ " << this << std::endl;
#endif
}

// Functions described for the trapezoidal integration method

Trapezoidal::Trapezoidal() : Integrator() {
#ifdef __DEBUG__
    std::cout << "Initializing empty TRAP class object @ " << this << std::endl;
#endif
}

Trapezoidal::Trapezoidal(double _t_step, const std::vector<double> &_init_guess, double _t_init) : Integrator(_t_step, _init_guess, _t_init) {
#ifdef __DEBUG__
    std::cout << "Initialized BE class object @ " << this << std::endl;
    std::cout << "With t_step = " << t_step << " t_init = " << t_init << std::endl;
#endif
}

void Trapezoidal::integrate (int n_steps) {
    integral.push_back(init_guess);
    std::cout << "ERROR: TRAP is not supported at the moment!\n";
}

Trapezoidal::~Trapezoidal() {
#ifdef __DEBUG__
    std::cout << "Freeing up TRAP Object @ " << this << std::endl;
#endif
}
