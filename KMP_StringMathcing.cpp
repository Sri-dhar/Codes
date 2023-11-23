#include <iostream>
#include <vector>
using namespace std;
// Function to compute the LPS (Longest Proper Prefix which is also Suffix) array
std::vector<int> computeLPS(const std::string& pattern) {
    int patternLength = pattern.length();
    std::vector<int> pie(patternLength, 0);

    int len = 0;  // Length of the previous longest prefix suffix

    for (int i = 1; i < patternLength; ) {
        if (pattern[i] == pattern[len]) {
            len++;
            pie[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = pie[len - 1];
            } 
            else if(len == 0) {
                pie[i] = 0;
                i++;
            }
        }
    }

    return pie;
}

// Function to perform string matching using KMP algorithm
void KMP(const std::string& text, const std::string& pattern) {
    int textLength = text.length();
    int patternLength = pattern.length();

    // Compute the LPS array
    std::vector<int> pie = computeLPS(pattern);

    int i = 0;  // Index for text
    int j = 0;  // Index for pattern

    while (i < textLength) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == patternLength) {
            std::cout << "Pattern found at index " << i - j << std::endl;
            j = pie[j - 1];
        } else if (i < textLength && pattern[j] != text[i]) {
            if (j != 0) {
                j = pie[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    std::string text, pattern;
    
    // Input text and pattern
    std::cout << "Enter the text: ";
    std::cin >> text;
    std::cout << "Enter the pattern: ";
    std::cin >> pattern;

    // Perform string matching using KMP algorithm
    KMP(text, pattern);
    
    cout<<endl;
    vector<int> LPS = computeLPS(pattern);
    for(int i=0; i<LPS.size(); i++){
        cout<<LPS[i]<<" ";
    }

    return 0;
}
