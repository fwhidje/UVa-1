#include <iostream>
#include <algorithm>
using namespace::std;

/*Past 3n+1 toe op 1 integer. Returnt lengte van langste cycle.*/
int cycle_length(int i) {
	int ctr = 1;
	while (i != 1) {
		(i & 1) ? (i = 3 * i + 1) : (i /= 2);
		++ctr;
	}
	return ctr;
}

/*Past 3n+1 toe op alle getallen in [i,j]. Returnt lengte van langste cycle.*/
int cycle_through(int i, int j) {
	int ret = 0;
	while (i <= j) 
		ret = max(ret, cycle_length(i++));
	return ret;
}
