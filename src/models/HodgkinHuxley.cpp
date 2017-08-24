#include "HodgkinHuxley.h"
#include "ModspecModel.h"
#include "vec_ops.h"
#include <vector>
#include <iostream>
#include <string>
#include <math.h>

// The main function handle for describing the rate equations for a
// Hodgkin-Huxley neuron

// Defining the static quantities for the class
const int HHVmNMH::n_args_in = __HH__N_UNKS;
const int HHVmNMH::n_args_out = __HH__N_UNKS;
const std::vector<double> HHVmNMH::d_parms = {
    1.0,       // Area     (in cm^2)
    0.3,       // Gl       (leakage conductivity in S/cm^2)
    36,      // TauK     (in S/ion_channel)
    120,      // TauNa    (in S/ion_channel)
    1.0,       // NK       (#K+ channels/cm^2)
    1.0,      // NNa      (#Na+ channels/cm^2)
    -54.387e-3,    // El       (Ligand resting potential)
    -77.0e-3,       // EK       (K+ resting potential)
    50.0e-3,     // ENa      (Na+ resting potential)
    1.0        // C        (Membrance Cap F/cm^2)
};

HHVmNMH::HHVmNMH() : FunHandle( HHVmNMH::n_args_in, HHVmNMH::n_args_out ) {
    #ifdef __DEBUG__
        std::cout << "WARNING: Parameters for HH Neuron not set. Using defaults." << std::endl;
    #endif
    parms = HHVmNMH::d_parms;
    assert (parms.size() == __HH__N_PARMS);
}

HHVmNMH::HHVmNMH(const std::vector<double> &in_parms) : FunHandle( HHVmNMH::n_args_in, HHVmNMH::n_args_out ) {
    parms = in_parms;
    assert (parms.size() == __HH__N_PARMS);
}

HHVmNMH::~HHVmNMH() {
    parms.clear();
}

std::vector<double> HHVmNMH::operator() (const std::vector<double> &v_in) {
#ifdef __PRINT_DETAILS__
    std::cout << "Rate equations called for HH Neuron with Vm = " << v_in[0] << std::endl;
#endif
    // First, calculate the __alpha and __beta terms for n, h and m
    double __alpha__n = ( 0.01 * ( __HH__Vm * 1e3 + 55.0 ) ) / 
        ( 1.0 - exp( -(__HH__Vm * 1e3 + 55.0 ) / 10.0 ) );
    double __beta__n = 0.125 * exp( -( __HH__Vm * 1e3 + 65.0 ) / 80.0 );

    double __alpha__h = 0.07 * exp( -( __HH__Vm * 1e3 + 65.0 ) / 20.0 );
    double __beta__h = 1.0 / ( 1.0 + exp( -(__HH__Vm * 1e3 + 35.0 ) / 10.0 ) );

    double __alpha__m = 0.1 * ( __HH__Vm * 1e3 + 40.0 ) / 
        ( 1.0 - exp( -( __HH__Vm * 1e3 + 40.0 ) / 10.0 ) );
    double __beta__m = 4.0 * exp( -( __HH__Vm * 1e3 + 65.0 ) / 18.0 );

    // Defining K+ / Na+ conductances
    double __HH__GK = __HH__TauK * __HH__NK * pow(__HH__n,4.0);
    double __HH__GNa = __HH__TauNa * __HH__NNa * __HH__h * pow(__HH__m,3.0);

#ifdef __PRINT_DETAILS__
    std::cout << "DEBUG_MSG: Obtained n = " << __HH__n << ", computed: ";
    std::cout << "n^4 = " << pow(__HH__n,4.0) << std::endl;
    std::cout << "DEBUG_MSG: Obtained h = " << __HH__h << std::endl;
    std::cout << "DEBUG_MSG: Obtained m = " << __HH__m << ", computed: ";
    std::cout << "m^3 = " << pow(__HH__m,3.0) << std::endl;
    std::cout << "Computed values: GK = " << __HH__GK << ", GNa = " << __HH__GNa << std::endl;
#endif

    __HH__on = ( __alpha__n * ( 1.0 - __HH__n) ) - ( __beta__n * __HH__n );
    __HH__oh = ( __alpha__h * ( 1.0 - __HH__h) ) - ( __beta__h * __HH__h );
    __HH__om = ( __alpha__m * ( 1.0 - __HH__m) ) - ( __beta__m * __HH__m );
    __HH__oVm = ( - 1.0/ __HH__C ) * (
        __HH__Gl * ( __HH__Vm - __HH__El ) + 
        __HH__GK * ( __HH__Vm - __HH__EK ) +
        __HH__GNa * ( __HH__Vm - __HH__ENa )
        - 2e-2
        ) ;   // TODO: Remove the HACK leakage current from here
#ifdef __PRINT_DETAILS__
    std::cout << "Computed: ";
    nn_utils::printV(calc);
#endif
    return calc;
}

// Definitions for the stochastic function in the Hodgkin Huxley's model for a
// neuron
const int HHStoFun::n_args_in = __HH__N_UNKS;
const int HHStoFun::n_args_out = __HH__N_UNKS;
const std::vector<double> HHStoFun::d_parms = {
    0.0,    // Gl
    0.0,    // TauK
    0.0,    // TauNa
    0.0,    // Nk
    0.0,    // NNa
    0.0,    // El
    0.0,    // Ek
    0.0,    // ENa
    0.0     // C
};

HHStoFun::HHStoFun() : FunHandle( n_args_in, n_args_out ) {

}

HHStoFun::HHStoFun(const std::vector<double> &in_parms) : FunHandle( n_args_in, n_args_out ) {

}

HHStoFun::~HHStoFun() {

}

std::vector<double> HHStoFun::operator() (const std::vector<double> &v_in) {
    // TODO: Fix this... Currently returns a Zero vector
    return std::vector<double>(HHStoFun::n_args_out, 0.0);
}

// The basic Hodgkin-Huxley classes - forked into 2 classes: A class for
// deterministic simulations (HodgkinHuxley__Det) and another class for
// stochastic simulations (HodgkinHuxley__Sto)

HodgkinHuxley__Det::HodgkinHuxley__Det() : ModspecModel(__HH__N_UNKS) {
    det_fun = new HHVmNMH();
}

HodgkinHuxley__Det::HodgkinHuxley__Det(const std::vector<double> &in_parms) :
    ModspecModel(__HH__N_UNKS, in_parms) {
    det_fun = new HHVmNMH(in_parms);
}

HodgkinHuxley__Sto::HodgkinHuxley__Sto() : ModspecModel__Sto(__HH__N_UNKS) {
    det_fun = new HHVmNMH();
    sto_fun = new HHStoFun();
}

HodgkinHuxley__Sto::HodgkinHuxley__Sto(const std::vector<double> &in_parms) :
    ModspecModel__Sto(__HH__N_UNKS, in_parms) {
    det_fun = new HHVmNMH(in_parms);
    sto_fun = new HHStoFun(in_parms);
}

