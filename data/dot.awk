#! /usr/bin/awk -f
BEGIN {size=1}  
	{ 
		mod=NR%size; 
		if(NR<=size) { 
			count++;
		} else { 
			sum_m=$7-array_m[mod]; 
			sum_a=$9-array_a[mod]; 
			sum_j=$12-array_j[mod]; 
			sum_j1=$10-array_j[mod]; 
			sum_j2=$11-array_j[mod]; 
			sum_m/=0.5*($7+array_m[mod]); 
			sum_a/=0.5*($9+array_a[mod]); 
			sum_j/=0.5*($12+array_j[mod]); 
			sum_j1/=0.5*($12+array_j[mod]); 
			sum_j2/=0.5*($12+array_j[mod]); 
		}; 
		array_m[mod]=$7; 
		array_a[mod]=$9; 
		array_j[mod]=$12; 
		array_j1[mod]=$10; 
		array_j2[mod]=$11; 
		print $1, sum_m,sum_a,sum_j,sum_j1,sum_j2;
	}
