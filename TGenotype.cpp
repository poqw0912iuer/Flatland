#pragma hdrstop
#include <vcl.h>
#include <fstream.h>
#include <vector.h>
#include "math.h"
#include "TGenotype.h"
#include "FlatlandAgent.h"
#include "TNet.h"
#include "TFlatland.h"
#include "TAgent.h"
#include "TTools.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
TGenotype::TGenotype(unsigned bits, unsigned Weights, TNet myNet, TFlatland **flatland, TAgent agent, TTools tool){
    weight_bits = bits;
    num_Weights = Weights;
    gens = new int[ num_Weights * bits];
    phenotypes = new double [ num_Weights];
    for(int i = 0; i < weight_bits * num_Weights; i ++)
        gens[ i] = random(2);
    FitnessEvaluation( myNet, flatland, agent, tool);
}
//---------------------------------------------------------------------------
void TGenotype::PhenotypeConvertion(){
    double divisor = 0;
    for(unsigned i = 0; i < weight_bits; ++i)
        divisor += pow(2., i);
    divisor /= 4;
    for(int i = 0; i < num_Weights; ++i){
        phenotypes[ i] = 0;
        for(unsigned j = 0; j < weight_bits; ++j)
            phenotypes[ i] += double(gens[ i * weight_bits + j]) * pow(2., j);
        phenotypes[ i] = phenotypes[ i] / divisor - 2;
    }
}
//---------------------------------------------------------------------------
double TGenotype::Get_Phenotype(int index){
    return phenotypes[ index];
}
//---------------------------------------------------------------------------
int TGenotype::Get_Gen(int index){
    return gens[index];
}
//---------------------------------------------------------------------------
void TGenotype::Put_Gen(int index, int value){
    gens[ index] = value;
}
//---------------------------------------------------------------------------
void TGenotype::FitnessEvaluation(TNet myNet, TFlatland **flatland, TAgent agent, TTools tool){
    fitnes = 0; fitnes_temp = 0;
    vector<double> inputVals;
    vector<double> resultVals;
    vector<double> Weights;
    bool turn_left, strait_ahead, turn_right;
    for(int scenario = 0; scenario < 5; ++scenario){
        if(Form1->RadioButton9->Checked == true)  flatland[scenario]->Change();
        TFlatland flatland_temp(*flatland[scenario]);
        PhenotypeConvertion();
        for(unsigned i = 0; i < num_Weights; ++i)
            Weights.push_back(phenotypes[ i]);
        myNet.setWeights(Weights);
        for(int i = 0; i < Form1->steps; ++i){
            tool.setInputValues(inputVals, flatland_temp, agent);  ///
            myNet.feedForward(inputVals);
            myNet.getResults(resultVals);
            tool.output(resultVals, turn_left, strait_ahead, turn_right);
            agent.Move(flatland_temp, turn_left, strait_ahead, turn_right); ///
            agent.FitnessUpdate(flatland_temp);                             ///
            flatland_temp.GridUpdate(agent.GetPosition_x(), agent.GetPosition_y());
        }
        fitnes += agent.GetFitness();   fitnes_temp += agent.GetFitness();
        delete &flatland_temp;
        agent.setInitialConditions();
    }
}
//---------------------------------------------------------------------------
float TGenotype::Get_Fitnes(){
    return fitnes;
}
//---------------------------------------------------------------------------
float TGenotype::Get_Fitnes_temp(){
    return fitnes_temp;
}
//---------------------------------------------------------------------------
void TGenotype::Scale_Fitnes(float value){
    fitnes_temp = value;
}
//---------------------------------------------------------------------------
int TGenotype::Get_weights_num(){
    return num_Weights;
}
//---------------------------------------------------------------------------
int TGenotype::Get_bits_num(){
    return weight_bits;
}
//---------------------------------------------------------------------------
