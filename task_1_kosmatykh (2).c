#include <stdio.h>
#include <math.h>
#include <omp.h>


int main()
{
	// f(x) = x^2

	double a = 2, b = 3, h, S = 0;
	int n = 10000000;

		// central rectangles

		//The essence of the rectangle method is expressed in the fact that the approximate value is considered an integral sum.
		//If the function y=f(x) has continuity on the segment [a;b] and it is necessary to calculate the value of the integral	
		//The method gets this name because of the nature of the choice of points, where the step of splitting the segment is taken as h
		//The absolute error of the formula of the rectangles of the segment [a;b] is equal to the sum of the errors of each elementary interval.

		h = (b - a) / n;
		
		double start = omp_get_wtime();
		#pragma omp parallel for reduction(+:S)
		for (int i = 0; i < n; i++)
		{
			S += (a + h * (i + 0.5)) * (a + h * (i + 0.5));
		}
		double end = omp_get_wtime();
		S *= h;
		printf("S= %lf - central rectangles \n", S);
		printf("work time %lf \n", end - start);

		
		// trapetions

		//The integration segment is divided into several intermediate segments, and the graph of the integrand is approximated by a polyline
		//Thus, our area is approximated by the sum of the trapezoid areas. Hence the name of the method. 
		//It is easy to see that the trapezoid method gives a much better approximation than the rectangle method
		//The more smaller intermediate segments we consider, the higher the accuracy will be.
		
		a = 2;
		S = 0;
		
		h = (b - a) / n;
		start = omp_get_wtime();
		#pragma omp parallel for reduction(+:S)
		for (int i = 0; i < n; i++)
		{
			S += ((a + h * i) * (a + h * i)) + ((a + h * (i + 1)) * (a + h * (i + 1))) ;
		}
		end = omp_get_wtime();
		S *= h / 2;
		printf("S= %lf - trapetions \n", S);
		printf("work time %lf \n", end - start);


		// Simpson

		//This is a more perfect way – the graph of the integrand function is approximated not by a polyline, but by small parabolas.
		//The Simpson method assumes an approximate calculation of certain integrals. 
		//Most often there are two types of problems for which this method is applicable:

		//for approximate calculation of a certain integral;
		//when finding an approximate value with an accuracy of a	
		//the length of each of the small segments or the step is h
		
		a = 2;
		S = 0;
		h = ((b - a) / (2 * n));
		S = (2 * (a * a) + 1) + (2 * (b * b) + 1);
		double check;

		start = omp_get_wtime();
		#pragma omp parallel for reduction(+:S)
		for (int i = 0; i < 2 * n - 1; i++)
		{
			S += (2+2*(i%2)) * ((a + i * h) * (a + i * h));
		}
		end = omp_get_wtime();
		S *= h / 3;
		printf("S= %lf - Simpson \n", S);
		printf("work time %lf \n", end - start);

	
}