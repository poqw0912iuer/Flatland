#pragma hdrstop
#include "TTools.h"
#include <vector.h>
#include "TFlatland.h"
#include "TAgent.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

void TTools::setInputValues(vector<double> &inputVals, TFlatland flatland, TAgent agent)const{
    inputVals.clear();
    int left, right, top;
    if(agent.GetDirection() == 0){
        if(agent.GetPosition_x() == 0){left = flatland.GetN() - 1;  right = agent.GetPosition_x()+1;}
        else if(agent.GetPosition_x() == flatland.GetN() - 1){left = agent.GetPosition_x() - 1; right = 0;}
        else {left = agent.GetPosition_x() - 1; right = agent.GetPosition_x()+1;}
        if(agent.GetPosition_y() == flatland.GetN() - 1) top = 0;
        else top = agent.GetPosition_y() + 1;

        if(flatland.GetItem(left,agent.GetPosition_y()) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(agent.GetPosition_x(),top) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(right,agent.GetPosition_y()) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.); // ****************************************
        if(flatland.GetItem(left,agent.GetPosition_y()) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(agent.GetPosition_x(),top) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(right,agent.GetPosition_y()) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
    }
    // *********** Direction 1 ************
    else if(agent.GetDirection() == 1){
        if(agent.GetPosition_y() == 0){right = flatland.GetN() - 1;  left = agent.GetPosition_y()+1;}
        else if(agent.GetPosition_y() == flatland.GetN() - 1){right = agent.GetPosition_y() - 1; left = 0;}
        else {left = agent.GetPosition_y() + 1; right = agent.GetPosition_y()-1;}
        if(agent.GetPosition_x() == flatland.GetN() - 1) top = 0;
        else top = agent.GetPosition_x() + 1;

        if(flatland.GetItem(agent.GetPosition_x(),left) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(top,agent.GetPosition_y()) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(agent.GetPosition_x(),right) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.); // ************
        if(flatland.GetItem(agent.GetPosition_x(),left) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(top,agent.GetPosition_y()) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(agent.GetPosition_x(),right) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
    }
    // *********** Direction 2 ************
    else if(agent.GetDirection() == 2){
        if(agent.GetPosition_x() == 0){right = flatland.GetN() - 1;  left = agent.GetPosition_x()+1;}
        else if(agent.GetPosition_x() == flatland.GetN() - 1){right = agent.GetPosition_x() - 1; left = 0;}
        else {left = agent.GetPosition_x() + 1; right = agent.GetPosition_x()-1;}
        if(agent.GetPosition_y() == 0) top = flatland.GetN() - 1;
        else top = agent.GetPosition_y() - 1;

        if(flatland.GetItem(left,agent.GetPosition_y()) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(agent.GetPosition_x(),top) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(right,agent.GetPosition_y()) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.); // **********
        if(flatland.GetItem(left,agent.GetPosition_y()) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(agent.GetPosition_x(),top) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(right,agent.GetPosition_y()) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
    }
    // *********** Direction 3 ************
    else if(agent.GetDirection() == 3){
        if(agent.GetPosition_y() == 0){left = flatland.GetN() - 1;  right = agent.GetPosition_y()+1;}
        else if(agent.GetPosition_y() == flatland.GetN() - 1){left = agent.GetPosition_x() - 1; right = 0;}
        else {right = agent.GetPosition_y() + 1; left = agent.GetPosition_y()-1;}
        if(agent.GetPosition_x() == 0) top = flatland.GetN() - 1;
        else top = agent.GetPosition_x() - 1;

        if(flatland.GetItem(agent.GetPosition_x(),left) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(top,agent.GetPosition_y()) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(agent.GetPosition_x(),right) == 2)
            inputVals.push_back(1.);
        else inputVals.push_back(0.); // ************
        if(flatland.GetItem(agent.GetPosition_x(),left) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(top,agent.GetPosition_y()) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
        if(flatland.GetItem(agent.GetPosition_x(),right) == 1)
            inputVals.push_back(1.);
        else inputVals.push_back(0.);
    }
}
//---------------------------------------------------------------------------
void TTools::output(const vector<double> &resultVals, bool &turn_left, bool &strait_ahead, bool &turn_right){
    turn_left = false;
    turn_right = false;
    strait_ahead = false;
    double treshold = 0.7;
    if(resultVals[0] >= resultVals[1] && resultVals[0] >= resultVals[2]){
        //if(resultVals[0] >= treshold)
        turn_left = true;
    }
    else if(resultVals[1] >= resultVals[0] && resultVals[1] >= resultVals[2]){
        //if(resultVals[1] >= treshold)
        strait_ahead = true;
    }
    else if(resultVals[2] >= resultVals[0] && resultVals[2] >= resultVals[1]){
        //if(resultVals[2] >= treshold)
        turn_right = true;
    }
}
//---------------------------------------------------------------------------
