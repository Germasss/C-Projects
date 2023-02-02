#include <stdio.h>
#include <math.h>

int main()
{
	// f(x) = 2x^2 + 1

	double a, b, h, S = 0;
	int n;
	printf("a=");
	scanf_s("%lf", &a);
	printf("b=");
	scanf_s("%lf", &b);
	printf("n=");
	scanf_s("%d", &n);

	int z;
	printf("Select method: \n\t1. Central rectangles \n\t2. Trapetions \n\t3. Simpson's method\n");
	scanf_s("%d", &z);
	switch (z)
	{
	case 1:
		// central rectangles

		//The essence of the rectangle method is expressed in the fact that the approximate value is considered an integral sum.
		//If the function y=f(x) has continuity on the segment [a;b] and it is necessary to calculate the value of the integral	
		//The method gets this name because of the nature of the choice of points, where the step of splitting the segment is taken as h
		//The absolute error of the formula of the rectangles of the segment [a;b] is equal to the sum of the errors of each elementary interval.

		h = (b - a) / n;
		for (int i = 0; i < n; i++)
		{
			S += (2 * ((a + (h / 2)) * (a + (h / 2))) + 1);
			a += h;
		}
		S *= h;
		printf("S= %lf", S);
		break;

	case 2:
		// trapetions

		//The integration segment is divided into several intermediate segments, and the graph of the integrand is approximated by a polyline
		//Thus, our area is approximated by the sum of the trapezoid areas. Hence the name of the method. 
		//It is easy to see that the trapezoid method gives a much better approximation than the rectangle method
		//The more smaller intermediate segments we consider, the higher the accuracy will be.

		h = (b - a) / n;
		for (int i = 0; i < n; i++)
		{
			S += ((2 * ((a + h) * (a + h)) + 1) + (2 * (a * a) + 1));
			a += h;
		}
		S *= h / 2;
		printf("S= %lf", S);
		break;

	case 3:
		// Simpson

		//This is a more perfect way – the graph of the integrand function is approximated not by a polyline, but by small parabolas.
		//The Simpson method assumes an approximate calculation of certain integrals. 
		//Most often there are two types of problems for which this method is applicable:

		//for approximate calculation of a certain integral;
		//when finding an approximate value with an accuracy of a	
		//the length of each of the small segments or the step is h

		h = ((b - a) / (2 * n));
		S = (2 * (a * a) + 1) + (2 * (b * b) + 1);
		double check;

		for (int i = 0; i < 2 * n - 1; i++)
		{
			if (i % 2 == 0)
			{
				check = 2;
			}
			else
			{
				check = 4;
			}
			S += check * (2 * ((a + i * h) * (a + i * h)) + 1);
		}
		S *= h / 3;
		printf("S= %lf", S);
		break;
	}
}