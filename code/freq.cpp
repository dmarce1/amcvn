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

#define FILENAME "./id.dat"
#define BUFSZ (1024*1024)
#define OMEGA_COL (14*(2-1))
#define DATCOL1 (14*(3-1))
#define DATCOL2 (14*(3-1))

int main(int, char* argv[]) {
	   feenableexcept (FE_DIVBYZERO);
	    feenableexcept (FE_INVALID);
	    feenableexcept (FE_OVERFLOW);

	std::vector<double> t, d;
	char buffer[BUFSZ];
	double last_t = 0.0;
	double this_t;
	double phase = 0.0;
	FILE* fp = fopen(FILENAME, "rt");
	while (!feof(fp)) {
		fgets(buffer, BUFSZ - 1, fp);
		if( feof(fp)) {
			break;
		}
		double this_t = atof(buffer);
		const double omega = atof(buffer + OMEGA_COL);
		const double num = atof(buffer + DATCOL2);
//		const double den = atof(buffer + DATCOL1);
		const double den = 1.0;
		const double dat = num / den;
		d.push_back(dat);
		t.push_back(phase);
	//	printf( "%e %e %e\n", phase, omega, dat);
		const double dt = this_t - last_t;
		phase += omega * dt;
		last_t = this_t;
	}
//	abort();
	int sz = t.size();
	double a, b;
	const double tmax = t[sz - 1];
	const double df = 1.0e-3;
	for( double f = 0.1; f < 15.0; f += df ) {
		a = b = 0.0;
		for (int i = 1; i < sz - 1; i++) {
			const double t0 = t[i];
			const double d0 = d[i];
			const double theta_0 = t0 * f;
			a += cos(theta_0) * d0;
			b += sin(theta_0) * d0;
		}
		printf("%e %e %e\n", f, a, b);
	}
	return 0;
}
