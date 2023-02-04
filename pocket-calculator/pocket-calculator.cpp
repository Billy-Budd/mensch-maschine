/* pocket-calculator.cpp
 * JML190001 - John Lawler
 * CS4375.004 Project One
 * 01/30/23
 *
 * Program takes in information from Boston.csv and does
 * calculations to find: sum, mean, median, range, covariance,
 * and correlation.
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <array>
using namespace std;

// by convention, constants are global variables
const int MAX_LEN = 1000;

// function prototypes
double* printStats(vector<double>);
void printMinMax(vector<double>);
double getSum(vector<double>);
double getMean(vector<double>, double);
double getMedian(vector<double>);
double getRange(vector<double>);
double getCovariance(vector<double>, vector<double>, double, double, int);
double getCorrelation(double, double, double);
double getStandardDeviation(vector<double>, double, int);

int main(int argc, char** argv) {

	// elements to create vectors from Boston.csv
	ifstream inFS;
	string line, rm_in, medv_in;
	vector<double> rm(MAX_LEN), medv(MAX_LEN);

	// attempt to open csv, return error 1 if failure
	cout << "Opening file Boston.csv." << endl;
	inFS.open("Boston.csv");
	if (!inFS.is_open()) {
		cout << "Could not open file Boston.csv." << endl;
		cout << "Press enter to end program...";
		cin.get();
		return 1;
	}

	// print headers
	cout << "Reading line 1" << endl;
	getline(inFS, line);
	cout << "heading: " << line << endl;

	// retrieve observations
	int numObservations = 0;
	while (inFS.good()) {
		getline(inFS, rm_in, ',');
		getline(inFS, medv_in, '\n');

		rm.at(numObservations) = stof(rm_in);
		medv.at(numObservations) = stof(medv_in);

		numObservations++;
	}

	// resize vectors
	rm.resize(numObservations);
	medv.resize(numObservations);

	// output size of the vector
	cout << "new length " << rm.size() << endl;

	// close file when done
	cout << "Closing file Boston.csv." << endl;
	inFS.close();

	// output number of records
	cout << "Number of records: " << numObservations << endl;

	// get stats for rm and print
	cout << "\nStats for rm" << endl;
	double* rmStats = printStats(rm);

	// get stats for medv and print
	cout << "\nStats for medv" << endl;
	double* medvStats = printStats(medv);

	// get covariance and print
	double covariance = getCovariance(rm, medv, rmStats[1], medvStats[1], numObservations);
	cout << "\nCovariance: " << covariance << endl;

	// get standard deviations for correlation calculation
	double rmStdDev = getStandardDeviation(rm, rmStats[1], numObservations);
	double medvStdDev = getStandardDeviation(medv, medvStats[1], numObservations);

	// get correlation and print
	double correlation = getCorrelation(rmStdDev, medvStdDev, covariance);
	cout << "\nCorrelation: " << correlation << endl;

	// program stop for executable
	cout << "Press enter to end program...";
	cin.get();

	// end program
	cout << "\nProgram terminated.";
	return 0;
}

/* double* printStats(vector<double> stats)
 * args:
 * vector to perform operations on
 *
 * return: double statsArr[4]
 * double vector returns stats in order: sum, mean, median, range
 *
 * function does operations on a vector and provides data
 */
double* printStats(vector<double> stats) {

	// doubles for data
	double* statsArr = new double[4];
	statsArr[0] = getSum(stats);
	statsArr[1] = getMean(stats, statsArr[0]);
	statsArr[2] = getMedian(stats);
	statsArr[3] = getRange(stats);

	// print data
	cout << "\tSum: " << statsArr[0] << endl
		<< "\tMean: " << statsArr[1] << endl
		<< "\tMedian: " << statsArr[2] << endl
		<< "\tRange: " << statsArr[3] << " | ";
	printMinMax(stats);

	return statsArr;
}

/* double printMinMax(vector<double> stats)
 * args:
 * vector to perform operations on
 *
 * return: nothing
 *
 * function prints min and max for range
 */
void printMinMax(vector<double> stats) {

	// sort vector
	vector<double> sortedVector(stats);
	sort(sortedVector.begin(), sortedVector.end());
	
	// print min and max
	cout << sortedVector[0] << " "
		<< sortedVector[sortedVector.size() - 1]
		<< endl;
}

/* double getSum(vector<double> stats)
 * args:
 * vector to perform operations on
 *
 * return: double sum
 * sum of all elements in vector
 *
 * function returns the sum of all elements in a vector
 */
double getSum(vector<double> stats) {

	// get the sum of all elements in a vector
	double sum = 0.0;
	for (int i = 0; i < stats.size(); i++)
		sum += stats[i];

	// return sum
	return sum;
}

/* double getMean(vector<double> stats, double sum)
 * args:
 * vector to perform operations on
 * sum of all elements in a vector from getSum function
 *
 * return: double mean
 * mean of elements in vector
 *
 * function returns the mean of the elements in a vector
 */
double getMean(vector<double> stats, double sum) {
	return sum / stats.size(); // return mean
}

/* double getMedian(vector<double> stats)
 * args:
 * vector to perform operations on
 *
 * return: double median
 * median of elements a vector
 *
 * function returns the median of a vector
 */
double getMedian(vector<double> stats) {

	// sort vector from smallest to largest using algorithm library
	vector<double> sortedVector(stats);
	sort(sortedVector.begin(), sortedVector.end());

	// find median if vector size is even
	if (sortedVector.size() % 2 == 0) {
		return((sortedVector[sortedVector.size() / 2 - 1]
			+ sortedVector[sortedVector.size() / 2]) / 2);
	}

	// find median if vector is odd
	else
		return sortedVector[sortedVector.size() / 2];

}

/* double getRange(vector<double> stats)
 * args:
 * vector to perform operations on
 *
 * return: double range
 * double of the largest element - the smallest element
 *
 * function sorts the vector and calculates the range
 * by subtracting the smallest element from the largest element
 */
double getRange(vector<double> stats) {

	// sort vector
	vector<double> sortedVector(stats);
	sort(sortedVector.begin(), sortedVector.end());

	// return range
	return sortedVector[sortedVector.size() - 1] - sortedVector[0];
}

/* double getCovariance(vector<double> rm, vector<double> medv,
 *		double meanRm, double meanMedv, int size)
 * args:
 * rm vector to calculate covariance
 * medv vector to calculate covariance
 * mean of rm vector
 * mean of medv vector
 * int of vector size
 *
 * return: covariance calculation
 *
 * function calculates covariance, formula is included in
 * /metropolis/portfolio-one-data-exploration/formulas.png
 */
double getCovariance(vector<double> rm, vector<double> medv,
	double meanRm, double meanMedv, int size) {

	// formula location included in function header
	double covariance = 0.0;
	for (int i = 0; i < size; i++)
		covariance += ((rm[i] - meanRm) * (medv[i] - meanMedv));

	return (covariance / (size - 1));
}

/* double getCorrelation(double rmStdDev, double medvStdDev, double covariance)
 * args:
 * double of the standard deviation of vector rm
 * double of the standard deviation of vector medv
 * double of calculated covariance
 *
 * return: correlation calculation
 *
 * function calculates correlation, formula is included in
 * /metropolis/portfolio-one-data-exploration/formulas.png
 */
double getCorrelation(double rmStdDev, double medvStdDev, double covariance) {

	double denominator = rmStdDev * medvStdDev;

	return (covariance / denominator);
}

/* double getStandardDeviation(vector<double> stats, double mean, int, size)
 * args:
 * vector to calculate standard deviation of
 * double of the mean
 * int of the size of the vector
 *
 * return: the standard deviation of the vector
 */
double getStandardDeviation(vector<double> stats,
	double mean, int size) {

	// double for calculation
	double sum = 0.0;

	// get the sum of each element in the vector subtracted by the mean
	for (int i = 0; i < size; i++)
		sum += pow(stats[i] - mean, 2);

	// square root the calcuation and return
	return sqrt(sum / (size - 1));
}