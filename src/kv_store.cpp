#include "kv_store.h"

KVStore::KVStore(const std::string& wal_file): wal_(wal_file) {
    wal_.recover(store_);
}

void KVStore::put(const std::string& key, const std::string& value) {
    std::unique_lock<std::shared_mutex> lock(mutex_);

    wal_.append(key, value);
    store_[key] = value;
};

std::string KVStore::get(const std::string& key) const{
    std::shared_lock<std::shared_mutex> lock(mutex_);
    
    auto it = store_.find(key);

    if(it == store_.end()){
        return "";
    }

    return it->second;

};