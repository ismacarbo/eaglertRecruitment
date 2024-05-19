#include <map>
#include <vector>
#include <stdint.h>
#include <fstream>


extern std::map<uint16_t, std::vector<long>> messaggi; //gia definita nel main

//calcola e salva le statistiche
void compute_statistics() {
    std::ofstream fileStatistiche("statistiche.csv"); //scrivo le stats nel csv
    fileStatistiche << "ID,number_of_messages,mean_time\n"; //come descritto nella consegna
    for (const auto &dato : messaggi)  { //itero nelle coppie della mappa ID,TIMESTAMP
        if (dato.second.size() > 1) { //piu di un timestamp per l'ID corrente?
            long tempoTotale = 0;
            //dal secondo elemento
            for (size_t i = 1; i < dato.second.size(); i++) { 
                //sommo la differenza di tempo tra i timestamp successivi
                tempoTotale += (dato.second[i] - dato.second[i - 1]); 
            }
            long mean_time = tempoTotale / (dato.second.size() - 1); //calcolo tempo medio tra messaggi con ID uguali
            //scrivo sul file le informazioni richieste: numeroMessaggi e tempo medio nel csv
            fileStatistiche << std::hex << dato.first << std::dec << "," << dato.second.size() << "," << mean_time << "\n"; 
        }
    }
}
