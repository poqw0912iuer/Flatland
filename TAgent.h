#ifndef TAgentH
#define TAgentH
//---------------------------------------------------------------------------
#endif

class TAgent{
friend class TFlatland;
private:
    int position_x;
    int position_y;
    int direction;
    float fitness;
public:
    TAgent();
    void Move(TFlatland flatland, bool turn_left, bool strait_ahead, bool turn_right);
    void WrapAround(TFlatland flatland);
    void FitnessUpdate(TFlatland flatland);
    float GetFitness();
    void setInitialConditions();
    int GetPosition_x(), GetPosition_y(), GetDirection();
};