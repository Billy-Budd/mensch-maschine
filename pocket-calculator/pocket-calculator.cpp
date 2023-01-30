#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

// by convention, constants are global variables
const int MAX_LEN = 1000;

// function prototypes
double* printStats(vector<double>);
double getSum(vector<double>);
double getMean(vector<double>, double);
double getMedian(vector<double>);
double getRange(vector<double>);
double getCovariance(vector<double>, vector<double>, double, double, int);
double getNormalSum(vector<double>, double, int);

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
	double *rmStats = printStats(rm);

	// get stats for medv and print
	cout << "\nStats for medv" << endl;
	double* medvStats = printStats(medv);

	double covariance = getCovariance(rm, medv, rmStats[1], medvStats[1], numObservations);
	cout << "\nCovariance: " << covariance << endl;


	// end program
	cout << "\nProgram terminated.";
	return 0;
}

/* double* printStats(vector<double> stats)
 * args: vector<double> stats
 * vector to perform operations on
 * 
 * return: double statsArr[4]
 * double vector returns stats in order: sum, mean, median, range
 * 
 * function does operations on a vector and provides data
 */
double* printStats(vector<double> stats) {
	
	// doubles for data
	double vectorSum = getSum(stats);
	double vectorMean = getMean(stats, vectorSum);
	double vectorMedian = getMedian(stats);
	double vectorRange = getRange(stats);

	// print data
	cout << "\tSum: " << vectorSum << endl
		<< "\tMean: " << vectorMean << endl
		<< "\tMedian: " << vectorMedian << endl
		<< "\tRange: " << vectorRange << endl;

	// array for the data to return
	double statsArr[4] = { vectorSum, vectorMean, 
		vectorMedian, vectorRange };
	return statsArr;
}

/* double getSum(vector<double> stats)
 * args: vector<double> stats
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
 * args: vector<double> stats, double sum
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
 * args: vector<double> stats
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
 * args: vector<double> stats
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

double getCovariance(vector<double> rm, vector<double> medv,
	double meanRm, double meanMedv, int size) {
	
	double normalSumRm = getNormalSum(rm, meanRm, size);
	double normalSumMedv = getNormalSum(medv, meanMedv, size);

	return ((normalSumRm * normalSumMedv) / (size - 1));
}

double getNormalSum(vector<double> stats, double mean, int size) {

	double normalSum = 0.0;
	for (int i = 0; i < size; i++) {
		normalSum += (stats[i] - mean);
	}

	return normalSum;

}