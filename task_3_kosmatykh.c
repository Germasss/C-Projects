#include<stdio.h>
#include<math.h>
#define n 7

double Sum(double x, double sum, double *last, double a, double b)
{
	double r = (x * x) / (a * b);
	*last *= r;
	sum += *last;
	return sum;
}

int main()
{
	//sh(2x)

	double arr[n];
	double h = 0.05;
	double x = 1.5;
	x *= 2;
	h *= 2;

	for (int i = 0; i < n; i++)
	{
		arr[i] = 0;
	}

	for (int i = 0; i < n; i++)
	{
		double sum = x;
		double last = x;
		double prelast = 0;
		double a = 0, b = 1;
		double difference = 0;

		for (int j = 2; ; j++)
		{
			prelast = last;
			a += 2;
			b += 2;
			sum = Sum(x, sum, &last, a, b);
			difference = last - prelast;
			if (difference == 0)
				break;
		}
		x += h;
		arr[i] = sum;
	}
	
	x = 3;

	for (int i = 0; i < 3; i++)
	{
		printf("%e \n", arr[i]);
		printf("%e \n", arr[i] - sinh(x));
		printf("\n");
		x += h;
	}

	for (int i = n-3; i < n; i++)
	{
		printf("%e \n", arr[i]);
		printf("%e \n", arr[i] - sinh(x));
		printf("\n");
		x += h;
	}
}
