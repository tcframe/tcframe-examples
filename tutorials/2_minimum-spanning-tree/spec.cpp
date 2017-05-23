#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N, M;
    vector<int> U, V, W;
    int res;

    void InputFormat() {
        LINE(N, M);
        LINES(U, V, W) % SIZE(M);
    }

    void OutputFormat() {
        LINE(res);
    }

    void GradingConfig() {
        TimeLimit(1);
        MemoryLimit(64);
    }

    void Constraints() {
        CONS(2 <= N && N <= 100000);
        CONS(N - 1 <= M && M <= 100000);
        CONS(eachElementBetween(U, 0, N - 1));
        CONS(eachElementBetween(V, 0, N - 1));
        CONS(eachElementBetween(W, 1, 1000));
        CONS(noSelfLoop(U, V));
        CONS(isConnected(N, U, V));
    }

    void Subtask1() {
        Points(20);

        CONS(M <= 20);
    }

    void Subtask2() {
        Points(30);

        CONS(allAreEqual(W));
    }

    void Subtask3() {
        Points(50);
    }

private:
    bool eachElementBetween(const vector<int>& v, int lo, int hi) {
        for (int x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }

    bool allAreEqual(const vector<int>& v) {
        for (int x : v) {
            if (x != v[0]) {
                return false;
            }
        }
        return true;
    }

    bool noSelfLoop(const vector<int>& u, const vector<int>& v) {
        for (int i = 0; i < u.size(); i++) {
            if (u[i] == v[i]) {
                return false;
            }
        }
        return true;
    }

    bool isConnected(int n, const vector<int>& u, const vector<int>& v) {
        vector<bool> isVisited(n);
        vector<vector<int>> adj(n);
        for (int i = 0; i < u.size(); i++) {
            adj[u[i]].push_back(v[i]);
            adj[v[i]].push_back(u[i]);
        }
        int numNodesVisited = 0;
        queue<int> q;
        q.push(0);
        while (!q.empty()) {
            int now = q.front();
            q.pop();
            if (isVisited[now]) {
                continue;
            }
            isVisited[now] = true;
            ++numNodesVisited;
            for (int v : adj[now]) {
                q.push(v);
            }
        }
        return numNodesVisited == n;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Subtasks({1, 3});
        Input({
            "3 3",
            "0 1 2",
            "1 2 3",
            "2 0 4"
        });
        Output({
            "5"
        });
    }

    void BeforeTestCase() {
        U.clear();
        V.clear();
        W.clear();
    }

    void TestGroup1() {
        Subtasks({1, 2, 3});

        CASE(N = 2, M = 1, U = {0}, V = {1}, W = {1});
        CASE(N = 21, M = 20, randomTree(N, U, V), W.assign(M, 1000));
        CASE(N = 20, M = 20, randomGraph(N, M, U, V), W.assign(M, 1000));

        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(2, 21),
                 M = rnd.nextInt(N - 1, 20),
                 randomGraph(N, M, U, V),
                 W.assign(M, rnd.nextInt(1, 1000)));
        }
    }

    void TestGroup2() {
        Subtasks({1, 3});

        // We manually create a small test case where greedily choosing
        // the first N - 1 edges with smallest weight will create a cycle.
        CASE(N = 4, M = 4,
             U = {0, 1, 2, 0},
             V = {1, 2, 0, 3},
             W = {1, 1, 1, 2});

        CASE(N = 2, M = 2, U = {0, 1}, V = {1, 0}, W = {1, 2});
        CASE(N = 21, M = 20, randomTree(N, U, V), randomWeight(M, W));

        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(2, 21),
                 M = rnd.nextInt(N - 1, 20),
                 randomGraph(N, M, U, V),
                 randomWeight(M, W));
        }
    }

    void TestGroup3() {
        Subtasks({2, 3});

        CASE(N = 2, M = 21, randomGraph(N, M, U, V), W.assign(M, rnd.nextInt(1, 1000)));
        CASE(N = 100000, M = 99999, randomGraph(N, M, U, V), W.assign(M, 1000));
        CASE(N = 100000, M = 100000, randomGraph(N, M, U, V), W.assign(M, 1000));

        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(2, 100000),
                 M = rnd.nextInt(max(N - 1, 21), 100000),
                 randomGraph(N, M, U, V),
                 W.assign(M, rnd.nextInt(1, 1000)));
        }
    }

    void TestGroup4() {
        Subtasks({3});

        CASE(N = 2, M = 21, randomGraph(N, M, U, V), randomWeight(M, W));
        CASE(N = 100000, M = 99999, randomGraph(N, M, U, V), randomWeight(M, W));
        CASE(N = 100000, M = 100000, randomGraph(N, M, U, V), randomWeight(M, W));

        for (int i = 0; i < 5; i++) {
            CASE(N = rnd.nextInt(2, 100000),
                 M = rnd.nextInt(max(N - 1, 21), 100000),
                 randomGraph(N, M, U, V),
                 randomWeight(M, W));
        }
    }

private:
    void randomWeight(int m, vector<int>& w, int minW = 1, int maxW = 1000) {
        for (int i = 0; i < m; i++) {
            w.push_back(rnd.nextInt(minW, maxW));
        }
    }

    void renumber(int n, vector<int>& u, vector<int>& v) {
        vector<int> permutation;
        for (int i = 0; i < n; i++) {
            permutation.push_back(i);
        }
        rnd.shuffle(permutation.begin(), permutation.end());
        for (int i = 0; i < u.size(); i++) {
            u[i] = permutation[u[i]];
            v[i] = permutation[v[i]];
        }
    }

    void randomTree(int n, vector<int>& u, vector<int>& v) {
        for (int i = 1; i < n; i++) {
            u.push_back(i);
            v.push_back(rnd.nextInt(0, i - 1));
        }
        renumber(n, u, v);
    }

    void randomGraph(int n, int m, vector<int>& u, vector<int>& v) {
        randomTree(n, u, v);
        while (u.size() < m) {
            int newU = rnd.nextInt(0, N - 2);
            int newV = rnd.nextInt(newU + 1, N - 1);
            u.push_back(newU);
            v.push_back(newV);
        }
    }
};
