#include <iostream>
#include <fstream>
#include <cstring>
#include "./tm_usage.h"

using namespace std;

int Top_Down(int* chords, int** MPS, int** CASE, int i, int j);

void find_max_chords(int** CASE, int* chords, bool* max_chords, int i, int j);

void help_message() {
    cout << "usage: ./mps <input_file> <output_file>" << endl;
}

int main(int argc, char *argv[]) {

    if (argc != 3){
        help_message();
        return 0;
    }
    
    CommonNs::TmUsage tmusg;
    CommonNs::TmStat stat;

    ifstream infile;
    ofstream outfile;

    infile.open(argv[1]);
    outfile.open(argv[2]);

    int num;
    infile >> num;

    int* chords = new int[num];
    int** MPS = new int*[num];
    int** CASE = new int*[num];
    bool* max_chords = new bool[num];

    for (int i=0 ; i<num ; ++i){
        MPS[i] = new int[num];
        CASE[i] = new int[num];
        max_chords[i] = false;
    }

    for (int i=0 ; i<num ; ++i){
        for (int j=0 ; j<num ; ++j){
            MPS[i][j] = -1;
            CASE[i][j] = 0;
        }
    }

    // read input file
    int point1, point2;
    for (int i=0 ; i<(num/2) ; ++i){
        infile >> point1 >> point2;
        chords[point1] = point2;
        chords[point2] = point1;
    }

    tmusg.periodStart();

    // DP Algorithm
    int ans = Top_Down(chords, MPS, CASE, 0, num-1);
    find_max_chords(CASE, chords, max_chords, 0, num-1);
    
    // CPU time and memory use
    tmusg.getPeriodUsage(stat);
    cout << "Total CPU time: " << (stat.uTime + stat.sTime) / 1000.0 << "ms" << endl; 
    cout << "memory: " << stat.vmPeak << "KB" << endl;


    // write output file
    outfile << ans << "\n";
    for (int i=0 ; i<num ; ++i){
        if (max_chords[i]){
            outfile << i << " " << chords[i] << "\n";  
            max_chords[chords[i]] = false;
        }
    }

    infile.close();
    outfile.close();

    return 0;
}


int Top_Down(int* chords, int** MPS, int** CASE, int i, int j){
    if (MPS[i][j] != -1){
        return MPS[i][j];
    }

    if(i == j){
        MPS[i][j] = 0;
    } else {
        int k = chords[j];
        if(k == i){
            MPS[i][j] = Top_Down(chords, MPS, CASE, i+1, j-1) + 1;
            CASE[i][j] = 1;
        } else if(k > i && k < j){
            int choose_chord_kj = Top_Down(chords, MPS, CASE, i, k-1) + Top_Down(chords, MPS, CASE, k+1, j-1) + 1;
            int not_choose_chord_kj = Top_Down(chords, MPS, CASE, i, j-1);
            if(choose_chord_kj >= not_choose_chord_kj){
                MPS[i][j] = choose_chord_kj;
                CASE[i][j] = 2;
            } else{
                MPS[i][j] = not_choose_chord_kj;
                CASE[i][j] = 3;
            }
        } else {
            MPS[i][j] =  Top_Down(chords, MPS, CASE, i, j-1);
            CASE[i][j] = 4;
        }
    }

    return MPS[i][j];
}


void find_max_chords(int** CASE, int* chords, bool* max_chords, int i, int j){
    if (i>=j){
        return;
    }

    if (CASE[i][j] == 1){
        max_chords[i] = true;
        max_chords[j] = true;
        find_max_chords(CASE, chords, max_chords, i+1, j-1);
    } else if (CASE[i][j] == 2){
        int k = chords[j];
        max_chords[k] = true;
        max_chords[j] = true;
        find_max_chords(CASE, chords, max_chords, i, k-1);
        find_max_chords(CASE, chords, max_chords, k+1, j-1);
    } else if (CASE[i][j] == 3 || CASE[i][j] == 4){
        find_max_chords(CASE, chords, max_chords, i, j-1);
    }
}


