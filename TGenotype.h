#ifndef TGenotypeH
#define TGenotypeH
#include <vector.h>
//---------------------------------------------------------------------------
class TGenotype{
friend class TForm1;
friend class TNet;
friend class TFlatland;
friend class Ttools;
friend class TAgent;
friend class TTools;
private:
    int *gens;
    double *phenotypes;
    int weight_bits, num_Weights;
    float fitnes, fitnes_temp;
public:
    TGenotype(unsigned bits, unsigned Weights, TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    void PhenotypeConvertion();
    double Get_Phenotype(int index);
    int Get_Gen(int index);
    void Put_Gen(int index, int value);
    void FitnessEvaluation(TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    float Get_Fitnes();
    float Get_Fitnes_temp();
    void Scale_Fitnes(float value);
    int Get_weights_num();
    int Get_bits_num();
};
#endif