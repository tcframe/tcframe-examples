#include <bits/stdc++.h>
#include <tcframe/spec.hpp>

using namespace std;
using namespace tcframe;

class ProblemSpec : public BaseProblemSpec {
protected:
    int N;
    vector<long long> A;
    long long res;

    void InputFormat() {
        LINE(N);
        LINE(A % SIZE(N));
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
        CONS(eachElementBetween(A, -1000000, 1000000));
    }

private:
    bool eachElementBetween(const vector<long long>& v, long long lo, long long hi) {
        for (long long x : v) {
            if (x < lo || x > hi) {
                return false;
            }
        }
        return true;
    }
};

class TestSpec : public BaseTestSpec<ProblemSpec> {
protected:
    void SampleTestCase1() {
        Input({
            "4",
            "4 -2 3 1"
        });
        Output({
            "12"
        });
    }

    void BeforeTestCase() {
        A.clear();
    }

    void TestCases() {
        // The answer is the product of two largest non-negative elements
        CASE(N = 5, A = {-2, -1, 2, 3, 0});

        // The answer is the product of two smallest negative elements
        // The smallest possible value for N
        CASE(N = 5, A = {3, 4, -1, -3, -5});

        // The answer is the product of the largest negative element and the smallest positive element
        CASE(N = 2, A = {2, -1});

        // The answer is 0
        CASE(N = 4, A = {0, 2, 0, 0});
        CASE(N = 4, A = {0, 0, 0, 0});

        // The answer is the maximum possible answer
        CASE(N = 3, A = {1000000, -1, 1000000});

        // The answer is the minimum possible answer
        CASE(N = 2, A = {-1000000, 1000000});

        // All elements are positive/negative
        CASE(N = 4, A = {1, 2, 3, 4});
        CASE(N = 4, A = {-1, -2, -3, -4});

        // Random values for elements of A
        CASE(N = 10, randomElements(5, 5));
        CASE(N = 100, randomElements(20, 50));
        CASE(N = 1000, randomElements(300, 300));
        CASE(N = 10000, randomElements(2500, 6000));

        // The maximum value of N
        CASE(N = 100000, randomElements(50000, 50000));
        CASE(N = 100000, randomElements(10000, 80000));
        CASE(N = 100000, randomElements(80000, 10000));
    }

private:
    void randomElements(int numPos, int numNeg) {
        assert(numPos + numNeg <= N);

        for (int i = 0; i < numPos; i++) {
            A.push_back(rnd.nextInt(1, 1000000));
        }
        for (int i = 0; i < numNeg; i++) {
            A.push_back(rnd.nextInt(-1000000, -1));
        }
        for (int i = 0; i < N-numPos-numNeg; i++) {
            A.push_back(0);
        }

        rnd.shuffle(A.begin(), A.end());
    }
};
