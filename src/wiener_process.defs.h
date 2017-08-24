// Implementaion file for implementing the various function described for a
// basic Wiener process in wiener_process.h. The only interesting part here is
// the ability to plot the simulated Wiener process upto any any point
//
// Author: Archit Gupta
// Date: Jan 02, 2017

#include <sstream>

// Defining the static const members of the class (For non integer/enum types,
// this cannot be done inside the class definition for some reason.

template<class OP_TYPE>
const std::string WienerProcess<OP_TYPE>::PLOT_FNAME = "data.tmp";

template<class OP_TYPE>
const OP_TYPE WienerProcess<OP_TYPE>::ZERO = OP_TYPE();

template<class OP_TYPE>
const int WienerProcess<OP_TYPE>::N_DOTS = 10;

// Implementation of the class functions

template<class OP_TYPE>
WienerProcess<OP_TYPE>::WienerProcess(double _t_step) {
    t_step = _t_step;
    OP_TYPE op = ZERO;
    op.initializeDistro(0.0, _t_step);
    s_vals.push_back(op);
    n_steps = 1;
}

template<class OP_TYPE>
WienerProcess<OP_TYPE>::WienerProcess() {
    t_step = 0.0;
    n_steps = 0;
}

template<class OP_TYPE>
void WienerProcess<OP_TYPE>::setNSteps(int _n_steps) {
    n_steps = _n_steps;
}

template<class OP_TYPE>
void WienerProcess<OP_TYPE>::setTStep(double _t_step) {
    t_step = _t_step;
}

template <class OP_TYPE>
void WienerProcess<OP_TYPE>::stepUniform(int _n_steps) {
    std::cout << "ERROR: Uniform Stepping undefined for class Wiener Process.";
    std::cout << std::endl << "Maybe you wanted to use Brownian Motion instead?" << std::endl;
}

template<class OP_TYPE>
void WienerProcess<OP_TYPE>::plot(std::string title) {
    std::cout << "Plotting simulation data ...\n";
    std::vector<std::string> commands_for_GnuPlot = {
        "set grid\n",
        "set title \"", title, " \"\n", 
        "set xlabel \"Time (in s)\"\n",
        "set ylabel \"W(t)\"\n",
    };
    std::fstream data;
    data.open(PLOT_FNAME, std::fstream::out);
    data.precision(3);

    int n_paths = s_vals.begin()->getNPaths();
    std::stringstream conv;
    // for (int i = 1; i < 1+n_paths; i++) {
    //     conv << "plot '" << PLOT_FNAME << "' using 0:" <<  i << " with linespoints notitle\n";
    //     commands_for_GnuPlot.push_back(conv.str());
    // }
    conv << "plot for [col=2:" << 1+n_paths << "]'" << PLOT_FNAME << "' using 1:col with linespoints notitle" << std::endl;
    commands_for_GnuPlot.push_back(conv.str());

    FILE* gnuplot_pipe = popen("gnuplot -persistent", "w");
    double t_val = 0.0;
    for (typename std::vector<OP_TYPE>::const_iterator it = s_vals.begin();
        it != s_vals.end(); it++) {
        data << t_val << " " << (it->toStr()) << "\n";
        t_val = t_val + t_step;
    }
    data.close();

    for (std::vector<std::string>::const_iterator it = commands_for_GnuPlot.begin();
            it != commands_for_GnuPlot.end(); it++) {
        fprintf(gnuplot_pipe, "%s", it->c_str());  
    }
}
