/*
 * animaly_detection_util.cpp
 *
 * Author: Miriam Zuckerbrot 315971424
 */

#include <math.h>
#include <cmath>  
#include "anomaly_detection_util.h"

float avg(float* x, int size){ 
	float mu = 0;
	for (int i = 0; i<size; i++ ){
		mu = mu + *(x+i);
	}
	mu = mu / size;
	return mu;
}

// returns the variance of X and Y
float var(float* x, int size){ 
	float mu = avg(x, size);
	float var = 0;
	for (int j = 0; j < size; j++){
		var = var + pow((*(x+j) - mu ), 2);
	}
	var = var / size;
	return var;
}

// returns the covariance of X and Y
float cov(float* x, float* y, int size){
	float mu_x = avg(x, size);
	float mu_y = avg(y, size);
	float cov = 0;
	for (int k = 0; k < size; k++){
		cov = cov + (*(x+k) - mu_x) * (*(y+k) - mu_y);
	}
	cov = cov / size;
	return cov;
}


// returns the Pearson correlation coefficient of X and Y
float pearson(float* x, float* y, int size){
	float sd_x = sqrt(var(x, size));
	float sd_y = sqrt(var(y, size));
	float pears = cov(x, y, size) / (sd_x * sd_y);
	return pears;
}

// performs a linear regression and returns the line equation
Line linear_reg(Point** points, int size){
	float x_p[size] = {};
	float y_p[size] = {};
	for (int i = 0; i < size; i++){
		x_p[i] = points[i] -> x;
		y_p[i] = points[i] -> y;
	}
	float a  = cov(x_p, y_p, size) / var(x_p, size); 
	float b = avg(y_p, size) - a * avg(x_p, size); 
	return Line(a,b);
}

// returns the deviation between point p and the line equation of the points
float dev(Point p,Point** points, int size){
	Line l = linear_reg(points, size);
	float fx = l.f(p.x);
	float dif = std::abs(fx - p.y);
	return dif;
}

// returns the deviation between point p and the line
float dev(Point p,Line l){
	float fx = l.f(p.x);
	float dif = std::abs(fx - p.y);
	return dif;
} 




