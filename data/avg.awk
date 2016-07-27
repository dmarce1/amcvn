awk 'BEGIN \
	{size=30}  \
	{ \
		mod=NR%size; \
		if(NR<=size) { \
			count++ \
		} else { \
			sum_m-=array_m[mod]; \
			sum_a-=array_a[mod]; \
			sum_j1-=array_j[mod]; \
			sum_j2-=array_j[mod]; \
			sum_j-=array_j[mod]; \
		}; \
		sum_m+=$7; \
		sum_a+=$9; \
		sum_j+=$12; \
		sum_j1+=$10; \
		sum_j2+=$12; \
		array_m[mod]=$7; \
		array_a[mod]=$9; \
		array_j[mod]=$12; \
		array_j1[mod]=$12; \
		array_j2[mod]=$12; \
		printf( "%0.12e %0.12e %0.12e %0.12e\n",  $1, sum_m/count, sum_a/count, sum_j/count); \
	}'  \
silo.dat
