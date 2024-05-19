#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <ctime>
#include <chrono>
#include <cstdint>
#include <sstream>
#include <iomanip>
#include <parse.cpp>

using namespace std;

extern "C"{
    #include "fake_receiver.h"
}

enum Stato{
    Idle,
    Run
};

Stato statoCorrente=Idle;
ofstream logFile;
ofstream outputLog;
unordered_map<uint16_t, vector<long>> messaggi; //i messaggi vengono codificati in output come: timeStamp messaggio
mutex statoMutex; //come lo stato delle risorse (mutualmente esclusive) non possono essere accedute da due thread nello stesso momento


void iniziaLog(){
    logFile.open("log_" + to_string(chrono::system_clock::now().time_since_epoch().count()) + ".log");
    messaggi.clear();
}

void stopLog(){
    logFile.close();
    //fai le statistiche
}

void processaMessaggio(const string& messaggio){
    //il messaggio è formato da <ID>#<PAYLOAD>
    uint16_t id;
    vector<uint8_t> payload;
    parseMessaggio(messaggio,id,payload);

    auto ora=chrono::system_clock::now().time_since_epoch().count();

     {
        lock_guard<mutex> lock(statoMutex); //blocco il mutex allo stato corrente
        messaggi[id].push_back(ora); //inserisco nella mappa il timeStamp del messaggio ricevuto
    }

    if(statoCorrente==Run){
        loggaMessaggio(messaggio);
    }

}


int main(void){

    

    return 0;
}