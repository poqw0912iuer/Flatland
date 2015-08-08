#ifndef TToolsH
#define TToolsH
#include <vector.h>
//---------------------------------------------------------------------------
#endif

class TTools{
friend class TFlatland;
friend class TAgent;
public:
    void setInputValues(vector<double> &inputVals, TFlatland flatland, TAgent agent) const;
    void output(const vector<double> &resultVals, bool &turn_left, bool &strait_ahead, bool &turn_right);
};                                                
