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

int main(int argc, char* argv[]) {
	feenableexcept (FE_DIVBYZERO);
	feenableexcept (FE_INVALID);
	feenableexcept (FE_OVERFLOW);
	int col1, col2;
	if( argc >= 3 ) {
		col1 = 14 * (atoi(argv[2])-1);
	}
	if( argc == 4 ) {
		col2 = 14 * (atoi(argv[3])-1);
	}
	const char* filename = argv[1];
	double phase = 0.0, last_t =-1.0;
	std::vector<double> d;
	char buffer[BUFSZ];
	FILE* fp = fopen(filename, "rt");
	double tot = 0.0;
	while (!feof(fp)) {
		fgets(buffer, BUFSZ - 1, fp);
		if( feof(fp)) {
			break;
		}
		double this_t = atof(buffer);
		const double omega = atof(buffer + OMEGA_COL);
		if( last_t > 0.0 ) {
			const double dt = this_t - last_t;
			phase += omega * dt;
		}
		last_t = this_t;
		double x = atof(buffer + col1);
		double dat;
		if( argc == 4 ) {
			const double y = atof(buffer + col2);
			dat = (x * cos(phase) - y*sin(phase)) / sqrt(x*x+y*y);
		} else {
			dat = x;
		}
		d.push_back(dat);
		tot += dat * dat;
//		printf( "%e\n", phase / 2.0 / 3.14159 );
	}
//	abort();
	tot = sqrt(tot);
	int sz = d.size();
	double a, b;
	for( int n = 0; n != sz/2; ++n ) {
		a = b = 0.0;
		const double theta_0 = 2.0 * M_PI * double(n) / double(sz);
		for (int i = 0; i < sz; i++) {
			const double d0 = d[i];
			a += cos(-theta_0 * i) * d0;
			b += sin(-theta_0 * i) * d0;
		}
		a /= sz;
		b /= sz;
		a /= tot;
		b /= tot;
		printf("%e %e %e\n", 2.0 * M_PI * n / phase, a, b);
	}
	return 0;
}
