#include <iostream>
#include <string.h>
#include "sha256.h"
#include <taskflow.hpp>

//Run Command for output eg: ./main.o neeraj http://lochan.website 21e8 1

void output_state(std::string keyword, std::string data, std::string data_hash, 
    std::string rotation_hash, uint64_t nonce, std::string target) {
    // output the state of a successful mining rotation to stdout

    std::cout << "DATA: " << data << std::endl;
    std::cout << "DATA HASH: " << data_hash << std::endl;
    std::cout << "ROTATION HASH: " << rotation_hash << std::endl;
    std::cout << "NONCE: " << nonce << std::endl;
    std::cout << "SOURCE: " << keyword << std::endl;
    std::cout << "TARGET: " << target << std::endl;
    std::cout << "-------------------------------\n" << std::endl;
}

bool is_prefix(std::string target, std::string data) {
    // checks if the target is a prefix of the data at index 0
    // i.e. the data "starts with" the target

    return data.substr(0, target.length()) == target;
}

std::string get_hash(std::string s) {
    // hashes data using sha256 and returns the digest

    SHA256 sha256;
    std::string digest = sha256(s);
    return digest;
}

int mine(std::string keyword, std::string data, std::string target, std::string mode) {
    // performs the mining, mode 1 -> rotate, mode 2 -> fork

    // perform initial total hash
    std::cout << "ROTATION 0:" << std::endl;
    std::string data_hash = get_hash(data);
    tf::Taskflow tf;
    tf::Executor ex;
    std::string final_h;
    uint64_t final_n[24];
    tf.for_each_index(0, 24, 1, [&](int i) {
        uint64_t nonce = i;
        std::string concatenated_str = keyword + data_hash + std::to_string(nonce);
        std::string total_hash = "";
        while (!is_prefix(target, total_hash) && !final_n[i]) {
            nonce += 8;
            concatenated_str = keyword + data_hash + std::to_string(nonce);
            total_hash = get_hash(concatenated_str);
        }
        if (is_prefix(target, total_hash)) {
            final_h = total_hash;
            for (int j = 0; j<24; j++) final_n[j] = nonce;
        }
    });
    ex.run(tf).wait();
    // perform first rotation of mining
    
    
    output_state(keyword, data, data_hash, final_h, final_n[0], target);

    return 0;
}

int main(int argc, char* argv[]) {

    if (argc <= 4) {
        std::cout << "Provide 4 args: {keyword} {data} {target} {mining mode}" << std::endl;
        return EXIT_FAILURE;
    }
    
    std::string keyword = argv[1];
    std::string data = argv[2];
    std::string target = argv[3];
    std::string mode = argv[4];

    int val = mine(keyword, data, target, mode);

    return val;
}