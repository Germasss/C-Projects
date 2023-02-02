#include <stdio.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
	int rank,size;
	// f(x) = x^2
	double start,end;
	double S;
	double x = 0;
	double sum1 = 0, sum2 = 0, sum3 = 0;
	double s1 = 0,s2 = 0,s3 = 0;
	double a = 2, b = 3, h;
	int n = 10000000;

		// central rectangles

		//The essence of the rectangle method is expressed in the fact that the approximate value is considered an integral sum.
		//If the function y=f(x) has continuity on the segment [a;b] and it is necessary to calculate the value of the integral	
		//The method gets this name because of the nature of the choice of points, where the step of splitting the segment is taken as h
		//The absolute error of the formula of the rectangles of the segment [a;b] is equal to the sum of the errors of each elementary interval.

		h = (b - a) / n;
		
		MPI_Init(&argc,&argv);
		MPI_Comm_rank(MPI_COMM_WORLD,&rank);
		MPI_Comm_size(MPI_COMM_WORLD,&size);
		if (rank==0)
			start = MPI_Wtime();
		for (int i = rank; i < n; i+=size)
		{
			sum1 += (a + h * (i + 0.5)) * (a + h * (i + 0.5));
		}
		
		sum1 *= h;
		MPI_Reduce(&sum1,&s1,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
		
		// trapetions

		//The integration segment is divided into several intermediate segments, and the graph of the integrand is approximated by a polyline
		//Thus, our area is approximated by the sum of the trapezoid areas. Hence the name of the method. 
		//It is easy to see that the trapezoid method gives a much better approximation than the rectangle method
		//The more smaller intermediate segments we consider, the higher the accuracy will be.
		
		a = 2;		
		h = (b - a) / n;
		
		for (int i = rank; i < n; i+=size)
		{
			sum2 += ((a + h * i) * (a + h * i)) + ((a + h * (i + 1)) * (a + h * (i + 1))) ;
		}
		
		sum2 *= h / 2;
		MPI_Reduce(&sum2,&s2,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);


		// Simpson

		//This is a more perfect way – the graph of the integrand function is approximated not by a polyline, but by small parabolas.
		//The Simpson method assumes an approximate calculation of certain integrals. 
		//Most often there are two types of problems for which this method is applicable:

		//for approximate calculation of a certain integral;
		//when finding an approximate value with an accuracy of a	
		//the length of each of the small segments or the step is h
		
		a = 2;
		h = ((b - a) / (2 * n));
		sum3 = (2 * (a * a) + 1) + (2 * (b * b) + 1);
		double check;
		
		for (int i = rank; i < 2 * n - 1; i+=size)
		{
			
			sum3 += (2+2*(i%2)) * ((a + i * h) * (a + i * h));
		}
		
		sum3 *= h / 3;
		MPI_Reduce(&sum3,&s3,1,MPI_DOUBLE,MPI_SUM,0,MPI_COMM_WORLD);
		if (rank == 0)
		{
			printf("sum1= %lf - central rectangles \n", s1);
			printf("sum2= %lf - trapetions \n", s2);
			printf("sum3= %lf - Simpson \n", s3);
			end = MPI_Wtime();
			printf("time: %lf",end-start);
		}
		MPI_Finalize();
}