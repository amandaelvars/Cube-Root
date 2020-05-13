// Amanda Elvarsdottir
// This program calculates the cuberoot to a second number of places. 

#include <iostream>
#include <string>
#include <cstdlib>
#include "PG1.h"
#include <vector>
using namespace std;


int main(int argc, char** argv) {

    string num, places;
    cout << "Enter a number:  ";
    getline(cin, num);
    cout << "Enter another number:  ";
    getline(cin, places);
    cuberoot(num, places);
    return 0;
}

void removeleadingzeroes(string& a) {
    // Method removes leading zeros and is used in all other smaller methods (all except cuberoot). 
    while (a.length() > 1 && a[0] == '0') a = a.substr(1);
}

string add(string a, string b) {
    //Method adds two string's together as if they were numbers.
    removeleadingzeroes(a);
    removeleadingzeroes(b);
    while (a.length() < b.length()) a = "0" + a;
    while (b.length() < a.length()) b = "0" + b;
    a = "0" + a;
    b = "0" + b;
    string sum = "";
    int carry = 0;
    for (int i = a.length() - 1; i >= 0; i--) {
        int s = (a[i] - '0') + (b[i] - '0') + carry;
        carry = s / 10;
        sum = (char)(s % 10 + '0') + sum;
    }
    removeleadingzeroes(sum);
    return sum;
}

string sub(string a, string b) {
    //Method subtracts two strings (b from a) as if they are integers.
    removeleadingzeroes(a);
    removeleadingzeroes(b);
    while (b.length() < a.length()) b = "0" + b;
    for (size_t i = 0; i < b.length(); i++){
        b[i] = 9 - (b[i] - '0') + '0';
        }
    string diff = add(add(a, b), "1");
    diff = diff.substr(1);
    removeleadingzeroes(diff);
    return diff;
}

string mult(string a, string b) {
    // Method multiplies two strings together as if they are integers.
    removeleadingzeroes(a);
    removeleadingzeroes(b);
    string sum = "0";
    for (size_t i = 0; i < a.length(); i++) {
        for (size_t j = 0; j < b.length(); j++) {
            string prod = to_string((a[i] - '0') * (b[j] - '0'));
            for (size_t k = 0; k < a.length() - i - 1 + b.length() - j - 1; k++) {
                prod += "0";
            }
            sum = add(sum, prod);
        }
    }
    return sum;
}

bool equals(string a, string b) {
    //Method returns a boolean if the two numbers are equal to one another. True if they are, false if not.
    removeleadingzeroes(a);
    removeleadingzeroes(b);
    if (a.length() != b.length()) { return false; }
    for (size_t i = 0; i < a.length(); i++) {
        if ((a[i] - '0') != (b[i] - '0')) return false;
    }
    return true;
    }

bool greaterthan(string a, string b) {
    // Method determines whether 'a' is greather than 'b'. First we see if the length of the string is shorter or longer if they are equal we go to a for loop to determine which is greater.
    removeleadingzeroes(a);
    removeleadingzeroes(b);
    // if the string length is the same it goes to a for loop to determine which number is higher.
    if (a.length() > b.length()) { return true; }
    if (a.length() < b.length()) { return false; }
    else {
        for (size_t i = 0; i < a.length(); i++) {
            if ((a[i] - '0') > (b[i] - '0')) {
                return true;
            }
            if ((a[i] - '0') < (b[i] - '0')) {
                return false;
            }
        }
        return false;
    }
}


bool lessthan(string a, string b) {
    // Method determines whether 'a' is less than 'b' and will return a boolean (true if less than, false if greather than). 
    // First we check if the length of the string is less than, then if it's greater than. If string is equal we have to go to a for loop to determine which is less.
    removeleadingzeroes(a);
    removeleadingzeroes(b);
    // if the string length is the same it goes to a for loop to determine which number is lower.
    if (a.length() < b.length()) { return true; }
    if (a.length() > b.length()) { return false; }
    else {
        for (size_t i = 0; i < a.length(); i++) {
            if ((a[i] - '0') < (b[i] - '0')) { return true; }
            if ((a[i] - '0') > (b[i] - '0')) { return false; }
        }
        return false;
    }
}

void cuberoot(string a, string b) {
    //Method using Andy Poe's formula to calculate the cuberoot of a number.
    string firstnumber = a;
    string numofplaces = b;
    string numofcube = a;
    string ct = "0";
    string places = mult(b, "3");

    string ans = "0";
    string rem;
    vector <string> eights;

    int dec = 0;
    string secct = "0";


    if (greaterthan(firstnumber, "0")) {
        while ((equals(ct, places) == false)) {
            numofcube.push_back('0');
            ct = add(ct, "1");
        }


        eights.push_back("1");

        while (lessthan(eights.back(), numofcube) == true) {
            string theeight = mult(eights.back(), "8");
            if (greaterthan(theeight, numofcube) == true) {
                break;
            }
            else { eights.push_back(theeight); }
        }

        rem = numofcube;
        string last;
        for (int i = eights.size() - 1; i >= 0; i--) {
            //this is the 12*ans^2 + 6 *ans =1 formula.
            last = add(mult("12", mult(ans, ans)), add(mult("6", ans), "1"));
            last = mult(eights.at(i), last);

            if (((lessthan(last, rem)) || (equals(last, rem))) == true) {
                rem = sub(rem, last);
                ans = add("1", mult(ans, "2"));
            }
            else {
                ans = mult("2", ans);
            }
        }

        //decimal
        for (int i = 0; i < (int)ans.length(); i++) {
            string move = ans.substr(0, i);
            if (equals(mult(mult(move, move), move), firstnumber) || (lessthan(mult(mult(move, move), move), firstnumber)) == true) {
                dec = i;
            }
            else {
                break;
            }
        }
        ans.insert(dec, ",");
        cout << ans << endl;
    }
    //else to the first greatherthan statement in cuberoot
    else{
        string secct = "0";
        while (equals(secct, numofplaces) == false) {
            numofcube.push_back('0');
            secct = add(secct, "1");
        }
        numofcube.insert(1, ",");
        cout << numofcube << endl;
    }
}