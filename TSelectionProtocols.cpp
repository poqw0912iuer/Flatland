#pragma hdrstop
#include <vcl.h>
#include "TSelectionProtocols.h"
#include "TGenotype.h"
#include "TGeneticOperators.h"
#include "TSelectionMechanisms.h"
#include "TPlottingRoutine.h"
#include "FlatlandAgent.h"
#include "TAgent.h"
#include "TFlatland.h"
#include "TNet.h"
#include "TTools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TGeneticOperators GA_Operator;
TSelectionMechanisms SelectionMechanism;
TPlottingRoutine GrphTool;
//---------------------------------------------------------------------------
void TSelectionProtocols::FullGenerationalReplacement(TGenotype **object,int population,int generations,
                                    int cross_probability, int mut_probability, int SelectionMechanismNr,
                                    TNet myNet, TFlatland **flatland, TAgent agent, TTools tool){
    for(int l = 1; l < generations; l ++){
        ChooseSelectionMechanism(SelectionMechanismNr, object, population, myNet, flatland, agent, tool);
        GA_Operator.Crossover(object, cross_probability, population, myNet, flatland, agent, tool);
        GA_Operator.Mutation(object, mut_probability, population, myNet, flatland, agent, tool);
        for(int i = 0; i < population; ++i) object[ i] -> FitnessEvaluation(myNet, flatland, agent, tool);
        GrphTool.Record_Data(object, population, l, myNet, flatland, agent, tool);
    }         
}
//---------------------------------------------------------------------------
void TSelectionProtocols::OverProduction(TGenotype **object, int population, int generations,
                         int cross_probability, int mut_probability, int SelectionMechanismNr,
                         TNet myNet, TFlatland **flatland, TAgent agent, TTools tool){
    TGenotype **Child = new TGenotype*[ 2 * population];
    for(int i = 0; i < 2 * population; i ++)
        Child[ i] = new TGenotype(object[ 0] -> Get_bits_num(), object[ 0] -> Get_weights_num(), myNet, flatland, agent, tool);
    TGenotype **Adult2 = new TGenotype*[ population];
    for(int i = 0; i < population; i ++){
        Adult2[ i] = new TGenotype(object[ 0] -> Get_bits_num(), object[ 0] -> Get_weights_num(), myNet, flatland, agent, tool);
        for(int n = 0; n < object[ 0] -> Get_bits_num() * object[ 0] -> Get_weights_num(); n ++)
            Adult2[ i]->Put_Gen(n, object[ i]->Get_Gen(n));
    }
    for(int l = 1; l < generations; l ++){
        ChooseSelectionMechanism(SelectionMechanismNr, object, population, myNet, flatland, agent, tool);
        GA_Operator.Crossover(object, cross_probability, population, myNet, flatland, agent, tool);
        GA_Operator.Mutation(object, mut_probability, population, myNet, flatland, agent, tool);
        GA_Operator.Crossover(Adult2, cross_probability, population, myNet, flatland, agent, tool);
        GA_Operator.Mutation(Adult2, mut_probability, population, myNet, flatland, agent, tool);
        for(int j = 0; j < population; j ++){
            for(int n = 0; n < object[ 0] -> Get_bits_num() * object[ 0] -> Get_weights_num(); n ++)
                Child[ j]->Put_Gen(n, object[ j]->Get_Gen(n));
            Child[ j]->FitnessEvaluation(myNet, flatland, agent, tool);
        }
        for(int j = 0; j < population; j ++){
            for(int n = 0; n < object[ 0] -> Get_bits_num() * object[ 0] -> Get_weights_num(); n ++)
                Child[ population + j]->Put_Gen(n, Adult2[ j]->Get_Gen(n));
            Child[ population + j]->FitnessEvaluation(myNet, flatland, agent, tool);
        }
        SelectionMechanism.Sort(Child, 2 * population);
        for(int i = 2 * population - 1; i >= population; i --){
            for(int n = 0; n  < object[ 0] -> Get_bits_num() * object[ 0] -> Get_weights_num(); n ++)
                object[ 2*population-1 - i]->Put_Gen(n, Child[ i]->Get_Gen(n));
            object[ 2*population-1 - i]->FitnessEvaluation(myNet, flatland, agent, tool);
        }
        for(int i = 0; i < population; ++i) object[ i] -> FitnessEvaluation(myNet, flatland, agent, tool);
        GrphTool.Record_Data(object, population, l, myNet, flatland, agent, tool);
    }
}
//---------------------------------------------------------------------------
void TSelectionProtocols::ChooseSelectionMechanism(int number, TGenotype **object, int population,
                                                   TNet myNet, TFlatland **flatland, TAgent agent, TTools tool){
    if(number == 1)
        SelectionMechanism.SigmaScaling(object, population, myNet, flatland, agent, tool);
    else if(number == 2)
        SelectionMechanism.BoltzmannScaling(object, population, Form1 -> Edit5->Text.ToDouble(),
                                            myNet, flatland, agent, tool);
    else if(number == 3)
        SelectionMechanism.RankSelection(object, population, 0.5, myNet, flatland, agent, tool);
    else if(number == 10)
        SelectionMechanism.FitnessProportionate(object, population, myNet, flatland, agent, tool);
}
//---------------------------------------------------------------------------
