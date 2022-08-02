
#include <iostream>
using namespace std;
/**
 * Let us go through some of the simple concepts of probability that we will use.
 * Consider the following example of tossing two coins.
 * If we toss two coins and look at all the different possibilities,
 * we have the sample space as:{HH, HT, TH, TT}
 */

int main(int argc, char const *argv[])
{
    const char probabilities[4][2] = {{'H', 'H'}, {'H', 'T'}, {'T', 'H'}, {'T', 'T'}};
    const char A = 'H'; // Second event
    const char B = 'H'; // First event

    const int totalProbabilities = sizeof(probabilities) / sizeof(probabilities[0]);
    double a_probabilities = 0;
    double b_probabilities = 0;

    for (int i = 0; i < totalProbabilities; i++)
    {
        if (probabilities[i][0] == A)
        {
            a_probabilities++;
        }
        if (probabilities[i][1] == B)
        {
            b_probabilities++;
        }
    }

    a_probabilities /= totalProbabilities;
    b_probabilities /= totalProbabilities;

    cout << "A Probabilities : " << a_probabilities << endl;
    cout << "B Probabilities :" << b_probabilities << endl;

    /** We're going to focus on A, and we write that out as a probability of A given B
     *  Probability = P(A|B)
     * = [ P(B|A) * P(A) ] / P(B)
     * = [ P(First coin being tail given the second coin is the head) * P(Second coin being head) ] / P(First coin being tail)
     */
    const double probability = ((a_probabilities + b_probabilities) / 2) * a_probabilities / b_probabilities;
    cout << "Result : " << probability << endl;
    return 0;
}
