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
vector <int> v_exp;
vector <int> v_clique;
vector <int> v_indep;

//ofstream out_diam("diam9.txt");
//ofstream out_duo("duo9.txt");
//ofstream out_komp("komp9.txt");
//ofstream out_obh("obh9.txt");
//ofstream out_rad("rad9.txt");
//ofstream out_sv("sv9.txt");
//ofstream out_treo("treo9.txt");
//ofstream out_exp("exp9.txt");
ofstream out_clique("clique9.txt");
ofstream out_indep("indep9.txt");

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
	for (int i = 0; i < g[v].size(); i++) {
		if (g[v][i] == 1) {
			k = 0;
			int to = i;
			if (used[to] == 0) {
				p[to] = v;
				dfs(to);
			}
			else if (used[to] == 1 && to != p[v]) {
				star = to; fin = v; k = 0;
				for (int j = fin; j != star; j = p[j])  
					k++;
				obh.push_back(k + 1);
			}
		}
	}
	used[v] = 2;
	return;
}

void komp_sv() {
	for (int i = 0; i < n; i++)  
		used.push_back(0);
	komp = 0;
	for (int i = 0; i < n; i++) {
		if (used[i] == 0) {
			dfs_1(i); 
			komp++;
		}
	}
	used.clear();
	//cout << endl << "Связный? ";
	if (komp == 1) {
		//cout << "Да"; 
		v_sv.push_back(1);
		//out_sv << 1 << endl;
	}
	else {
		//cout << "Нет"; 
		v_sv.push_back(-1);
		//out_sv << -1 << endl;
	}
	//cout << endl;
	//cout << "Количество компонент связности: " << komp;
	v_komp.push_back(komp);
	//out_komp << komp << endl;
	return;
}

void obhv() {
	for (int i = 0; i < n; i++) { 
		p.push_back(-1); 
		used.push_back(0); 
	}
	for (int i = 0; i<n; i++)
		if (used[i] == 0)
			dfs(i);

	used.clear();

	//cout << endl;
	if (obh.size() == 0) {
		//cout << "Обхват равен бесконечности"; 
		v_obh.push_back(-1);
		//out_obh << -1 << endl;
	}
	else {
		int min_ob = obh[0];
		for (int i = 0; i < obh.size(); i++) {
			if (obh[i] < min_ob) 
				min_ob = obh[i];
		}
		//cout << "Обхват: " << min_ob;
		v_obh.push_back(min_ob);
		//out_obh << min_ob << endl;
	}
	p.clear();
	obh.clear();
	return;
}

void treo(vector <vector <int>> &g) {
	int cnt = 0;
	for (int a = 0; a < n; a++)
		for (int b = a + 1; b < n; b++)
			for (int c = b + 1; c < n; c++)
				if (g[a][b] != 0 && g[b][c] != 0 && g[a][c] != 0) 
					cnt++;
	//cout << endl << "Количество треугольников: " << cnt;
	v_treo.push_back(cnt);
	//out_treo << cnt << endl;
	return;
}

void rad_diam() {
	vector <int> e(n);
	int rad = INF, diam = 0;
	for (int t = 0; t < n; t++)
		for (int u = 0; u < n; u++)
			for (int v = 0; v < n; v++)
				d[u][v] = min(d[u][v], d[u][t] + d[t][v]);

	for (int u = 0; u < n; u++)
		for (int v = 0; v < n; v++)
			if (d[u][v] == INF) 
				d[u][v] = 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			e[i] = max(e[i], d[i][j]);

	for (int i = 0; i < n; i++) {
		rad = min(rad, e[i]);
		diam = max(diam, e[i]);
	}
	//cout << endl << "Радиус = " << rad;
	v_rad.push_back(rad);
	//out_rad << rad << endl;
	//cout << endl << "Диаметр = " << diam;
	v_diam.push_back(diam);
	//out_diam << diam << endl;
	return;
}

void bfs(int s, bool &ok) { // поиск в ширину
	queue<int> q;
	q.push(s);
	used[s] = 1;
	dolya[s] = 1;
	while (!q.empty()) {
		int v = q.front();
		q.pop();
		for (int i = 0; i < g[v].size(); i++) {
			if (g[v][i] == 1) {
				int to = i;
				if (used[to] == 0) {
					used[to] = 1;
					if (dolya[v] == 1) 
						dolya[to] = 2;
					else 
						dolya[to] = 1;
					q.push(to);
				}
				else if (dolya[v] == dolya[to]) {
					ok = false; 
					return;
				}
			}
		}
	}
	return;
}

void duo() {
	bool ok = true;
	for (int i = 0; i < n; i++) {
		used.push_back(0); 
		dolya.push_back(0);
	}
	for (int i = 0; i < n; i++) {
		if (!ok) {
			//cout << endl << "Граф не двудольный";
			v_duo.push_back(-1);
			//out_duo << -1 << endl;
			dolya.clear(); 
			used.clear();
			return;
		}
		else if (used[i] == 0) 
			bfs(i, ok);
	}
	if (ok) {
		//cout << endl << "Граф двудольный"; 
		v_duo.push_back(1);
		//out_duo << 1 << endl;
	}
	else {
		//cout << endl << "Граф не двудольный";  
		v_duo.push_back(-1);
		//out_duo << -1 << endl;
	}
	dolya.clear();
	used.clear();
	return;
}

void ex(vector<vector<int> > &g) {
	int e = 1;
	int emax = 2*(n-1);
	vector<vector<int> > gg(g);
	vector<vector<int> > c(n, vector<int>(n));
	
	bool b = true;
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (g[i][j] == 0) {
				b = false;
				break;
			}
		}
	}

	if (b) {
		//cout << "Граф примитивный с экспонентой = " << e << endl;
		v_exp.push_back(e);
		//out_exp << e << endl;
		return;
	}
	else {
		bool bb = true;
		for (int i = 2; i <= emax; i++) {
			for (int j = 1; j < i; j++) {
				for (int ii = 0; ii < n; ii++) {
					for (int jj = 0; jj < n; jj++) {
						c[ii][jj] = 0;
						for (int k = 0; k < n; k++) {
							c[ii][jj] += g[ii][k] * gg[k][jj];
						}
					}
				}
			}
			gg = c;
			bb = true;
			for (int ii = 0; ii < n && bb; ii++) {
				for (int jj = 0; jj < n; jj++) {
					if (c[ii][jj] == 0) {
						bb = false;
						break;
					}
				}
			}
			if (bb) {
				//cout << "Граф примитивный с экспонентой = " << i << endl;
				v_exp.push_back(i);
				//out_exp << i << endl;
				return;
			}
		}
		if (!bb) {
			//cout << "Граф не примитивный" << endl;
			v_exp.push_back(0);
			//out_exp << 0 << endl;
			return;
		}
	}
}

void extend(set<int> comsub, set<int> &max_comsub, vector<int> candidates, set<int> not, vector<vector<int> > &gg) {
	// алгоритм брона-кербоша
	vector <int> new_candidates;
	set <int> new_not;
	while (candidates.size() != 0) {
		bool b = false;
		int cnt = 0;
		for (int i = 0; i < not.size(); i++) {
			cnt = 0;
			for (int j = 0; j < candidates.size(); j++)
				if (gg[i][candidates[j]] == 1)
					cnt++;
			if (cnt == candidates.size())
				b = true;
		}
		if (b) 
			return;

		int v = candidates[0];
		comsub.insert(v);
		for (int j = 0; j < candidates.size(); j++) {
			if (gg[v][candidates[j]] == 1)
				new_candidates.push_back(candidates[j]);
		}

		for (int item: not) {
			if (gg[v][item] == 1)
				new_not.insert(item);
		}
		if (new_candidates.size() == 0 && new_not.size() == 0) { // получается comsub - клика
			if (comsub.size() > max_comsub.size())
				max_comsub = comsub;
		}
		else 
			extend(comsub, max_comsub, new_candidates, new_not, gg);

		vector <int> tmp_candidates;
		set <int> tmp_comsub;
		not.insert(v);
		for (int item: comsub){
			if (item != v) 
				tmp_comsub.insert(item);
		}
		comsub = tmp_comsub;

		for (int i = 0; i < candidates.size(); i++) {
			if (candidates[i] != v)
				tmp_candidates.push_back(candidates[i]);
		}
		candidates = tmp_candidates;
	}

	return;
}

void clique(vector<vector<int> > &g) { //максимальная клика
	vector <int> candidates;
	set <int> not, comsub, max_comsub;
	for (int i = 0; i < n; i++)
		candidates.push_back(i);
	extend(comsub, max_comsub, candidates, not, g);
	//cout << "Максимальная клика графа = " << max_comsub.size() << endl;
	v_clique.push_back(max_comsub.size());
	out_clique << max_comsub.size() << endl;
	return;
}

void indep(vector<vector<int> > &g) { // число независимости
	vector<int> candidates;
	set <int>  comsub, max_comsub, not;
	vector <vector<int> > dop_g(n, vector<int>(n, 0));
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i != j) {
				if (g[i][j] == 0)
					dop_g[i][j] = 1;
				else
					dop_g[i][j] = 0;
			}
		}
	}	
	
	//for (int i = 0; i < n; i++) {
	//	cout << endl;
	//	for (int j = 0; j < n; j++)
	//		cout << g[i][j];
	//}
	//cout << endl;
	//for (int i = 0; i < n; i++) {
	//	cout << endl;
	//	for (int j = 0; j < n; j++)
	//		cout << dop_g[i][j];
	//}

	//cout << endl;

	for (int i = 0; i < n; i++)
		candidates.push_back(i);
	extend(comsub, max_comsub, candidates, not, dop_g);
	//cout << "Число независимости графа = " << max_comsub.size() << endl;
	v_indep.push_back(max_comsub.size());
	out_indep << max_comsub.size() << endl;
	return;
}


int main() {
	int kolvo = 0;
	setlocale(LC_ALL, "Russian");
	double start_time = clock();
	//считывание матриц смежности графов в цикле
	ifstream in("graphs9.txt");
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
					if (i == j) 
						d[i].push_back(0);
					else 
						d[i].push_back(INF);
				}
				else {
					g[i].push_back(1); 
					d[i].push_back(1); 
					m++;
				}
			}
		}
		//for (int i = 0; i < n; i++) {
			//cout << endl;
			//for (int j = 0; j < n; j++)
				//cout << g[i][j];
		//}
		//cout << endl << "n = " << n;
		//cout << endl << "m = " << m / 2;
		v_m.push_back(m / 2);

		//связный ли и количество компонент
		komp_sv();
		// чему равен обхват графа
		obhv();
		// количество треугольников
		treo(g);
		//радиус и диаметр
		rad_diam();
		// 
		duo();
		
		ex(g);

		clique(g);
		indep(g);

		kolvo++;

		//cout << endl;
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
	set <int> s_exp;
	set <int> s_clique;
	set <int> s_indep;
	for (int i = 0; i < v_sv.size(); i++) {
		s_sv.insert(v_sv[i]);
		s_komp.insert(v_komp[i]);
		s_obh.insert(v_obh[i]);
		s_treo.insert(v_treo[i]);
		s_rad.insert(v_rad[i]);
		s_diam.insert(v_diam[i]);
		s_duo.insert(v_duo[i]);
		s_m.insert(v_m[i]);
		s_exp.insert(v_exp[i]);
		s_clique.insert(v_clique[i]);
		s_indep.insert(v_indep[i]);

	}

	double end_time = clock();
	cout << "Время инициализации: " << (end_time - start_time) / CLOCKS_PER_SEC << endl;

	set <int>::iterator it1, it2, it3, it4, it5, it6, it7, it8, it9, it10;
	int t = 0;
	long long invar_cnt = s_sv.size() * s_komp.size() * s_obh.size() * s_treo.size() *
		s_rad.size() * s_diam.size() * s_duo.size() * s_m.size() * s_exp.size() * s_clique.size() * s_indep.size();
	cout << "Ожидаемое колличество комбинаций инвариантов: " << invar_cnt << endl;
	cout << "Ожидаемое колличество операций: " << invar_cnt * kolvo << endl;

	start_time = clock();   // Время основного обхода
	map<vector<int>, int> klass;
	for (int k = 0; k < kolvo; k++) {
		for (it1 = s_komp.begin(); it1 != s_komp.end(); it1++) {
			if (v_komp[k] != *it1)
				continue;
			for (it2 = s_m.begin(); it2 != s_m.end(); it2++) {
				if (v_m[k] != *it2)
					continue;
				for (it3 = s_obh.begin(); it3 != s_obh.end(); it3++) {
					if (v_obh[k] != *it3)
						continue;
					for (it4 = s_treo.begin(); it4 != s_treo.end(); it4++) {
						if (v_treo[k] != *it4)
							continue;
						for (it5 = s_duo.begin(); it5 != s_duo.end(); it5++) {
							if (v_duo[k] != *it5)
								continue;
							for (it6 = s_rad.begin(); it6 != s_rad.end(); it6++) {
								if (v_rad[k] != *it6)
									continue;
								for (it7 = s_diam.begin(); it7 != s_diam.end(); it7++) {
									if (v_diam[k] != *it7)
										continue;
									for (it8 = s_exp.begin(); it8 != s_exp.end(); it8++) {
										if (v_exp[k] != *it8)
											continue;
										for (it9 = s_clique.begin(); it9 != s_clique.end(); it9++) {
											if (v_clique[k] != *it9)
												continue;
											for (it10 = s_indep.begin(); it10 != s_indep.end(); it10++) {
												if (v_indep[k] != *it10)
													continue;
												vector<int> combo = { *it1, *it2, *it3, *it4,  *it5, *it6, *it7, *it8, *it9, *it10 };
												klass[combo]++;
											}
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	end_time = clock();
	double optim_time = end_time - start_time;
	start_time = clock();
	end_time = clock();

	cout << "Ответ: " << klass.size() << endl;
	cout << "Время: " << (optim_time) / CLOCKS_PER_SEC << endl;
	system("pause");
	return 0;

	//vector <int> klass;
	//unsigned int start_time = clock();
	//set <int>::iterator it1, it2, it3, it4, it5, it6, it7, it8, it9, it10;
	//int t = 0;
	//for (it1 = s_komp.begin(); it1 != s_komp.end(); it1++)
	//	for (it2 = s_m.begin(); it2 != s_m.end(); it2++)
	//		for (it3 = s_obh.begin(); it3 != s_obh.end(); it3++)
	//			for (it4 = s_treo.begin(); it4 != s_treo.end(); it4++)
	//				for (it5 = s_duo.begin(); it5 != s_duo.end(); it5++)
	//					for (it6 = s_rad.begin(); it6 != s_rad.end(); it6++)
	//						for (it7 = s_diam.begin(); it7 != s_diam.end(); it7++)
	//							for (it8 = s_exp.begin(); it8 != s_exp.end(); it8++)
	//								for (it9 = s_clique.begin(); it9 != s_clique.end(); it9++)
	//									for (it10 = s_indep.begin(); it10 != s_indep.end(); it10++)

	//						{
	//							for (int k = 0; k < kolvo; k++) {
	//								if (v_komp[k] == *it1 && v_m[k] == *it2 && v_obh[k] == *it3 && v_treo[k] == *it4 &&
	//									v_duo[k] == *it5 && v_rad[k] == *it6 && v_diam[k] == *it7 &&  v_exp[k] == *it8 &&
	//									v_clique[k] == *it9 && v_indep[k] == *it10)
	//									t++;
	//							}
	//							if (t != 0) klass.push_back(t);
	//							t = 0;
	//						}
	//unsigned int end_time = clock();
	//unsigned int search_time = end_time - start_time;
	//cout << klass.size();
	//cout << endl << (float(search_time)) / CLOCKS_PER_SEC;

}

