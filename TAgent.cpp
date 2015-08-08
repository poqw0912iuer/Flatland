#pragma hdrstop
#include <vcl.h>
#include "TAgent.h"
#include "TFlatland.h"
#include "FlatlandAgent.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TAgent::TAgent(){
    position_x = 0;
    position_y = 0;
    direction = 3;
    fitness = 0;
}
//---------------------------------------------------------------------------
void TAgent::setInitialConditions(){
    position_x = 0;
    position_y = 0;
    direction = 3;
    fitness = 0;
}
//---------------------------------------------------------------------------
void TAgent::Move(TFlatland flatland, bool turn_left, bool strait_ahead, bool turn_right){
    if(turn_left){
        if(direction == 0) direction = 3;
        else direction -= 1;
    }else if(turn_right){
        if(direction == 3) direction = 0;
        else direction += 1;
    }else if(!turn_left && !strait_ahead && !turn_right)
        return;

    if(direction == 0)  position_y += 1;
    else if(direction == 1)  position_x += 1;
    else if(direction == 2)  position_y -= 1;
    else position_x -= 1;
    WrapAround(flatland);
}
//---------------------------------------------------------------------------
void TAgent::WrapAround(TFlatland flatland){
    if(position_x < 0) position_x = flatland.GetN() - 1;
    else if(position_x > flatland.GetN() - 1) position_x = 0;
    if(position_y < 0) position_y = flatland.GetN() - 1;
    else if(position_y > flatland.GetN() - 1) position_y = 0;
}
//---------------------------------------------------------------------------
void TAgent::FitnessUpdate(TFlatland flatland){
    if(flatland.GetItem(position_x, position_y) == 1)  fitness += 1.0;
    else if (flatland.GetItem(position_x, position_y) == 2)  fitness -= 5;
    if(fitness < 0) fitness = 0.0;
}
//---------------------------------------------------------------------------
float TAgent::GetFitness(){
    return fitness;
}
//---------------------------------------------------------------------------
int TAgent::GetPosition_x(){
    return position_x;
}
//---------------------------------------------------------------------------
int TAgent::GetPosition_y(){
    return position_y;
}
//---------------------------------------------------------------------------
int TAgent::GetDirection(){
    return direction;
}
//---------------------------------------------------------------------------
