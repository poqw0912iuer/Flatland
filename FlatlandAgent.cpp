#include <vcl.h>
#include <fstream.h>
#pragma hdrstop
#include "math.h"
#include <vector.h>
#include <cassert>
#include "FlatlandAgent.h"
#include "TAgent.h"
#include "TFlatland.h"
#include "TNet.h"
#include "TTools.h"
#include "TPlottingRoutine.h"
#include "TGenotype.h"
#include "TGeneticOperators.h"
#include "TSelectionMechanisms.h"
#include "TSelectionProtocols.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TForm1 *Form1;
TGenotype **Adult, **Child;
TGeneticOperators GA_Operator;
TSelectionMechanisms SelectionMechanism;
TPlottingRoutine GrphTool;
TSelectionProtocols SelectionProtocol;
TTools tool;
TShape *myAgent; TShape *myAgentNose;
TShape *myShapes[65];
TShape *Boundary;
bool trained = false; unsigned interval;
int click_count = 0;
int N = 8;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{   interval = 1;
    steps = Edit9 -> Text.ToInt();
    weight_bits = 8, num_Weights = 21;//33;
    DoubleBuffered = true;
    SelectionMechanismNr = 1;
    Label3->Caption = "Fitnes = ";
    Label4->Caption = "Scenario no. ";
}
//---------------------------------------------------------------------------
void saveWeights(const vector<double> &Weights){
    std::ofstream myStream;
    myStream.open( "Weights.txt", std::ios::out );
    if( myStream.good() == true ){
        myStream << Weights.size() << "\n";
        for(unsigned i = 0; i < Weights.size(); ++i)
            myStream << Weights[i] << "\n";
    }
}
//---------------------------------------------------------------------------
void loadWeights(const vector<double> &Weights){
    Weights.clear();
    std::ifstream myStream;
    myStream.open( "Weights.txt", std::ios::in );
    if( myStream.good() == true ){
        unsigned size;
        myStream >> size;
        double value;
        for(unsigned i = 0; i < size; ++i){
            myStream >> value;
            Weights.push_back(value);
        }
    }
}
//---------------------------------------------------------------------------
void BoundaryConst(int N, TShape **myShapes, TFlatland flatland){
for(int i = 0; i < N; i ++)
    for(int j = 0; j < N; j ++){
        switch(flatland.GetItem(i,j)){
            case 1: {
                myShapes[i * N + j]->SendToBack();
                myShapes[i * N + j]->Brush->Color = clGreen;
                myShapes[i * N + j]->Pen->Color = clGreen;
                myShapes[i * N + j]->Top = 605 - j * 50;
                myShapes[i * N + j]->Left = 45 + i * 50;
                myShapes[i * N + j]->Width = 40;
                myShapes[i * N + j]->Height = 40;
                myShapes[i * N + j]->Shape = stEllipse;
                Boundary->SendToBack();
                break;
            }
            case 2: {
                myShapes[i * N + j]->SendToBack();
                myShapes[i * N + j]->Brush->Color = clRed;
                myShapes[i * N + j]->Pen->Color = clRed;
                myShapes[i * N + j]->Top = 605 - j * 50;
                myShapes[i * N + j]->Left = 45 + i * 50;
                myShapes[i * N + j]->Width = 40;
                myShapes[i * N + j]->Height = 40;
                myShapes[i * N + j]->Shape = stSquare;
                Boundary->SendToBack();
                break;
            }
            case 0:{
                myShapes[i * N + j]->Visible = false;
                break;
            }
        }
    }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
    Randomize();
if(!trained && RadioButton10->Checked == true)   MessageBox( NULL, "First train the network!", "EA_Basic", MB_OK);
else{
    float overal_performance = 0;
    steps = Edit9 -> Text.ToInt();
    TFlatland flatland(N);
    TAgent agent;
    // ***************************************
    vector<unsigned> topology;
    topology.push_back(6);
    //topology.push_back(3);////////
    topology.push_back(3);
    TNet myNet(topology);
    vector<double> inputVals;
    vector<double> resultVals;
    // ***************************************
    vector<double> Weights;
    //myNet.getWeights(Weights);
    //saveWeights(Weights);
    loadWeights(Weights);
    myNet.setWeights(Weights);
    vector<double> W;
    myNet.getWeights(W);
    
for(unsigned scenario = 0; scenario < 5; ++scenario){
    Label4->Caption = "Scenario no. " + IntToStr(scenario + 1);

    if(click_count){
        for (int i = 0; i < 65; i++)  delete myShapes[i];
        delete myAgent; delete myAgentNose;
        delete Boundary;
    }
    click_count ++;

    if(RadioButton9->Checked == true)
        flatland.Change();
    else{
        switch (scenario){
            case 0: flatland.Modify(flatland_memory1);
                    break;
            case 1: flatland.Modify(flatland_memory2);
                    break;
            case 2: flatland.Modify(flatland_memory3);
                    break;
            case 3: flatland.Modify(flatland_memory4);
                    break;
            case 4: flatland.Modify(flatland_memory5);
                    break;
        }
    }
    int previous_x = agent.GetPosition_x();   int previous_y = agent.GetPosition_y();
    Boundary = new TShape(this);
    Boundary->Parent=Form1;
    Boundary->Visible=true;
    Boundary->SendToBack();
    Boundary->Pen->Color = clBlack;
    Boundary->Pen->Width = 40;
    Boundary->Top = 215;
    Boundary->Left = 5 ;
    Boundary->Width = 470;
    Boundary->Height = 470;
    Boundary->Shape = stRectangle;

    myAgent = new TShape(this);       myAgentNose = new TShape(this);
    myAgent->Parent = Form1;          myAgentNose->Parent = Form1;
    myAgent->Visible = true;          myAgentNose->Visible = true;
    myAgent->Shape = stEllipse;       myAgentNose->Shape = stRectangle;
    myAgent->Width = 40;              myAgentNose->Width = 16;
    myAgent->Height = 40;             myAgentNose->Height = 16;
    myAgent->Brush->Color = clBlue;   myAgentNose->Brush->Color = clFuchsia;
    myAgent->Pen->Color = clBlue;     myAgentNose->Pen->Color = clFuchsia;

    for (int i = 0; i < 65; i++) {
        myShapes[i] = new TShape(this);
        myShapes[i]->Parent = Form1;
        myShapes[i]->Visible = true;
    }
    BoundaryConst(N, myShapes, flatland);
        myAgent->Top = 605-previous_y*50;
        myAgent->Left = 45+previous_x*50;
    if(agent.GetDirection() == 0){
        myAgentNose->Top = 605 - previous_y*50;
        myAgentNose->Left = 45 + (previous_x*50 + 12);
    }else if(agent.GetDirection() == 1){
        myAgentNose->Top = 605 - (previous_y*50 - 12);
        myAgentNose->Left = 45 + (previous_x*50 + 24);
    }else if(agent.GetDirection() == 2){
        myAgentNose->Top = 605-(previous_y*50 - 24);
        myAgentNose->Left = 45+(previous_x*50 + 12);
    }else if(agent.GetDirection() == 3){
        myAgentNose->Top = 605-(previous_y*50 - 12);
        myAgentNose->Left = 45+previous_x*50;
    }
    for(int i = 0; i < steps; i ++){
        //***********
        tool.setInputValues(inputVals, flatland, agent);
        myNet.feedForward(inputVals);
        myNet.getResults(resultVals);
        tool.output(resultVals, turn_left, strait_ahead, turn_right);
        //***********
        agent.Move(flatland, turn_left, strait_ahead, turn_right);
        agent.FitnessUpdate(flatland);
        Label3->Caption = "Fitnes = " +FloatToStr(overal_performance + agent.GetFitness());
        BoundaryConst(N, myShapes, flatland);
        //----Agent--begin---
        if(agent.GetDirection() == 0){
            myAgentNose->Top = 605 - agent.GetPosition_y()*50;
            myAgentNose->Left = 45+(agent.GetPosition_x()*50 + 12);
        }else if(agent.GetDirection() == 1){
            myAgentNose->Top = 605-(agent.GetPosition_y()*50 - 12);
            myAgentNose->Left = 45+(agent.GetPosition_x()*50 + 24);
        }else if(agent.GetDirection() == 2){
            myAgentNose->Top = 605-(agent.GetPosition_y()*50 - 24);
            myAgentNose->Left = 45+(agent.GetPosition_x()*50 + 12);
        }else if(agent.GetDirection() == 3){
            myAgentNose->Top = 605-(agent.GetPosition_y()*50 - 12);
            myAgentNose->Left = 45+(agent.GetPosition_x()*50);
        }

        if(previous_x == 7 && agent.GetPosition_x() == 0){
            for(int k = 0; k < 40; k ++){
                myAgent->Left = 5 + k;  myAgentNose->Left = 5 + k + 24;
                Sleep(interval);
                Application->ProcessMessages();
            }
        }
        else if(previous_x == 0 && agent.GetPosition_x() == 7){
            for(int k = 0; k < 40; k ++){
                myAgent->Left = 435 - k;  myAgentNose->Left = 435 - k;
                Sleep(interval);
                Application->ProcessMessages();
            }
        }
        else if(previous_y == 0 && agent.GetPosition_y() == 7){
            for(int k = 0; k < 40; k ++){
                myAgent->Top = 215 + k;  myAgentNose->Top = 215 + k + 24;
                Sleep(interval);
                Application->ProcessMessages();
            }
        }
        else if(previous_y == 7 && agent.GetPosition_y() == 0){
            for(int k = 0; k < 40; k ++){
                myAgent->Top= 625 - k;  myAgentNose->Top = 625 - k;
                Sleep(interval);
                Application->ProcessMessages();
            }
        }
        else for(int k = 0; k < 50; k ++){
            myAgent->Top = 605-(previous_y*50+(agent.GetPosition_y()-previous_y)*50/50*k);
            myAgent->Left = 45+(previous_x*50+(agent.GetPosition_x()-previous_x)*50/50*k);
            if(agent.GetDirection() == 0){
                myAgentNose->Top = 605-(previous_y*50+(agent.GetPosition_y()-previous_y)*50/50*k);
                myAgentNose->Left = 45+(previous_x*50+(agent.GetPosition_x()-previous_x)*50/50*k + 12);
            }else if(agent.GetDirection() == 1){
                myAgentNose->Top = 605-(previous_y*50+(agent.GetPosition_y()-previous_y)*50/50*k - 12);
                myAgentNose->Left = 45+(previous_x*50+(agent.GetPosition_x()-previous_x)*50/50*k + 24);
            }else if(agent.GetDirection() == 2){
                myAgentNose->Top = 605-(previous_y*50+(agent.GetPosition_y()-previous_y)*50/50*k - 24);
                myAgentNose->Left = 45+(previous_x*50+(agent.GetPosition_x()-previous_x)*50/50*k + 12);
            }else if(agent.GetDirection() == 3){
                myAgentNose->Top = 605-(previous_y*50+(agent.GetPosition_y()-previous_y)*50/50*k - 12);
                myAgentNose->Left = 45+(previous_x*50+(agent.GetPosition_x()-previous_x)*50/50*k);
            }
            Sleep(interval);
            Application->ProcessMessages();
        }
        if(flatland. GetItem(agent.GetPosition_x(),agent.GetPosition_y()) == 2)
            for (int i = 0; i <10; i++) {
                int a = agent.GetFitness();
                myAgent->Pen->Color=static_cast<TColor>(RGB(random(255.),random(255.),random(255.)));
                myAgent->Brush->Color=static_cast<TColor>(RGB(random(255.),random(255.),random(255.)));
                myAgentNose->Pen->Color=static_cast<TColor>(RGB(random(255.),random(255.),random(255.)));
                myAgentNose->Brush->Color=static_cast<TColor>(RGB(random(255.),random(255.),random(255.)));
                myAgent->Top -= 8; myAgent->Left -= 8;
                myAgent->Width += 16; myAgent->Height+=16;
                Sleep(60);
                Application->ProcessMessages();
                myAgent->Width -= 16; myAgent->Height-=16;
                myAgent->Top += 8; myAgent->Left += 8;
                Sleep(60);
                Application->ProcessMessages();
            }
        myAgent->Brush->Color = clBlue;   myAgentNose->Brush->Color = clFuchsia;
        myAgent->Pen->Color = clBlue;     myAgentNose->Pen->Color = clFuchsia;
        flatland.GridUpdate(agent.GetPosition_x(), agent.GetPosition_y());
        previous_x = agent.GetPosition_x();
        previous_y = agent.GetPosition_y();
        //----Agent -- end---
        BoundaryConst(N, myShapes, flatland);
    }
    overal_performance += agent.GetFitness();
    Sleep(1000);
    agent.setInitialConditions();
}
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
    Randomize();
    population = Edit2 -> Text.ToInt();
    steps = Edit9 -> Text.ToInt();
    if(population % 2 )   MessageBox( NULL, "Type in even volume of population!", "EA_Basic", MB_OK);
    else if((population < 4))   MessageBox( NULL, "Type in at least 4", "EA_Basic", MB_OK);
    else{
        generations = Edit8->Text.ToInt();
        cross_probability = 100 * Edit3 -> Text.ToDouble();
        mut_probability = 100 * Edit4 -> Text.ToDouble();
        max = new float[ generations];
        average = new float[ generations];
        st_dew = new float[ generations];

        TFlatland **flatland;
        flatland = new TFlatland*[5];
        for(unsigned i = 0; i < 5; ++i)
            flatland[ i] = new TFlatland(N);
        for(unsigned j = 0; j < 8; ++j)
            for(unsigned k = 0; k < 8; ++k){
                flatland_memory1[ j * 8 + k] = flatland[0]->GetItem(j, k); flatland_memory2[ j * 8 + k] = flatland[1]->GetItem(j, k);
                flatland_memory3[ j * 8 + k] = flatland[2]->GetItem(j, k); flatland_memory4[ j * 8 + k] = flatland[3]->GetItem(j, k);
                flatland_memory5[ j * 8 + k] = flatland[4]->GetItem(j, k);
            }
        TAgent agent;
        //****Net Beigin*****
        vector<unsigned> topology;
        topology.push_back(6);
        //topology.push_back(3);////////
        topology.push_back(3);
        TNet myNet(topology);
        //****Net End*****
        best_genotype = new TGenotype(weight_bits, num_Weights, myNet, flatland, agent, tool);

        Adult = new TGenotype*[population];
        for(int i = 0; i < population; i ++)
            Adult[ i] = new TGenotype(weight_bits, num_Weights, myNet, flatland, agent, tool);
        GrphTool.Record_Data(Adult, population, 0, myNet, flatland, agent, tool);

        if(RadioButton6 -> Checked == true){
            SelectionProtocol.FullGenerationalReplacement(Adult, population, generations,
                             cross_probability, mut_probability, SelectionMechanismNr,
                             myNet, flatland, agent, tool);
        }
        else if(RadioButton7 -> Checked == true){
            SelectionProtocol.OverProduction(Adult, population, generations, cross_probability,
                                             mut_probability, SelectionMechanismNr, myNet, flatland, agent, tool);
        }
        vector<double> Weights;
        for(unsigned i = 0; i < best_genotype->Get_weights_num(); ++i)
            Weights.push_back(best_genotype->Get_Phenotype(i));
        saveWeights(Weights);
        Button5->Enabled=true;
    }
    trained = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
    GrphTool.Plot(generations);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton2Click(TObject *Sender)
{
    Edit5 -> Enabled = false;
    SelectionMechanismNr = 1;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton3Click(TObject *Sender)
{
    Edit5 -> Enabled = true;
    SelectionMechanismNr = 2;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton4Click(TObject *Sender)
{
    Edit5 -> Enabled = false;
    SelectionMechanismNr = 3;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton1Click(TObject *Sender)
{
    Edit5 -> Enabled = false;
    SelectionMechanismNr = 10;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton9Click(TObject *Sender)
{
    RadioButton9->Checked = true;
    RadioButton10->Checked = false;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::RadioButton10Click(TObject *Sender)
{
    RadioButton9->Checked = false;
    RadioButton10->Checked = true;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::TrackBar1Change(TObject *Sender)
{
    interval = TrackBar1->Position;
}
//---------------------------------------------------------------------------

