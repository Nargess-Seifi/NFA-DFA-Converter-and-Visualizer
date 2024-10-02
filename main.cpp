#include <bits/stdc++.h>
#include "vis.h"
using namespace std;

set<string> uniooon(set<string> s1, set<string> s2){
	s1.insert(s2.begin(), s2.end());
	return s1;
}

class DFA{
	private:
		bool isStart(string q){
			return (q==S);
		}
		
		bool isFinal(string q){
			return (F.find(q)!=F.end());
		}
		
		
		bool dfs(string q, string s){
			if(s=="")
				return isFinal(q);
			if(Sigma.find(s[0])==Sigma.end()) return false;
			
			string q2 = del[{q, s[0]}];
			string s2 = s.substr(1, s.length()-1);
			return dfs(q2, s2);
		}	
		
		bool done(set<set<string> > s, map<string, int> cmp){
			for(set<string> t : s){
				set<vector<int> > st;
				for(string q : t){
					vector<int> v;
					for(char c : Sigma)
						v.push_back(cmp[del[{q, c}]]);
					st.insert(v);
				}
				if(st.size()>1) return false;
			}
			return true;
		}
		
		bool done(set<string> t, map<string, int> cmp, set<vector<int> >&st, map<string, vector<int> >& mp){
			st.clear();
			mp.clear();
			for(string q : t){
				vector<int> v;
				for(char c : Sigma)
					v.push_back(cmp[del[{q, c}]]);
				mp[q] = v;
				st.insert(v);
			}
			if(st.size()>1) return false;
			return true;
		}
		
		public: map<string, int> cmp(set<set<string> > myset){
			map<string , int> m;
			int comp = 0;
			for(set<string> s : myset){
				for(string t : s)
					m[t] = comp;
				comp++;
			}
			return m;
		}
		
		
			
	public:
		set <string> Q;
		set <char> Sigma;
		set <string> F;
		string S;
		map <pair<string, char>, string> del; //transition function, <state, input> --> state
	
		DFA(set<string> q, set<char> sigma, string s,  set <string> f){
			//constructor
			Q = q;
			Sigma = sigma;
			F = f;
			S = s;
		}
		
		void addTransition (string q1, char c, string q2){
			del[{q1, c}] = q2;
		}	
		
		
		
		bool isAcceptByDFA(string s){
			return dfs(S, s);
		}
		
		
		DFA makeSimpleDFA(){
			set<string> QQ = Q;
			set<string> FF;
			string SS;
			
			
			map<string, int> comp;
			set<set<string>> myset;
			
			set<string> temp[2];
			for(string q : Q)
				temp[this->isFinal(q)].insert(q);
			myset.insert(temp[0]);
			myset.insert(temp[1]);
			
			
			while(!done(myset, cmp(myset))){
				for(set<string> s : myset){
					set<vector<int> > st;
					map<string, vector<int> > mp;
					if(!done(s, cmp(myset), st, mp)){
						for(vector<int> v: st){
							set<string> tmp;
							for(string q: s)
								if(mp[q]==v)
									tmp.insert(q);
							myset.insert(tmp);
						}
						myset.erase(s);
						break;
					}
				}
			}
			
			map <string, int> finalcomp = cmp(myset);
			map <string, string> newnames;
			QQ = Q;
			
			for(string q : QQ){
				newnames[q] = q;
				if(this->isStart(q)) SS = q;
				for(string p : QQ)
					if(p!=q && finalcomp[p]==finalcomp[q]){
						QQ.erase(p);
						newnames[p] = q;
						if(this->isStart(p))
							SS = q;
					}
			}
			for(string q : QQ)
				if(this->isFinal(newnames[q]))
					FF.insert(newnames[q]);
			
			DFA d(QQ, Sigma, SS, FF);
			for(string q : QQ)
				for(char c : Sigma)
				d.addTransition(q, c, newnames[del[{q, c}]]);
			
			return d;
		}
		
	
	
	void showSchematicDFA(){
		vector<pair<int, char>> arr[this->Q.size()];
		map<string, int> index;
		vector<string> v;
		for(string q : this->Q){
			index[q] = v.size();
			v.push_back(q);
		}
		
	
		getNames(v, F);	
		
		for(int i = 0; i < v.size(); i++){
			for(char c : this->Sigma){
				addEdge(arr, i, index[this->del[{v[i], c}]], c);
			}
		}	
		
		int gd=DETECT,gm;
	    initgraph(&gd, &gm, ""); //or  "C:\\TC\\BGI"
	    diplayGraph(arr,this->Q.size());
	    getch();
	    closegraph();
		
	}
	
};

class NFA{
	private:
		bool isStart(string q){
			return (q==S);
		}
		
		bool isFinal(string q){
			return (F.find(q)!=F.end());
		}
		
		bool dfs(string q, string s){
			bool res = false;
			
			if(s=="")
				return isFinal(q);
			if(Sigma.find(s[0])==Sigma.end()) return false;
			
			string s2 = s.substr(1, s.length()-1);
			for(string q2 : del[{q, s[0]}])
				res|= dfs(q2, s2);
			
			return res;
		}
		
		
		string nextName(set<string> q){
			static int num = 0;
			string name;
			do{
				name = "q" + to_string(num++);
			}while(q.find(name)!=q.end());
			return name;
		}
		
			
	public:
		set <string> Q;
		set <char> Sigma;
		set <string> F;
		string S;
		map <pair<string, char>, set<string> > del;
		
		
		NFA(set<string> q, set<char> sigma, string s,  set <string> f){
			Q = q;
			Sigma = sigma;
			F = f;
			S = s;
		}
		
		
		void addTransition (string q1, char c, string q2){
			del[{q1, c}].insert(q2);
		}
		
		bool isAcceptByNFA(string s){
			return dfs(S, s);
		}
		
	
		
		DFA createEquivalentDFA(){
			
			map< pair<set<string>, char>, set<string> > newdel;
			map<pair<string, char>, set<string> >deldel;
			map<set<string>, string> mp; //set to new name
			map<string, set<string> > mprev; //new name to set
			set<set<string> > QQ;
			set<string> QQQ;
			set<string> FF;
			
			QQ.insert({S});
			while(true){
				bool brkflg = false;
				for(set<string> q : QQ){
//					brkflg = false;
					for(char c : Sigma){
						if(newdel.find({q, c})==newdel.end()){
							set<string> myset;
							for(string p : q){
								myset = uniooon(myset, del[{p, c}]);
							}
							newdel[{q, c}] = myset;
							QQ.insert(myset);							
							brkflg = true;
							break;
						}
					}
					if(brkflg) break;
				}
				if(!brkflg) break;
			}		
			for(set<string> q : QQ){
				string name;
				name = nextName(QQQ);
				
				mp[q] = name;
				mprev[name] = q;
				QQQ.insert(name);
			}
			
			for(set<string> s : QQ)
				for(string f : F)
					if(s.find(f)!=s.end())
						FF.insert(mp[s]);
			
			DFA d(QQQ, Sigma, mp[{S}], FF);			
			
			for(string q : QQQ)
				for(char c : Sigma){
					d.addTransition(q, c, mp[newdel[{mprev[q], c}]]);
				}
	
			return d.makeSimpleDFA();
		}	
		
		
	void showSchematicNFA(){
		vector<pair<int, char>> arr[Q.size()];
		map<string, int> index;
		vector<string> v;
		for(string q : Q){
			index[q] = v.size();
			v.push_back(q);
		}
		
	
		getNames(v, F);	
		
		for(int i = 0; i < v.size(); i++){
			for(char c : Sigma){
				for(string q2: del[{v[i], c}])
					addEdge(arr, i, index[q2], c);
			}
		}	
		
		int gd=DETECT,gm;
	    initgraph(&gd, &gm, "");
	    diplayGraph(arr,Q.size());
	    getch();
	    closegraph();
	
	}
				
};

void printdfa(DFA d){
	cout << "dfa: " << endl;
	for(string q : d.Q)
		cout << q << " ";
	cout << "\n S: " << d.S << endl;
	cout << "F: ";
	for(string f : d.F)
		cout << f << " ";
	cout << "\ndel: " << endl;
	for(string q : d.Q)
		for(char c : d.Sigma)
			cout << q << " " << c << " " << d.del[{q,c}] << endl;
}


set<string> input(string s, string &first){
	set<string> myset;
	size_t pos = 0;
	bool b = true;
	string token;
	s.erase(0,1);
	
	while ((pos = s.find(",")) != string::npos) {
	    token = s.substr(0, pos);
	    if(b){first = token; b = false;}
	    myset.insert(token);
	    s.erase(0, pos+1);
	}
	myset.insert(s.substr(0,s.length()-1));
	return myset;
}


int main(){
	string in, first, tmp, q1, q2, token, s;
	char ch, temp;
	int n;
	
	cin >> in; //Q
	set<string> Q = input(in, first);
	cin >> in; // sigma
	set<char> sigma;
	for(char c : in)
		if(c!=',' && c!='{' && c!='}')
			sigma.insert(c);
	cin >> in; //Finals
	set<string> F = input(in, tmp);
	
	NFA nfa(Q, sigma, first, F);
	
	cin >> n;
	while(n--){
		cin >> in;
		size_t pos = 0;
		pos = in.find(",");
		q1 = in.substr(0, pos);
		in.erase(0, pos+1);
		
		pos = in.find(",");
		q2 = in.substr(0, pos);
		in.erase(0, pos+1);
		
		ch = in[0];
		
		nfa.addTransition(q1, ch, q2);
	}
	
	DFA d({},{},"",{});
	bool made = false;
	
	while(true){
		cout << "0- Exit" << endl;
		cout << "1- is acc by NFA" << endl;
		cout << "2- create equi DFA" << endl;
		cout << "3- show schematic NFA" << endl;
		cout << "4- is acc by DFA" << endl;
		cout << "5- make simple DFA" << endl;
		cout << "6- show schematic DFA" << endl;
		
		int cmnd;
		cin >> cmnd;
		switch(cmnd){
			case 0:
				return 0;
				
			case 1:
				s;
				cin >> s;
				if(nfa.isAcceptByNFA(s)) cout << "YES" << endl;
				else cout << "NO" << endl;
				break;
				
			case 2:
				made = true;
				d = nfa.createEquivalentDFA();
				cout << "done" << endl;
				break;
				
			case 3:
				nfa.showSchematicNFA();
				break;
			
			case 4:
				if(!made) {cout << "no dfa" << endl; break;}
				s;
				cin >> s;
				if(d.isAcceptByDFA(s)) cout << "YES" << endl;
				else cout << "NO" << endl;
				break;
			
			case 5:
				if(!made) {cout << "no dfa" << endl; break;}
				d = d.makeSimpleDFA();
				cout << "done, minimized dfa" << endl;
				break;
			case 6:
				if(!made) {cout << "no dfa" << endl; break;}
				d.showSchematicDFA();
		}
		
	}
	
	return 0;
}
