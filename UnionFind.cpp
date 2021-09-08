#include <iostream>
#include <vector>

using namespace std;

class UF {
public:
    UF(int size) {
        id.resize(size);
        sz.resize(size,1);
        for(int i=0;i<id.size();i++) {
            id[i] = i;
        }
    }

    UF(const UF&) = delete;
    UF& operator=(const UF&) = delete;

    void Union(int a,int b) {
        int r_a = find_root(a);
        int r_b = find_root(b);
        if(sz[r_a] > sz[r_b]) {
            id[r_b] = r_a;
            sz[r_a] += sz[r_b];
        } else {
            id[r_a] = r_b;
            sz[r_b] += sz[r_a];
        }
    }

    bool Connected(int a,int b) {
        return find_root(a) == find_root(b);
    }

private:
    int find_root(int a) {
        while(id[a]!=a) {
            int b = id[a];
            id[a] = id[id[a]];
            a = b;
        }
        return a;
    }

    vector<int> id;
    vector<int> sz;
};

int main() {
    UF uf(10);
    uf.Union(0,1);
    uf.Union(1,2);
    uf.Union(3,1);

    uf.Union(4,5);  
    uf.Union(6,5); 

    uf.Union(9,8);
    uf.Union(8,9);
    uf.Union(7,9);

    cout<<uf.Connected(0,9)<<endl;
    cout<<uf.Connected(0,3)<<endl;
    cout<<uf.Connected(4,6)<<endl;
    cout<<uf.Connected(5,9)<<endl;
    cout<<uf.Connected(7,8)<<endl;
}
