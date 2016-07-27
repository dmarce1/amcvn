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

#define FILENAME "./silo.dat"
#define BUFSZ (1024*1024)
#define DATCOL (14*(23-1))

int main() {
	   feenableexcept (FE_DIVBYZERO);
	    feenableexcept (FE_INVALID);
	    feenableexcept (FE_OVERFLOW);

	std::vector<double> t, d;
	char buffer[BUFSZ];
	FILE* fp = fopen(FILENAME, "rt");
	while (!feof(fp)) {
		fgets(buffer, BUFSZ - 1, fp);
		if( feof(fp)) {
			break;
		}
		t.push_back(atof(buffer));
		d.push_back(atof(buffer + DATCOL));
	//	printf( "%e %e\n", t[t.size()-1], d[d.size()-1]);
	}
	//abort();
	int sz = t.size();
	std::vector<double> a(sz, 0.0), b(sz, 0.0);
	double tmax = t[sz - 1];
	for (int n = 1; n < sz/2; ++n) {
		for (int i = 1; i < sz - 1; i += 2) {
			double dt = (t[i+1]-t[i-1])/2.0;
			double dtr = (t[i + 1] - t[i]) / dt;
			double dtl = (t[i] - t[i - 1]) / dt;
			double tl = t[i - 1];
			double t0 = t[i];
			double tr = t[i + 1];
			double dl = d[i - 1];
			double d0 = d[i];
			double dr = d[i + 1];
			double theta_l = 2.0 * n * M_PI * tl / tmax;
			double theta_0 = 2.0 * n * M_PI * t0 / tmax;
			double theta_r = 2.0 * n * M_PI * tr / tmax;
			double co_l = 1.0 / (dtr * dtr + dtr * dtl) / 3.0;
			double co_r = 1.0 / (dtl * dtl + dtr * dtl) / 3.0;
			double co_0 = (3.0 * dtr * dtl - 1.0) / 3.0;
			a[n] += co_l * cos(theta_l) * dl * dt;
			a[n] += co_0 * cos(theta_0) * d0 * dt;
			a[n] += co_r * cos(theta_r) * dr * dt;
			b[n] += co_l * sin(theta_l) * dl * dt;
			b[n] += co_0 * sin(theta_0) * d0 * dt;
			b[n] += co_r * sin(theta_r) * dr * dt;
		}
		double orb = n * 242.2 / tmax;
//		if (orb >= 0.5 && orb <= 14.0) {
			printf("%e %e %e\n", (n * 242.2 / tmax), a[n], b[n]);
//		}
	}

	return 0;
}
