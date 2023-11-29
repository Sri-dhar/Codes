#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<int> PieArray(string pattern) {
    int n = pattern.length();
    vector<int> pie(n, 0);
    int len = 0;
    int i = 1;
    while (i < n) 
    {
        if (pattern[i] == pattern[len]) pie[i++] = ++len;
        else 
        {
            if (len != 0) len = pie[len - 1];
            else  pie[i++] = 0;
        }
    }
    return pie;
}

void KMP(string text, string pattern) {
    int n = text.length();
    int m = pattern.length();
    vector<int> pie = PieArray(pattern);
    int i = 0;
    int j = 0;
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }
        if (j == m) {
            cout << "Pattern found at index " << i - j << endl;
            j = pie[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = pie[j - 1];
            } else {
                i++;
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB";
    string pattern = "ABABCABAB";
    vector<int> pieArray = PieArray(pattern);
    for (int i = 0; i < pieArray.size(); i++) {
        cout << pattern[i] <<" "<< pieArray[i] << "\n";
    }
    KMP(text, pattern);
    return 0;
}

