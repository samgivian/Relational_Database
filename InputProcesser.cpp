//
//  InputProcesser.cpp
//  Database 1.0
//
//  Created by Saman Givian on 7/7/22.
//

#include "InputProcesser.hpp"
      // The class
InputProcesser:: InputBuffer read_input() {
    printf("db > ");
    InputProcesser::InputBuffer user_input;
    std::getline (std::cin,user_input.buffer);
    ssize_t input_size = user_input.buffer.size();
    //error when input is empty
    if (input_size <= 1) {
        printf("Error reading input\n");
        exit(EXIT_FAILURE);
    }
    user_input.input_length = input_size ;
    return user_input;
}
