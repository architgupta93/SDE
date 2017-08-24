#ifndef __COMMON_FUNCTIONS_H__
#define __COMMON_FUNCTIONS_H__

#include "SDE.h"
#include <vector>
#include <math>
#include <cassert>
#include <iostream>

#define __StepFun_n_parms 2
#define __StepFun_th parms[0]
#define __StepFun_h parms[1]
class StepFun : public FunHandle {
    public:
        StepFun();
        StepFun(const std::vector<double> &in_parms);
        ~StepFun();
        std::vector<double> operator() (const std::vector<double> &v_in);
}; 

#define __PulseFun_n_parms 4
#define __PulseFun_on_edge parms[0]
#define __PulseFun_rise_time parms[1]
#define __PulseFun_on_time parms[2]
#define __PulseFun__fall_time parms[3]
class PulseFun : public FunHandle {
    public:
        PulseFun();
        PulseFun(const std::vector<double> &in_parms);
        ~PulseFun();
        std::vector<double> operator() (const std::vector<double> &v_in);
};

#define __PeriodicPulseFun_n_parms 3
#define __PeriodicPulseFun_delay parms[0]
#define __PeriodicPulseFun_period parms[1]
#define __PeriodicPulseFun_duty_cycle parms[2]
class PeriodicPulseFun : public FunHandle {
    public:
        PeriodicPulseFun();
        PeriodicPulseFun(const std::vector<double> &in_parms):
        ~PeriodicPulseFun();
        std::vector<double> operator() (const std::vector<double> &v_in);
};

#define __SineFunc__n_parms 2
#define __SineFunc__init_phase parms[0]
#define __SineFunc__period parms[1]
class SineFun : public FunHandle {
    public:
        SineFun();
        SineFun(const std::vector<double> &in_parms);
        ~SineFun();
        std::vector<double> operator() (const std::vector<double> &v_in);
};

#endif
