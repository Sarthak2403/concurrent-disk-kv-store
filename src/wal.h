#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <mutex>

class WAL {
    public:
        explicit WAL(const std::string& filename);
        ~WAL();

        void append(const std::string& key, const std::string& value);
        void recover(std::unordered_map<std::string, std::string>& map);

    private:
        std::string filename_;
        std::ofstream log_writer_;
        std::mutex wal_mutex_;
};