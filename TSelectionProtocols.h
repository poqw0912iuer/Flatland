#ifndef TSelectionProtocolsH
#define TSelectionProtocolsH
//---------------------------------------------------------------------------
class TSelectionProtocols{
friend class TGenotype;
friend class TNet;
friend class TFlatland;
friend class TAgent;
friend class TTools;
public:
    void FullGenerationalReplacement(TGenotype **object, int populationint, int generations,
                                     int cross_probability, int mut_probability, int SelectionMechanismNr,
                                     TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    void OverProduction(TGenotype **object, int population, int generations, int cross_probability,
                                     int mut_probability, int SelectionMechanismNr,
                                     TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    void ChooseSelectionMechanism(int number, TGenotype **object, int population,
                                  TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
};
#endif