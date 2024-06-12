#include <iostream>
#include <vector>
using namespace std;

template<typename T>
struct sliding_max {
	vector<T> frontv, backv;
	vector<T> frontmx, backmx;
	
	void push(T v) {
		frontv.push_back(v);
		if (frontmx.size()) frontmx.push_back(max(frontmx.back(), v)); // combine
		else frontmx.push_back(v);
	}
	
	void pop() {
		if (!backv.size()) {
			while (frontv.size()) {
				backv.push_back(frontv.back());
				if (backmx.size()) backmx.push_back(max(backmx.back(), frontv.back())); // combine
				else backmx.push_back(frontv.back());
				frontv.pop_back();
			}
			frontmx.clear();
		}
		if (!backv.size()) return; // popping nothing, btw
		backv.pop_back();
		backmx.pop_back();
	}
	
	T query() {
		if (frontmx.size() && backmx.size()) return max(frontmx.back(), backmx.back()); // combine
		if (frontmx.size()) return frontmx.back();
		if (backmx.size()) return backmx.back();
		return T(-1e9); // sentinel
	}
};

int main() {
	sliding_max<long > sm;
	vector<int> nums = {1, 3, -1, -3, 5, 3, 6, 7};
	int k = 3; // Window size

	// Simulate the sliding window
	for (int i = 0; i < nums.size(); ++i) {
		sm.push(nums[i]);
		if (i >= k - 1) {
			cout << "Max in window ending at index " << i << ": " << sm.query() << endl;
			sm.pop();
		}
	}

	return 0;
}