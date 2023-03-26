#include<stdio.h>

/*print Fahrenheit-Celsius table
	for fahr(0,20,...,300*/
main()
{
	float fahr, celsius;
	int lower, upper, step;

	lower=0;	/*lower limit*/
	upper=300;	/*upper limit*/
	step=20;	/*step size*/

	fahr=(float)lower;
	/* original: fahr=lower; */
	while (fahr <= upper) 
	{
		celsius=
			(float)((5.0/9.0)*(fahr-32.0));
			/* original: (5.0/9.0)*(fahr-32); */
		printf("%3.0f%6.1f\n",fahr, celsius);
		fahr=fahr+step;
	}
	step = step; /* for a breakpoint */
}
