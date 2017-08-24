#ifndef __INTEGRATOR_H__
#define __INTEGRATOR_H__

// Integrator is an abstract class. It is not really supposed to do anything. It
// only provides an interface for various different integration methods
// (Riemann, Stochastic etc.)

#include "SDE.h"
#include <vector>
#include <cassert>

#define DEFAULT_TIME_STEP 2e-12

class Integrator {
    protected:
        DiffEqn *de;
        std::vector<std::vector<double> > integral;
        double t_step;
        std::vector<double> init_guess;
        double t_init;
        void checkInitGuessSize();

    public:
        Integrator();
        Integrator(double _t_step, const std::vector<double> &_init_guess, double _t_init);
        virtual ~Integrator();

        // General Set/Get Functions for changing simulation parameters
        void attachDE(DiffEqn *eq) { de = eq; };
        void setInitGuess(const std::vector<double> &_init_guess) { init_guess = _init_guess; }
        void setTInit(double _t_init) { t_init = _t_init; }
        void setTStep(double _t_step) { t_step = _t_step; }
        std::vector<std::vector<double> > getSolution() const { return integral; }

        // Abstract function definitions that depend entirely on the integration
        // method being used
        virtual void integrate(int n_steps) = 0;

        // Other helper functions which will probably be removed in the future
        // when we can think of a better way of doing these tasks for a generic
        // class
        void plot(const std::string &title);
        void plot();
};

class ForwardEuler : public Integrator {
    public:
        ForwardEuler();
        ForwardEuler(double _t_step, const std::vector<double> &_init_guess, double _t_init);
        ~ForwardEuler();
        void integrate(int n_steps);
};

class BackwardEuler : public Integrator {
    public:
        BackwardEuler();
        BackwardEuler(double _t_step, const std::vector<double> &_init_guess, double _t_init);
        ~BackwardEuler();
        void integrate(int n_steps);
};

class Trapezoidal : public Integrator {
    public:
        Trapezoidal();
        Trapezoidal(double _t_step, const std::vector<double> &_init_guess, double _t_init);
        ~Trapezoidal();
        void integrate(int n_steps);
};

#endif
