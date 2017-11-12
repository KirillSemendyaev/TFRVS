#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void calculateTheta(int N, vector<double> lambda, vector<int> m, vector<int> mu)
{
    ofstream fout;
    int n;
    if (mu.size() > 1)
        fout.open("21.out", ios_base::out | ios_base::trunc);
    if (lambda.size() > 1)
        fout.open("22.out", ios_base::out | ios_base::trunc);
    if (m.size() > 1)
        fout.open("23.out", ios_base::out | ios_base::trunc);

    if (!fout.is_open()) {
        cout << "Cant open file" << endl;
        return;
    }
    vector<double>::iterator lit = lambda.begin();
    vector<int>::iterator mit = m.begin();
    vector<int>::iterator muit = mu.begin();
    double sum, mult;

    for (n = 65527; n < 65536; n++) {
        fout << n << " ";
        for (lit = lambda.begin(), mit = m.begin(), muit = mu.begin();
             ((lambda.size() == 1) || (lit != lambda.end())) &&
             ((m.size() == 1) || (mit != m.end())) &&
             ((mu.size() == 1) || (muit != mu.end()));
             lit = lambda.size() == 1 ? lit : (lit + 1),
             mit = m.size() == 1 ? mit : (mit + 1),
             muit = mu.size() == 1 ? muit : (muit + 1)) {
            sum = 0;
            for (int j = n + 1; j <= N; j++) {
                mult = 1;
                for (int l = n; l <= j - 1; l++) {
                    mult *= (l < (N - *mit) ? (*mit * *muit) : ((N - l) * *muit)) / (l * *lit);
                }
                sum += mult / (j * *lit);
            }
            sum += 1 / (n * *lit);
            /*int j = n + 1;
            do {
                mult = 1;
                for (int l = n; l <= j - 1; l++) {
                    mult *= (l < (N - *mit) ? *mit * *muit : (N - l) * *muit) / (l * *lit) + 1 / (n * *lit);
                }
                sum += mult / (j * *lit);
                j++;
            } while(j <= N);*/
            fout << sum << " ";
        }
        fout << endl;
    }

    fout.close();
}

void calculateT(int N, vector<double> lambda, vector<double> m, vector<double> mu, vector<double> n)
{
    ofstream fout;
    if (mu.size() > 1)
        fout.open("31.out", ios_base::out | ios_base::trunc);
    if (lambda.size() > 1)
        fout.open("32.out", ios_base::out | ios_base::trunc);
    if (m.size() > 1)
        fout.open("33.out", ios_base::out | ios_base::trunc);

    if (!fout.is_open()) {
        cout << "Cant open file" << endl;
        return;
    }
    vector<double>::iterator lit = lambda.begin();
    vector<double>::iterator mit = m.begin();
    vector<double>::iterator muit = mu.begin();
    double sum, mult;
    cout << "N = " << endl;
    for (vector<double>::iterator nit = n.begin(); nit != n.end(); nit++) {
        fout << *nit << " ";
        cout << *nit << " ";
        for (lit = lambda.begin(), mit = m.begin(), muit = mu.begin();
             ((lambda.size() == 1) || (lit != lambda.end())) &&
             ((m.size() == 1) || (mit != m.end())) &&
             ((mu.size() == 1) || (muit != mu.end()));
             lit = lambda.size() == 1 ? lit : (lit + 1),
             mit = m.size() == 1 ? mit : (mit + 1),
             muit = mu.size() == 1 ? muit : (muit + 1)) {
            sum = 0;
            for (int j = 1; j < *nit; j++) {
                mult = 1 / (j * *lit);
                for (int l = j; l < *nit; l++)
                    mult *= l * *lit / (l < (N - *mit) ? (*mit * *muit) : ((N - l) * *muit));
                sum += mult;
            }
            mult = 1 / (*mit * *muit);
            for (int l = 1; l < *nit; l++) {
                mult *= l * *lit / (l < (N - *mit) ? (*mit * *muit) : ((N - l) * *muit));
            }
            sum += mult;
            fout << sum << " ";
        }
        fout << endl;
    }

    fout.close();
}

int main() 
{
    /*vector<double> lambda;
    vector<int> m;
    vector<int> mu;
    lambda.push_back(10e-5);
    m.push_back(1);*/
    vector<double> n;
    calculateTheta(65536, {1E-5}, {1}, {1, 10, 100, 1000});
    calculateTheta(65536, {1E-5, 1E-6, 1E-7, 1E-8, 1E-9}, {1}, {1});
    calculateTheta(65536, {1E-5}, {1, 2, 3, 4}, {1});
    for (int i = 900; i < 1000; i += 10)
        n.push_back(i);
    calculateT(1000, {1E-3}, {1}, {1, 2, 4, 6}, n);
    n.clear();
    for (int i = 8092; i < 8192; i += 10)
        n.push_back(i);
    calculateT(8192, {1E-5, 1E-6, 1E-7, 1E-8, 1E-9}, {1}, {1}, n);
    calculateT(8192, {1E-5}, {1, 2, 3, 4}, {1}, n);
    return 0;
}
