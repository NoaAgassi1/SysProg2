#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "SquareMat.hpp"
#include <cmath>

using namespace matrix;

constexpr double EPS = 1e-6;

bool isEqual(double a, double b, double eps = EPS) {
    return std::abs(a - b) < eps;
}

bool isEqual(const SquareMat& a, const SquareMat& b) {
    if (a.getSize() != b.getSize()) return false;
    for (int i = 0; i < a.getSize(); ++i)
        for (int j = 0; j < a.getSize(); ++j)
            if (!isEqual(a[i][j], b[i][j]))
                return false;
    return true;
}

TEST_SUITE("Basic Operations") {
    TEST_CASE("Add, Subtract, Multiply, Transpose, Power") {
        double d1[] = {1, 2, 3, 4};
        double d2[] = {1, 2, 3, 4};
        SquareMat m1(2, d1);
        SquareMat m2(2, d2);

        double expectedAdd[] = {2, 4, 6, 8};
        CHECK(isEqual(m1 + m2, SquareMat(2, expectedAdd)));

        double expectedSub[] = {0, 0, 0, 0};
        CHECK(isEqual(m1 - m2, SquareMat(2, expectedSub)));

        double expectedMul[] = {7, 10, 15, 22};
        CHECK(isEqual(m1 * m2, SquareMat(2, expectedMul)));

        double expectedTranspose[] = {1, 3, 2, 4};
        CHECK(isEqual(~m1, SquareMat(2, expectedTranspose)));

        CHECK(isEqual(m1 ^ 0, SquareMat(2, new double[4]{1,0,0,1})));
        CHECK(isEqual(m1 ^ 1, m1));
        CHECK(isEqual(m1 ^ 2, SquareMat(2, expectedMul)));
    }

    TEST_CASE("Scalar Multiply, Divide, Modulo") {
        double d[] = {1, 2, 3, 4};
        SquareMat m(2, d);

        double expectedMul[] = {2, 4, 6, 8};
        CHECK(isEqual(m * 2, SquareMat(2, expectedMul)));
        CHECK(isEqual(2 * m, SquareMat(2, expectedMul)));

        double expectedDiv[] = {0.5, 1, 1.5, 2};
        CHECK(isEqual(m / 2, SquareMat(2, expectedDiv)));

        double expectedMod[] = {1, 2, 0, 1};
        CHECK(isEqual(m % 3, SquareMat(2, expectedMod)));

        CHECK_THROWS_AS(m / 0, std::invalid_argument);
        CHECK_THROWS_AS(m % 0, std::invalid_argument);
    }

    TEST_CASE("Determinant") {
        double d[] = {1, 2, 3, 4};
        SquareMat m(2, d);
        CHECK(isEqual(!m, -2.0));

        SquareMat zero(2);
        CHECK(isEqual(!zero, 0.0));

        m[0][0] = m[0][1] = 0;
        CHECK(isEqual(!m, 0.0));
    }
}

TEST_SUITE("Comparison Operators") {
    TEST_CASE("==, !=, <=, >=, <, > based on sum") {
        double d1[] = {1, 2, 3, 4}; // sum = 10
        double d3[] = {4, 3, 2, 1}; // sum = 10
        SquareMat m1(2, d1);
        SquareMat m3(2, d3);

        CHECK(m1 == m3); // same sum
        CHECK_FALSE(m1 != m3);

        m3[0][0] += 2; // sum = 12
        CHECK(m3 > m1);
        CHECK(m1 < m3);
        CHECK(m1 != m3);
    }
}

TEST_SUITE("Increment / Decrement") {
    TEST_CASE("++ / -- operators") {
        double d[] = {1, 2, 3, 4};
        SquareMat m(2, d);

        SquareMat inc = m;
        ++inc;
        double expectedPre[] = {2, 3, 4, 5};
        CHECK(isEqual(inc, SquareMat(2, expectedPre)));

        inc = m;
        SquareMat post = inc++;
        CHECK(isEqual(post, m));
        CHECK(isEqual(inc, SquareMat(2, expectedPre)));

        inc = m;
        --inc;
        double expectedPreDec[] = {0, 1, 2, 3};
        CHECK(isEqual(inc, SquareMat(2, expectedPreDec)));

        inc = m;
        post = inc--;
        CHECK(isEqual(post, m));
        CHECK(isEqual(inc, SquareMat(2, expectedPreDec)));
    }
}

TEST_SUITE("Copy / Assignment") {
    TEST_CASE("Copy constructor and assignment") {
        double d[] = {1, 2, 3, 4};
        SquareMat m1(2, d);
        SquareMat copy(m1);
        CHECK(copy == m1);

        SquareMat other(3); // different size
        other = m1;
        CHECK(other == m1);
    }
}

TEST_SUITE("Exceptions and invalid input") {
    TEST_CASE("Invalid construction") {
        CHECK_THROWS_AS(SquareMat(0), std::invalid_argument);
    }

    TEST_CASE("Mismatched matrix sizes") {
        double d2[] = {1,2,3,4};
        double d3[] = {1,2,3,4,5,6,7,8,9};
        SquareMat m2(2, d2);
        SquareMat m3(3, d3);
        CHECK_THROWS_AS(m2 + m3, std::invalid_argument);
        CHECK_THROWS_AS(m2 - m3, std::invalid_argument);
        CHECK_THROWS_AS(m2 * m3, std::invalid_argument);
        CHECK_THROWS_AS(m2 % m3, std::invalid_argument);
    }
}

TEST_SUITE("Compound Assignment Operators") {
    TEST_CASE("+= -= *= /= %=") {
        double d[] = {1, 2, 3, 4};
        SquareMat m1(2, d);
        SquareMat copy = m1;

        copy += m1;
        double add[] = {2, 4, 6, 8};
        CHECK(isEqual(copy, SquareMat(2, add)));

        copy = m1;
        copy -= m1;
        double sub[] = {0, 0, 0, 0};
        CHECK(isEqual(copy, SquareMat(2, sub)));

        copy = m1;
        double mul[] = {7, 10, 15, 22};
        CHECK(isEqual(copy *= m1, SquareMat(2, mul)));

        copy = m1;
        double div[] = {0.5, 1, 1.5, 2};
        CHECK(isEqual(copy /= 2, SquareMat(2, div)));

        copy = m1;
        double mod[] = {1, 2, 0, 1};
        CHECK(isEqual(copy %= 3, SquareMat(2, mod)));
    }
}
