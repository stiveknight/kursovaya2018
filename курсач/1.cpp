#include <iostream> 
#include <fstream> 
#include <vector> 
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <string> 
#include <ctime> 

using namespace std;
vector <int> v_sv;
vector <int> v_komp;
vector <int> v_obh;
vector <int> v_treo;
vector <int> v_rad;
vector <int> v_diam;
vector <int> v_duo;
vector <int> v_m;

vector <int> used;
vector <int> dolya;
vector <int> p;
int n, m, k;
const int INF = 1000000000;
vector <vector <int>> g(n);
vector <vector <int>> d(n);
vector <int> vec;
string str;
vector <int> obh;
bool x;
int komp, star, fin;
bool ok = true;

void dfs_1(int v) {
	used[v] = 1;
	for (int i = 0; i < g[v].size(); i++) {
		if (g[v][i] == 1) {
			int to = i;
			if (used[to] == 0)
				dfs_1(to);
		}
	}
}

void dfs(int v) { //поиск в глубину
	used[v] = 1;
	for (int i = 0; i<g[v].size(); i++) {
		if (g[v][i] == 1) {
			k = 0;
			int to = i;
			if (used[to] == 0) {
				p[to] = v;
				dfs(to);
			}
			else if (used[to] == 1 && to != p[v]) {
				star = to; fin = v; k = 0;
				for (int j = fin; j != star; j = p[j])  k++;
				obh.push_back(k + 1);
			}
		}
	}
	used[v] = 2;
	return;
}

void komp_sv(vector <vector <int>> g) {
	for (int i = 0; i < n; i++)  used.push_back(0);
	komp = 0;
	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			dfs_1(i); komp++;
		}
	}
	used.clear();
	cout << endl << "Связный? ";
	if (komp == 1) {
		cout << "Да"; v_sv.push_back(1);
	}
	else {
		cout << "Нет"; v_sv.push_back(-1);
	}
	cout << endl;
	cout << "Количество компонент связности: " << komp;
	v_komp.push_back(komp);
	return;
}

void obhv(vector <vector <int>> g) {
	for (int i = 0; i < n; i++) { p.push_back(-1); used.push_back(0); }
	for (int i = 0; i<n; i++)
		if (used[i] == 0) {
			dfs(i);
		}
	used.clear();

	cout << endl;
	if (obh.size() == 0) {
		cout << "Обхват равен бесконечности"; v_obh.push_back(-1);
	}
	else {
		int min_ob = obh[0];
		for (int i = 0; i < obh.size(); i++) {
			if (obh[i] < min_ob) min_ob = obh[i];
		}
		cout << "Обхват: " << min_ob;
		v_obh.push_back(min_ob);
	}
	p.clear();
	obh.clear();
	return;

}

void treo(vector <vector <int>> g) {
	int cnt = 0;
	for (int a = 0; a < n; a++)
		for (int b = a + 1; b < n; b++)
			for (int c = b + 1; c < n; c++)
				if (g[a][b] != 0 && g[b][c] != 0 && g[a][c] != 0) cnt++;
	cout << endl << "Количество треугольников: " << cnt;
	v_treo.push_back(cnt);
	return;
}

void rad_diam(vector <vector <int>> g) {
	vector <int>e(n, 0);
	int rad = INF, diam = 0;
	for (int t = 0; t < n; t++)
		for (int u = 0; u < n; u++)
			for (int v = 0; v < n; v++)
				d[u][v] = min(d[u][v], d[u][t] + d[t][v]);

	for (int u = 0; u < n; u++)
		for (int v = 0; v < n; v++)
			if (d[u][v] == INF) d[u][v] = 0;


	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			e[i] = max(e[i], d[i][j]);

	for (int i = 0; i < n; i++) {
		rad = min(rad, e[i]);
		diam = max(diam, e[i]);
	}
	cout << endl << "Радиус = " << rad;
	v_rad.push_back(rad);
	cout << endl << "Диаметр = " << diam;
	v_diam.push_back(diam);
	return;
}

void bfs(int s) { // поиск в ширину
	queue<int> q;
	q.push(s);
	used[s] = 1;
	dolya[s] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < g[v].size(); i++) {
			if (g[v][i] == 1)
			{
				int to = i;
				if (used[to] == 0) {
					used[to] = 1;
					if (dolya[v] == 1) dolya[to] = 2;
					else dolya[to] = 1;
					q.push(to);
				}
				else if (dolya[v] == dolya[to]) {
					ok = false; return;
				}
			}
		}
	}
	return;
}

void duo(vector <vector <int>> g) {
	for (int i = 0; i < n; i++) {
		used.push_back(0); dolya.push_back(0);
	}
	for (int i = 0; i < n; i++) {
		if (!ok) {
			cout << endl << "Граф не двудольный";
			v_duo.push_back(-1);
			dolya.clear(); used.clear();
			return;
		}
		else if (used[i] == 0) bfs(i);
	}
	if (ok) {
		cout << endl << "Граф двудольный"; v_duo.push_back(1);
	}
	else {
		cout << endl << "Граф не двудольный";  v_duo.push_back(-1);
	}
	dolya.clear();
	used.clear();
	return;
}

int main() {
	int kolvo = 0;
	setlocale(LC_ALL, "Russian");
	//считывание матриц смежности графов в цикле
	ifstream in("graphs5.txt");
	in >> n;
	getline(in, str);
	while (getline(in, str)) {
		getline(in, str);
		m = 0;
		for (int i = 0; i < n; i++) {
			g.push_back(vec);
			d.push_back(vec);
			getline(in, str);
			for (int j = 0; j < n; j++) {
				if (str[j] == '0') {
					g[i].push_back(0);
					if (i == j) d[i].push_back(0);
					else d[i].push_back(INF);
				}
				else {
					g[i].push_back(1); d[i].push_back(1); m++;
				}
			}
		}
		for (int i = 0; i < n; i++) {
			cout << endl;
			for (int j = 0; j < n; j++)
				cout << g[i][j];
		}
		cout << endl << "n = " << n;
		cout << endl << "m = " << m / 2;
		v_m.push_back(m / 2);

		//связный ли и количество компонент
		komp_sv(g);
		// чему равен обхват графа
		obhv(g);
		// количество треугольников
		treo(g);
		//радиус и диаметр
		rad_diam(g);
		// двудольность
		duo(g);
		kolvo++;

		cout << endl;
		g.clear();
		d.clear();
	}
	set <int> s_sv;
	set <int> s_komp;
	set <int> s_obh;
	set <int> s_treo;
	set <int> s_rad;
	set <int> s_diam;
	set <int> s_duo;
	set <int> s_m;
	for (int i = 0; i < v_sv.size(); i++) {
		s_sv.insert(v_sv[i]);
		s_komp.insert(v_komp[i]);
		s_obh.insert(v_obh[i]);
		s_treo.insert(v_treo[i]);
		s_rad.insert(v_rad[i]);
		s_diam.insert(v_diam[i]);
		s_duo.insert(v_duo[i]);
		s_m.insert(v_m[i]);
	}
	vector <int> klass;
	unsigned int start_time = clock();
	set <int>::iterator it1, it2, it3, it4, it5, it6, it7;
	int t = 0;
	for (it1 = s_komp.begin(); it1 != s_komp.end(); it1++)
		for (it2 = s_m.begin(); it2 != s_m.end(); it2++)
			for (it3 = s_obh.begin(); it3 != s_obh.end(); it3++)
				for (it4 = s_treo.begin(); it4 != s_treo.end(); it4++)
					for (it5 = s_duo.begin(); it5 != s_duo.end(); it5++)
						for (it6 = s_rad.begin(); it6 != s_rad.end(); it6++)
							for (it7 = s_diam.begin(); it7 != s_diam.end(); it7++)
							{
								for (int k = 0; k < kolvo; k++) {
									if (v_komp[k] == *it1 && v_m[k] == *it2 && v_obh[k] == *it3 && v_treo[k] == *it4 && v_duo[k] == *it5 && v_rad[k] == *it6 && v_diam[k] == *it7)
										t++;
								}
								if (t != 0) klass.push_back(t);
								t = 0;
							}
	unsigned int end_time = clock();
	unsigned int search_time = end_time - start_time;
	cout << klass.size();
	cout << endl << (float(search_time)) / CLOCKS_PER_SEC;
	system("pause");
	return 0;
}

