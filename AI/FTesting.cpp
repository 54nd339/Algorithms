// use hill climb search and simulated annealing to find the global minima of following functions in their search domain 
// avoiding local minima and plateaus with the help of random restarts and random walk
// 1. Rastrigin function (Search domain: [-5.12, 5.12])
// 2. Ackley function (Search domain: [-5, 5])
// 3. Sphere function (Search domain: [-5.12, 5.12])

#include <iostream>
#include <cmath>
#include <time.h>

using namespace std;
#define PI 3.1416

// Rastrigin function
double Rastrigin(double x, double y) {
    return 20 + x*x - 10*cos(2*PI*x) + y*y - 10*cos(2*PI*y);
}

// Ackley function
double Ackley(double x, double y) {
    return -20*exp(-0.2*sqrt(0.5*(x*x + y*y))) - exp(0.5*(cos(2*PI*x) + cos(2*PI*y))) + exp(1) + 20;
}

// Sphere function
double Sphere(double x, double y) {
    return x*x + y*y;
}

// Hill climb search
double HillClimbSearch(double (*f)(double, double), double x, double y, double step, double min, double max) {
    double fx = f(x, y);
    int count = 0;
    int restarts = 0;
    while (true) {
        count++;
        double newX = x + (rand() % 1000 / 1000.0 - 0.5) * step;    // random walk
        double newY = y + (rand() % 1000 / 1000.0 - 0.5) * step;
        if (newX < min || newX > max || newY < min || newY > max) { // out of search domain
            continue;
        }

        double newfx = f(newX, newY);   // evaluate new point
        if (newfx < fx) {               // if new point is better, update
            fx = newfx;
            x = newX;
            y = newY;
            restarts = 0;
        }
        else {                          // if new point is worse, restart
            restarts++;
            if (restarts > 100) break;
        }
    }
    // cout << "Hill climb search: " << fx << " at (" << x << ", " << y << ") in " << count << " iterations" << endl;
    return fx;
}

// Simulated annealing
double SimulatedAnnealing(double (*f)(double, double), double x, double y, double step, double min, double max) {
    double fx = f(x, y);
    int count = 0;
    int restarts = 0;
    double T = 1000;
    double alpha = 0.99;
    while (T > 0.0001) {
        count++;
        double newX = x + (rand() % 1000 / 1000.0 - 0.5) * step;
        double newY = y + (rand() % 1000 / 1000.0 - 0.5) * step;
        if (newX < min || newX > max || newY < min || newY > max) {
            continue;
        }

        double newfx = f(newX, newY);
        if (newfx < fx) {
            fx = newfx;
            x = newX;
            y = newY;
            restarts = 0;
        }
        else {
            double p = exp((fx - newfx) / T);   // probability of accepting worse point
            if (rand() % 1000 / 1000.0 < p) {   // accept worse point with probability p
                fx = newfx;
                x = newX;
                y = newY;
                restarts = 0;
            }
            else {                              // reject worse point
                restarts++;
                if (restarts > 100) break;
            }
        }
        T *= alpha;
    }
    // cout << "Simulated annealing: " << fx << " at (" << x << ", " << y << ") in " << count << " iterations" << endl;
    return fx;
}

int main() {
    srand(time(NULL));
    double x, y, z; int count;

    // Rastrigin function
    cout << "Rastrigin function" << endl;
    x = rand() % 1000 / 1000.0 * 10.24 - 5.12;
    y = rand() % 1000 / 1000.0 * 10.24 - 5.12;
    cout << "Initial point (HCS): (" << x << ", " << y << ")" << endl;
    z = HillClimbSearch(Rastrigin, x, y, 0.1, -5.12, 5.12);
    count = 0;
    while (z > 0.0001) {
        // cout << "Restarting from a random point..." << endl;
        x = rand() % 1000 / 1000.0 * 10.24 - 5.12;
        y = rand() % 1000 / 1000.0 * 10.24 - 5.12;
        z = HillClimbSearch(Rastrigin, x, y, 0.1, -5.12, 5.12);
        count++;
    }
    cout << "Found global minima: " << z << " at (" << x << ", " << y << ")" << " with " << count << " restarts" << endl;
    cout << endl;

    x = rand() % 1000 / 1000.0 * 10.24 - 5.12;
    y = rand() % 1000 / 1000.0 * 10.24 - 5.12;
    cout << "Initial point (SA): (" << x << ", " << y << ")" << endl;
    z = SimulatedAnnealing(Rastrigin, x, y, 0.1, -5.12, 5.12);
    count = 0;
    while (z > 0.0001) {
        // cout << "Restarting from a random point..." << endl;
        x = rand() % 1000 / 1000.0 * 10.24 - 5.12;
        y = rand() % 1000 / 1000.0 * 10.24 - 5.12;
        z = SimulatedAnnealing(Rastrigin, x, y, 0.1, -5.12, 5.12);
        count++;
    }
    cout << "Found global minima: " << z << " at (" << x << ", " << y << ")" << " with " << count << " restarts" << endl;
    cout << endl;

    // Ackley function
    cout << "Ackley function" << endl;
    x = rand() % 1000 / 1000.0 * 10 - 5;
    y = rand() % 1000 / 1000.0 * 10 - 5;
    cout << "Initial point (HCS): (" << x << ", " << y << ")" << endl;
    z = HillClimbSearch(Ackley, x, y, 0.1, -5, 5);
    count = 0;
    while (z > 0.0001) {
        // cout << "Restarting from a random point..." << endl;
        x = rand() % 1000 / 1000.0 * 10 - 5;
        y = rand() % 1000 / 1000.0 * 10 - 5;
        z = HillClimbSearch(Ackley, x, y, 0.1, -5, 5);
        count++;
    }
    cout << "Found global minima: " << z << " at (" << x << ", " << y << ")" << " with " << count << " restarts" << endl;
    cout << endl;

    x = rand() % 1000 / 1000.0 * 10 - 5;
    y = rand() % 1000 / 1000.0 * 10 - 5;
    cout << "Initial point (SA): (" << x << ", " << y << ")" << endl;
    z = SimulatedAnnealing(Ackley, x, y, 0.1, -5, 5);
    count = 0;
    while (z > 0.0001) {
        // cout << "Restarting from a random point..." << endl;
        x = rand() % 1000 / 1000.0 * 10 - 5;
        y = rand() % 1000 / 1000.0 * 10 - 5;
        z = SimulatedAnnealing(Ackley, x, y, 0.1, -5, 5);
        count++;
    }
    cout << "Found global minima: " << z << " at (" << x << ", " << y << ")" << " with " << count << " restarts" << endl;
    cout << endl;

    // Sphere function
    cout << "Sphere function" << endl;
    x = rand() % 1000 / 1000.0 * 10 - 5;
    y = rand() % 1000 / 1000.0 * 10 - 5;
    cout << "Initial point (HCS): (" << x << ", " << y << ")" << endl;
    z = HillClimbSearch(Sphere, x, y, 0.1, -5, 5);
    count = 0;
    while (z > 0.0001) {
        // cout << "Restarting from a random point..." << endl;
        x = rand() % 1000 / 1000.0 * 10 - 5;
        y = rand() % 1000 / 1000.0 * 10 - 5;
        z = HillClimbSearch(Sphere, x, y, 0.1, -5, 5);
        count++;
    }
    cout << "Found global minima: " << z << " at (" << x << ", " << y << ")" << " with " << count << " restarts" << endl;
    cout << endl;

    x = rand() % 1000 / 1000.0 * 10 - 5;
    y = rand() % 1000 / 1000.0 * 10 - 5;
    cout << "Initial point (SA): (" << x << ", " << y << ")" << endl;
    z = SimulatedAnnealing(Sphere, x, y, 0.1, -5, 5);
    count = 0;
    while (z > 0.0001) {
        // cout << "Restarting from a random point..." << endl;
        x = rand() % 1000 / 1000.0 * 10 - 5;
        y = rand() % 1000 / 1000.0 * 10 - 5;
        z = SimulatedAnnealing(Sphere, x, y, 0.1, -5, 5);
        count++;
    }
    cout << "Found global minima: " << z << " at (" << x << ", " << y << ")" << " with " << count << " restarts" << endl;
    cout << endl;

    return 0;
}