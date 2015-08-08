#ifndef TPlottingRoutineH
#define TPlottingRoutineH
//---------------------------------------------------------------------------
class TPlottingRoutine{
friend class TGenotype;
friend class TForm1;
friend class TNet;
friend class TFlatland;
friend class TAgent;
friend class TTools;

public:
    void Record_Data(TGenotype **object, int population, int generation,
                     TNet myNet, TFlatland **flatland, TAgent agent, TTools tool);
    void Plot(int generations);
};
#endif