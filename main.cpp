#include <cmath>
#include <iostream>
#include <numeric>
#include <sstream>
#include <set>
#include <tuple>
#include "Utils.hpp"
#include "UCDUtilities.hpp"
#include "PolyhedralMesh.hpp"

using namespace std;
using namespace PolyhedralLibrary;

int main(int argc, char *argv[])
{
    int p;
	int q;
	int b;
	int c;
	int id_origin;
	int id_end;
	
	set<tuple<int, int>> set_valid_pq = {
		{3,3}, {3,4}, {3,5}, {4,3}, {5,3}
	};
	
	
    if(argc == 5)
    {
		p = stoi(argv[1]);
		q = stoi(argv[2]);
		b = stoi(argv[3]);
		c = stoi(argv[4]);
		
		tuple<int, int> tuple_pq = {p,q};
		
		/* Cerchiamo la coppia (p,q), se presente, nel set dei valori validi.
		   Iteriamo con un iteratore sugli elementi del set e se la tupla (p,q)
		   non è salvata nel set stampa "Invalid input" */
		
		if(auto iter = set_valid_pq.find(tuple_pq); iter == set_valid_pq.end()) {
			cerr << "Invalid input: error in p,q" << endl;
			return 1;
		}
		
		
		
		// Controllo sulla validità di b e c secondo le condizioni richieste
		
		if(!(b == c || b == 0 || c == 0)) {
			cerr << "Invalid input: error in b,c" << endl;
			return 2;
		}
		
		// Se b == c o b == 0 o c == 0, non entra nell'if precedente e continua con il codice
		
		if(!(b > 0 || c > 0)){
			cerr << "Invalid input: error in b,c" << endl;
			return 3;
		}
			
        
    }
    else if(argc==7)
	{
		p = stoi(argv[1]);
		q = stoi(argv[2]);
		b = stoi(argv[3]);
		c = stoi(argv[4]);
		id_origin = stoi(argv[5]);
		id_end = stoi(argv[6]);
		
		tuple<int, int> tuple_pq = {p,q};
		
		/* Cerchiamo la coppia (p,q), se presente, nel set dei valori validi.
		   Iteriamo con un iteratore sugli elementi del set e se la tupla (p,q)
		   non è salvata nel set stampa "Invalid input" */
		
		if(auto iter = set_valid_pq.find(tuple_pq); iter == set_valid_pq.end()) {
			cerr << "Invalid input: error in p,q" << endl;
			return 4;
		}
		
		
		// Controllo sulla validità di b e c secondo le condizioni richieste
		
		if(!(b == c || b == 0 || c == 0)) {
			cerr << "Invalid input: error in b,c" << endl;
			return 5;
		}
		
		// Se b == c o b == 0 o c == 0, non entra nell'if precedente e continua con il codice
		
		if(!(b > 0 || c > 0)) {
			cerr << "Invalid input: error in b,c" << endl;
			return 6;
		}
		
		
		
		// DA FARE ANCORA CONTROLLO SU ID_ORIGIN E END CONTROLLANDO CHE SIANO ID DISPONIBILI (ABBIAMO GIA p,q,b,c)
        
    }
	else
	{
        cerr << "Invalid input: invalid number of elements"  << endl;
		return 7;
	}
	
	PolyhedralMesh mesh;
	BuildPolyhedron(mesh, p, q);
	
	Triangulation_I(mesh, b, c);
	
	/*for(unsigned int i=0; i < mesh.NumCell0Ds; i++) {
		for(unsigned int j=0; j <3; j++)
			cout << mesh.Cell0DsCoordinates(i,j) << " ";
		cout << endl;
	}
	unsigned int count = 0;
	for(auto iter=mesh.Cell1DsMarker[2].begin(); iter !=mesh.Cell1DsMarker[2].end(); iter++)
		count++;
	cout << "count "<< count << endl;
	
	for(unsigned int i = 0; i<mesh.NumCell1Ds; i++)
		cout << mesh.Cell1DsExtrema(i, 0) << ", " << mesh.Cell1DsExtrema(i, 1) << endl;*/
	
	 // Visual test 
    Gedim::UCDUtilities utilities;
    utilities.ExportPoints("./Cell0Ds.inp",
                           mesh.Cell0DsCoordinates);

    utilities.ExportSegments("./Cell1Ds.inp",
                             mesh.Cell0DsCoordinates,
                             mesh.Cell1DsExtrema);

	
	return 0;
}