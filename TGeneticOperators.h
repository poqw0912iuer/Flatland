#ifndef TGeneticOperatorsH
#define TGeneticOperatorsH
//---------------------------------------------------------------------------
class TGeneticOperators{
friend class TGenotype;
friend class TNet;
friend class TFlatland;
friend class TAgent;
friend class TTools;
public:
    void Crossover(TGenotype **object,  int probability, int population, TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    void Mutation(TGenotype **object, int probability, int population, TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
};
#endif
