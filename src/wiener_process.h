// Header file defining the class required for a Wiener process
// The naming convention is as follows (for readability):
//      t_varname -> time_varname
//      n_varname -> number of varname
//      m_varname -> my varname (used to identify private variables)
//      s_varname -> simulated varname
//      r_varname -> random varname
//       _varname -> Used in an argument if the class has a member varname
// Author: Archit Gupta
// Date: Jan 02, 2017

#ifndef __WIENER_PROCESS_H__
#define __WIENER_PROCESS_H__

#include <iostream>
#include <fstream>
#include <random>
#include <vector>
#include <string>
#include <stdlib.h>

template <class OP_TYPE> class WienerProcess {
    private:
        static const std::string PLOT_FNAME;

    protected:
        static const int N_DOTS;
        static const OP_TYPE ZERO;
        std::vector<OP_TYPE> s_vals;
        double t_step;
        int n_steps;

    public:
        // Getting and setting simulation parameters
        int getNSteps() const { return n_steps; };
        OP_TYPE getTStep() const { return t_step; };
        void setNSteps(int _n_steps);
        void setTStep(double _t_step);

        // Main functions for interacting with the model.. time stepping
        WienerProcess();
        WienerProcess(double _t_step);
        void stepUniform(int _n_steps);
        void plot(std::string title);
};

#include "wiener_process.defs.h"

#endif
