//
//  InputProcesser.hpp
//  Database 1.0
//
//  Created by Saman Givian on 7/7/22.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#ifndef InputProcesser_hpp
#define InputProcesser_hpp

class InputProcesser{
public:
    typedef struct {
        std::string buffer;
        size_t buffer_length;
        ssize_t input_length;
    } InputBuffer;
};

InputProcesser:: InputBuffer read_input();

#endif /* InputProcesser_hpp */
