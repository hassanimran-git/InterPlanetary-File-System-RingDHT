#pragma once
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream>
#include <cctype>
#include <openssl/sha.h>
using namespace std;

string readFile(const string &filePath)
{
    ifstream file(filePath);

    if (!file.is_open())
    {
        cout << "Error reading file!" << endl;
        return ""; // return an empty string to indicate an error
    }

    stringstream buffer;
    buffer << file.rdbuf();
    file.close();

    return buffer.str();
}

int calculateUniqueChars(int totalNodes)
{
    // function to calculate the minimum number of characters needed for uniqueness
    int uniqueChars = static_cast<int>(ceil(log2(totalNodes) / 4.0));

    return uniqueChars;
}

string Hash(const string &input)
{
    unsigned char hash[SHA_DIGEST_LENGTH];
    SHA1(reinterpret_cast<const unsigned char *>(input.c_str()), input.length(), hash);

    // convert the hash to a hex string
    stringstream ss;
    ss << hex << setfill('0');
    for (int i = 0; i < SHA_DIGEST_LENGTH; ++i)
    {
        ss << setw(2) << static_cast<unsigned int>(hash[i]);
    }

    return ss.str();
}

string getLastSubstring(const string &sha1Hash, int length)
{
    if (length > static_cast<int>(sha1Hash.length()))
    {
        return sha1Hash; // return entire hash if length is greater
    }

    // calculate the starting index for the last substring
    int startIndex = static_cast<int>(sha1Hash.length()) - length;

    // extract the last substring
    string lastSubstring = sha1Hash.substr(static_cast<size_t>(startIndex), static_cast<size_t>(length));

    return lastSubstring;
}

string padString(const string &str, int desiredLength)
{
    if (str.length() >= desiredLength)
    {
        return str; // string is already long enough
    }

    // calculate the number of leading zeros needed
    int zerosToAdd = desiredLength - str.length();

    string paddedString = string(zerosToAdd, '0') + str;

    return paddedString;
}

string subtractHexadecimalStrings(const string &hex1, const string &hex2)
{
    // Ensure hex1 is greater than or equal to hex2
    if (hex1 < hex2)
    {
        cerr << "Error in hexa subtraction" << endl;
        return "";
    }

    // pad the strings with leading zeros
    size_t maxLength = hex1.length();
    string paddedHex2 = padString(hex2, maxLength);

    // perform hexadecimal subtraction
    string result;
    int borrow = 0;

    for (int i = maxLength - 1; i >= 0; --i)
    {
        int digit1 = (hex1[i] >= '0' && hex1[i] <= '9') ? (hex1[i] - '0') : (toupper(hex1[i]) - 'A' + 10);
        int digit2 = (paddedHex2[i] >= '0' && paddedHex2[i] <= '9') ? (paddedHex2[i] - '0') : (toupper(paddedHex2[i]) - 'A' + 10);

        int difference = digit1 - digit2 - borrow;

        if (difference < 0)
        {
            difference += 16;
            borrow = 1;
        }
        else
        {
            borrow = 0;
        }

        char diffDigit = (difference < 10) ? ('0' + difference) : ('a' + difference - 10);
        result = diffDigit + result;
    }

    // remove leading zeros from the result
    size_t firstNonZero = result.find_first_not_of('0');
    result = (firstNonZero != string::npos) ? result.substr(firstNonZero) : "0";

    return result;
}

string addHexadecimalStrings(const string &hex1, const string &hex2)
{
    // pad the strings with leading zeros
    size_t maxLength = max(hex1.length(), hex2.length());
    string paddedHex1 = padString(hex1, maxLength);
    string paddedHex2 = padString(hex2, maxLength);

    // Perform hexadecimal addition
    string result;
    int carry = 0;

    for (int i = maxLength - 1; i >= 0; --i)
    {
        int digit1 = (paddedHex1[i] >= '0' && paddedHex1[i] <= '9') ? (paddedHex1[i] - '0') : (toupper(paddedHex1[i]) - 'A' + 10);
        int digit2 = (paddedHex2[i] >= '0' && paddedHex2[i] <= '9') ? (paddedHex2[i] - '0') : (toupper(paddedHex2[i]) - 'A' + 10);

        int sum = digit1 + digit2 + carry;
        carry = sum / 16;
        sum %= 16;

        char sumDigit = (sum < 10) ? ('0' + sum) : ('a' + sum - 10);
        result = sumDigit + result;
    }

    // if there is a carry after the loop, add it to the result
    if (carry > 0)
    {
        result = (char)('0' + carry) + result;
    }

    return result;
}

string powerOfTwoToHex(int exponent)
{
    if (exponent < 0)
    {
        return "Invalid input. Exponent must be non-negative.";
    }

    if (exponent == 0)
    {
        return "1";
    }

    string result = "2";

    for (int i = 1; i < exponent; ++i)
    {
        result = addHexadecimalStrings(result, result);
    }

    return result;
}
