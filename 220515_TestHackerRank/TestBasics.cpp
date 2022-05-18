#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <math.h>
#include "TestBasics.h"

using namespace std;
static int getgcd(int ain, int bin) {
	int a = std::max(ain, bin), b = std::min(ain, bin);
	int tmp;
	while (b > 0) {
		tmp = a; a = b; b = tmp % a;
	}
	return a;
}

static int getgcd(const vector<int>& nums) {
	int r = nums[0];
	for (int i = 1; i < nums.size(); ++i) {
		r = getgcd(r, nums[i]);
	}
	return r;
}

static int getlcm(int ain, int bin) {
	int gcd = getgcd(ain, bin);
	return ain * bin / gcd;
}

static int getlcm(const vector<int>& nums) {
	int r = nums[0];
	for (int i = 1; i < nums.size(); ++i) {
		r = getlcm(r, nums[i]);
	}
	return r;
}

int main() {
	vector<int> testnumbers = { 256, 12, 24, 48, 96, 128 };
	int num = getgcd(testnumbers);
	printf("gcd : %d", num);
	num = getlcm(testnumbers);
	printf("lcm : %d", num);
	return 0;
}
