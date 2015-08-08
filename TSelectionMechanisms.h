#ifndef TSelectionMechanismsH
#define TSelectionMechanismsH
//---------------------------------------------------------------------------
class TSelectionMechanisms{
friend class TGenotype;
friend class TNet;
friend class TFlatland;
friend class TAgent;
friend class TTools;

private:
public:
    void FitnessProportionate(TGenotype **object, int population,
                              TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    void SigmaScaling(TGenotype **object, int population,
                      TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    void BoltzmannScaling(TGenotype **object, int population, double T,
                          TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    void RankSelection(TGenotype **object, int population, float Min,
                       TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    void Sort( TGenotype **object, int population);
    void RuletteWheel(TGenotype **object, int population,
                      TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
};
#endif