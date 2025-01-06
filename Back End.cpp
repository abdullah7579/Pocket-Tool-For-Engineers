#include <iostream>
#include <vector>
#include <stack>
#include <cmath>
#include <queue>
#include <string>
#include <list>
#include <algorithm>
#include <fstream>

using namespace std;

vector<int> bin; // Task-01
int dec; // Global variable
stack<int> dec_bin_stack;

// Task-01: Decimal to Binary Conversion
void dec_bin_recursive(int decimal)
{
    if (decimal == 0)
    {
        if (dec_bin_stack.empty())
        {
            dec_bin_stack.push(0);
        }
        return;
    }
    dec_bin_stack.push(decimal % 2);
    dec_bin_recursive(decimal / 2);
}

void dec_bin(int decimal)
{
    dec_bin_recursive(decimal);
    while (!dec_bin_stack.empty())
    {
        bin.push_back(dec_bin_stack.top());
        dec_bin_stack.pop();
    }
}

int bin_dec_recursive(const vector<int>& binary, int index = 0)
{
    if (index == binary.size())
    {
        return 0;
    }
    int value = binary[index] * pow(2, binary.size() - 1 - index);
    return value + bin_dec_recursive(binary, index + 1);
}

void bin_dec(const vector<int>& binary)
{
    ::dec = bin_dec_recursive(binary); // Explicitly access the global variable dec
}

// Task-02: Delta to Wye and Wye to Delta
double r1, r2, r3;
void delta_wye(int ra, int rb, int rc)
{
    r1 = (rb * rc) / (ra + rb + rc);
    r2 = (rc * ra) / (ra + rb + rc);
    r3 = (ra * rb) / (ra + rb + rc);
}

void wye_delta(int ra, int rb, int rc)
{
    int total_res = (ra * rb + rb * rc + ra * rc);
    r1 = total_res / ra;
    r2 = total_res / rb;
    r3 = total_res / rc;
}

// Task-06: Resistor Value Verification
double res_val = 0, res_tol = 0;

int band_value(string band)
{
    if (band == "black") return 0;
    else if (band == "brown") return 1;
    else if (band == "red") return 2;
    else if (band == "orange") return 3;
    else if (band == "yellow") return 4;
    else if (band == "green") return 5;
    else if (band == "blue") return 6;
    else if (band == "violet") return 7;
    else if (band == "grey") return 8;
    else if (band == "white") return 9;
    else return -1;
}

double resistor_tolerance(string x)
{
    if (x == "black") return 1;
    else if (x == "red") return 2;
    else if (x == "green") return 0.5;
    else if (x == "blue") return 0.25;
    else if (x == "violet") return 0.1;
    else if (x == "grey") return 0.05;
    else if (x == "gold") return 5;
    else if (x == "silver") return 10;
    else return -1;
}

double multiplier_value(string band)
{
    if (band == "black") return 1;
    else if (band == "brown") return 10;
    else if (band == "red") return 100;
    else if (band == "orange") return 1000;
    else if (band == "yellow") return 10000;
    else if (band == "green") return 100000;
    else if (band == "blue") return 1000000;
    else if (band == "violet") return 10000000;
    else if (band == "grey") return 100000000;
    else if (band == "white") return 1000000000;
    else if (band == "gold") return 0.1;
    else if (band == "silver") return 0.01;
    else return -1;
}

void resistor_value(string b1, string b2, string b3, string b4)
{
    int x1 = band_value(b1);
    int x2 = band_value(b2);
    int x3 = multiplier_value(b3);
    int x4 = resistor_tolerance(b4);
    
    if (x1 == -1 || x2 == -1 || x3 == -1 || x4 == -1)
    {
        cout << "Invalid color bands entered!" << endl;
        return;
    }
    
    // Calculate resistor value and tolerance
    res_val = (x1 * 10 + x2) * x3;
    res_tol = x4;

    // Display the calculated resistor value and tolerance
    cout << "Resistor Value: " << res_val << " ohms" << endl;
    cout << "Tolerance: ±" << res_tol << "%" << endl;
}

// Task-05: Hamming Code Generation and Checking
vector<int> code; // Task-05

void generateHammingCode(vector<int> bits)
{
    int m = bits.size();
    int r = 0;

    while (pow(2, r) < m + r + 1)
    {
        r++;
    }

    int n = m + r;
    vector<int> hammingCode(n, 0);

    int dataIndex = 0;

    for (int i = 0; i < n; i++)
    {
        if ((i + 1) & i)
        {
            hammingCode[i] = bits[dataIndex++];
        }
    }

    for (int i = 0; i < r; i++)
    {
        int parityPos = pow(2, i) - 1;
        int parityValue = 0;

        for (int j = parityPos; j < n; j += 2 * (parityPos + 1))
        {
            for (int k = 0; k <= parityPos && (j + k) < n; k++)
            {
                parityValue ^= hammingCode[j + k];
            }
        }

        hammingCode[parityPos] = parityValue;
    }
    code = hammingCode;
}

bool checkHammingCode(vector<int> receivedCode)
{
    int n = receivedCode.size();
    int r = 0;

    while (pow(2, r) < n + 1)
    {
        r++;
    }

    for (int i = 0; i < r; i++)
    {
        int parityPos = pow(2, i) - 1;
        int parityValue = 0;

        for (int j = parityPos; j < n; j += 2 * (parityPos + 1))
        {
            for (int k = 0; k <= parityPos && (j + k) < n; k++)
            {
                parityValue ^= receivedCode[j + k];
            }
        }

        if (parityValue != 0)
        {
            return false;
        }
    }

    return true;
}

// Task-04: Norton and Thevenin Equivalent
int Vth, Rth, In, Rn; // Task-04

void calculateVth(double v, int r, int r2)
{
    Vth = (r2 / (r1 + r2)) * v;
}

void calculateRth(int r1, int r2)
{
    Rth = (r1 * r2) / (r1 + r2);
}

void calculateIn(double V, int r1, int r2)
{
    In = V / (r1 + r2);
}

void calculateRn(int R1, int R2)
{
    Rn = (r1 * r2) / (r1 + r2);
}

// Main Menu Functionality with Resistor Value Verification on choice 9
int main()
{
    int choice;

    while (choice != -1)
    {
        cout << "\t\t\tMENU" << endl;
        cout << "Press:" << endl;
        cout << "1. To Convert dec to binary" << endl;
        cout << "2. Binary to decimal" << endl;
        cout << "3. Delta to Wye" << endl;
        cout << "4. Wye to Delta" << endl;
        cout << "5. Norton Equivalent" << endl;
        cout << "6. Thevenin Equivalent" << endl;
        cout << "7. Generate Hamming code" << endl;
        cout << "8. Check Hamming Code" << endl;
        cout << "9. Resistor Value Verification" << endl; // Updated menu option
        cout << "-1 to exit" << endl;
        cin >> choice;

        if (choice == 1)
        {
            cout << "Enter Decimal: ";
            int dec;
            cin >> dec;
            dec_bin(dec);
            cout << "Converted Binary is: ";
            for (int i = 0; i < bin.size(); i++)
            {
                cout << bin[i];
            }
            cout << endl;
        }
        else if (choice == 2)
        {
            cout << "Enter binary to convert to decimal: ";
            vector<int> binary;
            int bit;
            while (cin >> bit && bit != -1)
            {
                binary.push_back(bit);
            }
            bin_dec(binary);
            cout << "Converted Decimal is: " << ::dec << endl; // Use global dec
        }
        else if (choice == 3)
        {
            cout << "Enter ra, rb, rc: ";
            int ra, rb, rc;
            cin >> ra >> rb >> rc;
            delta_wye(ra, rb, rc);
            cout << "r1: " << r1 << ", r2: " << r2 << ", r3: " << r3 << endl;
        }
        else if (choice == 4)
        {
            cout << "Enter ra, rb, rc: ";
            int ra, rb, rc;
            cin >> ra >> rb >> rc;
            wye_delta(ra, rb, rc);
            cout << "r1: " << r1 << ", r2: " << r2 << ", r3: " << r3 << endl;
        }
        else if (choice == 5)
        {
            cout << "Enter voltage, r1, r2: ";
            double V;
            int r1, r2;
            cin >> V >> r1 >> r2;
            calculateVth(V, r1, r2);
            cout << "Vth: " << Vth << endl;
        }
        else if (choice == 6)
        {
            cout << "Enter r1, r2: ";
            int r1, r2;
            cin >> r1 >> r2;
            calculateRth(r1, r2);
            cout << "Rth: " << Rth << endl;
        }
        else if (choice == 7)
        {
            cout << "Enter bits to generate Hamming code: ";
            vector<int> bits;
            int bit;
            while (cin >> bit && bit != -1)
            {
                bits.push_back(bit);
            }
            generateHammingCode(bits);
            cout << "Generated Hamming Code: ";
            for (int i = 0; i < code.size(); i++)
            {
                cout << code[i];
            }
            cout << endl;
        }
        else if (choice == 8)
        {
            cout << "Enter received Hamming Code to check: ";
            vector<int> receivedCode;
            int bit;
            while (cin >> bit && bit != -1)
            {
                receivedCode.push_back(bit);
            }
            if (checkHammingCode(receivedCode))
            {
                cout << "The Hamming Code is correct." << endl;
            }
            else
            {
                cout << "The Hamming Code is incorrect." << endl;
            }
        }
        else if (choice == 9) // Resistor Value Verification
		{
    		cout << "Enter color bands for resistor value verification:" << endl;
    		cout << "Enter first band color: ";
    		string band1, band2, band3, band4;
    		cin >> band1;
    		cout << "Enter second band color: ";
    		cin >> band2;
    		cout << "Enter third band color (multiplier): ";
    		cin >> band3;
    		cout << "Enter fourth band color (tolerance): ";
    		cin >> band4;

    		resistor_value(band1, band2, band3, band4); // Call the function to calculate resistor value
		}
        else if (choice == -1)
        
        {
            cout << "Exiting program." << endl;
        }
        else
        {
            cout << "Invalid choice, please try again." << endl;
        }
    }

    return 0;
}

