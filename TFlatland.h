#ifndef TFlatlandH
#define TFlatlandH
//---------------------------------------------------------------------------
#endif

class TFlatland{
private:
    int **grid;
    int N, f, p;
public:
    TFlatland(int N);
    TFlatland(const TFlatland &module);
    void FPD(int f, int p);
    void Modify(int *new_array);
    void Change();
    int GetItem(int x, int y);
    void GridUpdate(int x, int y);
    int GetN();
};