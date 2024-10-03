#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

long long inc(long long timer){
    return timer;
}

void csma_cd_simulation(int num_stations, int total_slots, int k) {
    float timer = 51.2;
    std::vector<bool> stations(num_stations, true);
    std::vector<int> transmission_times(num_stations, 0);
    std::vector<int> successful_transmissions(num_stations, 0);
    std::vector<int> collisions(num_stations, 0);
    int total_collisions = 0;

    std::cout << "\nSimulation started...\n";
    std::cout << "-------------------\n";

    for (int slot = 0; slot < total_slots; slot++) {
        std::vector<int> ready_stations;
        for (int i = 0; i < num_stations; i++) {
            if (stations[i] && transmission_times[i] == slot) {
                ready_stations.push_back(i);
            }
        }

        if (ready_stations.empty()) {
            std::cout << "Slot " << slot <<" ("<< timer*(slot+1) <<" μs)" << ": No stations ready to transmit.\n";
            continue;
        }

        if (ready_stations.size() == 1) {
            int station = ready_stations[0];
            std::cout << "Slot " << slot <<" ("<< timer*(slot+1) <<" μs)" << ": Station " << station << " successfully began transmitting.\n";
            transmission_times[station] = slot + 1;
            successful_transmissions[station]++;
            continue;
        }

        std::cout << "Slot " << slot <<" ("<< timer*(slot+1) <<" μs)" << ": Collision detected between stations: ";
        for (size_t i = 0; i < ready_stations.size(); ++i) {
            std::cout << ready_stations[i];
            if (i < ready_stations.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;

        total_collisions++;

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3); 
        for (int station : ready_stations) {
            int backoff_time = dis(gen);
            transmission_times[station] = slot + 1 + backoff_time;
            collisions[station]++;
            if(collisions[station] > k){
                stations[station] = false;
                std::cout << " Station " << station << " exceeded the retransmission limit" << std::endl;
            }
            if(stations[station])
                std::cout << "  Station " << station << " will retry at slot " << transmission_times[station] << std::endl;
        }
    }

    std::cout << "\nSimulation completed.\n";
    std::cout << "---------------------\n";
    std::cout << "Total collisions: " << total_collisions << std::endl;
    std::cout << "\nStation Statistics:\n";
    std::cout << std::setw(10) << "Station" 
              << std::setw(15) << "Successful" 
              << std::setw(15) << "Collisions" << std::endl;
    std::cout << std::setw(10) << "Number" 
              << std::setw(15) << "Transmissions" 
              << std::setw(15) << "Involved" << std::endl;
    std::cout << std::string(40, '-') << std::endl;

    for (int station = 0; station < num_stations; station++) {
        std::cout << std::setw(10) << station 
                  << std::setw(15) << successful_transmissions[station]
                  << std::setw(15) << collisions[station] << std::endl;
    }

    std::cout << std::string(40, '-') << std::endl;
}


int main() {
    int num_stations, total_slots;

    std::cout << "CSMA/CD Network Simulation\n";
    std::cout << "==========================\n";    

    do {
        std::cout << "Enter the number of stations (1-100): ";
        std::cin >> num_stations;
        if (num_stations < 1 || num_stations > 100) {
            std::cout << "Invalid input. Please enter a number between 1 and 100.\n";
        }
    } while (num_stations < 1 || num_stations > 100);

    do {
        std::cout << "Enter the total number of time slots (10-1000): ";
        std::cin >> total_slots;
        if (total_slots < 10 || total_slots > 1000) {
            std::cout << "Invalid input. Please enter a number between 10 and 1000.\n";
        }
    } while (total_slots < 10 || total_slots > 1000);

    csma_cd_simulation(num_stations, total_slots, 15);

    return 0;
}