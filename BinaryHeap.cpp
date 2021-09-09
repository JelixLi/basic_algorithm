#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

class PQ {
public:
    PQ() { elems.resize(1); }

    PQ(const PQ&) = delete;
    PQ& operator=(const PQ&) = delete;

    void Insert(int e) {
        elems.push_back(e);
        up(elems.size()-1);
    }

    int Max_elem() {
        assert(elems.size() > 1);
        return elems[1];
    }

    int Del_max_elem() {
        int m = elems[1];
        exch(1,elems.size()-1);
        elems.pop_back();
        down(1);
        return m;
    }

private:
    void up(int idx) {
        while(idx>1 && less(idx>>1,idx)) {
            exch(idx,idx>>1);
            idx >>= 1;
        }
    }

    void down(int idx) {
        while(idx<elems.size()-1) {
            int j = (idx>>1);
            if(less(j,j+1)) j++;
            if(less(idx,j)) exch(idx,j);
            else break;
        }
    }

    void exch(int idx_1,int idx_2) {
        int t = elems[idx_1];
        elems[idx_1] = elems[idx_2];
        elems[idx_2] = t;
    }

    bool less(int idx_1,int idx_2) {
        // max heap
        return elems[idx_1] < elems[idx_2];
    }

    vector<int> elems;
};

int main() {
    PQ pq;
    pq.Insert(0);
    pq.Insert(10);
    pq.Insert(9);
    cout<<pq.Max_elem()<<endl;
    cout<<pq.Del_max_elem()<<endl;
    cout<<pq.Max_elem()<<endl;
    cout<<pq.Del_max_elem()<<endl;
    cout<<pq.Max_elem()<<endl;
    cout<<pq.Del_max_elem()<<endl;
}
