#ifndef TNetH
#define TNetH
#include <vector.h>
//---------------------------------------------------------------------------
#endif

struct Connection{
    double weight;
};

class Neuron;

typedef vector<Neuron> Layer;

//******************* class Neuron *******************
class Neuron{
private:
	static double transferFunction(double x);
	static double randomWeight(){ return 2 * rand()/double(RAND_MAX) - 1;}
	double m_outputVal;
	vector<Connection> m_outputWeights;
	unsigned m_myIndex, num_Outputs;
public:
        //static double randomWeight(){ return 2 * rand()/double(RAND_MAX) - 1;}
	Neuron (unsigned numOutputs, unsigned myIndex);
	void setOutputVal(double val){ m_outputVal = val;}
	double getOutputVal() const { return m_outputVal;}
	void feedForward(const Layer &prevLayer);
        void getWeights(const Layer &prevLayer, vector<double> &Weights) const;
        void setWeights(unsigned &ind, const vector<double> &Weights);
};

//******************* class Net *******************
class TNet{
private:
	vector<Layer> m_layers;  //m_layers[layerNum][neuronNum]
public:
	TNet(const vector<unsigned> &topology);
	void feedForward(const vector<double> &inputVals);
	void getResults(vector<double> &resultVals) const;
        void getWeights(vector<double> &Weights) const;
        void setWeights(const vector<double> &Weights);
};
