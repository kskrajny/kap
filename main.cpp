include <iostream>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cassert>
#include <chrono>
#include <set>
using namespace std::chrono;
using namespace std;


// 0-gora, 1-prawo, 2-dol, 3-lewo

#define MAX 1000000000
namespace my {

    struct pair {
        int z;
        int id;
        pair(int z, int id){
            this->z = z;
            this->id = id;
        }
    } ;

    struct comp {
        bool operator() (const pair a, const pair b) const {
            if(a.z == b.z) return (a.id < b.id);
            return (a.z<b.z);}
    } ;

    struct comp1 {
        bool operator() (pair a, pair b) const { return (a.z<b.z);}
    } comp1;

}


int main(){
    clock_t tStart = clock();
    ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<my::pair> X;
    vector<my::pair> Y;
    vector<int> xco;
    vector<int> yco;
    for(int i=0;i<n;i++){
        int a, b;
        cin >> a >> b;
        X.push_back(my::pair(a, i));
        Y.push_back(my::pair(b, i));
        xco.push_back(a);
        yco.push_back(b);
    }

    sort(X.begin(), X.end(), my::comp1);
    sort(Y.begin(), Y.end(), my::comp1);


    vector<vector<int>> mapa;
    for(int i=0;i<n;i++){
        vector<int> w(4, -1);
        mapa.push_back(w);
    }

    // 0-gora, 1-prawo, 2-dol, 3-lewo

    //ustalam id tych na prawo i na gore
    for(int i=0;i<n-1;i++){
        mapa[X[i].id][1] = X[i+1].id;
        mapa[Y[i].id][0] = Y[i+1].id;
    }

    // ustalam id tych na lewo i na dol
    for(int i=n-1;i>0;i--){
        mapa[X[i].id][3] = X[i-1].id;
        mapa[Y[i].id][2] = Y[i-1].id;
    }

    vector<my::pair> odl;
    for(int i=0;i<n;i++){
        odl.push_back(my::pair(2*MAX, i));
    }
    odl[0].z = 0;

    set<my::pair, my::comp> q;
    q.insert(odl[0]);
    while(!q.empty()){
        set<my::pair>::iterator it = q.begin();
        int j = q.begin()->id;
        q.erase(q.begin());
        for(int i=0;i<4;i++) {
            if (mapa[j][i] != -1) {
                if (i % 2 == 0) {
                    if (odl[j].z + min(abs(yco[mapa[j][i]] - yco[j]),abs(xco[mapa[j][i]] - xco[j])) < odl[mapa[j][i]].z) {
                        auto f = q.find(odl[mapa[j][i]]);
                        if(f != q.end()) {q.erase(f);}
                        odl[mapa[j][i]].z = odl[j].z +  min(abs(yco[mapa[j][i]] - yco[j]),abs(xco[mapa[j][i]] - xco[j]));
                        q.insert(odl[mapa[j][i]]);
                    }
                } else {
                    if (odl[j].z + min(abs(yco[mapa[j][i]] - yco[j]),abs(xco[mapa[j][i]] - xco[j])) < odl[mapa[j][i]].z) {
                        auto f = q.find(odl[mapa[j][i]]);
                        if(f != q.end()) {q.erase(f);}
                        odl[mapa[j][i]].z = odl[j].z + min(abs(yco[mapa[j][i]] - yco[j]),abs(xco[mapa[j][i]] - xco[j]));
                        q.insert(odl[mapa[j][i]]);
                    }
                }
            }
        }
    }

    cout << odl[n-1].z;

    return 0;
}