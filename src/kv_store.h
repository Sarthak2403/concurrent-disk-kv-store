#pragma once
#include <string>
#include <unordered_map>
#include "wal.h"
#include <shared_mutex>

class KVStore {
    public:
        explicit KVStore(const std::string& wal_file);

        void put(const std::string& key, const std::string& value);
        std::string get(const std::string& key) const;
    
    private:
        std::unordered_map<std::string, std::string> store_;
        WAL wal_;

        mutable std::shared_mutex mutex_;
};
