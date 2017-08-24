#ifndef __MODSPEC_MODEL__
#define __MODSPEC_MODEL__

#include "SDE.h"
#include <vector>
#include <string>

// Defines an interface class for a ModSpec model. Every model should follow
// this template to interact with the ODE/SODE classes (and therefore the
// integration methods)

class ModspecModel {
    protected:
        FunHandle *det_fun;

    public:
        ModspecModel();
        ModspecModel(int _n_unks);
        ModspecModel(int _n_unks, const std::vector<double> &in_parms);
        FunHandle* const getDetFun() { return det_fun; };
        virtual ~ModspecModel();
        const int n_unks;
};

class ModspecModel__Sto : public ModspecModel {
    protected:
        FunHandle *sto_fun;

    public:
        ModspecModel__Sto();
        ModspecModel__Sto(int _n_unks);
        ModspecModel__Sto(int _n_unks, const std::vector<double> &in_parms);
        FunHandle* const getStoFun() { return sto_fun; };
        virtual ~ModspecModel__Sto();
};

#endif
