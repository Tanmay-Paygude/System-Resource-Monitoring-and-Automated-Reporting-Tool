
#include <iostream>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
#include <sys/sysinfo.h>
#include <cstdlib>

// Function to get CPU usage
float getCPUUsage() {
    std::string line;
    float cpu_usage = 0.0;

    std::ifstream file("/proc/stat");
    if (file.is_open()) {
        getline(file, line);
        file.close();
        
        int user, nice, system, idle, iowait, irq, softirq;
        sscanf(line.c_str(), "cpu  %d %d %d %d %d %d %d", &user, &nice, &system, &idle, &iowait, &irq, &softirq);
        
        int total = user + nice + system + idle + iowait + irq + softirq;
        int total_idle = idle + iowait;
        cpu_usage = (float)(total - total_idle) / total * 100.0;
    }

    return cpu_usage;
}

// Function to get memory usage
float getMemoryUsage() {
    struct sysinfo memInfo;
    sysinfo(&memInfo);
    long totalPhysMem = memInfo.totalram;
    long physMemUsed = memInfo.totalram - memInfo.freeram;

    return (float)physMemUsed / totalPhysMem * 100;
}

// Function to get disk usage
float getDiskUsage() {
    std::string command = "df / | awk 'NR==2 {print $5}' > disk_usage.txt";
    system(command.c_str());

    std::ifstream file("disk_usage.txt");
    std::string diskUsage;
    if (file.is_open()) {
        file >> diskUsage;
        file.close();
    }
    return std::stof(diskUsage);
}

int main() {
    while (true) {
        float cpu = getCPUUsage();
        float memory = getMemoryUsage();
        float disk = getDiskUsage();

        std::cout << "CPU Usage: " << cpu << "%\n";
        std::cout << "Memory Usage: " << memory << "%\n";
        std::cout << "Disk Usage: " << disk << "%\n";

        std::ofstream dataFile("system_metrics.txt");
        if (dataFile.is_open()) {
            dataFile << cpu << "\n" << memory << "\n" << disk << "\n";
            dataFile.close();
        }

        std::this_thread::sleep_for(std::chrono::seconds(60));
    }

    return 0;
}
