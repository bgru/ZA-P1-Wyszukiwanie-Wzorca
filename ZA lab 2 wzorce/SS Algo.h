#pragma once
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

static int complexity = 0;


const int HASH_PRIME = 31; // prime number used for hashing
const int MOD = 1e9 + 9; // modulo used for hashing

int hashString(const string& s) {
    int length = s.length();
    int hash_val = 0;
    int pow_p = 1;
    for (int i = 0; i < length; i++) {
        hash_val = (hash_val + (s[i] - 'a' + 1) * pow_p) % MOD;
        pow_p = (pow_p * HASH_PRIME) % MOD;
    }
    return hash_val;
}

vector<int> rabinKarp(const string& text, const string& pattern) {
    int t = text.length();
    int p = pattern.length();

    if (t < p) {
        return {}; // no matches possible
    }

    int pattern_hash = hashString(pattern);
    int text_hash = hashString(text.substr(0, p));

    vector<int> matches;
    for (int i = 0; i <= t - p; i++) {
        if (text_hash == pattern_hash) {
            bool match = true;
            for (int j = 0; j < p; j++) {
                if (text[i + j] != pattern[j]) {
                    match = false;
                    break;
                }
            }
            if (match) {
                matches.push_back(i);
            }
        }
        if (i < t - p) {
            text_hash = (text_hash - (text[i] - 'a' + 1) * (int)pow(HASH_PRIME, p - 1) % MOD + MOD) % MOD;
            text_hash = (text_hash * HASH_PRIME + (text[i + p] - 'a' + 1)) % MOD;
        }
    }

    return matches;
}

vector<int> boyerMoore(const string& text, const string& pattern) { // not working yet
    vector<int> matches;
    int t = text.size();
    int p = pattern.size();

    if (t < p) {
        cerr << "\n\nPodany tekst jest krotszy od wzorca!\n\n";
        exit(1);
    }

    complexity = 0;

    vector<int> last_occurrence(256, -1);
    for (int i = 0; i < p; ++i) {
        last_occurrence[pattern[i]] = i;
    }

    int i = p - 1;
    while (i < t) {
        int j = p - 1;
        while (j >= 0 &&(complexity++, text[i] == pattern[j])) {
            --i; --j;
        }
        if (j < 0) {
            matches.push_back(i + 1);
            i += p + 1;
        }
        else {
            i += max(1, j - last_occurrence[text[i]]);
        }
        complexity++;

    }
    return matches;
}

vector<int> boyerMoore2(string text, string pattern) {
    vector<int> matches;
    int t = text.size();
    int p = pattern.size();

    complexity = 0;

    // Preprocessing the bad character heuristic
    vector<int> bad_char(256, -1);
    for (int i = 0; i < p; i++) {
        bad_char[(int)pattern[i]] = i;
    }

    // Preprocessing the good suffix heuristic
    // Calculate the suffix and prefix arrays for the good suffix heuristic
    vector<int> suffix(p, 0);
    vector<bool> prefix(p, false);

    for (int i = p - 2; i >= 0; i--) {
        int j = i;
        while (j >= 0 && pattern[j] == pattern[p - 1 - i + j]) {
            j--;
        }
        suffix[i] = i - j;
        if (j == -1) {
            prefix[i] = true;
        }
    }

    for (int i = 0; i < p - 1; i++) {
        if (suffix[i] == i + 1) {
            for (int j = 0; j < p - 1 - i; j++) {
                if (!suffix[j]) {
                    suffix[j] = -(i + 1);
                }
            }
        }
    }
    if (suffix[0] == 0) {
        suffix[0] = p;
    }
    for (int i = 0; i < p - 1; i++) {
        if (suffix[i] > 0) {
            int j = suffix[i] - 1;
            if (prefix[p - suffix[i]]) {
                suffix[i] = -j;
            }
            else {
                while (j > 0 && pattern[i] != pattern[p - 1 - j]) {
                    j = suffix[j] - 1;
                }
                suffix[i] = j + 1;
            }
        }
    }

    // Boyer-Moore main part of the string searching algorithm
    // Search for the pattern:
    int i = 0;
    while (i <= t - p) {
        int j = p - 1;
        while (j >= 0 && (complexity++, pattern[j] == text[i + j])) {
            j--;
            //complexity++; incorrect
        }
        if (j < 0) {
            matches.push_back(i);
            i += suffix[0];
        }
        else {
            int bad_char_shift = max(1, j - bad_char[(int)text[i + j]]);
            int good_suffix_shift = 0;
            if (j < p - 1) {
                if (suffix[j + 1] == 0) {
                    good_suffix_shift = p - 1 - j;
                }
                else {
                    good_suffix_shift = p - suffix[j + 1];
                    if (prefix[suffix[j + 1]]) {
                        good_suffix_shift = min(good_suffix_shift, j - suffix[j + 1] + 1);
                    }
                }
            }
            i += max(bad_char_shift, good_suffix_shift);
            if (bad_char_shift == 0 && good_suffix_shift == 0) {
                i++;
            }
        }
        //cout << "algorithm i:" << i << '\n';
    }


    return matches;
}


vector<int> sunday(const string& text, const string& pattern) {
    int t = text.length();      
    int p = pattern.length();
    //cout << "Length of text: " << t << ", length of pattern: " << p << '\n';

    if (t < p) {
        cerr << "\n\nPodany tekst jest krotszy od wzorca!\n\n";
        exit(1);
    }

    unordered_map<char, int> move;      
    for (int i = 0; i < p; i++) {
        move[pattern[i]] = p - i; //dont use move.insert(make_pair(pattern[i], p - i)); THIS DOES NOT overwrite VALUES IT THE SAME KEY IS PROVIDED!!!
        //cout << pattern[i] << " and " << p - i << '\n';
    }

    //print map//
    //for (auto& kv : move) {
    //    std::cout << kv.first << ": " << kv.second << std::endl;
    //}

    complexity = 0;

    vector<int> matches;
    int i = 0;
    while (i <= t - p) {
        int j = 0;
        while (j < p && text[i + j] == pattern[j]) {
            j++;
            complexity++;
        }
        
        if (j == p) {   // if matches the pattern add index to result
            matches.push_back(i);   
        }
        
        if (i + p >= t) { // !(i <= n - m) check the current loop condition
            break;
        }

        // calculate the next move
        char check = text[i + p];   //set check to the current position plus the length of pattern
        if (move.find(check) != move.end()) {  // find() function will return interator to unordered_map::end() if there is no check inside the map
            i += move[check];   // if the map contains check, then the move value is calculated from the hash table
        }
        else {
            i += p + 1;     // if the map does not contain check. then the move value is set to pattern.lenght() + 1
        }
    }

    return matches; // returns vector of results
}

vector<int> kmp(const string& text, const string& pattern) {
    int t = text.length();
    int p = pattern.length();
    //cout << "Length of text: " << t << ", length of pattern: " << p << '\n';

    if (t < p) {
        cerr << "\n\nPodany tekst jest krotszy od wzorca!\n\n";
        exit(1);
    }

    vector<int> move(p, 0);
    int j = 0;
    for (int i = 1; i < p; i++) {
        while (j > 0 && pattern[i] != pattern[j]) {
            j = move[j - 1];
        }
        if (pattern[i] == pattern[j]) {
            j++;
        }
        move[i] = j;
    }

    complexity = 0;

    vector<int> matches;
    j = 0;
    for (int i = 0; i < t; i++) {
        while (j > 0 && (complexity++, text[i] != pattern[j])) {
            j = move[j - 1];
            //complexity++;
        }
        if (text[i] == pattern[j]) {
            j++;
            //complexity++;
        }
        if (j == p) {
            matches.push_back(i - p + 1);
            j = move[j - 1];
        }
    }

    return matches;
}

vector<int> sundayPairs(const string& text, const string& pattern) {

    int t = text.length();
    int p = pattern.length();

    if (t < p) {
        cerr << "\n\nPodany tekst jest krotszy od wzorca!\n\n";
        exit(1);
    }

    unordered_map<string, int> move;
    for (int i = 0; i < p - 1; i++) {
        move[pattern.substr(i, 2)] = p - i - 1;
        //cout << pattern.substr(i, 2) << " and " << p - i - 1 << '\n';
    }


    complexity = 0;

    vector<int> matches;
    int i = 0;
    while (i <= t - p) {
        int j = 0;
        while (j < p && text[i + j] == pattern[j]) {
            j++;
            complexity++;
        }

        if (j == p) {   // if matches the pattern add index to result
            matches.push_back(i);
            //cout << "MATCH!\n";
        }

        if (i + p >= t) { // !(i <= n - m) check the current loop condition
            break;
        }

        string check = text.substr(i + p - 1, 2);
        //cout << i << "  " << i + p - 1 << "  "  << check << '\n';
        if (move.find(check) != move.end()) {
            //cout << "found check\n";
            //cout << move[check] << " + " << i << " = " << i + move[check] << '\n';
            i = i + move[check];
        }
        else {

            //cout << "check not found\n";
            //cout << i << " + " << p << " = " << i+p << '\n';
            i += p;
            //cout << i << '\n';
        }
    
    }

    return matches;
}

vector<int> naive(const string& text, const string& pattern) {
    int t = text.length();
    int p = pattern.length();
    //cout << "Length of text: " << t << ", length of pattern: " << p << '\n';

    if (t < p) {
        cerr << "\n\nPodany tekst jest krotszy od wzorca!\n\n";
        exit(1);
    }

    complexity = 0;

    vector<int> matches;
    int i = 0;
    while (i <= t - p) {
        int j = 0;
        while (j < p && text[i + j] == pattern[j]) {
            j++;
            complexity++;
        }

        if (j == p) {   // if matches the pattern add index to result
            matches.push_back(i);
        }

        // next move
        ++i;

    }

    return matches; // returns vector of results

}