class FreqStack {
public:

    vector<int> v;
    map<int> mp;

    FreqStack() {
        
    }
    
    void push(int val) {
        v.push_back(val);
        mp[val]++;
    }
    
    int pop() {
        int max_freq = 0;
        for(auto it = mp.begin(); it != mp.end(); it++) {
            max_freq = max(max_freq, it->second);
        }

        for(int i = v.size() - 1; i >= 0; i--) {
            if(mp[v[i]] == max_freq) {
                int val = v[i];
                v.erase(v.begin() + i);
                mp[val]--;
                if(mp[val] == 0) {
                    mp.erase(val);
                }
                return val;
            }
        }

        return -1;
    }
};

/**
 * Your FreqStack object will be instantiated and called as such:
 * FreqStack* obj = new FreqStack();
 * obj->push(val);
 * int param_2 = obj->pop();
 */