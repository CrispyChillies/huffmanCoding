#include "function.h"

vector<int> encoding(string s1)
{
    // cout << "Encoding\n";
    unordered_map<string, int> table;
    for (int i = 0; i <= 255; i++)
    {
        string ch = "";
        ch += char(i);
        table[ch] = i;
    }

    string p = "", c = "";
    p += s1[0];
    int code = 256;
    vector<int> output_code;
    // cout << "String\tOutput_Code\tAddition\n";
    for (int i = 0; i < s1.length(); i++)
    {
        if (i != s1.length() - 1)
            c += s1[i + 1];
        if (table.find(p + c) != table.end())
        {
            p = p + c;
        }
        else
        {
            // cout << p << "\t" << table[p] << "\t\t" << p + c << "\t" << code << endl;
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    // cout << p << "\t" << table[p] << endl;
    output_code.push_back(table[p]);
    return output_code;
}

void decoding(vector<int> op, string outputFile)
{
    // cout << "\nDecoding\n";
    ofstream out(outputFile);

    if (!out)
    {
        cout << "Can't open file to write.\n";
        return;
    }

    unordered_map<int, string> table;
    for (int i = 0; i <= 255; i++)
    {
        string ch = "";
        ch += char(i);
        table[i] = ch;
    }
    int old = op[0], n;
    string s = table[old];
    string c = "";
    c += s[0];
    out << s;
    int count = 256;
    for (int i = 0; i < op.size() - 1; i++)
    {
        n = op[i + 1];
        if (table.find(n) == table.end())
        {
            s = table[old];
            s = s + c;
        }
        else
        {
            s = table[n];
        }
        out << s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }

    out.close();
}

void writeBinaryToFile(const vector<int> &data, const string &filename)
{
    ofstream file(filename, ios::binary | ios::out);
    if (!file)
    {
        cout << "Error opening file " << filename << " for writing.\n";
        return;
    }

    for (int number : data)
    {
        file.write(reinterpret_cast<const char *>(&number), sizeof(int));
    }

    file.close();
}

vector<int> readBinaryFromFile(const string &filename)
{
    ifstream file(filename, ios::binary | ios::in);
    if (!file)
    {
        cout << "Error opening file " << filename << " for reading.\n";
        return {};
    }

    vector<int> outputBin;
    int number;
    while (file.read(reinterpret_cast<char *>(&number), sizeof(int)))
    {
        outputBin.push_back(number);
    }

    file.close();
    return outputBin;
}

string readFile(string inputFile)
{
    string text;
    string line;

    ifstream inf(inputFile);
    if (!inf)
    {
        cout << "Can't open file.\n";
        return text;
    }

    while (getline(inf, line))
    {
        text += line;
    }

    inf.close();

    return text;
}

bool checkInput(string inputFile, string outputFile)
{
    istringstream iss(inputFile);
    string token;
    string trash;

    getline(iss, trash, '.');
    getline(iss, token, '.');

    if (token == "bin")
        return false;

    istringstream iss_1(outputFile);
    getline(iss_1, trash, '.');
    getline(iss_1, token, '.');

    if (token == "txt")
        return false;

    return true;
}