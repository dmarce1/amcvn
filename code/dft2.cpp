/*
 * main.cpp
 *
 *  Created on: May 13, 2016
 *      Author: dmarce1
 */

#include <stdio.h>
#include <math.h>
#include <vector>
#include <stdlib.h>
#include <fenv.h>

#define BUFSZ (1024*1024)

#define OMEGA_COL (14*(2-1))
#define DATCOLX (14*(3-1))
#define DATCOLY (14*(3-1))

int main(int, char* argv[]) {
	feenableexcept (FE_DIVBYZERO);
	feenableexcept (FE_INVALID);
	feenableexcept (FE_OVERFLOW);
	//const int col1 = 14 * (atoi(argv[2]) - 1);
	//const int col2 = 14 * (atoi(argv[2]));
	const char* filename = argv[1];
	double phase = 0.0, last_t = 0.0;
	std::vector<double> d;
	char buffer[BUFSZ];
	FILE* fp = fopen(filename, "rt");
	while (!feof(fp)) {
		fgets(buffer, BUFSZ - 1, fp);
		if( feof(fp)) {
			break;
		}
		double this_t = atof(buffer);
		const double omega = atof(buffer + OMEGA_COL);
		const double y = atof(buffer + DATCOLY);
		const double x = atof(buffer + DATCOLX);
		d.push_back(y);
		const double dt = this_t - last_t;
		phase += omega * dt;
		last_t = this_t;
	}

	int sz = d.size();
	double a, b;
	for( int n = 1; n != sz/2; ++n ) {
		a = b = 0.0;
		const double theta_0 = 2.0 * M_PI * double(n) / double(sz);
		for (int i = 0; i < sz; i++) {
			const double d0 = d[i];
			a += cos(-theta_0 * i) * d0;
			b += sin(-theta_0 * i) * d0;
		}
		a /= sz;
		b /= sz;
		printf("%e %e %e\n", theta_0, a, b);
	}
	return 0;
}
