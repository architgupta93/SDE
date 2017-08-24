#include "common_functions.h"
#include "SDE.h"
#include <vector>
#include <math>
#include <cassert>
#include <iostream>

// Step Function
StepFun::StepFun() : FunHandle(1,1) {
#ifdef __DEBUG__
    std::cout << "Initialized Step Function @ " << this << " with default parameters." << std::endl;
#endif
    parms.reserve(__StepFun_n_parms);
    parms.push_back(0.0);   // Default value for __StepFun_th, parms[0]
    parms.push_back(1.0);   // Default value for __StepFun_h, parms[1]
}

StepFun::StepFun(const std::vector<double> &in_parms) : FunHandle(1, 1, in_parms) {
#ifdef __DEBUG__
    std::cout << "Initialized Step Function @ " << this << " with parameters: " << std::endl;
    std::cout << " T_threshold - " << __StepFun_th << std::endl;
    std::cout << " Step Height - " << __StepFun_h << std::endl;
#endif
}

StepFun::~StepFun() {
#ifdef __DEBUG__
    std::cout << "Cleared Step Function @ " << this << std::endl;
#endif
}

std::vector<double> StepFun::operator() (const std::vector<double> &v_in) {

}

// Pulse Function
PulseFun::PulseFun() : FunHandle(1,1)  {
#ifdef __DEBUG__
    std::cout << "Initialized Pulse Function @ " << this << " with default parameters." << std::endl;
#endif
    parms.reserve(__PulseFun__n_parms);
    parms.push_back(0.0);   // Default value for __PulseFun_on_edge
    parms.push_back(1e-6);  // Default value for __PulseFun_rise_time
    parms.push_back(1e-3);  // Default value for __PulseFun_on_time
    parms.push_back(1e-6);  // Default value for __PulseFun__fall_time
}

PulseFun::PulseFun(const std::vector<double> &in_parms) : FunHandle(1, 1, in_parms) {

}

PulseFun::~PulseFun() {
#ifdef __DEBUG__
    std::cout << "Cleared Pulse Function @ " << this << std::endl;
#endif
}

std::vector<double> PulseFun::operator() (const std::vector<double> &v_in) {

}

// Periodic Pulse Function
PeriodicPulseFun::PeriodicPulseFun() : FunHandle(1,1)  {
#ifdef __DEBUG__
    std::cout << "Initialized Periodic Pulse Function @ " << this << " with default parameters." << std::endl;
#endif
    parms.reserve(__PeriodicPulseFun_n_parms);
    parms.push_back(0.0);   // Default value for __PeriodicPulseFun_delay
    parms.push_back(1e-3);  // Default value for __PeriodicPulseFun_duty_cycle
    parms.push_back(0.50);  // Default value for __PeriodicPulseFun_period
}

PeriodicPulseFun::PeriodicPulseFun(const std::vector<double> &in_parms) : FunHandle(1, 1, in_parms) {

}

PeriodicPulseFun::~PeriodicPulseFun() {
#ifdef __DEBUG__
    std::cout << "Cleared Periodic Pulse Function @ " << this << std::endl;
#endif
}

std::vector<double> PeriodicPulseFun::operator() (const std::vector<double> &v_in) {

}

// Sine Function
SineFun::SineFun() : FunHandle(1,1) {
#ifdef __DEBUG__
    std::cout << "Initialized Sine Function @ " << this << " with default parameters." << std::endl;
#endif
    parms.reserve(__SineFunc__n_parms);
    parms.push_back(0.0);   // Default value for __SineFunc__init_phase
    parms.push_back(1e-3);  // Default value for __SineFunc__period
}

SineFun::SineFun(const std::vector<double> &in_parms) : FunHandle(1, 1, in_parms) {

}

SineFun::~SineFun() {
#ifdef __DEBUG__
    std::cout << "Cleared Sine Function @ " << this << std::endl;
#endif
}

std::vector<double> SineFun::operator() (const std::vector<double> &v_in) {

}
