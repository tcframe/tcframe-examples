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
        CONS(M <= 20);
    }

    void Subtask2() {
        CONS(allAreEqual(W));
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

    bool allAreEqual(const vector<int> &v) {
        for (int x : v) {
            if (x != v[0]) {
                return false;
            }
        }
        return true;
    }

    bool noSelfLoop(const vector<int> &U, const vector<int> &V) {
        for (int i = 0; i < (int)U.size(); ++i) {
            if (U[i] == V[i]) {
                return false;
            }
        }
        return true;
    }

    bool isConnected(const int &N, const vector<int> &U, const vector<int> &V) {
        vector<bool> isVisited(N);
        vector<vector<int>> adj(N);
        for (int i = 0; i < (int)U.size(); ++i) {
            adj[U[i]].push_back(V[i]);
            adj[V[i]].push_back(U[i]);
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
        return numNodesVisited == N;
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
        CASE(N = 21, M = 20, randomTree(), W.assign(M, 1000));
        CASE(N = 20, M = 20, randomGraph(), W.assign(M, 1000));

        for (int i = 0; i < 5; ++i) {
            CASE(N = rnd.nextInt(2, 21),
                 M = rnd.nextInt(N - 1, 20),
                 randomGraph(),
                 W.assign(M, rnd.nextInt(1, 1000)));
        }
    }

    void TestGroup2() {
        Subtasks({1, 3});
        
        CASE(N = 4, M = 4,
             U = {0, 1, 2, 0},
             V = {1, 2, 0, 3},
             W = {1, 1, 1, 2});

        CASE(N = 2, M = 2, U = {0, 1}, V = {1, 0}, W = {1, 2});
        CASE(N = 21, M = 20, randomTree(), randomWeight());

        for (int i = 0; i < 5; ++i) {
            CASE(N = rnd.nextInt(2, 21),
                 M = rnd.nextInt(N - 1, 20),
                 randomGraph(),
                 randomWeight());
        }

    }

    void TestGroup3() {
        Subtasks({2, 3});

        CASE(N = 2, M = 21, randomGraph(), W.assign(M, rnd.nextInt(1, 1000)));
        CASE(N = 100000, M = 99999, randomGraph(), W.assign(M, 1000));
        CASE(N = 100000, M = 100000, randomGraph(), W.assign(M, 1000));

        for (int i = 0; i < 5; ++i) {
            CASE(N = rnd.nextInt(2, 100000),
                 M = rnd.nextInt(max(N - 1, 21), 100000),
                 randomGraph(),
                 W.assign(M, rnd.nextInt(1, 1000)));
        }
    }

    void TestGroup4() {
        Subtasks({3});

        CASE(N = 2, M = 21, randomGraph(), randomWeight());
        CASE(N = 100000, M = 99999, randomGraph(), randomWeight());
        CASE(N = 100000, M = 100000, randomGraph(), randomWeight());

        for (int i = 0; i < 5; ++i) {
            CASE(N = rnd.nextInt(2, 100000),
                 M = rnd.nextInt(max(N - 1, 21), 100000),
                 randomGraph(),
                 randomWeight());
        }
    }

private:
    void randomWeight(int minW = 1, int maxW = 1000) {
        for (int i = 0; i < M; ++i) {
            W.push_back(rnd.nextInt(minW, maxW));
        }
    }

    void renumber() {
        vector<int> permutation;
        for (int i = 0; i < N; ++i) {
            permutation.push_back(i);
        }
        rnd.shuffle(permutation.begin(), permutation.end());
        for (int i = 0; i < M; ++i) {
            U[i] = permutation[U[i]];
            V[i] = permutation[V[i]];
        }
    }

    void randomTree() {
        for (int i = 1; i < N; ++i) {
            U.push_back(i);
            V.push_back(rnd.nextInt(0, i - 1));
        }
        renumber();
    }

    void randomGraph() {
        randomTree();
        while (U.size() < M) {
            int u = rnd.nextInt(0, N - 2);
            int v = rnd.nextInt(u + 1, N - 1);
            U.push_back(u);
            V.push_back(v);
        }
    }
};



