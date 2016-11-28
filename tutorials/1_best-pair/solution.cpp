#include <bits/stdc++.h>
using namespace std;

int N;
vector<long long> pos;
vector<long long> neg;

int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		long long x;
		cin >> x;
		if (x >= 0) {
			pos.push_back(x);
		} else {
			neg.push_back(x);
		}
	}
	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end());

	long long res = LLONG_MIN;
	if (pos.size() >= 2) {
		res = max(res, pos[pos.size()-1] * pos[pos.size()-2]);
	}
	if (neg.size() >= 2) {
		res = max(res, neg[0] * neg[1]);
	}
	if (!neg.empty() && !pos.empty()) {
		res = max(res, neg[neg.size()-1] * pos[0]);
	}

	cout << res << endl;
}
