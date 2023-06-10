#include <iostream>
#include <iomanip>
#include <cmath>
#include <complex>
using namespace std;

unsigned M, N;

complex<double> h[320000];
complex<double> y[320000];
complex<double> temp[320000];

double hh[50000];
double yy[150000];
double x[100000];

double temp2;

typedef complex<double> Comp;

void fft(complex<double>* a, int n, int rev)
{
    if (n == 1)
        return;
    for (unsigned i = 0; i < n; i++)
        temp[i] = a[i];
    for (unsigned i = 0; i < n; i++)
    {
        if (i % 2 == 0)
            a[i / 2] = temp[i];
        else
            a[(i + n) / 2] = temp[i];
    }
    fft(a, n / 2, rev);
    fft(a + n / 2, n / 2, rev);
    complex<double> cur(1, 0), step(cos(2 * M_PI / n), sin(2 * M_PI / n) * rev);
    for (unsigned i = 0; i < n / 2; i++)
    {
        temp[i] = a[i] + cur * a[i + n / 2];
        temp[i + n / 2] = a[i] - cur * a[i + n / 2];
        cur *= step;
    }
    for (unsigned i = 0; i < n; i++)
        a[i] = temp[i];
}

int main()
{
    ios::sync_with_stdio(false);
    cin >> N >> M;
    if (N > 5000 && M > 1000)
    {
        for (unsigned i = 0; i < M + N - 1; i++)
            cin >> y[i];
        for (unsigned i = 0; i < M; i++)
            cin >> h[i];

        unsigned size = M + N - 1;
        unsigned pow = 1;
        while (size /= 2)
            pow++;
        size = 1 << pow;
        for (unsigned i = M; i < M + N - 1; i++)
            h[i] = 0;
        for (unsigned i = M + N - 1; i < size; i++)
        {
            h[i] = 0;
            y[i] = 0;
        }
        fft(h, size, 1);
        fft(y, size, 1);
        for (unsigned i = 0; i < size; i++)
        {
            y[i] /= h[i];
            y[i] /= size;
        }
        fft(y, size, -1);
        for (unsigned i = 0; i < N; i++)
            if (y[i].real() < 1e-8)
            {
                cout << N;
                return 0;
            }
        for (unsigned i = 0; i < N; i++)
            cout << fixed << setprecision(4) << y[i].real() << " ";
    }
    else
    {
        for (unsigned i = 0; i < M + N - 1; i++)
            cin >> yy[i];
        for (unsigned i = 0; i < M; i++)
            cin >> hh[i];
        for (unsigned i = 0; i < M; i++)
        {
            x[i] = yy[i];
            for (unsigned j = 0; j < i; j++)
                x[i] -= x[j] * hh[i - j];
            if (x[i] < 0)
            {
                cout << N;
                return 0;
            }
            x[i] /= hh[0];
            temp2 = (int)round(10000 * x[i]);
            x[i] = (double)temp2 / 10000;
        }
        for (unsigned i = M; i < N; i++)
        {
            x[i] = yy[i];
            for (unsigned j = 1; j < M; j++)
            {
                x[i] -= x[i - j] * hh[j];
            }
            temp2 = (int)round(10000 * x[i]);
            x[i] = (double)temp2 / 10000;
            if (x[i] < 0)
            {
                cout << N;
                return 0;
            }
            x[i] /= hh[0];
        }
        for (unsigned i = 0; i < N; i++)
            cout << fixed << setprecision(4) << x[i] << " ";
    }
}