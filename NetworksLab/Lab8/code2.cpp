#include <iostream>
#include <vector>
#include <random>
#include <iomanip>

const double SLOT_TIME_MS = 0.0512;  // Slot time in milliseconds (51.2 μs)
const int FRAME_TIME_SLOTS = 10;     // Assume a frame takes 10 slots to transmit

void csma_cd_simulation(int num_stations, int total_slots) {
    std::vector<bool> stations(num_stations, true);
    std::vector<int> transmission_times(num_stations, 0);
    std::vector<int> transmission_duration(num_stations, 0); // Duration of current transmission
    std::vector<int> successful_transmissions(num_stations, 0);
    std::vector<int> collisions(num_stations, 0);
    int total_collisions = 0;

    std::cout << "\nSimulation started...\n";
    std::cout << "-------------------\n";

    for (int slot = 0; slot < total_slots; slot++) {
        double current_time_ms = slot * SLOT_TIME_MS;
        std::vector<int> ready_stations;

        for (int i = 0; i < num_stations; i++) {
            // Check if a station is not currently transmitting and is ready
            if (stations[i] && transmission_times[i] == slot && transmission_duration[i] == 0) {
                ready_stations.push_back(i);
            }
        }

        if (ready_stations.empty()) {
            std::cout << "Slot " << slot << " (" << current_time_ms << " ms): No stations ready to transmit.\n";
            continue;
        }

        if (ready_stations.size() == 1) {
            int station = ready_stations[0];
            std::cout << "Slot " << slot << " (" << current_time_ms << " ms): Station " << station << " successfully began transmitting.\n";
            transmission_duration[station] = FRAME_TIME_SLOTS;  // Transmission takes 10 slots
            successful_transmissions[station]++;
            continue;
        }

        // Collision detected if more than one station is ready to transmit
        std::cout << "Slot " << slot << " (" << current_time_ms << " ms): Collision detected between stations: ";
        for (size_t i = 0; i < ready_stations.size(); ++i) {
            std::cout << ready_stations[i];
            if (i < ready_stations.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;

        total_collisions++;

        // Backoff for each station involved in the collision
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0, 3);  // Random backoff range [0, 3 slots]
        for (int station : ready_stations) {
            int backoff_time = dis(gen);
            transmission_times[station] = slot + 1 + backoff_time;
            collisions[station]++;
            transmission_duration[station] = 0;  // Reset transmission duration on collision
            std::cout << "  Station " << station << " will retry at slot " << transmission_times[station] << std::endl;
        }
    }

    std::cout << "\nSimulation completed.\n";
    std::cout << "---------------------\n";
    std::cout << "Total collisions: " << total_collisions << std::endl;
    std::cout << "\nStation Statistics:\n";
    std::cout << std::setw(10) << "Station" << std::setw(15) << "Successful" << std::setw(15) << "Collisions" << std::endl;
    std::cout << std::setw(10) << "Number" << std::setw(15) << "Transmissions" << std::setw(15) << "Involved" << std::endl;
    std::cout << std::string(40, '-') << std::endl;
    for (int station = 0; station < num_stations; station++) {
        std::cout << std::setw(10) << station 
                  << std::setw(15) << successful_transmissions[station]
                  << std::setw(15) << collisions[station] << std::endl;
    }
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

    csma_cd_simulation(num_stations, total_slots);

    return 0;
}
