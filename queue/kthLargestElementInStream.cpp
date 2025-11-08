#include <bits/stdc++.h>
using namespace std;

/* -----------------------------------------------------------
     BRUTE FORCE APPROACH
   ----------------------------------------------------------- 
   IDEA:
    Split the string into words.
    For each word, count its occurrences using nested loops.
    Sort words by frequency in descending order.
    Return top K.

   TIME COMPLEXITY: O(N²)
   SPACE COMPLEXITY: O(M)
----------------------------------------------------------- */
vector<string> topKFrequent_Brute(string text, int k) {
    stringstream ss(text);
    vector<string> words;
    string word;

    while (ss >> word)
        words.push_back(word);

    vector<pair<string, int>> freq;

    for (int i = 0; i < words.size(); i++) {
        bool found = false;
        for (auto &p : freq) {
            if (p.first == words[i]) {
                p.second++;
                found = true;
                break;
            }
        }
        if (!found)
            freq.push_back({words[i], 1});
    }

    sort(freq.begin(), freq.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });

    vector<string> res;
    for (int i = 0; i < k && i < freq.size(); i++)
        res.push_back(freq[i].first);

    return res;
}

/* -----------------------------------------------------------
     BETTER APPROACH
   ----------------------------------------------------------- 
   IDEA:
    Use unordered_map to count each word’s frequency (O(N)).
    Store map entries into a vector and sort by frequency (O(M log M)).
    Pick top K.

   TIME COMPLEXITY: O(N + M log M)
   SPACE COMPLEXITY: O(M)
----------------------------------------------------------- */
vector<string> topKFrequent_Better(string text, int k) {
    unordered_map<string, int> freq;
    stringstream ss(text);
    string word;

    while (ss >> word)
        freq[word]++;

    vector<pair<string, int>> vec(freq.begin(), freq.end());
    sort(vec.begin(), vec.end(), [](auto &a, auto &b) {
        return a.second > b.second;
    });

    vector<string> res;
    for (int i = 0; i < k && i < vec.size(); i++)
        res.push_back(vec[i].first);

    return res;
}

/* -----------------------------------------------------------
    OPTIMAL APPROACH
   ----------------------------------------------------------- 
   IDEA:
   Count frequencies with unordered_map (O(N)).
    Maintain a MIN HEAP of size K.
       - Push each {word, freq}.
       - If heap size > K → pop smallest frequency.
   The heap contains top K frequent words.

   TIME COMPLEXITY: O(N + M log K)
   SPACE COMPLEXITY: O(M)
----------------------------------------------------------- */
vector<string> topKFrequent_Optimal(string text, int k) {
    unordered_map<string, int> freq;
    stringstream ss(text);
    string word;

    while (ss >> word)
        freq[word]++;

    // Min heap (least frequent element at top)
    auto cmp = [](auto &a, auto &b) {
        return a.second > b.second;
    };
    priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp)> minHeap(cmp);

    for (auto &p : freq) {
        minHeap.push(p);
        if (minHeap.size() > k)
            minHeap.pop();
    }

    vector<string> res;
    while (!minHeap.empty()) {
        res.push_back(minHeap.top().first);
        minHeap.pop();
    }

    reverse(res.begin(), res.end());
    return res;
}

/* -----------------------------------------------------------
     MAIN FUNCTION 
----------------------------------------------------------- */
int main() {
    string text = "apple banana apple orange banana apple";
    int k = 2;

    cout << "\n BRUTE FORCE \n";
    for (auto &w : topKFrequent_Brute(text, k)) cout << w << " ";
    cout << "\n\n BETTER APPROACH \n";
    for (auto &w : topKFrequent_Better(text, k)) cout << w << " ";
    cout << "\n\nOPTIMAL APPROACH \n";
    for (auto &w : topKFrequent_Optimal(text, k)) cout << w << " ";
    cout << "\n";
}
