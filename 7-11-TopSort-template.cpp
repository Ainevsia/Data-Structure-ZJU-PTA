//
// Created by xuzhp on 2018/9/21.
//

#include <iostream>
#include "Graph_linked_list.h"
#define inf 10000

using namespace std;

struct switch_point {
    int index;
    int earliest_finish_time;
    int latest_finish_time;
};

int main(int argc, char const *argv[]) {
    freopen("D:\\SJTU\\Freshman Summer\\DS\\test.txt", "r", stdin);
    LGraph Graph = BuildGraph();
    auto * TopOrder = new Vertex [Graph->Nv];
    bool loop_donot_existed = TopSort(Graph,TopOrder);
    if (!loop_donot_existed) {
        cout << 0;
        return 0;
    }
    switch_point * task = new switch_point [Graph->Nv];
    for (int i = 0; i < Graph->Nv; ++i) {
        task[i].index = i;
        task[i].earliest_finish_time = 0;
        task[i].latest_finish_time = inf;
    }

    // setting the earliest time
    int longest_time = 0;
    for (int i = 0; i < Graph->Nv; ++i) {
        //cout << "Now is at node " << TopOrder[i] + 1 << endl;
        PtrToAdjVNode ptr = Graph->G[TopOrder[i]].FirstEdge;
        for ( ; ptr; ptr = ptr->Next) {
            if (ptr->Weight+task[TopOrder[i]].earliest_finish_time > task[ptr->AdjV].earliest_finish_time) {
                task[ptr->AdjV].earliest_finish_time = ptr->Weight+task[TopOrder[i]].earliest_finish_time;
                if (longest_time < task[ptr->AdjV].earliest_finish_time)
                    longest_time = task[ptr->AdjV].earliest_finish_time;
                //cout << "changing " << ptr->AdjV + 1 << "'s time to " << task[ptr->AdjV].earliest_finish_time << endl;
            }
        }
    }

    // setting the latest time
    for (int i = Graph->Nv - 1; i >= 0 ; --i) {
        //cout << "Now is at node " << TopOrder[i] + 1 << endl;
        PtrToAdjVNode ptr = Graph->G[TopOrder[i]].FirstEdge;
        if (!ptr) {
            task[TopOrder[i]].latest_finish_time = longest_time;
            //cout << "changing " << TopOrder[i] + 1 << "'s latest time to " << task[TopOrder[i]].earliest_finish_time << endl;
            continue;
        }
        for ( ; ptr; ptr = ptr->Next) {
            if (task[ptr->AdjV].latest_finish_time - ptr->Weight < task[TopOrder[i]].latest_finish_time) {
                task[TopOrder[i]].latest_finish_time = task[ptr->AdjV].latest_finish_time - ptr->Weight;
                //cout << "changing " << ptr->AdjV + 1 << "'s latest time to " << task[TopOrder[i]].latest_finish_time << endl;
            }
        }
    }
    // output
    cout << task[TopOrder[Graph->Nv-1]].earliest_finish_time << endl;
    for (int i = 0; i < Graph->Nv; ++i) {
        //cout << task[i].index + 1 << ' ' << task[i].latest_finish_time << endl;
        if (task[i].earliest_finish_time!=task[i].latest_finish_time) continue;
        PtrToAdjVNode ptr = Graph->G[i].FirstEdge;
        for ( ; ptr; ptr = ptr->Next) {
            if (task[ptr->AdjV].earliest_finish_time==task[ptr->AdjV].latest_finish_time)
                cout << i + 1 << "->" << ptr->AdjV + 1 << endl;
        }
    }
    return 0;
}