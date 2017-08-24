#ifndef __HODGKIN_HUXLEY_H__
#define __HODGKIN_HUXLEY_H__

#include "SDE.h"
#include "ModspecModel.h"
#include <vector>
#include <string>
#include <math.h>

// Function handles required by the class

// Some definitions to make the code more readable while avoiding several
// different unnecessary copies of the data at each iteration of the function as
// we expect it to be called several times

#define __HH__N_UNKS 4
#define __HH__N_PARMS 10
#define __HH__Area parms[0]
#define __HH__Gl parms[1]
#define __HH__TauK parms[2]
#define __HH__TauNa parms[3]
#define __HH__NK parms[4]
#define __HH__NNa parms[5]
#define __HH__El parms[6]
#define __HH__EK parms[7]
#define __HH__ENa parms[8]
#define __HH__C parms[9]

#define __HH__Vm v_in[0]
#define __HH__n v_in[1]
#define __HH__m v_in[2]
#define __HH__h v_in[3]

#define __HH__oVm calc[0]
#define __HH__on calc[1]
#define __HH__om calc[2]
#define __HH__oh calc[3]

class HHVmNMH : public FunHandle {
    private:
        static const int n_args_in;
        static const int n_args_out;
        static const std::vector<double> d_parms;

        std::vector<double> parms;
        // In order, these parameters are:
        // Gl, Tauk, TauNa
        // Nk, NNa, El, Ek, ENa, C
        // While using them, we write __<parameter_name> to avoid any naming
        // conflicts
    
    public:
        HHVmNMH();
        HHVmNMH(const std::vector<double> &in_parms);
        ~HHVmNMH();
        std::vector<double> operator() (const std::vector<double> &v_in);
};

class HHStoFun : public FunHandle {
    private:
        static const int n_args_in;
        static const int n_args_out;
        static const std::vector<double> d_parms;

    public:
        HHStoFun();
        HHStoFun(const std::vector<double> &in_parms);
        ~HHStoFun();
        std::vector<double> operator() (const std::vector<double> &v_in);
};

// Class definitions
class HodgkinHuxley__Det : public ModspecModel {
    public:
        HodgkinHuxley__Det();
        HodgkinHuxley__Det(const std::vector<double> &in_parms);

};

class HodgkinHuxley__Sto : public ModspecModel__Sto {
    public:
        HodgkinHuxley__Sto();
        HodgkinHuxley__Sto(const std::vector<double> &in_parms);
};

#endif
