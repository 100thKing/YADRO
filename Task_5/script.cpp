#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

string line;
ifstream DL_RLC("source/DlRlcStats.txt");
ifstream UL_RLC("source/UlRlcStats.txt");

int main() 
{
    float Tx_DL_1 = 0;
    float Tx_DL_2 = 0;
    float Rx_DL_1 = 0;
    float Rx_DL_2 = 0;
    float Tx_UL_1 = 0;
    float Tx_UL_2 = 0;
    float Rx_UL_1 = 0;
    float Rx_UL_2 = 0;
    float time = 0; 

    if (!DL_RLC || !UL_RLC) 
    {
        cout << "Не удалось открыть входной файл" << endl;
        return 1;
    }

    
    getline(DL_RLC, line); //skip column names

    while (getline(DL_RLC, line)) 
    {
        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, '\t')) 
        {
            tokens.push_back(token);
        }
        int imsi = stoi(tokens[3]);
        if (imsi == 2) 
        {
            time += (stod(tokens[1]) - stod(tokens[0]));
            Tx_DL_2+= stoi(tokens[7]);
            Rx_DL_2+= stoi(tokens[9]);
        } else 
        {
            Tx_DL_1+= stoi(tokens[7]);
            Rx_DL_1+= stoi(tokens[9]);
        }
    }
    
    getline(UL_RLC,line); //skip column names

    while (getline(UL_RLC, line)) 
    {
        istringstream iss(line);
        vector<string> tokens;
        string token;

        while (getline(iss, token, '\t')) 
        {
            tokens.push_back(token);
        }

        int imsi = stoi(tokens[3]);

        if (imsi == 2) 
        {
            Tx_UL_2+= stoi(tokens[7]);
            Rx_UL_2+= stoi(tokens[9]);
        } else 
        {
            Tx_UL_1+= stoi(tokens[7]);
            Rx_UL_1+= stoi(tokens[9]);
        }
    }

    DL_RLC.close();
    UL_RLC.close();

    cout.precision(10);
    cout << "Time: " << time << endl;
    cout << "Throughput_Tx_Dl_Client_1: " << Tx_DL_1 / time << " Bytes per second" << endl;
    cout << "Throughput_Rx_Dl_Client_1: " << Rx_DL_1 / time << " Bytes per second" << endl;
    cout << "Throughput_Tx_Dl_Client_2: " << Tx_DL_2 / time << " Bytes per second" << endl;
    cout << "Throughput_Rx_Dl_Client_2: " << Rx_DL_2 / time << " Bytes per second" << endl;
    cout << "Throughput_Tx_Ul_Client_1: " << Tx_UL_1 / time << " Bytes per second" << endl;
    cout << "Throughput_Rx_Ul_Client_1: " << Rx_UL_1 / time << " Bytes per second" << endl;
    cout << "Throughput_Tx_Ul_Client_2: " << Tx_UL_2 / time << " Bytes per second" << endl;
    cout << "Throughput_Rx_Ul_Client_2: " << Rx_UL_2 / time << " Bytes per second" << endl;
    

    return 0;
}
