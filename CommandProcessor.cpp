//
//  CommandProcessor.cpp
//  Database 1.0
//
//  Created by Saman Givian on 7/7/22.
//

#include "CommandProcessor.hpp"

void disply_help(){
    //how to make a table
    printf("CREATE TABLE saman givian int asd char PRIMARY KEY givian\n");
    printf("INSERT INTO saman givian VALUES 20\n");
    printf("INSERT INTO saman asd VALUES 15\n");
    printf("INSERT INTO saman givian asd VALUES 10 12\n");
    printf("LOAD saman");
    printf("\nCREATE TABLE test val1 int val2 char\n");
    printf("INSERT INTO test val1 VALUES 20\n");
    printf("SHOW saman\n");
    printf("SELECT * FROM test\n");
    printf("SELECT val2 from test \n");
    //INSERT INTO saman givian VALUES 10
    /*
     CREATE TABLE saman givian int asd char PRIMARY KEY givian
     INSERT INTO saman givian VALUES 20
     INSERT INTO saman asd VALUES 15
     INSERT INTO saman givian asd VALUES 10 12
     SELECT givian FROM saman
     SELECT * FROM saman
     
     CREATE TABLE test givian int asd char PRIMARY KEY givian
     CREATE TABLE test givian int asd char PRIMARY KEY givian
     SELECT givian FROM saman
     */
}

std::vector<std::string> SplitStringByNewLine( std::string str)
{
    auto result = std::vector<std::string>{};
    auto ss = std::stringstream{str};
    
    for (std::string line; std::getline(ss, line, '\r');)
        result.push_back(line);
    
    return result;
}
std::string AddressTokenizer(std::string s)
{
    std:: string del = "/";
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        //std::cout << s.substr(start, end - start) << end;
        start = end + del.size();
        end = s.find(del, start);
    }
    //std::cout << s.substr(start, end - start);
    return  s.substr(start, end - start-4);
}
std:: vector<std::string> StringVectorizer(std::string s)
{
    std::vector<std::string> OutputStringVec;
    std::istringstream ss(s);
    std::string word; // for storing each word
    // Traverse through all words
    // while loop till we get
    // strings to store in string word
    while (ss >> word)
    {
        OutputStringVec.push_back(word);
        // print the read word
        // std::cout << word << "\n";
    }
    // std::cout << "\n";
    //std::cout << s.substr(start, end - start);
    return  OutputStringVec;
}

std::vector<std::string> InputTokenizer(InputProcesser::InputBuffer *user_input) {
    std::vector <std::string> tokens;
    std::stringstream check1(user_input->buffer);
    
    std::string intermediate;
    while(getline(check1, intermediate, ' '))
    {
        tokens.push_back(intermediate);
    }
    /*
     // Printing the token vector
     for(int i = 0; i < tokens.size(); i++)
     std::cout << tokens[i] << '\n';
     */
    return tokens;
}

void CommandExecuter(InputProcesser:: InputBuffer* UserInput, BPTree *BPTreePtr, int * ReleationCounterPtr, record_node *RecordNodesPtr[100][100]){  // Porgram commands
    if(UserInput->buffer[0] == '.'){
        if (UserInput->buffer == ".exit") {
            exit(EXIT_SUCCESS);
        }
        else if (UserInput->buffer == ".help"){
            disply_help();
        }
        else {
            printf("Unrecognized command.\n");
        }
    }
    else{
        std::vector<std::string> InputToken = InputTokenizer(UserInput);
        if (InputToken[0] == "CREATE" && InputToken[1] == "TABLE"){
            
            if(InputToken.size() < 5 ){
                printf("Failed to build the table");
            }
            else{
                bool TableBuild = true;
                std:: string ReleationName  = InputToken[2];
                std:: string PrimaryKey="";
                std::vector<std::string> Attributes;
                std::vector<std::string> AttributesTypes;
                char DirName[100] = "/Users/samangivian/Desktop/Database 1.0/";
                strcat(DirName, ReleationName.c_str());
                if (mkdir(DirName, 0777) == -1){
                    std::cout << "Error :  " << strerror(errno) << std::endl;
                }
                else{
                    std:: ofstream out("/Users/samangivian/Desktop/Database 1.0/" + ReleationName + "/"+ ReleationName+".txt");
                    out << ReleationName.c_str() << "\r" ;
                    
                    for(int i = 3; i < InputToken.size(); i++){
                        if(InputToken[i] == "PRIMARY" ){
                            if(InputToken[i+1] == "KEY"){
                                //table_page[table_page_counter].primarykey = input_token[i+2];
                                PrimaryKey = InputToken[i+2];
                                out <<"PK "<< InputToken[i+2];
                                i = i+3;
                            }
                        }
                        else if(i % 2 == 0){
                            if (InputToken[i] == "char"){
                                out << " char" << "\r";
                                AttributesTypes.push_back(InputToken[i]);
                            }
                            else if(InputToken[i] == "int"){
                                out <<" int"<< "\r";
                                AttributesTypes.push_back(InputToken[i]);
                            }
                            else if(InputToken[i] == "varchar"){
                                out << " varchar"<< "\r";
                                AttributesTypes.push_back(InputToken[i]);
                            }
                            else if(InputToken[i] == "bool"){
                                out << " bool"<< "\r";
                                AttributesTypes.push_back(InputToken[i]);
                            }
                            else if(InputToken[i] == "double"){
                                out << " double"<< "\r";
                                AttributesTypes.push_back(InputToken[i]);
                            }
                            else{
                                printf("Unrecognized data type .\n");
                                TableBuild = false;
                                break;
                                //potential leak on failure
                            }
                        }
                        else{
                            out << InputToken[i].c_str();
                            Attributes.push_back( InputToken[i]);
                        }
                        
                    }
                    
                    if(TableBuild){
                        // std::cout<< ReleationCounterPtr <<"  ---- "<<*ReleationCounterPtr<<std::endl;
                        //std::cout << ReleationName << " "<<PrimaryKey <<std::endl;
                        BPTreePtr[*ReleationCounterPtr].BPTreeReleationName = ReleationName;
                        BPTreePtr[*ReleationCounterPtr].Primarykey  = PrimaryKey;
                        BPTreePtr[*ReleationCounterPtr].Attributes = Attributes;
                        BPTreePtr[*ReleationCounterPtr].AttributesTypes = AttributesTypes;
                        //std:: cout<< PrimaryKey << "Primay "<<BPTreePtr[*ReleationCounterPtr].BPTreeReleationName <<std::endl;
                        *ReleationCounterPtr += 1;
                        printf("Table built successfully!\n");
                    }
                    out.close();
                }
            }
            
        }
        else if(InputToken[0] == "LOAD"){
            
            std::string ReleationName = InputToken[1];
            std::string path = "/Users/samangivian/Desktop/Database 1.0/"+ReleationName;
            std::ifstream MyReadFile("/Users/samangivian/Desktop/Database 1.0/" + ReleationName + "/"+ ReleationName+".txt");
            std:: string myText;
            int RecordNum = 0;
            std::vector<std::string>LineParse;
            //std::cout<<"File open "<<std::endl;
            
            BPTreePtr[*ReleationCounterPtr].BPTreeReleationName = ReleationName;
            // std::vector<std::string> LineParse;
            while (getline (MyReadFile, myText)) {
                // Output the text from the file
                std::vector<std::string> Lines = SplitStringByNewLine(myText);
                for(int LineCounter = 0 ; LineCounter<Lines.size(); LineCounter++){
                    LineParse = StringVectorizer(Lines[LineCounter]);
                    if(LineParse[0] == "PK"){
                        BPTreePtr[*ReleationCounterPtr].Primarykey = LineParse[1];
                    }
                    else if(LineParse.size() == 2){
                        BPTreePtr[*ReleationCounterPtr].Attributes.push_back(LineParse[0]);
                        BPTreePtr[*ReleationCounterPtr].AttributesTypes.push_back(LineParse[1]);
                    }
                }
            }
            for (const auto & entry : fs::directory_iterator(path)){
                //std::cout << entry.path() << std::endl;
                std::ifstream MyReadFile(entry.path());
                // Use a while loop together with the getline() function to read the file line by line
                
                if(entry.path() != "/Users/samangivian/Desktop/Database 1.0/" + ReleationName + "/"+ ReleationName+".txt"){
                    record_node* NewRecord = new record_node();
                    while (getline (MyReadFile, myText)) {
                        // Output the text from the file
                        std::vector<std::string> LineParse = SplitStringByNewLine(myText);
                        //std::cout<<LineParse.size()<<std::endl;
                        for(int Col = 0; Col<LineParse.size();Col++){
                            std::strcpy(NewRecord->record[Col], LineParse[Col].c_str());
                        }
                    }
                    int PrimaryKey = stoi(AddressTokenizer(entry.path()));
                    RecordNodesPtr[*ReleationCounterPtr][ BPTreePtr[*ReleationCounterPtr].RecordNum] = NewRecord;
                    BPTreePtr[*ReleationCounterPtr].insert(PrimaryKey,NewRecord);
                    RecordNum +=1;
                }
            }
            BPTreePtr[*ReleationCounterPtr].RecordNum = RecordNum;
            *ReleationCounterPtr += 1;
            // Close the file
            MyReadFile.close();
            printf("Loaded sucessfully!\n");
        }
        else if (InputToken[0] == "INSERT" && InputToken[1] == "INTO"){
            
            std:: string RelationName = InputToken[2];
            std::string PrimaryKey ;
            std:: vector <std::string> AttrUpdated;
            std:: vector <std:: string> Values;
            int BPTreeReleation = 0;
            int InputCounter = 3;
            
            while(true){
                if(InputToken[InputCounter] == "VALUES"){
                    InputCounter = InputCounter + 1;
                    break;
                }
                AttrUpdated.push_back(InputToken[InputCounter]);
                InputCounter = InputCounter + 1;
            }
            while(InputCounter < InputToken.size()){
                Values.push_back(InputToken[InputCounter]);
                InputCounter = InputCounter + 1;
            }
            
            for(int BPTreeCounter = 0; BPTreeCounter < *ReleationCounterPtr; BPTreeCounter++){
                if(RelationName == BPTreePtr[BPTreeCounter].BPTreeReleationName){
                    BPTreeReleation = BPTreeCounter;
                    if(BPTreePtr[BPTreeCounter].Primarykey == ""){
                        PrimaryKey =  std::to_string(BPTreePtr[BPTreeCounter].RecordNum);
                    }
                    break;
                }
            }
            //record_node NewRecord;
            record_node* NewRecord = new record_node();
            
            //std::cout<<"PK " <<BPTreePtr[BPTreeReleation].Primarykey<<std::endl;
            for(int Col = 0; Col < BPTreePtr[BPTreeReleation].Attributes.size(); Col++){
                for (int AttrCol = 0; AttrCol < AttrUpdated.size(); AttrCol++){
                    
                    if(AttrUpdated[AttrCol] == BPTreePtr[BPTreeReleation].Attributes[Col]){
                        strcpy(NewRecord->record[Col], Values[AttrCol].c_str());
                    }
                    //std::cout<<AttrUpdated[AttrCol]<<" "<<BPTreePtr[BPTreeReleation].Primarykey<<std::endl;
                    if(AttrUpdated[AttrCol] == BPTreePtr[BPTreeReleation].Primarykey){
                        //std::cout<<"Asdsad";
                        PrimaryKey =  Values[AttrCol];
                    }
                }
                
            }
            //std:: cout<<"Pr asd "<<PrimaryKey<<std::endl;
            RecordNodesPtr[BPTreeReleation][ BPTreePtr[BPTreeReleation].RecordNum] = NewRecord;
           // std::cout<<"Node Address: "<<RecordNodesPtr[BPTreeReleation][ BPTreePtr[BPTreeReleation].RecordNum] <<std::endl;
            //  std::cout<<"Address main: "<<NewRecord<<std::endl;
            BPTreePtr[BPTreeReleation].insert(std::stoi(PrimaryKey), NewRecord);
            
            BPTreePtr[BPTreeReleation].RecordNum += 1;
            //std::cout<<PrimaryKey<<std::endl;
            std:: ofstream out("/Users/samangivian/Desktop/Database 1.0/" + RelationName + "/"+PrimaryKey+".txt");
            for(int Col = 0; Col < BPTreePtr[BPTreeReleation].Attributes.size(); Col++){
                for (int AttrCol = 0; AttrCol < AttrUpdated.size(); AttrCol++){
                    if(AttrUpdated[AttrCol] == BPTreePtr[BPTreeReleation].Attributes[Col]){
                        out << Values[AttrCol];
                       
                    }
                }
                out <<'\r';
            }

            
            out.close();
            //std::cout<<RecordNodesPtr[BPTreeReleation][ BPTreePtr[BPTreeReleation].RecordNum-1]->record[1];
            std::cout<<"Inserted sucessfully"<<std::endl;
        }
        else if(InputToken[0] == "SHOW"){
            int BPTreeAddress = 0;
            for(int ReleationCounter = 0; ReleationCounter < *ReleationCounterPtr;ReleationCounter++){
                if(BPTreePtr[ReleationCounter].BPTreeReleationName == InputToken[1]){
                    BPTreeAddress = ReleationCounter;
                    break;
                }
            }
            std::vector<std::string> OUTPUT= {BPTreePtr[BPTreeAddress].Attributes};
            std::cout<<"ATTR:"<<BPTreePtr[BPTreeAddress].Attributes[1]<<std::endl;
            BPTreePtr[BPTreeAddress].ReleationDisplay(BPTreePtr[BPTreeAddress], BPTreePtr[BPTreeAddress].getRoot(),OUTPUT);
            
        }
        else if (InputToken[0] == "SELECT"){
            
            std:: vector <std::string> SelectedAttr;
            bool AllAttr = false;
            int BPTreeAddress = 0;
            int InputCounter = 1;
            BPTree BPTreeTemp;
            
            while(true){
                if(InputToken[InputCounter] == "FROM"){
                    InputCounter++;
                    for(int ReleationCounter = 0; ReleationCounter < *ReleationCounterPtr;ReleationCounter++){
                        if(BPTreePtr[ReleationCounter].BPTreeReleationName == InputToken[InputCounter]){
                            BPTreeAddress = ReleationCounter;
                            break;
                        }
                    }
                    if(AllAttr){
                        SelectedAttr = BPTreePtr[BPTreeAddress].Attributes;
                    }
                    record_node *  recordNodeTemp =  BPTreePtr[BPTreeAddress].RecordArrayFinder(BPTreePtr[BPTreeAddress]);
                    for(int i = 0;i<BPTreePtr[BPTreeAddress].RecordNum;i++){
                        std::cout<<recordNodeTemp[i].record[1   ]<<std::endl;
                    }
                    if(InputToken[InputCounter] == "WHERE"){
                        InputCounter ++;
                        while(InputCounter < InputToken.size()){
                            std::string AttrCompare1 = InputToken[InputCounter] ;
                            std::string AttrCompare2 = InputToken[InputCounter+2];
                            
                            InputCounter = InputCounter + 3;
                        }
                    }
                    else{
                        BPTreeTemp = BPTreePtr[BPTreeAddress];
                    }
                    
                    break;
                }
               
                if(InputToken[InputCounter] == "*"){
                    AllAttr = true;
                }
                else{
                    SelectedAttr.push_back(InputToken[InputCounter]);
                }
               
                InputCounter++;
            }
            BPTreeTemp.ReleationDisplay(BPTreeTemp, BPTreeTemp.getRoot(),SelectedAttr);
        }
    }
    return ;
}

