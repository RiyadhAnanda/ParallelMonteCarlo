//Riyadh Ananda
//Assignment 4 Parallel Programming
//Monte Carlo Pi Calculation

#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NUM_THREADS 4
static long total_nr_points = 10000;
using namespace std;


void serial_montecarlo_pi() //Serial monte carlo implementation of pi
{
	
	int nr_points_in_circle = 10000; //maximum number of points within circle
	double x, y;    // coordinates
	int r;       // storage variable of number of number of points in circle
	double pi = 0.0;
	srand(time(0));
	for (int j = 0;j < total_nr_points;j++) 
	{
		r = 0;
		x = 0; y = 0;
		
		for (int i = 0;i < nr_points_in_circle;i++) 
		{
			x = double(rand()) / double(RAND_MAX);
			y = double(rand()) / double(RAND_MAX);

			if (y <= sqrt(1 - pow(x, 2))) r += 1;
		}         
		//cout << "" << 4 * double(r) / double(nr_points_in_circle) << endl;
		pi = 4* double(r) / double(nr_points_in_circle);
  }
	std::cout<<endl;
	std::cout << "Serial Monte Carlo Pi value = " << pi << std::endl;
}
void parallel_montecarlo_pi() //Serial monte carlo implementation of pi
{

	int nr_points_in_circle = 10000; //maximum number of points within circle
	double x, y;    // coordinates
	int r;       // storage variable of number of number of points in circle
	double pi = 0.0;
	omp_set_num_threads(NUM_THREADS);
	srand(time(0));

	#pragma omp parallel
	{
	#pragma omp for 
	for (int j = 0;j < total_nr_points;j++)
		{
			r = 0;
			x = 0; y = 0;

			for (int i = 0;i < nr_points_in_circle;i++)
			{
				x = double(rand()) / double(RAND_MAX);
				y = double(rand()) / double(RAND_MAX);

	#pragma omp critical
				if (y <= sqrt(1 - pow(x, 2))) r += 1;
			}
			//cout << "" << 4 * double(r) / double(nr_points_in_circle) << endl;
			pi = 4 * double(r) / double(nr_points_in_circle);
		}
	}
	std::cout << endl;
	std::cout << "Parallel Monte Carlo Pi value = " << pi << std::endl;
}
int main() {

  double start_time, end_time;
  start_time = omp_get_wtime();
  serial_montecarlo_pi();
  end_time = omp_get_wtime();
  std::cout<<"Serial Monte Carlo time = "<< end_time-start_time<<std::endl<<std::endl;
  
	start_time = omp_get_wtime();
	parallel_montecarlo_pi();
	end_time = omp_get_wtime();
	std::cout << "Parallel Monte Carlo time = " << end_time - start_time << std::endl << std::endl;
  return 0;
}