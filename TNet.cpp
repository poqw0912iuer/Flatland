
#pragma hdrstop
#include "TNet.h"
#include <math.h>
#include <vector.h>
#include <cassert>

//---------------------------------------------------------------------------
#pragma package(smart_init)

//******************* class Neuron *******************
Neuron::Neuron(unsigned numOutputs, unsigned myIndex){
    // Sum the previous layer's outputs (which are our inputs)
    // Include the bias node from the prevoius layer
    for(unsigned c = 0; c < numOutputs; c ++){
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = randomWeight();
    }
    m_myIndex = myIndex;
    num_Outputs = numOutputs;
}   
//---------------------------------------------------------------------------
double Neuron::transferFunction(double x){
    return x;//1/(1+exp(5-x));
}
//---------------------------------------------------------------------------
void Neuron::feedForward(const Layer &prevLayer){
    double sum = 0.0;
    for(unsigned n = 0; n < prevLayer.size(); ++n){
	sum += prevLayer[n].getOutputVal() * prevLayer[n].m_outputWeights[m_myIndex].weight;
    }
    m_outputVal = Neuron::transferFunction(sum);
}
//---------------------------------------------------------------------------
void Neuron::getWeights(const Layer &prevLayer, vector<double> &Weights) const{
    /*for(unsigned n = 0; n < prevLayer.size(); ++n){
        Weights.push_back(prevLayer[n].m_outputWeights[m_myIndex].weight);
    } */
    for(unsigned n = 0; n < num_Outputs; ++n){
        Weights.push_back(m_outputWeights[n].weight);
    }
}
//---------------------------------------------------------------------------
void Neuron::setWeights(unsigned &ind, const vector<double> &Weights){
    m_outputWeights.clear();
    for(unsigned n = 0; n < num_Outputs; ++n){
        m_outputWeights.push_back(Connection());
        m_outputWeights.back().weight = Weights[ind];
        ind += 1;
    }
}

//******************* class Net *******************
TNet::TNet(const vector<unsigned> &topology){
    unsigned numLayers = topology.size();
    for(unsigned layerNum = 0; layerNum < numLayers; ++layerNum){
        m_layers.push_back(Layer());
        unsigned numOutputs = layerNum == topology.size() -1 ? 0: topology[layerNum + 1];
        // We have new layer, now fill it with neurons , and
        // add a bias neuron in each layer.
        for(unsigned neuronNum = 0; neuronNum <= topology[layerNum]; ++ neuronNum)
            m_layers.back().push_back(Neuron(numOutputs, neuronNum));
        m_layers.back().back().setOutputVal(1.0);
    }
}
//---------------------------------------------------------------------------
void TNet::getResults(vector<double> &resultVals)const{
    resultVals.clear();
    for(unsigned n = 0; n < m_layers.back().size() - 1; ++n)
        resultVals.push_back(m_layers.back()[n].getOutputVal());
}
//---------------------------------------------------------------------------
void TNet::feedForward(const vector<double> &inputVals){
    assert(inputVals.size() == m_layers[0].size() - 1);

    //Assign the input values into the input neurons
    for(unsigned i = 0; i < inputVals.size(); ++i){
        m_layers[0][i].setOutputVal(inputVals[i]);
    }

    //Forward propagate
    for(unsigned layerNum = 1; layerNum < m_layers.size(); ++layerNum){
        Layer &prevLayer = m_layers[layerNum - 1];
        for(unsigned n = 0; n < m_layers[layerNum].size() - 1; ++n){
            m_layers[layerNum][n].feedForward(prevLayer);
        }
    }
}
//---------------------------------------------------------------------------
void TNet::getWeights(vector<double> &Weights) const{
    Weights.clear();
    for(unsigned layerNum = 0; layerNum < m_layers.size() - 1; ++layerNum){
    Layer &prevLayer = m_layers[layerNum];
        for(unsigned n = 0; n < m_layers[layerNum].size(); ++n)
            m_layers[layerNum][n].getWeights(prevLayer, Weights);
    }
}
//---------------------------------------------------------------------------
void TNet::setWeights(const vector<double> &Weights){
    unsigned ind = 0;
    for(unsigned layerNum = 0; layerNum < m_layers.size() - 1; ++layerNum){
        for(unsigned n = 0; n < m_layers[layerNum].size(); ++n)
            m_layers[layerNum][n].setWeights(ind, Weights);
    }
}
//---------------------------------------------------------------------------
