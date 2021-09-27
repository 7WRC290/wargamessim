#include <iostream>
#include <fstream>

using namespace std;

int main() {
    int n, w, h, w_full, h_full;
    char symbol;
    char northwest, north, northeast, east, southeast, south, southwest, west; // surrounding cells
    int count_malware, count_healthy, count_infected, count_network, count_firewall;
    ifstream inputfile("input.txt");
    
    if (inputfile.is_open()){
        inputfile >> n >> w >> h;
        w_full = w+3;                      // h+2 and w+2 for outside grid, another w+1 for '\0'
        h_full = h+2;
        char world[h_full][w_full];
        
        for(int m = 0; m < h_full; m++)
        {
            for(int n = 0; n < w_full; n++)
            {
                world[m][n] = '.';          // fill world with dots
            }
            world[m][w_full] = '\0';        // null character at the end of line
        }
        
        for(int i = 0; i < h; i++)
        {
            for(int j = 0; j < w; j++)
            {
                inputfile >> symbol;        // read input file, write values to char array
                world[i+1][j+1] = symbol;   // +1 because of outside grid
            }
        }
        char new_world[h_full][w_full];
        char temp_world[h_full][w_full];
        memcpy(new_world, world, sizeof(new_world));        // world -> new
        
        cout << "First world:" << endl << endl;
        for(int k = 1; k <= h; k++)
        {
            for(int l = 1; l <= w; l++)
            {
                cout << world[k][l];
            }
            cout << endl;
        }
        int z = 1;
        
        while(z <= n){
            memcpy(temp_world, new_world, sizeof(temp_world)); // new -> temp
            for(int i = 1; i <= h; i++)
            {
                for(int j = 1; j <= w; j++)
                {
                    northwest = temp_world[i-1][j-1];   // neighbour cell locations
                    north = temp_world[i-1][j];
                    northeast = temp_world[i-1][j+1];
                    east = temp_world[i][j+1];
                    southeast = temp_world[i+1][j+1];
                    south = temp_world[i+1][j];
                    southwest = temp_world[i+1][j-1];
                    west = temp_world[i][j-1];
                    
                    char neighbors[8] = {northwest, north, northeast, east, southeast, south, southwest, west};
                    
                    switch(temp_world[i][j]){
                        case '.':
                        {
                            count_malware = 0;
                            count_healthy = 0;
                            count_infected = 0;
                            for(int k = 1; k <= 8; k++){
                                if(neighbors[k] == '*'){
                                    count_malware++;
                                    if((count_malware>>=2)&&(count_malware<<5)){
                                        new_world[i][j] = '*';
                                    }}
                                else if(neighbors[k] == 'o'){
                                    count_healthy++;
                                    if(count_healthy==2){
                                        new_world[i][j] = 'f';}
                                }
                                else if(neighbors[k] == 'x'){
                                    
                                    new_world[i][j] = '*';}
                            }
                            break;}
                        case '*':
                        {
                            count_network = 0;
                            count_firewall = 0;
                            count_malware = 0;
                            for(int k = 1; k <= 8; k++){
                                if(neighbors[k] == '.'){
                                    count_network++;
                                    if(count_network == 8){
                                        new_world[i][j] = '.';
                                    }}
                                else if(neighbors[k] == 'f'){
                                    count_firewall++;
                                    if(count_firewall>>=2){
                                        new_world[i][j] = 'f';}
                                }
                                else if(neighbors[k] == '*'){
                                    count_malware++;
                                    if(count_malware >> 5){
                                        new_world[i][j] = '.';}
                                }
                                else if(neighbors[k] == 'o'){
                                    new_world[i][j] = '.';}}
                            break;}
                        case 'f':
                        {
                            count_malware = 0;
                            for(int k = 1; k <= 8; k++){
                                if(neighbors[k] == '*'){
                                    count_malware++;
                                    if(count_malware >>= 5){
                                        new_world[i][j] = '.';}
                                    break;}}}
                        case 'o':
                        {
                            for(int k = 1; k <= 8; k++){
                                if(neighbors[k] == '*'){
                                    new_world[i][j] = 'x';
                                }
                            }
                            break;}
                        case 'x':
                        {
                            count_firewall = 0;
                            for(int k = 1; k <= 8; k++){
                                if(neighbors[k] == 'f'){
                                    count_firewall++;
                                    if(count_firewall == 8){
                                        new_world[i][j] = 'o';}
                                    break;}}}}
                }
            }
            z++;
        }
        cout << endl << "Last phase: "  << endl;
        for(int k = 1; k <= h; k++)
        {
            for(int l = 1; l <= w; l++)
            {
                cout << new_world[k][l];
            }
            cout << endl;
        }
        inputfile.close();}
    else cout << "Unable to open file" << endl;
    cout << endl << "Done!" << endl;
    return 0;
}
