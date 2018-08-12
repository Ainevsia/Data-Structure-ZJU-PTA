#include <iostream>

using namespace std;

void comparetree(int n, int l);

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    while (true) {
        int n;cin>>n;
        if (n==0) break;
        int l;cin>>l;
        comparetree(n,l);
    }
    return 0;
}

void print(bool same)
{
    switch (same) {
        case true: cout << "Yes" << endl;break;
        case false:cout << "No"  << endl;break;
    }
}

void comparetree(int n, int l)
{
    int * src = new int [n];                        //src--the original array
    int * select = new int [n];                     //select 0-->not added to the cmp tree
    for (size_t i = 0; i < n; i++) cin >> src[i];   //select 1-->added to the cmp tree
    int * cmp = new int [n];
    for (size_t i = 0; i < l; i++) {
        bool same = true;
        for (size_t i = 0; i < n; i++) {cin >> cmp[i];select[i]=0;}
        if (src[0]!=cmp[0]) {                       //judge the head
            same = false;
            print(same);
            continue;
        }else select[0] = 1;
        for (size_t i = 1; i < n && same; i++) {    //i--indecate the cmp node
            int rootcmp = src[0];
            for (size_t k = 1; k < n; k++) {
                if (src[k]>rootcmp&&select[k]==1&&cmp[i]>rootcmp) {
                    rootcmp = src[k];
                }else if (src[k]<rootcmp&&select[k]==1&&cmp[i]<rootcmp) {
                    rootcmp = src[k];
                }
            }
            for (size_t j = 1; j < n; j++) {
                if (select[j]==1) continue;
                if (cmp[i]==src[j]) {
                    select[j] = 1;
                    break;
                }
                int rootsrc = src[0];
                for (size_t k = 1; k < j; k++) {
                    if (src[k]>rootsrc&&src[j]>rootsrc) {
                        rootsrc = src[k];
                    }else if (src[k]<rootsrc&&src[j]<rootsrc) {
                        rootsrc = src[k];
                    }
                }
                if (rootcmp==rootsrc) {
                    if (cmp[i]>rootcmp&&src[j]>rootsrc&&cmp[i]!=src[j]) {
                        same = false;
                        print(same);
                        break;
                    }
                    if (cmp[i]<rootcmp&&src[j]<rootsrc&&cmp[i]!=src[j]) {
                        same = false;
                        print(same);
                        break;
                    }
                }
            }
        }
        if (same) print(same);
    }
}
