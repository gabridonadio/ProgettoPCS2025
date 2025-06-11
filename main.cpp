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
    }
	else
	{
        cerr << "Invalid input: invalid number of elements"  << endl;
		return 7;
	}
	
	if(b == c)
	{
		cerr << "Class II not available" << endl;
		return 8;
	}
	
	unsigned int T = b*b + b*c + c*c;
	unsigned int V;
	unsigned int E;
	unsigned int F;
	unsigned int E_initial;	
	unsigned int F_initial;

	if(p==3 && q==3)
		{
			V = 2*T + 2;
			E = 6*T;
			F = 4*T;
			E_initial = 6;
			F_initial = 4;
		}
		
		if((p==3 && q==4)||(p==4 && q==3))
		{
			V = 4*T + 2;
			E = 12*T;
			F = 8*T;
			E_initial = 12;
			F_initial = 8; 
		}
		
		if((p==3 && q==5)||(p==5 && q==3))
		{
			V = 10*T + 2;
			E = 30*T;
			F = 20*T;
			E_initial = 30;
			F_initial = 20;
		}
		
	PolyhedralMesh mesh;
	BuildPolyhedron(mesh, p, q);
	if(max(b,c) != 1)
		Triangulation_I(mesh, p, q, b, c);
	
	Gedim::UCDUtilities utilities;
	
	vector<Gedim::UCDProperty<double>> VShortestPath;
	vector<Gedim::UCDProperty<double>> EShortestPath;
	
	if(p == 3)
	{
		if(argc == 7)
		{		
			if(id_origin < 0 || id_origin >= mesh.NumCell0Ds || id_end < 0 || id_end >= mesh.NumCell0Ds)
			{
				cerr << "Invalid input: error in id_origin or id_end" << endl;
				return 9;
			}
			
			if(max(b,c)!=1)
			{
				ShortestPath(mesh, id_origin, id_end, E_initial);
			}
			else if(max(b,c)==1)
			{
				E_initial = 0;
				ShortestPath(mesh, id_origin, id_end, E_initial);
			}
			
			VShortestPath.resize(1);
			VShortestPath[0].Label = "VerticesShortestPath";
			VShortestPath[0].UnitLabel = "Id";
			VShortestPath[0].Size = mesh.NumCell0Ds;
			VShortestPath[0].NumComponents = 1;
			VShortestPath[0].Data=mesh.VerticesShortestPath.data();

			EShortestPath.resize(1);
			EShortestPath[0].Label = "EdgesShortestPath";
			EShortestPath[0].UnitLabel = "Id";
			EShortestPath[0].Size = mesh.NumCell1Ds;
			EShortestPath[0].NumComponents = 1;
			EShortestPath[0].Data=mesh.EdgesShortestPath.data();
		}
		
		// proietto sulla sfera
		SphereProjection(mesh);
		
		Eigen::MatrixXd points = mesh.Cell0DsCoordinates.topRows(mesh.NumCell0Ds).transpose();
		Eigen::MatrixXi segments;
		if(max(b,c)!=1)
		{
			segments = mesh.Cell1DsExtrema.bottomRows(mesh.Cell1DsExtrema.rows()-E_initial).transpose();
		}
		else
		{
			segments = mesh.Cell1DsExtrema.bottomRows(mesh.Cell1DsExtrema.rows()).transpose();
		}
		
		if(argc == 7)
		{
			utilities.ExportPoints("./Cell0Ds.inp", points, VShortestPath);
			utilities.ExportSegments("./Cell1Ds.inp", points, segments, {}, EShortestPath);
		}
		else
		{
			utilities.ExportPoints("./Cell0Ds.inp", points);
			utilities.ExportSegments("./Cell1Ds.inp", points, segments);
		}
		if(max(b,c)!=1)
		{
			ExportMesh(mesh, "./mesh_", E_initial, F_initial);
		}
		else
		{
			E_initial = 0;
			F_initial = 0;
			ExportMesh(mesh, "./mesh_", E_initial, F_initial);
		}
	}
	else
	{
		PolyhedralMesh dual;
		
		if(max(b,c)!=1)
			Dual(mesh, dual, E_initial, F/T);
		else
			Dual(mesh, dual, 0, 0);
		
		if(argc == 7)
		{		
			if(id_origin < 0 || id_origin >= dual.NumCell0Ds || id_end < 0 || id_end >= dual.NumCell0Ds)
			{
				cerr << "Invalid input: error in id_origin or id_end" << endl;
				return 9;
			}
			
			if(max(b,c)!=1)
			{
				ShortestPath(dual, id_origin, id_end, 0);
			}
			else if(max(b,c)==1)
			{
				E_initial = 0;
				ShortestPath(dual, id_origin, id_end, E_initial);
			}
			
			VShortestPath.resize(1);
			VShortestPath[0].Label = "VerticesShortestPath";
			VShortestPath[0].UnitLabel = "Id";
			VShortestPath[0].Size = dual.NumCell0Ds;
			VShortestPath[0].NumComponents = 1;
			VShortestPath[0].Data=dual.VerticesShortestPath.data();

			EShortestPath.resize(1);
			EShortestPath[0].Label = "EdgesShortestPath";
			EShortestPath[0].UnitLabel = "Id";
			EShortestPath[0].Size = dual.NumCell1Ds;
			EShortestPath[0].NumComponents = 1;
			EShortestPath[0].Data=dual.EdgesShortestPath.data();
		}
		
		// proietto sulla sfera
		SphereProjection(dual);
		
		Eigen::MatrixXd points = dual.Cell0DsCoordinates.topRows(dual.NumCell0Ds).transpose();
		Eigen::MatrixXi segments;
		segments = dual.Cell1DsExtrema.bottomRows(dual.Cell1DsExtrema.rows()).transpose();
		
		if(argc == 7)
		{
			utilities.ExportPoints("./Cell0Ds.inp", points, VShortestPath);
			utilities.ExportSegments("./Cell1Ds.inp", points, segments, {}, EShortestPath);
		}
		else
		{
			utilities.ExportPoints("./Cell0Ds.inp", points);
			utilities.ExportSegments("./Cell1Ds.inp", points, segments);
		}
		
		E_initial = 0;
		F_initial = 0;
		ExportMesh(dual, "./dual_", E_initial, F_initial);
	}
	return 0;
}