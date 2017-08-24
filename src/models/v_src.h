#ifndef __V_SRC_H__
#define __V_SRC_H__

#include "ModspecModel.h"

class VSrc : public ModspecModel {
    public:
        VSRC();
        VSRC(const std::vector<double> &in_parms);
        ~VSRC();
}

#endif
