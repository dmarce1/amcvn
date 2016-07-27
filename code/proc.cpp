
#include <array>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

#define NCOL 35
#define LEN 14
#define LINE_LEN (NCOL * LEN + 3)

#define PLEN 242.2
#define SAMPLE_SIZE 10.0

char buffer[LINE_LEN];

std::vector<std::array<double, NCOL>> data;
std::vector<std::array<double, NCOL>> avg;

int main(int argc, char* argv[]) {
	FILE* fp = fopen(argv[1], "rt");
	if( fp == NULL ) {
		printf( "File not found\n" );
		abort();
	}


	while( !feof(fp ) ) {
		fgets( buffer, LINE_LEN, fp );
		char* ptr = buffer;
		std::array<double, NCOL> line;
		for( int col = 0; col != NCOL; ++col ) {
			line[col] = atof( ptr );
			ptr += LEN;
		}
		data.push_back(line);
	}
	const std::size_t nrow = data.size();
	FILE* fp_avg = fopen( "avg.dat", "wt" );
	FILE* fp_dot = fopen( "dot.dat", "wt" );
	FILE* fp_log_dot = fopen( "dot_log.dat", "wt" );
	for( int row = 0; row != nrow; ++row ) {
		if( (data[row][0] - SAMPLE_SIZE*PLEN / 2.0 > data[0][0]) && (data[row][0] + SAMPLE_SIZE*PLEN / 2.0 <= data[nrow-1][0]) ) {
			std::array<double, NCOL> a;
			for( int col = 0; col != NCOL; ++col ) {
		//		data_dot[row][col] = 0.0;
				int cnt = 0;
				double val = 0.0;
				for( int row2 = 0; row2 < nrow; ++row2 ) {
					if( (data[row2][0] + SAMPLE_SIZE*PLEN / 2.0 > data[row][0]) && (data[row2][0] - SAMPLE_SIZE*PLEN / 2.0 <= data[row][0]) ) {
						val += data[row2][col];
						++cnt;
					}
				}
				if( col == 0 ) {
					val /= PLEN;
				}
				val /= cnt;
				a[col] = val;
				fprintf( fp_avg, "%13e ", val );
			}
			avg.push_back(a);
			fprintf( fp_avg, "\n" );
		}	
	}

	int npts = 0;
	for( int row = 0; row != avg.size(); ++row ) {
		if( (avg[row][0] - SAMPLE_SIZE / 2.0 > avg[0][0]) && (avg[row][0] + SAMPLE_SIZE / 2.0 <= avg[avg.size()-1][0]) ) {
			std::array<double, NCOL> a;
			fprintf( fp_dot, "%13e ", avg[row][0] );
			fprintf( fp_log_dot, "%13e ", avg[row][0] );
			for( int col = 1; col != NCOL; ++col ) {
				int cnt = 0;
				double val1, val2, t1, t2;
				npts = 0;
				for( int row2 = 0; row2 != avg.size(); ++row2 ) {
					if( (avg[row2][0] + SAMPLE_SIZE / 2.0 > avg[row][0]) && (avg[row2][0] - SAMPLE_SIZE / 2.0 <= avg[row][0]) ) {
						if( npts == 0 ) {
							val1 = avg[row2][col];
							t1 = avg[row2][0];
						} else {
							val2 = avg[row2][col];
							t2 = avg[row2][0];
						}
						++npts;
					}
				}
				if( npts > 1 ) {
					fprintf( fp_dot, "%13e ", (val2-val1)/(t2-t1) );
					fprintf( fp_log_dot, "%13e ", (val2-val1)/(t2-t1)/(val1+val2)/2.0 );
				}
			}
			fprintf( fp_dot, "\n" );
			fprintf( fp_log_dot, "\n" );
		}	
	}

	fclose( fp_avg );
	fclose( fp_log_dot );
	fclose( fp_dot );
	fclose(fp);
}



