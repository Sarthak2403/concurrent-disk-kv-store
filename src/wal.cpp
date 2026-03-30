#include "wal.h"

WAL::WAL(const std::string& filename) : filename_(filename), log_writer_(filename, std::ios::binary | std::ios::app) {}

void WAL::append(const std::string& key, const std::string& value) {
    std::lock_guard<std::mutex> lock(wal_mutex_);

    uint32_t ksize = key.size();
    uint32_t vsize = value.size();

    log_writer_.write(reinterpret_cast<char*>(&ksize), sizeof(ksize));
    log_writer_.write(reinterpret_cast<char*>(&vsize), sizeof(vsize));
    log_writer_.write(key.data(), ksize);
    log_writer_.write(value.data(), vsize);

    log_writer_.flush();
}

void WAL::recover(std::unordered_map<std::string, std::string>& map) {
    std::ifstream reader(filename_, std::ios::binary);

    while(true){
        uint32_t ksize, vsize;

        if(!reader.read(reinterpret_cast<char*>(&ksize), sizeof(ksize)))
            break;
        if(!reader.read(reinterpret_cast<char*>(&vsize), sizeof(vsize)))
            break;
        
        std::string key(ksize, '\0');
        std::string value(vsize, '\0');

        if(!reader.read(&key[0], ksize)) break;
        if(!reader.read(&value[0], vsize)) break;

        map[key] = value;
    }

}

WAL::~WAL() {
    if(log_writer_.is_open()){
        log_writer_.flush();
        log_writer_.close();
    }
};