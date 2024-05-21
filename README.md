# CAN Bus Message Processor

## Overview

This project implements a CAN Bus message processor in C++. It includes functionalities for state management, message logging, parsing, statistics collection, and multithreaded message reception. The system can transition between two states (`Inattivo` and `Esecuzione`) based on specific CAN messages. 

## Components

### 1. FSM (Finite State Machine)

Manages the system states (`Inattivo` and `Esecuzione`).

- **Functions**:
  - `void cambiaStato(Stato nuovoStato)`
  - `Stato ottieniStato()`
  - `void iniziaLog()`
  - `void fermaLog()`
  - `void processaMessaggio_fsm(const std::string& messaggio)`

- **Global Variables**:
  - `std::mutex statoMutex`
  - `Stato statoCorrente`
  - `std::unordered_map<uint16_t, std::vector<long>> messaggi`

### 2. Logging

Handles logging of messages to a file.

- **Functions**:
  - `void iniziaLogLogging()`
  - `void stopLog()`
  - `void processaMessaggio_logging(const std::string& messaggio)`

- **Global Variable**:
  - `std::ofstream fileLog`

### 3. Message Parsing

Parses incoming CAN messages into IDs and payloads.

- **Function**:
  - `void parseMessaggio(const std::string& message, uint16_t& id, std::vector<uint8_t>& payload)`

### 4. Statistics

Collects and saves statistics about message processing.

- **Structure**:
  - `struct Statistiche`

- **Functions**:
  - `void aggiornaStatistiche(const std::string& id, uint64_t timestamp)`
  - `void salvaStatistiche()`

- **Global Variable**:
  - `std::unordered_map<std::string, Statistiche> mappaStatistiche`

### 5. Thread Receiver

Manages the reception of CAN messages in a separate thread.

- **Functions**:
  - `void avviaThreadRicezione()`
  - `void fermaThreadRicezione()`
  - `void threadRicezioneCAN()`

- **Global Variables**:
  - `std::mutex codaMutex`
  - `std::condition_variable codaCV`
  - `std::queue<std::string> codaMessaggi`
  - `std::atomic<bool> inEsecuzione`
  - `std::thread threadRicezione`

## Installation

1. **Clone the repository**:
    ```sh
    git clone https://github.com/ismacarbo/eagletrtRecruitment.git
    cd eagletrtRecruitment
    ```

2. **Build the project**:
    ```sh
    mkdir build
    cd build
    cmake ..
    make
    ```

## Usage

1. **Run the main application**:
    ```sh
    ./bin/project_2
    ```

2. **Simulate CAN messages**:
    - Open `candump.log` file and append CAN messages to simulate.

## File Descriptions

- `include/fsm.h`: Header for state management.
- `include/logging.h`: Header for logging functionality.
- `include/parse.h`: Header for message parsing.
- `include/statistics.h`: Header for statistics management.
- `include/threadReceiver.h`: Header for the message receiver thread.
- `src/fsm.cpp`: Implementation of the FSM.
- `src/logging.cpp`: Implementation of logging functions.
- `src/parse.cpp`: Implementation of message parsing.
- `src/statistics.cpp`: Implementation of statistics functions.
- `src/threadReceiver.cpp`: Implementation of the message receiver thread.
- `main.cpp`: Main application logic.

## Contributing

1. Download this repo. #**Don't Fork it**.
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -m 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Open a pull request

## Acknowledgments

- Assignment for E-Agle Trento Racing Team Recruitment
    
