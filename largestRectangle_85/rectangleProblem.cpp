#include <iostream>
#include <vector>

#define MAX(A, B)	(((A) > (B)) ? (A) : (B))
#define MIN(A, B)	(((A) > (B)) ? (B) : (A))

using std::cin;
using std::cout;
using std::endl;
using std::vector;

// *Is not necessary for leetcode
// Used for simple tests
void scanInp(vector<vector<char>>& matr)
{
	size_t n, m;
	char ch;
	cin >> n >> m;	
	for(int i {0}; i < n; ++i) {
		matr.emplace_back();
		for(int j {0}; j < m; ++j) {
			cin >> ch;
		       	matr[i].push_back(ch);	
		}	
	}
}

// filling base for dynamic programming table
void setBaseX(vector<vector<char>>& matr, vector<vector<unsigned short>>& dp)
{
	unsigned short max;
	char plen = (matr[0][0] == '1') ? 1 : 0;
	for(size_t x {1}; x < matr.size(); ++x) {
		if(matr[x][0] == '1') {
			++plen;
			max = MAX(dp[x - 1][0], plen);
			dp[x][0] = max;
		} else {
			plen = 0;
			dp[x][0] = dp[x - 1][0];	
		}
	}
}

// filling base for dynamic programming table
void setBaseY(vector<vector<char>>& matr, vector<vector<unsigned short>>& dp)
{
	unsigned short max;
	char plen = (matr[0][0] == '1') ? 1 : 0;
	for(size_t y {1}; y < matr[0].size(); ++y) {
		if(matr[0][y] == '1') {
			++plen;
			max = MAX(dp[0][y - 1], plen);
			dp[0][y] = max;
		} else {
			dp[0][y] = dp[0][y - 1];	
			plen = 0;
		}
	}
}

// preprocessing
void fillInfo(vector<vector<char>>& matr, vector<vector<unsigned char>>& info)
{
	char count;
	for(size_t x {0}; x < matr.size(); ++x) {
		count = 0;
		for(size_t y {0}; y < matr[0].size(); ++y) {
			if(matr[x][y] == '1') ++count;	
			else count = 0;
			info[x][y] = count;
		}
	}	
}

// subfunction for dynamic programming
unsigned short subLargestRect(size_t x, size_t y,
		vector<vector<char>>& matr, vector<vector<unsigned char>>& info)
{
	unsigned char ry {info[x][y]};
	unsigned short res {0};
	for(int x_ {static_cast<int>(x)}; x_ >= 0; --x_) {
		ry = MIN(ry, info[x_][y]);
		res = MAX(res, (x - x_ + 1) * ry);
		if(ry == 0) break;
	}
	return res;
}

// main dynamic programming function
unsigned short largestRectangle(vector<vector<char>>& matr)
{
	char plen;
	unsigned short max;
	size_t n {matr.size()}, m {matr[0].size()};
	vector<vector<unsigned short>> dp {n, vector<unsigned short>(m, 0)};
	vector<vector<unsigned char>> info {n, vector<unsigned char>(m, 0)};

	fillInfo(matr, info);

	dp[0][0] = (matr[0][0] == '1') ? 1 : 0;
	setBaseX(matr, dp);
	setBaseY(matr, dp);

	for(size_t x {1}; x < n; ++x) {
		for(size_t y {1}; y < m; ++y) {
			max = MAX(dp[x - 1][y], dp[x][y - 1]);
			max = MAX(max, subLargestRect(x, y, matr, info));
			dp[x][y] = max;	
		}
	}

	return dp[n - 1][m - 1];
}

int main()
{
	vector<vector<char>> matr {};
	scanInp(matr);
	cout << largestRectangle(matr) << endl;
	return 0;
}
