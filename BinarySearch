#include <iostream>
#include <algorithm>
#include <vector>

int search(std::vector<int>& nums,int value) {
    int l = 0;
    int r = nums.size() - 1;
    while(l<=r) {
        int m = l + (r-l) / 2;
        if(nums[m]==value) return m;
        else if(nums[m]<value) l = m + 1;
        else r = m - 1;
    }
    return -1;
}

int lower_bound(std::vector<int>& nums,int value) {
    int l = 0;
    int r = nums.size();
    while(l<r) {
        int m = l + ((r-l)>>1);
        if(nums[m]>=value) r = m;
        else l = m + 1;
    }
    return l;
}

int upper_bound(std::vector<int>& nums,int value) {
    int l = 0;
    int r = nums.size();
    while(l<r) {
        int m = l + ((r-l)>>1);
        if(nums[m]>value) r = m;
        else l = m + 1;
    }
    return l;
}

int main() {
    std::vector<int> A{1,1,2,3,3,4,5,6};
    int value = 4;
    int res = upper_bound(A,value);
    std::cout<<res<<std::endl;
    // std::vector<int>::iterator cit = std::lower_bound(A.begin(),A.end(),value);
    // std::cout<<(cit==A.begin())<<std::endl;
}
