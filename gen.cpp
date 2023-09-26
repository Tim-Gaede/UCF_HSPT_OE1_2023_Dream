#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef vector<int> vi;

template<class S, class T> string join(S sep, vector<T>& vec){
    stringstream res;
    rep(i, 0, vec.size()){
        if(i) res << sep;
        res << vec[i];
    }
    return res.str();
}

typedef tuple<int, int, vector<int>> testcase;
typedef string answer;

const string fail = "It do go down";

ostream& operator<<(ostream &os, testcase &tc){
    auto [n, k, fs] = tc;
    return os << n << " " << k << "\n" << join(" ", fs);
}

testcase genTestcase(int maxn, int maxk, int maxv){
    int n = 1 + (rand()%maxn);
    int k = 1 + (rand()%n); 
    assert(k <= n); assert(n <= 2000);
    vector<int> vals(n);
    for(auto &x : vals) x = 1 + (rand()%maxv);
    return {n, k, vals};
}

answer solve(testcase tc){
    auto [n_, k, fs_] = tc;
    auto n = n_;
    auto fs = fs_;
    assert(n == fs.size());
    if(k > 11) return fail;
    int orr = 0; for(auto x : fs) orr |= x;
    if(k > __builtin_popcount(orr)) return fail;
    vector<vector<vector<int>>> dp(k+1, vector<vector<int>>(n, vector<int>(orr + 10, -1)));
    auto solve = [&](int k, int i, int sum, auto &&solve)->int{
        if(k < 0) return -1;
        if(i >= n) return k == 0 ? sum : -1;
        auto &ans = dp[k][i][sum];
        if(ans != -1) return ans;

        ans = solve(k, i+1, sum, solve);
        if((sum & fs[i]) == 0) ans = max(ans, solve(k-1, i+1, sum + fs[i], solve));
        return ans;
    };

    int res = solve(k, 0, 0, solve);
    if(res == -1) return fail;
    return to_string(res);
}

int kBitNumber(int nbits, int maxBit){
    int res = 0;
    while(nbits--) res |= 1 << (rand()%(maxBit+1));
    return res;
}

vector<testcase> trickyCases(){
    vector<testcase> res;

    { // Should be 2047, we'll surely generate one of each bit so just pick those bad boys. 
        int n = 100, k = 11;
        vector<int> fs(n);
        for(auto &x : fs) x = kBitNumber(1, 10);
        res.emplace_back(n, k, fs);
    }
    for(int i = 0; i < 5; i++) { // Probably possible, the numbers have 1 or 2 bits on 
        int n = 100, k = 5 + (rand()%4);
        vector<int> fs(n);
        for(auto &x : fs) x = kBitNumber(2, 10);
        res.emplace_back(n, k, fs);
    }
    for(int i = 0; i < 10; i++) { // Probably possible, the numbers have 1 or 2 bits on 
        int n = 100, k = 5 + (rand()%4);
        vector<int> fs(n);
        for(auto &x : fs) x = kBitNumber(2, 6);
        for(int j = 0; j < 10; j++) n++, fs.push_back(kBitNumber(2, 10));
        res.emplace_back(n, k, fs);
    }

    return res;
}

int main(){
    cin.tie(0)->sync_with_stdio(0);
    cin.exceptions(cin.failbit);
    vector<testcase> samples = {
        {5, 1, {1, 2, 4, 8, 16}},
        {3, 2, {10, 2, 5}},
        {3, 3, {10, 2, 5}}
    };

    vector<testcase> input;
    vector<answer> output;

    srand(2);
    cout << "Generating..." << endl;
    for(auto x : samples) input.push_back(x);
    rep(i, 0, 10) input.push_back(genTestcase(20, 5, 511)); // little correctness cases
    rep(i, 0, 10) input.push_back(genTestcase(100, 4, 2000)); // The bulk of the cases
    rep(i, 0, 3) input.push_back(genTestcase(2000, 1999, 2000)); // TLE cases, definitely impossible
    rep(i, 0, 3) input.push_back(genTestcase(2000, 11, 2000)); // Max cases, probably impossible

    auto tricky = trickyCases();
    for(auto c : tricky) input.push_back(c);

    cout << "Solving..." << endl;
    for(auto x : input) output.push_back(solve(x));


    ofstream inFile("dream.in");
    ofstream outFile("dream.out");

    cout << "Printing..." << endl;
    inFile << input.size() << endl;
    for(auto x : input) inFile << x << endl;
    for(auto x : output) outFile << x << endl;

    return 0;
}
