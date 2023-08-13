#include "function.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        cout << "---------------HELP-----------------------\n";
        cout << "Use the command below to use the program: \n";
        cout << "-co [Input file name].txt [Output file name].bin  \n";
        cout << "-de [Input file name].bin [Output file name].txt  \n";
        cout << "------------------------------------------\n";
    }
    else
    {
        string mode = argv[1];
        string inputFile = argv[2];
        string outputFile = argv[3];

        if (mode == "-co")
        {
            if (checkInput(inputFile, outputFile))
            {
                string text = readFile(inputFile);
                vector<int> output_code = encoding(text);
                writeBinaryToFile(output_code, outputFile);
                cout << "Data has been compressed into " << outputFile << "\n";
            }
            else
            {
                cout << "The input file extension is (.txt) and the output file extension is (.bin) \n";
                return -1;
            }
        }
        else if (mode == "-de")
        {
            if (checkInput(outputFile, inputFile))
            {
                vector<int> input_bin;
                input_bin = readBinaryFromFile(inputFile);
                decoding(input_bin, outputFile);
                cout << "Data has been decompressed into " << outputFile << "\n";
            }
            else
            {
                cout << "The input file extension is (.bin) and the output file extension is (.txt) \n";
                return -1;
            }
        }
    }

    return 0;
}