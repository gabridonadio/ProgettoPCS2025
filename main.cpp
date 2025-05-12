#include <cmath> 
#include <iostream>
#include <numeric> 
#include <iostream>
#include <sstream>
#include <set>
#include <tuple>

using namespace std;

int main(int argc, char *argv[])
{

    cout << "argc: " << argc << endl;
    for(int a = 0; a < argc; a++)
        cout << argv[a] << " ";
    cout << endl;

    unsigned int p;
	unsigned int q;
	unsigned int b;
	unsigned int c;
	unsigned int id_origin;
	unsigned int id_end;
	
	set<tuple<unsigned int, unsigned int>> set_valid_pq = {
		{3,3}, {3,4}, {3,5}, {4,3}, {5,3}
	};
	
	
    if(argc == 5)
    {
		char _;
        istringstream convert(argv[1]);
		convert >> _;
		convert >> p >> q >> b >> c;
		cout << p << " " << q << " " << b << " " << c << endl;
		
		tuple<unsigned int, unsigned int> tuple_pq = {p,q};
		
		/* Cerchiamo la coppia (p,q), se presente, nel set dei valori validi.
		   Iteriamo con un iteratore sugli elementi del set e se la tupla (p,q)
		   non è salvata nel set stampa "Invalid input" */
		
		if(auto iter = set_valid_pq.find(tuple_pq); iter != set_valid_pq.end())
			cerr << "Invalid input" << endl;
		else 
			cout << "ok" << endl;
			
        
    }
    else if(argc==7)
	{
		char _;
        istringstream convert(argv[1]);
		convert >> _;
		convert >> p >> q >> b >> c >> id_origin >> id_end;
		
		tuple<unsigned int, unsigned int> tuple_pq = {p,q};
		
		/* Cerchiamo la coppia (p,q), se presente, nel set dei valori validi.
		   Iteriamo con un iteratore sugli elementi del set e se la tupla (p,q)
		   non è salvata nel set stampa "Invalid input" */
		
		if(auto iter = set_valid_pq.find(tuple_pq); iter != set_valid_pq.end())
			cerr << "Invalid input" << endl;
        
    }
	else
	{
        cerr << "Invalid input"  << endl;
	}
	
	return 0;
}