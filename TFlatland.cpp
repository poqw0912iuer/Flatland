#pragma hdrstop
#include <vcl.h>
#include "TFlatland.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)

TFlatland::TFlatland(int size){
    N = size;
    f = 50;
    p = 50;
    grid = new int*[N];
    for(int i = 0; i < N; i ++)
        grid[i] = new int[N];
    FPD(f, p);
}
//---------------------------------------------------------------------------
TFlatland::TFlatland(const TFlatland &module){
    N = 8;
    f = 50;
    p = 50;
    grid = new int*[N];
    for(int i = 0; i < N; i ++)
        grid[i] = new int[N];

    for(int i = 0; i < N; i ++)
        for(int j = 0; j < N; j ++)
            grid[i][j] = module.GetItem(i,j);
}
//---------------------------------------------------------------------------
void TFlatland::FPD(int f, int p){
    for(int i = 0; i < N; i ++)
        for(int j = 0; j < N; j ++){
            if(random(100) < f)  grid[i][j] = 1;
            else if(random(100) < p)  grid[i][j] = 2;
            else grid[i][j] = 0;
        }
}
//---------------------------------------------------------------------------
void TFlatland::Modify(int *new_array){
    for(int i = 0; i < N; i ++)
        for(int j = 0; j < N; j ++)
            grid[i][j] = new_array[i * N + j];
}
//---------------------------------------------------------------------------
void TFlatland::Change(){
    FPD(f, p);
}
//---------------------------------------------------------------------------
int TFlatland::GetItem(int x, int y){
    return grid[x][y];
}
//---------------------------------------------------------------------------
void TFlatland::GridUpdate(int x, int y){
    grid[x][y] = 0;
}
//---------------------------------------------------------------------------
int TFlatland::GetN(){
    return N;
}
//---------------------------------------------------------------------------

