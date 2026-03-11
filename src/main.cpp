#include "kv_store.h"
#include <thread>
#include <vector>


void writer(KVStore& store, int id){
    for(int i = 0; i <= 1000; i++){
        store.put("key"+std::to_string(id*1000+i),
        "value"+std::to_string(i));
    }
}

int main(){
    // KVStore db("database.wal");

    // db.put("name", "Sarthak");
    // db.put("city", "Chicago");

    // std::cout<< db.get("name")<< "\n";
    // std::cout<< db.get("city")<< "\n";

    KVStore store("log.wal");
    std::vector<std::thread> threads;

    for(int i = 0; i<4; i++){
        threads.emplace_back(writer, std::ref(store), i);
    }

    for(auto& t: threads){
        t.join();
    }

}
