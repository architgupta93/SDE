#ifndef __SDE_H__
#define __SDE_H__

#include <cassert>
#include <vector>
#include "vec_ops.h"
#include "multipath_rv.h"
#include "gaussian_multipath_rv.h"

class FunHandle {
    protected:
        std::vector<double> calc;

    public:
        FunHandle();
        FunHandle(unsigned int _n_in, unsigned int _n_out);
        FunHandle(const FunHandle &rhs);
        virtual ~FunHandle();
        const unsigned int n_in;
        const unsigned int n_out;
        virtual std::vector<double> operator() (const std::vector<double> &v_in) = 0;
        // FunHandle& operator = (const FunHandle &rhs);
        // void swap(const FunHandle &rhs);
};

// Template classes for some commonly used function classes. Since the classes
// have been templated, it is best if we describe the entire class here instead
// of putting it in another header file which would have to compiled later on

template <int n_args_in, int n_args_out>
class ConstFun : public FunHandle {
    protected:
        double lambda;

    public:
        ConstFun(double _lambda) : FunHandle(n_args_in, n_args_out) {
        #ifdef __DEBUG__
            std::cout << "Instantiating Constant function @ " << this;
            std::cout << " with <" << n_args_in  << ", " << n_args_out << ">" << std::endl;
        #endif
            lambda = _lambda;
            calc = std::vector<double>(n_out, lambda);
        }
               
        ~ConstFun() {
        #ifdef __DEBUG__
            std::cout << "CLEAN UP: Cleaning up f_handle @ " <<  this << std::endl;
        #endif
        } 

        // This function just takes in a vector of n_in inputs and returns an empty
        // vector on n_out outputs.. ZeroFun -_-
        std::vector<double> operator() (const std::vector<double> &v_in) {
            assert( v_in.size() == n_args_in );
            return calc;
        }
};

template <int n_args_in, int n_args_out>
class ZeroFun : public ConstFun<n_args_in, n_args_out> {
    public:
        ZeroFun() : ConstFun<n_args_in, n_args_out>(0.0) {

        }
               
        ~ZeroFun() {

        } 
};

template <int n_args>
class FxIsX : public FunHandle {
    private:
        double lambda;

    public:
        FxIsX(double _lambda) : FunHandle(n_args, n_args) {
        #ifdef __DEBUG__
            std::cout << "Instantiating function f(x) = lx @ " << this; 
            std::cout << " with <" << n_in  << ", " << n_out << ">" << std::endl;
        #endif
            lambda = _lambda;
        }

        ~FxIsX() {
        #ifdef __DEBUG__
            std::cout << "CLEAN UP: Cleaning up f_handle @ " <<  this << std::endl;
        #endif
        }

        std::vector<double> operator() (const std::vector<double> &v_in) {
            assert( v_in.size() == n_args );
            std::vector<double> result = v_in * lambda;
        #ifdef __PRINT_DETAILS__
            std::cout << "Computed linear function: ";
            nn_utils::printV(result);
        #endif
            return result;
        }
};

// Class defining various kinds of differential equations: ODE/SDE... In the
// future, we also intend to add DAE/SDE classes.
class DiffEqn { // Abstract class for providing an interface for all the
                // different kinds of differential equations
    protected:
        const unsigned int n_unks;
        const unsigned int n_eqns;
    public:
        DiffEqn(FunHandle* _f);
        DiffEqn(unsigned int _n_unks, unsigned int _n_eqns);
        unsigned int getNUnks() { return n_unks; }
        unsigned int getNEqns() { return n_eqns; }
        virtual ~DiffEqn();
        virtual std::vector<double> operator() (const std::vector<double> &v_in, double t) = 0;
        virtual std::vector<double> getG(const std::vector<double> &v_in, double t);
        virtual std::vector<double> getDW(double dt);
        FunHandle* f;
};

class ODE : public DiffEqn {
    private:

    protected:

    public:
        ODE(FunHandle *_f);
        ODE(unsigned int _n_unks, unsigned int _n_eqns);
        // TODO: Copy constructor might be needed sometime in the future
        std::vector<double> operator() (const std::vector<double> &v_in, double t);
        ~ODE();
};

class SODE : public ODE {
    protected:

    public:
        FunHandle *g;
        MultipathRV *dW;
        SODE(FunHandle* _f, FunHandle* _g, MultipathRV* _dW);
        SODE(unsigned int _n_unks, unsigned int _n_eqns);
        // TODO: Copy constructor might be needed some time in the future
        std::vector<double> getG(const std::vector<double> &v_in, double t);
        std::vector<double> getDW(double dt);
        ~SODE();
};

#endif
