#include "SquareMat.hpp"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;
using namespace matrix;

int main() {
    srand(time(nullptr));

    // ---------- Constructors ----------
    const int SIZE = 3;
    double data[] = {1, 2, 3, 4};
    SquareMat m1(2, data);
    SquareMat m2(2, data);
    SquareMat m3 = m1; // Copy constructor
    SquareMat m4(2);   // Zero matrix

    cout << "m1:\n" << m1;
    cout << "m2:\n" << m2;

    // ---------- Binary operations ----------
    cout << "m1 + m2:\n" << (m1 + m2);
    cout << "m1 - m2:\n" << (m1 - m2);
    cout << "m1 * m2:\n" << (m1 * m2);
    cout << "m1 * 2:\n" << (m1 * 2);
    cout << "2 * m1:\n" << (2 * m1);
    cout << "m1 / 2:\n" << (m1 / 2);
    cout << "m1 % m2:\n" << (m1 % m2);
    cout << "m1 % 3:\n" << (m1 % 3);

    // ---------- Compound assignment operators ----------
    m4 = m1;
    m4 += m2;
    cout << "m1 += m2:\n" << m4;
    m4 -= m2;
    cout << "After -= (should be back to m1):\n" << m4;
    m4 *= m2;
    cout << "*= matrix:\n" << m4;
    m4 *= 2;
    cout << "*= scalar:\n" << m4;
    m4 /= 2;
    cout << "/= scalar:\n" << m4;
    m4 %= m2;
    cout << "%= matrix:\n" << m4;
    m4 %= 3;
    cout << "%= scalar:\n" << m4;

    // ---------- Transpose and Power ----------
    cout << "~m1 (transpose):\n" << ~m1;
    cout << "m1 ^ 0 (identity):\n" << (m1 ^ 0);
    cout << "m1 ^ 1:\n" << (m1 ^ 1);
    cout << "m1 ^ 2:\n" << (m1 ^ 2);

    // ---------- Determinant ----------
    cout << "!m1 (det): " << !m1 << endl;

    // ---------- Comparisons ----------
    cout << boolalpha;
    cout << "m1 == m2: " << (m1 == m2) << endl;
    cout << "m1 != m3: " << (m1 != m3) << endl;
    cout << "m1 < m3: " << (m1 < m3) << endl;
    cout << "m1 <= m3: " << (m1 <= m3) << endl;
    cout << "m1 > m3: " << (m1 > m3) << endl;
    cout << "m1 >= m3: " << (m1 >= m3) << endl;

    // ---------- Increment / Decrement ----------
    cout << "++m1:\n" << ++m1;
    cout << "m1++:\n" << m1++;
    cout << "After post-increment:\n" << m1;
    cout << "--m1:\n" << --m1;
    cout << "m1--:\n" << m1--;
    cout << "After post-decrement:\n" << m1;

    // ---------- Random matrix ----------
    SquareMat randMat(SIZE);
    for (int i = 0; i < SIZE * SIZE; ++i) {
        randMat[i / SIZE][i % SIZE] = (rand() % 100) / 10.0; // Range: 0.0 to 9.9
    }
    cout << "\nRandom matrix (" << SIZE << "x" << SIZE << "):\n" << randMat;

    // Actual use of randMat
    cout << "randMat + randMat:\n" << (randMat + randMat);
    cout << "randMat - randMat:\n" << (randMat - randMat);
    cout << "randMat * randMat:\n" << (randMat * randMat);
    cout << "~randMat:\n" << ~randMat;
    cout << "randMat ^ 2:\n" << (randMat ^ 2);
    cout << "!randMat: " << !randMat << endl;

    return 0;
}
