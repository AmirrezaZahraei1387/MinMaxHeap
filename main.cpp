#include <iostream>
#include <vector>
#include "MinMaxH/MinMaxHeap.hpp"

using APP_TYPE = int;

std::vector<std::string> split(const std::string& s, const std::string& delimiter) {
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos) {
        token = s.substr (pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back (token);
    }

    res.push_back (s.substr (pos_start));
    return res;
}


bool getCommand(std::string& command, std::string& args){
    std::cin>>command;

    if(command == "insertHeap") {
        std::cin >> args;
        return true;
    }else if(command == "buildHeap"){
        std::getline(std::cin, args);
        return true;
    }else if(command == "deleteMin"){
        return true;
    }else if(command == "deleteMax"){
        return true;
    }else if(command == "findMin"){
        return true;
    }else if(command == "findMax"){
        return true;

    }else if(
#ifdef TEST_IS_MIN_MAX_HEAP
    command == "check"
#else
    false
#endif
    ){
        return true;
    }else if(command == "print") {
        return true;
    }else if(command == "getSize") {
        return true;
    }else if(command == "exit") {
        return true;
    }else if(command == "clear"){
        return true;
    }else
        return false;
}


void processCommand(MinMaxHeap<APP_TYPE>& mmh, const std::string& command, const std::string& args){

    if(command == "insertHeap") {
        mmh.insert(std::stoi(args));

    }else if(command == "buildHeap"){
        std::vector<std::string> as{split(args, " ")};

        std::vector<APP_TYPE> as_int;

        for(auto& num: as) {
            if(num != "\0")
                as_int.push_back(std::stoi(num));
        }

        mmh.reBuild(as_int.begin(), as_int.end());
    }else if(command == "deleteMin"){
        mmh.deleteMin();
    }else if(command == "deleteMax"){
        mmh.deleteMax();
    }else if(command == "findMin"){
        std::cout<<mmh.findMin()<<std::endl;
    }else if(command == "findMax"){
        std::cout<<mmh.findMax()<<std::endl;
    }else if(
#ifdef TEST_IS_MIN_MAX_HEAP
command == "check"
#else
        false
#endif
            ){
#ifdef TEST_IS_MIN_MAX_HEAP
        std::cout<<isMinMaxHeap(mmh)<<std::endl;
#endif
    }else if(command == "print"){
        std::cout<<mmh<<std::endl;
    }else if(command == "getSize"){
        std::cout<<mmh.size()<<std::endl;
    }else if(command == "clear"){
        mmh.makeEmpty();
    }
}


int main() {

    std::string args;
    std::string command;

    MinMaxHeap<APP_TYPE> mmHeap;

    while(true){
        if(!getCommand(command, args)) {
            std::cerr << "Error: undefined command" << std::endl;
            continue;
        }

        if(command == "exit")
            break;

        processCommand(mmHeap, command, args);
    }

    return 0;
}
