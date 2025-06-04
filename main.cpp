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
	
	Triangulation_I(mesh, p, q, b, c);
	
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
	
	for (unsigned int i=0; i<mesh.NumCell0Ds; i++)
	{
		double norma = mesh.Cell0DsCoordinates.row(i).norm();
		mesh.Cell0DsCoordinates(i,0) /= norma;
		mesh.Cell0DsCoordinates(i,1) /= norma;
		mesh.Cell0DsCoordinates(i,2) /= norma;
	}
	 
	unsigned int T = b*b + b*c + c*c;
	unsigned int V;
	unsigned int E;
	unsigned int F;
	unsigned int E_initial;	
	if(p==3 && q==3)
		{
			V = 2*T + 2;
			E = 6*T;
			F = 4*T;
			E_initial = 6;
			
		}
		
		if((p==3 && q==4)||(p==4 && q==3))
		{
			V = 4*T + 2;
			E = 12*T;
			F = 8*T;
			E_initial = 12;
		}
		
		if((p==3 && q==5)||(p==5 && q==3))
		{
			V = 10*T + 2;
			E = 30*T;
			F = 20*T;
			E_initial = 30;
		}
		
	PolyhedralMesh dual;
	if(b!=1)
		Dual(mesh, dual, E_initial, F/T);
	else
		Dual(mesh, dual, 0, 0);
	
	Gedim::UCDUtilities utilities;
	Eigen::MatrixXd points = mesh.Cell0DsCoordinates.topRows(mesh.NumCell0Ds).transpose();
	Eigen::MatrixXi segments;
	if(b!=1)
	{
		segments = mesh.Cell1DsExtrema.bottomRows(dual.Cell1DsExtrema.rows()-E_initial).transpose();
	}
	else
	{
		segments = mesh.Cell1DsExtrema.bottomRows(dual.Cell1DsExtrema.rows()).transpose();
	}
	utilities.ExportPoints("./Cell0Ds.inp", points);

	utilities.ExportSegments("./Cell1Ds.inp", points, segments);

	
	return 0;
}