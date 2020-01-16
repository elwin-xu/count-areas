#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iterator>
#include <getopt.h>
#include "image.h"

// These are used for the double dash parameters --shape <height>,<width>
// Names for the values of the 'has_arg' field of 'struct option'.
# define no_argument          0
# define required_argument    1
# define optional_argument    2

using namespace std;

/**
* obtain the file path and size data from the command line input
* @param filePath return the file path input (the first parameter)
* @param shapeSize return the size data input (<height,width>), please note no space should be between height and width
*/
int getFilePath(int argc, const char * argv[], string& filePath, vector<int>& shapeSize) {
    // check if an input file has been provided
    if (argc == 1)
    {
        cout << "Please include an input file!\n";
        return 1;
    }
    
    // take the first parameter as the filePath
    filePath = argv[1];
    
    // set up double dash command-line parameters
    const char *short_options = "";
    static struct option long_options[] ={
        {"shape",required_argument,NULL,'s'}
    };

    int opt = -1;
    int option_index = -1;
    
    // get the input data
    while((opt = getopt_long(argc, (char**)argv, short_options, long_options, &option_index)) != -1){
        if (opt == 's') {
            // Parse a comma-delimited string
            string str = optarg;
            stringstream ss(str);
            for (int i; ss >> i;) {
                shapeSize.push_back(i);
                if (ss.peek() == ',')
                    ss.ignore();
            }
        }
    }
    
    if (shapeSize.size() != 2) {
        cout << "Please check the size input!";
        return 2;
    }
    
    return 0;
}

int main(int argc, const char * argv[]) {
    // Obtain the parameters from the command line
    string filePath;
    vector<int> shapeSize;
    int status = getFilePath(argc, argv,filePath, shapeSize);
    
    if (status != 0) {return status;}
    
    // open the input file
    ifstream input( filePath, std::ios::binary );

    // copies all data into bufferChar
    vector<unsigned char> bufferChar(std::istreambuf_iterator<char>(input), {});
    
    // converts the char data into unsigned int
    vector<unsigned int> buffer;
    for (int i = 0; i < bufferChar.size(); i++) {
        buffer.push_back(static_cast<unsigned int>(bufferChar[i]));
    }

    // initialise an image object
    Image image = Image(shapeSize[1], shapeSize[0]);
    
    // initialise pixel data in the image object
    image.setPixels(buffer);
    
    // count the numbers of areas of different shades of grey
    vector<unsigned int> countAreas;
    countAreas = image.countAreas();
    
    // output the results
    for (int i = 0; i < countAreas.size(); i++) {
        cout << countAreas[i] << "\n";
    }
    
    return 0;
}


