//
//  main.cpp
//  Database 1.0
//
//  Created by Saman Givian on 7/7/22.
//
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "InputProcesser.hpp"
#include "CommandProcessor.hpp"//;
#include "BPTree.hpp"

/* commands
 CREATE TABLE
 INSERT INTO
 SELECT FROM
 DROP TABLE
 WHERE
 AND
 OR
 JOIN/ THETA JOIN/ NATURAL JOIN
 GROUP BY
 PRIMARY
 FOREIGN KEY
 */
// Reading input from Terminal


int main(int argc, const char * argv[]) {
   
    BPTree BPTreeList[100];
    record_node *RecordNodes[100][100];
    int c = 0;
    int ReleationCounter = 0;
    std::cout<<"To learn how this database works type '.help'"<<std::endl;
    while(true){
        InputProcesser::InputBuffer user_input = read_input();
        //printf(user_input.buffer);
        CommandExecuter(&user_input,BPTreeList,&ReleationCounter,RecordNodes);
        std::cout <<"\n Releation Counter: "<< ReleationCounter <<std::endl;
        printf("\n");
       
        
        if(c >= 2){
            //cout<<RecordNodes[0][0]->record[0]<<endl;
            //cout<<RecordNodes[0][0]->record[1]<<endl;
            //DisplayReleation(BPTreeList[0],BPTreeList[0].getRoot());
            //cout<<"PK: "<<BPTreeList[0].Primarykey<<endl;
            //BPTreeList[0].display(BPTreeList[0].getRoot());
            BPTreeList[0].ReleationDisplay(BPTreeList[0], BPTreeList[0].getRoot());
        }
        c++;
         
    }
    return 0;
}
