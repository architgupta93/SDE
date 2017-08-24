#include "SDE.h"
#include "vec_ops.h"
#include "multipath_rv.h"
#include "gaussian_multipath_rv.h"
#include <iostream>
#include <vector>
#include <cassert>

//  Function definitions for Function Handle class
FunHandle::FunHandle(unsigned int _n_in, unsigned int _n_out) : n_in(_n_in), n_out(_n_out) {
#ifdef __DEBUG__
    std::cout << "Creating new f_handle @ " << this;
    std::cout << " (n_in = " << n_in << " n_out = " << n_out  << ")" << std::endl;
#endif
    calc = std::vector<double>(n_out, (double) 0.0);
}

FunHandle::FunHandle(const FunHandle &rhs) : n_in(rhs.n_in), n_out(rhs.n_out) {
#ifdef __DEBUG__
    std::cout << "Evoking copy constructor from the interface class. ";
    std::cout << " Copying " << rhs.calc.size() << " elements from base f_handle" << std::endl;
#endif
    assert(rhs.calc.size() == n_out);
    for (std::vector<double>::const_iterator it = rhs.calc.begin(); it != rhs.calc.end(); it++) {
        this->calc.push_back(*it);
    }
}

// void FunHandle::swap(const FunHandle &rhs) {
//     // TODO
// }

// FunHandle& FunHandle::operator = (const FunHandle &rhs) {
//     FunHandle tmp = FunHandle(rhs);
//     this->swap(tmp);
// #ifdef __DEBUG__
//     std::cout << "Equal-To operator called..." << std::endl;
//     std::cout << "RHS: n_in = " << rhs.n_in << " n_out = " << rhs.n_out << std::endl;
//     std::cout << "LHS: n_in = " << this->n_in << " n_out = " << this->n_out << std::endl;
// #endif
//     return *this;
// }

FunHandle::~FunHandle() {
    calc.clear();
}

// Function description for the abstract Differential Equation class

DiffEqn::DiffEqn(FunHandle *_f) : n_unks(_f->n_in), n_eqns(_f->n_out) {
    f = _f;
}

DiffEqn::DiffEqn(unsigned int _n_unks, unsigned int _n_eqns) : n_unks(_n_unks), n_eqns(_n_eqns) {
    // f = new FunHandle(_n_unks, _n_eqns);
    f = NULL;
}

DiffEqn::~DiffEqn() {
#ifdef __DEBUG__
    std::cout << "CLEAN UP: Deleting Differential Equation." << std::endl;
    std::cout << "f_handle @ " << f << " cleared!" << std::endl;
#endif
}

std::vector<double> DiffEqn::getG(const std::vector<double> &v_in, double t) {
#ifdef __DEBUG__
    std::cout << "ERROR: Inappropriate use of abstract class DiffEqn" << std::endl;
#endif
    return std::vector<double>(0, 0);
}

std::vector<double> DiffEqn::getDW(double dt) {
#ifdef __DEBUG__
    std::cout << "ERROR: Inappropriate use of abstract class DiffEqn" << std::endl;
#endif
    return std::vector<double>(0, 0);
}

// Function description for the simple ODE class... We might need a separate
// class to describe DAE(s)

ODE::ODE(FunHandle* _f) : DiffEqn(_f) {
#ifdef __DEBUG__
    std::cout << "Creating new ODE object @ " << this << " from f_handle @ " << f << std::endl;
#endif
    // Nothing to be done specifically for an ODE
}

ODE::ODE(unsigned int _n_unks, unsigned int _n_eqns) : DiffEqn(_n_unks, _n_eqns) {
#ifdef __DEBUG__
    std::cout << "Creating new ODE Object @ " << this << std::endl;
    std::cout << "WARNING: Function Handle for f not initialized." << std::endl;
#endif
    // Again, nothing specific needs to be done for an ODE
}

ODE::~ODE() {
#ifdef __DEBUG__
    std::cout << "CLEAN UP: Deleting ODE Object @ !" << this << std::endl;
#endif
}

std::vector<double> ODE::operator() (const std::vector<double> &v_in, double t) {
#ifdef __PRINT_DETAILS__
    std::cout << "Evaluating ODE " << this << " @ time: " << t << std::endl;
#endif
    return f->operator()(v_in);
}

// Function description for the Stochastic (ordinary) differential equations
// class. Extending this to the Stochastic differential (algebriac) equations
// should not be difficult in practice (theory is a different issue)

SODE::SODE(FunHandle* _f, FunHandle* _g, MultipathRV* _dW) : ODE(_f) {
    g = _g;
    dW = _dW;

#ifdef __DEBUG__
    std::cout << "Verfying that IO behavior for f, g is sane" << std::endl;
    std::cout << "f: <" << f->n_in << ", " << f->n_out << ">, and ";
    std::cout << "g: <" << g->n_in << ", " << g->n_out << ">" << std::endl;

    assert( g->n_in == f->n_in);
    assert( g->n_out == f->n_out);

    std::cout << "Initializing Stochastic Differential Equation Object @ " << this << std::endl;
    std::cout << "Functions initialized: f@ " << f << " g@ "<< g << ", RV dW initialized @ " << dW << std::endl;
#endif
}

SODE::SODE(unsigned int _n_unks, unsigned int _n_eqns) : ODE(_n_unks, _n_eqns) {
    g = NULL;
    dW = NULL;
#ifdef __DEBUG__
    std::cout << "Initializing Stochastic Differential Equation Object @ " << this << std::endl;
    std::cout << "WARNING: Handles f, g and dW not initilized" << std::endl;
#endif
}

SODE::~SODE() {
#ifdef __DEBUG__
    std::cout << "CLEAN UP: Deleting SODE Object @ !" << this << std::endl;
#endif
}

std::vector<double> SODE::getG (const std::vector<double> &v_in, double t) {
#ifdef __PRINT_DETAILS__
    std::cout << "Evaluating SODE " << this << " @ time: " << t << std::endl;
#endif
    return g->operator()(v_in);
}

std::vector<double> SODE::getDW (double dt) {
    return dW->draw(); 
}
