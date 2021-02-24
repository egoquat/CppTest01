#include "Test201205_01.h"
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <iostream>
#include <cmath>
#include <functional>

using namespace std;

namespace test01
{
string solutiontest(vector<string> participant, vector<string> completion) {
	string answer = "";
	for (int i = 0; i < completion.size(); ++i)
	{
		const string& nameC = completion[i];
		vector<string>::iterator* iterRemove = nullptr;
		for (vector<string>::iterator iterP = participant.begin(); iterP != participant.end(); ++iterP)
		{
			if (*iterP == nameC)
			{
				iterRemove = &iterP;
				break;
			}
		}
		if (nullptr != iterRemove)
		{
			cout << "Erase : " << *(*iterRemove) << endl;
			participant.erase(*iterRemove);
		}
	}
	return answer;
}
}

///////////////////////// ����
namespace marathon
{

string solution(vector<string> participant, vector<string> completion) {
	string answer = "";
	unordered_map<string, int> strMap;
	for (auto elem : completion)
	{
		if (strMap.end() == strMap.find(elem))
			strMap.insert(make_pair(elem, 1));
		else
			strMap[elem]++;
	}

	for (auto elem : participant)
	{
		if (strMap.end() == strMap.find(elem))
		{
			answer = elem;
			break;
		}
		else
		{
			strMap[elem]--;
			if (strMap[elem] < 0)
			{
				answer = elem;
				break;
			}
		}
	}
	return answer;
}
}
///////////////////////// ���� //


///////////////////////// ���� �ؽ�
/*��ȭ��ȣ ���
���� ����
��ȭ��ȣ�ο� ���� ��ȭ��ȣ ��, �� ��ȣ�� �ٸ� ��ȣ�� ���ξ��� ��찡 �ִ��� Ȯ���Ϸ� �մϴ�.
��ȭ��ȣ�� ������ ���� ���, ������ ��ȭ��ȣ�� �������� ��ȭ��ȣ�� ���λ��Դϴ�.
������ : 119
���ؿ� : 97 674 223
������ : 11 9552 4421
��ȭ��ȣ�ο� ���� ��ȭ��ȣ�� ���� �迭 phone_book �� solution �Լ��� �Ű������� �־��� ��, 
� ��ȣ�� �ٸ� ��ȣ�� ���ξ��� ��찡 ������ false�� �׷��� ������ true�� return �ϵ��� solution �Լ��� �ۼ����ּ���.*/
bool solution_phone_book(vector<string> phone_book) {
	bool answer = true;
	//01
	/*sort(phone_book.begin(), phone_book.end());
	for (int idx = 0; idx < phone_book.size(); ++idx)
	{
		if (idx >= phone_book.size() - 1)
			break;
		string& phone = phone_book[idx];
		string& phoneNext = phone_book[idx+1];
		if (phoneNext.compare(0, phone.length(), phone) == 0)
		{
			answer = false;
			break;
		}
	}*/

	//02
	unordered_map<string, bool> map_phone;
	for (string& phone : phone_book)
	{
		map_phone[phone] = true;
	}

	for (string& phone : phone_book)
	{
		string phoneCheck;
		for (char& c : phone)
		{
			phoneCheck += c;
			if (0 == phoneCheck.compare(phone))
				break;
			if (true == map_phone[phoneCheck])
			{
				return false;
			}
		}
	}

	return answer;
}
///////////////////////// ���� //

///////////////////////// ���� ����� ��
/*�ؽ� : ����
�����̵��� ���� �ٸ� ���� �����Ͽ� �Ծ� �ڽ��� �����մϴ�.
���� ��� �����̰� ���� ���� �Ʒ��� ���� ���� �����̰� ���׶� �Ȱ�, �� ��Ʈ, �Ķ��� Ƽ������ �Ծ��ٸ� 
�������� û������ �߰��� �԰ų� ���׶� �Ȱ� ��� ���� ���۶󽺸� �����ϰų� �ؾ� �մϴ�.

����	�̸�
��	���׶� �Ȱ�, ���� ���۶�
����	�Ķ��� Ƽ����
����	û����
�ѿ�	�� ��Ʈ
�����̰� ���� �ǻ���� ��� 2���� �迭 clothes�� �־��� �� ���� �ٸ� ���� ������ ���� return �ϵ��� solution �Լ��� �ۼ����ּ���.*/
int solution_clothes(vector<vector<string>> clothes) {
	unordered_map<string, int> Parts;
	int total = 0;
	for (vector<string>& cloth : clothes)
	{
		Parts[cloth[1]]++; total++;
	}

	int answer = Parts.size() >= 1 ? 1 : 0;
	for (pair<string, int> pair : Parts)
	{
		answer = answer * (pair.second + 1);
	}

	return answer - 1;
}
///////////////////////// ���� //

///////////////////////// ����
#include <queue>
/*��: �� �ʰ�
���� ����
�ſ� ���� �����ϴ� Leo�� ��� ������ ���ں� ������ K �̻����� ����� �ͽ��ϴ�.
��� ������ ���ں� ������ K �̻����� ����� ���� Leo�� ���ں� ������ ���� ���� �� ���� ������ �Ʒ��� ���� Ư���� ������� ���� ���ο� ������ ����ϴ�.
���� ������ ���ں� ���� = ���� ���� ���� ������ ���ں� ���� + (�� ��°�� ���� ���� ������ ���ں� ���� * 2)
Leo�� ��� ������ ���ں� ������ K �̻��� �� ������ �ݺ��Ͽ� �����ϴ�.*/
int solution(vector<int> scoville, int K) {
	priority_queue<int, vector<int>, greater<int>> queue;
	for (int item : scoville)
	{
		queue.push(item);
	}

	int answer = 0, a = 0, b = 0;
	while (queue.top() < K)
	{
		a = queue.top(); queue.pop();
		if (queue.size() <= 0)
			return -1;
		b = queue.top(); queue.pop();
		queue.push(a + (b * 2));
		answer++;
	}

	return queue.top() < K ? -1 : answer;
}
///////////////////////// ���� //

///////////////////////// ����
/*��: ��ũ ��Ʈ�ѷ�
���� ����
�ϵ��ũ�� �� ���� �ϳ��� �۾��� ������ �� �ֽ��ϴ�.��ũ ��Ʈ�ѷ��� �����ϴ� ����� ���� ������ �ֽ��ϴ�.���� �Ϲ����� ����� ��û�� ���� ������� ó���ϴ� ���Դϴ�.

�������

- 0ms ������ 3ms�� �ҿ�Ǵ� A�۾� ��û
- 1ms ������ 9ms�� �ҿ�Ǵ� B�۾� ��û
- 2ms ������ 6ms�� �ҿ�Ǵ� C�۾� ��û*/
struct Compare
{
	bool operator()(vector<int>& a, vector<int>& b) { return a[1] > b[1]; }
};

int solution(vector<vector<int>> jobs) {
	sort(jobs.begin(), jobs.end());

	priority_queue<vector<int>, vector<vector<int>>, Compare> queue;
	int i = 0, time = 0, time_sum = 0;
	while (i < jobs.size() || false == queue.empty())
	{
		if (i < jobs.size() && time >= jobs[i][0])
		{
			//cout << " queue.push/i:" << i << endl;
			queue.push(jobs[i++]);
			continue;
		}

		if (true == queue.empty())
		{
			time = jobs[i][0];
			//cout << " (true == queue.empty())/i:" << i << "/time:" << time << endl;
		}
		else
		{
			time = time + queue.top()[1];
			time_sum = time_sum + (time - queue.top()[0]);
			queue.pop();
			//cout << " queue.pop()/i:" << i << "/time:" << time << endl;
		}
	}

	int answer = time_sum / jobs.size();
	return answer;
}
///////////////////////// ���� // 


///////////////////////// ����
/*���߿켱����ť
���� ����
���� �켱���� ť�� ���� ������ �� �� �ִ� �ڷᱸ���� ���մϴ�.

��ɾ�	���� ž(����)
I ����	ť�� �־��� ���ڸ� �����մϴ�.
D 1	ť���� �ִ��� �����մϴ�.
D - 1	ť���� �ּڰ��� �����մϴ�.*/
vector<int> solution_deque(vector<string> operations) {
	deque<int> numbers;

	for (string& o : operations)
	{
		char operate = o[0];
		int num = stoi(o.substr(2));
		if (operate == 'I') {
			numbers.push_back(num);
			sort(numbers.begin(), numbers.end());
		}
		else if (numbers.size() >= 1) {
			if (num >= 1)
				numbers.pop_back();
			else
				numbers.pop_front();
		}
	}
	vector<int> answer;
	answer.push_back(0); answer.push_back(0);
	if (numbers.empty() == false)
	{
		answer[0] = numbers.back(); answer[1] = numbers.front();
	}
	return answer;
}

///////////////////////// ���� // 


///////////////////////// ����
/*�ֽİ���
���� ����
�� ������ ��ϵ� �ֽİ����� ��� �迭 prices�� �Ű������� �־��� ��, ������ �������� ���� �Ⱓ�� �� �������� return �ϵ��� solution �Լ��� �ϼ��ϼ���.*/
#include <stack>
vector<int> solution(vector<int> prices) {
	int count = prices.size();
	vector<int> answer(count);

	stack<int> s;
	for (int i = 0; i < count; ++i)
	{
		while (false == s.empty() && prices[s.top()] > prices[i])
		{
			int last = s.top(); s.pop();
			answer[last] = i - last;
		}
		s.push(i);
	}

	while (false == s.empty())
	{
		int last = s.top(); s.pop();
		answer[last] = count - last - 1;
	}

	return answer;
}
///////////////////////// ���� //


///////////////////////// ���� 
/*���� 01*/
vector<int> solutionsort01(vector<int> array, vector<vector<int>> commands) {
	vector<int> answer(commands.size());
	vector<int> partial;
	for (int i = 0; i < commands.size(); ++i)
	{
		vector<int>& cmd = commands[i];
		partial.assign(array.begin() + cmd[0]-1, array.begin() + cmd[1]);
		sort(partial.begin(), partial.end());
		answer[i] = partial[cmd[2]-1];
	}
	return answer;
}
///////////////////////// ���� //


///////////////////////// ���� �׽�Ʈ
/*����ū�� �׽�Ʈ*/
string solutionhighestnumber_test(vector<int> numbers) {
	vector<string> nums;
	for (int i = 0; i < numbers.size(); ++i) {
		nums.push_back(to_string(numbers[i]));
	}
	sort(nums.begin(), nums.end(), [](string& a, string& b)
		{
			string& l = a.length() < b.length() ? a : b;
			string& h = a.length() < b.length() ? b : a;
			int i = 0, iHigh = 0; bool isHighB = a.length() < b.length();
			while (iHigh < h.length())
			{
				for (i = 0; i < l.length() && i + iHigh < h.length(); ++i)
				{
					int numl = l[i] - '0', numh = h[i + iHigh] - '0';
					if (i + iHigh == h.length() - 1) numl = l[l.length() - 1] - '0';
					if (numl == numh) continue;
					if (numl > numh) return isHighB;
					else return !isHighB;
				}
				iHigh += l.length();
			}
			return false;
		});

	string answer = "";
	for (int i = 0; i < numbers.size(); ++i) {
		answer += nums[i];
	}
	cout << answer << endl;
	return answer;
}
///////////////////////// ���� �׽�Ʈ //

///////////////////////// ����
/*����ū��*/
string solutionhighestnumber(vector<int> numbers) {
	vector<string> nums;
	for (int i = 0; i < numbers.size(); ++i) {
		nums.push_back(to_string(numbers[i]));
	}
	sort(nums.begin(), nums.end(), [](string& a, string& b)
	{
		return a + b > b + a;
	});

	if (nums[0] == "0") return "0";
	string answer = "";
	for (int i = 0; i < nums.size(); ++i) {
		answer += nums[i];
	}
	cout << answer << endl;
	return answer;
}
///////////////////////// ���� //

///////////////////////// ���� 
/*���ǰ��*/
vector<int> solutionexamination(vector<int> answers) {
	vector<vector<int>> pattern = {
		{1,2,3,4,5},
		{2,1,2,3,2,4,2,5},
		{3,3,1,1,2,2,4,4,5,5}
	};
	vector<int> checks(3); int n0 = pattern[0].size(), n1 = pattern[1].size(), n2 = pattern[2].size();
	for (int i = 0; i < answers.size(); ++i)
	{
		int a = answers[i];
		if (pattern[0][i%n0] == a) checks[0]++;
		if (pattern[1][i%n1] == a) checks[1]++;
		if (pattern[2][i%n2] == a) checks[2]++;
	}

	vector<int> answer;
	int first = max(checks[0], max(checks[1], checks[2]));
	for (int i = 0; i < 3; ++i) { if (first == checks[i]) answer.push_back(i + 1); }
	return answer;
}
///////////////////////// ���� //

///////////////////////// ���� 
/*�Ҽ�ã��*/
namespace primefind
{
#include <unordered_set>
#include <cmath>
#include <queue>

void GetComsTestR(const vector<char>& arr, int depth, string stack, vector<bool>& visits, unordered_set<int>& combs) {
	if (depth >= arr.size()) return;
	for (int i = 0; i < arr.size(); ++i) {
		if (true == visits[i]) continue;
		visits[i] = true;
		stack.push_back(arr[i]);
		combs.insert(stoi(stack));
		GetComsTestR(arr, depth + 1, stack, visits, combs);
		stack.pop_back();
		visits[i] = false;
	}
}

void GetComsTest(const vector<char>& arr, unordered_set<int>& combs) {
	vector<bool> visits(arr.size(), false);
	string stack;
	GetComsTestR(arr, 0, stack, visits, combs);
}

void GetComsTestQR(const vector<char>& arr, int depth, string stack, vector<bool>& visits, priority_queue<int>& combs) {
	if (depth >= arr.size()) return;
	for (int i = 0; i < arr.size(); ++i) {
		if (true == visits[i]) continue;
		visits[i] = true;
		stack.push_back(arr[i]);
		combs.push(stoi(stack));
		GetComsTestQR(arr, depth + 1, stack, visits, combs);
		stack.pop_back();
		visits[i] = false;
	}
}

void GetComsTestQ(const vector<char>& arr, priority_queue<int>& combs) {
	vector<bool> visits(arr.size(), false);
	string stack;
	GetComsTestQR(arr, 0, stack, visits, combs);
}

bool IsPrimeSimple(int n) {
	if (n <= 1) return false;
	if (n <= 3) return true;
	//int s = sqrt(n + 1);
	int s = n / 2;
	for (int i = 2; i <= s; ++i) {
		if (n % i == 0) return false;
	}
	return true;
}

int solution(string nums) {
	vector<char> arr(nums.begin(), nums.end());
	unordered_set<int> combs;
	GetComsTest(arr, combs);

	priority_queue<int> combsq;
	GetComsTestQ(arr, combsq);

	vector<pair<int, bool>> isprimes(combs.size());
	unordered_set<int>::iterator iter = combs.begin();
	for (int i = 0; iter != combs.end(); ++iter, ++i) {
		int num = *iter;
		isprimes[i] = make_pair(num, IsPrimeSimple(num));
	}

	int answer = 0;
	return answer;
}
}
///////////////////////// ���� //

///////////////////////// ����
/*Ÿ�ٳѹ� ����Ž��*/
#include <unordered_set>

void GetCombsR(vector<bool> visits, int depth, vector<string>& combs) {
	if (depth >= visits.size()){
		string combination;
		for (int j = 0; j < visits.size(); ++j) {
			combination += visits[j] == true ? '1' : '0';
		}
		combs.push_back(combination);
		return;
	}
	
	visits[depth] = true;
	GetCombsR(visits, depth + 1, combs);
	visits[depth] = false;
	GetCombsR(visits, depth + 1, combs);
}

void GetCombs(int n, vector<string>& combs) {
	vector<bool> visits(n, false);
	GetCombsR(visits, 0, combs);
}

int solutiontargetnumbertest(vector<int> numbers, int target) {
	unordered_map<char, int> operates = { make_pair('0', 1), make_pair('1', -1) };
	vector<string> combs;
	GetCombs(numbers.size(), combs);
	int answer = 0;
	vector<int> numbs(combs.size());
	for (int i = 0; i < combs.size(); ++i) {
		string& operate = combs[i];
		int num = 0;
		for (int j = 0; j < operate.length(); ++j) {
			num = num + (numbers[j] * operates[operate[j]]);
		}
		numbs[i] = num;
		if (num == target) answer++;
	}
	return answer;
}
///////////////////////// ���� // 

///////////////////////// ����
/*��Ʈ��ũ ���̳ʺ�켱Ž�� DFS,BFS*/
void GetLinkR(int idx, vector<vector<int>>& coms, vector<bool>& visits, int depth) {
	if (true == visits[idx]) return;
	vector<int> links = coms[idx];
	visits[idx] = true;
	for (int i = 0; i < links.size(); ++i) {
		if (i == idx || links[i] == 0) continue;
		GetLinkR(i, coms, visits, depth + 1);
	}
}

int GetLink(vector<vector<int>>& coms) {
	vector<bool> visits(coms.size(), false);
	int num = 0;
	for (int i = 0; i < coms.size(); ++i) {
		if (true == visits[i]) continue;
		GetLinkR(i, coms, visits, 0); num++;
	}
	return num;
}

int solutionnetwork(int n, vector<vector<int>> computers) {
	int answer = GetLink(computers);
	return answer;
}
///////////////////////// ���� //

///////////////////////// ����
/*
�ܾȯ ����/�ʺ� �켱 Ž��(DFS/BFS)*/
#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

int Find(vector<string>& words, string& target){
	vector<string>::iterator it = std::find(words.begin(), words.end(), target);
	if (it == words.end()) return -1;
	return std::distance(words.begin(), it);
}

bool IsAdj(string& a, string& b){
	int diff = 0;
	for (int i = 0; i < a.size(); ++i){
		if (a[i] == b[i]) continue;
		diff++;
	}
	return 1 == diff;
}

void GetLinkWordR(vector<string>& words, vector<bool>& visits, int current, int target, int depth, int& link_out) {
	if (target == current) {
		link_out = std::min(depth, link_out);
		return;
	}
	visits[current] = true;
	for (int i = 0; i < words.size(); ++i) {
		if (true == visits[i]) continue;
		if (IsAdj(words[i], words[current]) == false) continue;
		GetLinkWordR(words, visits, i, target, depth + 1, link_out);
	}
}

int GetLinkWord(vector<string>& words, string& start, int target){
	int min = words.size();
	//vector<int> counts(words.size(), -1);
	for (int i = 0; i <words.size(); ++i){
		if (IsAdj(words[i], start) == false) continue;
		vector<bool> visits(words.size(), false);
		int cnt = words.size();
		GetLinkWordR(words, visits, i, target, 1, cnt);
		//counts[i] = cnt;
		min = std::min(min, cnt);
	}
	return min;
}
int solutionwordsimilar(string begin, string target, vector<string> words) {
	int idx = Find(words, target);
	if (-1 == idx) return 0;
	GetLinkWord(words, begin, idx);
	int answer = 0;
	return answer;
}
///////////////////////// ���� //

///////////////////////// ����
/*������ ����/�ʺ� �켱 Ž��(DFS/BFS)*/
#include <string>
#include <vector>

vector<string> solutiontairportpath(vector<vector<string>> tickets) {
	vector<string> answer;
	return answer;
}
///////////////////////// ���� //

///////////////////////// ����
/*ü���� Ž���*/
#include <string>
#include <vector>

int solutiontrainingwear(int n, vector<int> lost, vector<int> reserve) {
	
	int answer = 0;
	return answer;
}
///////////////////////// ���� //

///////////////////////// ����
/*����ճ��: fault : �ð��ʰ� �׽�Ʈ */
#include <string>
#include <vector>
#include <algorithm>
namespace fartestnode{
struct Node {
	int Idx = -1;
	int Dist = 999999;
	vector<int> Adjs;
};
vector<Node> Nodes;
void AddEdge(vector<int>& edge) {
	for (int i = 0; i <= 1; ++i) {
		Node& node = Nodes[edge[i]];
		node.Idx = edge[i];
		node.Adjs.push_back(edge[1 - i]);
	}
}
void SetDistR(int idx, vector<bool> visits, int depth) {
	Node& node = Nodes[idx];
	if (node.Dist > depth) node.Dist = depth;
	if (true == visits[idx]) return;
	visits[idx] = true;
	for (int adj : node.Adjs) {
		SetDistR(adj, visits, depth + 1);
	}
}
void SetDist() {
	vector<bool> visits(Nodes.size() + 1, false);
	SetDistR(1, visits, 0);
}
int solutionfarstnodetest01(int n, vector<vector<int>> edge) {
	Nodes.resize(n + 1);
	for (vector<int>& e : edge) {
		AddEdge(e);
	}
	SetDist();
	vector<int> orders(Nodes.size() - 1);
	for (int i = 1; i < Nodes.size(); ++i) {
		orders[i - 1] = i;
	}
	sort(orders.begin(), orders.end(), [&](const int& a, const int& b) {
		return Nodes[a].Dist > Nodes[b].Dist;
		 });
	int answer = 0;
	int farst = Nodes[orders[0]].Dist;
	for (int idx : orders) {
		if (farst == Nodes[idx].Dist) answer++;
		else break;
	}
	return answer;
}

int solutionfarstnodetest02(int n, vector<vector<int>> edge) {
	int answer = 0;

	return answer;
}
}
///////////////////////// ���� // 

///////////////////////// ����
namespace cardscompare
{

vector<string> solutioncard(vector<string> card, vector<string> word) {
	function<void(string&, map<char, int>&)> mapping = [](string& str, map<char, int>& wordmap) {
		for (int j = 0; j < str.length(); ++j) {
			wordmap[str[j]]++;
		}
	};
	vector<map<char, int>> bases(card.size());
	for (int i = 0; i < card.size(); ++i) {
		string& str = card[i];
		map<char, int>& base = bases[i];
		mapping(str, base);
	}

	vector<string> answer = {};
	for (string& w : word) {
		map<char, int> wordmap;
		mapping(w, wordmap);
		vector<bool> uses(bases.size(), false);
		bool noneany = false;
		for (char c : w) {
			bool found = false;
			for (int i = 0; i < bases.size(); ++i) {
				map<char, int>& base = bases[i];
				int count = base[c];
				if (0 == count) continue;
				if (count - wordmap[c] >= 0) {
					found = true;
					uses[i] = true;
					break;
				}
			}
			if (false == found) {
				noneany = true;
				break;
			}
		}
		if (true == noneany) continue;
		bool alluse = find(uses.begin(), uses.end(), false) == uses.end();
		if (true == alluse) {
			answer.push_back(w);
		}
	}

	return answer;
}
}
///////////////////////// ���� //

///////////////////////// ����
long long solutionrobotrail(string block, int pos) {
	std::function<int(char&)> getdir = [](char& c) {
		if (c == '>') { c = '<'; return 1; }
		c = '>';
		return -1;
	};
	long long answer = 0;
	int cur = pos - 1;
	while (true) {
		char c = block[cur];
		int nextcur = getdir(c);
		block[cur] = c;
		cur = cur + nextcur;
		cout << "next:" << cur << "/" << block << endl;
		++answer;
		if ((cur >= block.length() && block.back() == '<')
			|| (cur <= -1 && block.front() == '>')) {
			break;
		}
	}
	return answer;
}
///////////////////////// ���� //

///////////////////////// ����
#include <string>
#include <vector>
#include <cmath>

namespace quadtreestring
{
struct CNode {
	int Idx;
	int IdxParent = -1;
	int Depth = 0;
	char State = 'n';
	vector<int> Childs;
	bool IsRoot() { return IdxParent == -1; }
	int GetSize() { return std::pow(32 / (Depth + 1), 2); }
	void Set(char state, int depth, int parent) { State = state; Depth = depth; IdxParent = parent; }
};
vector<CNode> N1;
vector<CNode> N2;
vector<CNode> N3;
void SetNodesR(vector<CNode>& nodes, string& s, int cur, int parent, int depth) {
	char state = s[cur];
	nodes[cur].Set(state, depth, parent);
	if (state == 'b' || state == 'w') {
		return;
	}
	nodes[cur].Childs.resize(4);
	for (int i = 1; i <= 4; ++i) {
		int idxnext = cur + i;
		nodes[cur].Childs[i - 1] = idxnext;
		SetNodesR(nodes, s, idxnext, cur, depth + 1);
	}
}
void SetNodes(string& s, vector<CNode>& nodes) {
	nodes[0].Set(s[0], 1, -1);
	SetNodesR(nodes, s, 1, 0, 0);
}
int solutionquadtree(string S1, string S2) {
	N1.resize(S1.length());
	N2.resize(S2.length());
	SetNodes(S1, N1);
	SetNodes(S2, N2);
	int answer = 0;
	return answer;
}
}
///////////////////////// ���� //

///////////////////////// ����
/* ���� / ť : �ٸ��� ������ Ʈ�� */
namespace truck
{
#include <string>
#include <vector>
#include <queue>
#include <iostream>
#include <map>

struct Truck {
	int W = 0;
	int Idx = 0;
	int T = 0;
	Truck(int w, int idx) { W = w; Idx = idx; }
	Truck(Truck& o, int t) { W = o.W; Idx = o.Idx; T = t; }
};
int solution(int bridge_length, int weight, vector<int> truck_weights) {
	int answer = 0;
	queue<Truck> queue01, queue02;
	for (int i = 0; i < truck_weights.size(); ++i) {
		int w = truck_weights[i];
		queue01.push(Truck(w, i));
	}
	int w = 0, len = bridge_length;
	cout << " 01 : " << queue01.size() << " /02 : " << queue02.size() << endl;
	while (true != queue01.empty() || true != queue02.empty()) {
		bool ispoped = false;
		if (queue02.size() >= 1 && answer >= queue02.front().T) {
			w = w - queue02.front().W;
			cout << " pop 02 T : " << (queue02.front().T) << endl;
			queue02.pop();
			ispoped = true;
		}

		if (true != queue01.empty() && w + queue01.front().W <= weight) {
			w += queue01.front().W;
			cout << " push 02 T : " << (answer + len) << endl;
			queue02.push(Truck(queue01.front(), answer + len));
			queue01.pop();
		}
		answer++;
	}
	return answer;
}
}
///////////////////////// ���� //

///////////////////////// ����
/* ���� / ť : ������ */
namespace printer
{
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

struct Pr {
	int P = -1;
	int Idx = -1;
	Pr(int p, int idx) { P = p; Idx = idx; }
};
int solution(vector<int> priorities, int location) {
	priority_queue<int> pqueue;
	queue<Pr> queue;
	for (int i = 0; i < priorities.size(); ++i) {
		queue.push(Pr(priorities[i], i));
		pqueue.push(priorities[i]);
	}

	int answer = 0;
	while (queue.empty() != true) {
		Pr pr = queue.front();
		queue.pop();

		if (pr.P == pqueue.top()) {
			pqueue.pop();
			answer++;

			if (pr.Idx == location) {
				break;
			}
		}
		else {
			queue.push(pr);
		}
	}
	return answer;
}
}
///////////////////////// ���� //

namespace sumint
{
#include <string>
#include <vector>
#include <algorithm>

void GetCombsR(const vector<int>& nums,
			   int depth,
			   int sum,
			   int target,
			   vector<int> stack,
			   vector<bool>& visits,
			   vector<vector<int>>& combs) {
	if (depth >= nums.size()) return;
	if (stack.size() >= 2) return;
	for (int i = 0; i < nums.size(); ++i) {
		if (true == visits[i]) continue;
		visits[i] = true;
		int sumnext = sum + nums[i];
		if (sumnext > target) continue;
		vector<int> stacknew = stack;
		stacknew.push_back(i);
		if (sumnext == target) {
			combs.push_back(stacknew);
			continue;
		}
		GetCombsR(nums, depth + 1, sumnext, target, stacknew, visits, combs);
		visits[i] = false;
	}
}

void GetCombs(const vector<int>& nums, vector<vector<int>>& combs, int target) {
	vector<bool> visits(nums.size(), false);
	vector<int> stack;
	int sum = 0, depth = 0; 
	GetCombsR(nums, depth, sum, target, stack, visits, combs);
}

vector<int> solution(vector<int> nums, int target) {
	vector<vector<int>> combs;
	GetCombs(nums, combs, target);
	vector<int> answer;
	sort(combs.begin(), combs.end());

	if (combs.size() >= 1){
		answer = combs[0];
	}
	return answer;
}
}

namespace operatorstring
{
#include <string>
#include <vector>

int GetOp(char op, int num, int sum) {
	switch (op) {
	case '+':
	sum += num; break;
	case '-':
	sum -= num; break;
	case '*':
	sum *= num; break;
	case '/':
	sum /= num; break;
	}
	return sum;
}
int GetNum(char c) { return c - '0'; }
bool IsNum(char c) { return c >= '0' && c <= '9'; }
bool IsDivByZero(char op, int num) { return op == '/' && num == 0; }
string solution(string input) {
	int sum = GetNum(input[0]);
	string buf;
	for (int i = 1; i < input.length(); i = i + 2) {
		char op = input[i];
		int num = GetNum(input[i+1]);
		if (true == IsDivByZero(op, num))
		{
			return "Impossible";
		}
		sum = GetOp(op, num, sum);
	}
	string answer = to_string(sum);
	return answer;
}
}

namespace landarea
{
#include <string>
#include <vector>

struct Area {
	int W = 0, H = 0;
	int idxW = 0, idxH = 0;
	bool IsSameSize(Area& o) { return (W == o.H && H == o.W) || (W == o.W && H == o.H); }
	Area(int h, int w) { W = w; H = h; }
};

int solution(vector<int> buildingSize, vector<vector<int>> land) {
	for (int w = 0; w < land.size(); ++w) {
		vector<int>& vers = land[w];
		for (int h = 0; h < vers.size(); ++h) {
			int state = land[w][h];
			if (state == 1) continue;

		}
	}
	int answer = 0;
	return answer;
}
}

int main()
{
	//vector<string> phone_book = { "123","1235","12","567","88" };
	//solution_phone_book(phone_book);

	//vector<int> array = { 1, 5, 2, 6, 3, 7, 4 };
	//vector<vector<int>> commands = { {2, 5, 3}, {4, 4, 1}, {1, 7, 3} };
	//solutionsort01(array, commands);

	//vector<int> array = { 1, 25, 2, 26, 3, 7, 34, 34343, 3434,3434343 };
	//solutionhighestnumber(array);
	
	//string numfindprime = "7025361";
	//string numfindprime = "17";
	//string numfindprime = "702";
	string numfindprime = "011038";
	primefind::solution(numfindprime);

	//vector<int> numbers = { 1, 1, 1, 1, 1 };
	//int target = 3;
	//solutiontargetnumbertest(numbers, target);

	//vector<vector<int>> computers = {{1, 1, 0}, {1, 1, 0}, {0, 0, 1}};
	//int n = 3;
	//solutionnetwork(n, computers);

	//vector<string> words = { "hot", "dot", "dog", "lot", "log", "cog" };
	//string begin = "hit";
	//string target = "cog";
	//solutionwordsimilar(begin, target, words);

	//vector<string> card = { "ABACDEFG", "NOPQRSTU", "HIJKLKMM" };
	//vector<string> word = { "GPQM", "GPMZ", "EFU", "MMNA" };
	//solutioncard(card, word);

	//string block = ">><";
	//string block = ">><>>";
	//int pos = 2;
	//solutionrobotrail(block, pos);
	
	//string S1 = "ppwwwbpbbwwbw";
	//string S2 = "pwbwpwwbw";
	//quadtreestring::solutionquadtree(S1, S2);

	//int bridge_length = 2;
	//int weight = 10;
	//vector<int> truck_weights = { 7,4,5,6 };
	//truck::solution(bridge_length, weight, truck_weights);

	//int location = 5;
	////vector<int> priorities = { 2,1,3,2 };
	//vector<int> priorities = { 1,1,9,1,1,1 };
	//printer::solution(priorities, location);

	//vector<int> nums = { 1, 2, 3, 4, 5 };
	//int target = 6;
	//sumint::solution(nums, target);
	//string input = "2+3";
	//operatorstring::solution(input);

	//vector<int> buildingSize;
	//vector<vector<int>> land;
	//landarea::solution(buildingSize, land);

	return 0;
}