#include <iostream> 
#include <fstream> 
#include <vector> 
#include <algorithm>
#include <map>
#include <set>
#include <queue>
#include <string> 

using namespace std;

int main() {
	setlocale(LC_ALL, "Russian");
	int n = 1044;
	int a, b, tmp;
	//ifstream in_diam("diam7.txt");
	ifstream in_duo("duo7.txt");
	//ifstream in_komp("komp7.txt");
	//ifstream in_obh("obh7.txt");
	//ifstream in_rad("rad7.txt");
	//ifstream in_sv("sv7.txt");
	ifstream in_clique("clique7.txt");
	//ifstream in_treo("treo7.txt");
	ifstream in_exp("exp7.txt");
	ifstream in_indep("indep7.txt");
	map <int, int> m_sv;
	map <int, int> m_komp;
	map <int, int> m_obh;
	map <int, int> m_treo;
	map <int, int> m_rad;
	map <int, int> m_diam;
	map <int, int> m_duo;
	map <int, int> m_exp;
	map <int, int> m_clique;
	map <int, int> m_indep;

	for (int i = 0; i < n; i++) {
		//in_diam >> tmp; m_diam[tmp]++;
		in_duo >> tmp; m_duo[tmp]++;
		//in_komp >> tmp; m_komp[tmp]++;
		//in_obh >> tmp; m_obh[tmp]++;
		//in_rad >> tmp; m_rad[tmp]++;
		//in_sv >> tmp; m_sv[tmp]++;
		//in_treo >> tmp; m_treo[tmp]++;
		in_exp >> tmp; m_exp[tmp]++;
		in_clique >> tmp; m_clique[tmp]++;
		in_indep >> tmp; m_indep[tmp]++;
	}

	map <int, int>::iterator it;
	/*cout << "Связность:" << endl;
	for (it = m_sv.begin(); it != m_sv.end(); it++) 
		cout << (*it).first << ' ' << (*it).second << endl;
	cout << "Компоненты связности:" << endl;
	for (it = m_komp.begin(); it != m_komp.end(); it++)
		cout << (*it).first << ' ' << (*it).second << endl;
	cout << "Обхват" << endl;
	for (it = m_obh.begin(); it != m_obh.end(); it++)
		cout << (*it).first << ' ' << (*it).second << endl;
	cout << "Диаметр" << endl;
	for (it = m_diam.begin(); it != m_diam.end(); it++)
		cout << (*it).first << ' ' << (*it).second << endl;
	cout << "Радиус" << endl;
	for (it = m_rad.begin(); it != m_rad.end(); it++)
		cout << (*it).first << ' ' << (*it).second << endl;
	cout << "Треугольники" << endl;
	for (it = m_treo.begin(); it != m_treo.end(); it++)
		cout << (*it).first << ' ' << (*it).second << endl;*/
	cout << "Двудольность" << endl;
	for (it = m_duo.begin(); it != m_duo.end(); it++)
		cout << (*it).first << ' ' << (*it).second << endl;
	cout << "Экспонент" << endl;
	for (it = m_exp.begin(); it != m_exp.end(); it++)
		cout << (*it).first << ' ' << (*it).second << endl;
	cout << "Клика" << endl;
	for (it = m_clique.begin(); it != m_clique.end(); it++)
		cout << (*it).first << ' ' << (*it).second << endl;
	cout << "Независимость" << endl;
	for (it = m_indep.begin(); it != m_indep.end(); it++)
		cout << (*it).first << ' ' << (*it).second << endl;
		system("pause");
		return 0;

}