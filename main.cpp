#include <bits/stdc++.h>
using namespace std;
vector<int> encoding(string s1)
{
    cout << "Encoding\n";
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
    cout << "String\tOutput_Code\tAddition\n";
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
            cout << p << "\t" << table[p] << "\t\t"
                 << p + c << "\t" << code << endl;
            output_code.push_back(table[p]);
            table[p + c] = code;
            code++;
            p = c;
        }
        c = "";
    }
    cout << p << "\t" << table[p] << endl;
    output_code.push_back(table[p]);
    return output_code;
}

void decoding(vector<int> op)
{
    cout << "\nDecoding\n";
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
    cout << s;
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
        cout << s;
        c = "";
        c += s[0];
        table[count] = table[old] + c;
        count++;
        old = n;
    }
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

int main()
{
    string s = "toi yeu Viet Nam";
    vector<int> output_code = encoding(s);
    vector<int> outputBin;

    cout << "Output Codes are: ";
    for (int i = 0; i < output_code.size(); i++)
    {
        cout << output_code[i] << " ";
    }
    cout << endl;

    // Write the binary data to the binary file
    writeBinaryToFile(output_code, "convert.bin");
    cout << "Binary representation has been written to convert.bin" << endl;

    // Read the binary data from the binary file
    outputBin = readBinaryFromFile("convert.bin");
    cout << "Binary representation read from the file: ";
    for (int i = 0; i < outputBin.size(); i++)
    {
        cout << outputBin[i] << " ";
    }
    cout << endl;

    decoding(outputBin);

    return 0;
}