#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace PolyhedralLibrary
{
	void ChoosePoly(PolyhedralMesh& mesh, int p, int q)
	{	
		const double phi = (1+sqrt(5))/2; 
		// tetraedro
		if(p==3 && q==3)
		{
			mesh.NumCell0Ds = 4;
			mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(mesh.NumCell0Ds, 3);
			mesh.Cell0DsCoordinates <<
				1,1,1,
				-1,-1,1,
				-1,1,-1,
				1,-1,-1;	
				
			mesh.Cell0DsCoordinates /= sqrt(3);
		}
		
		// nel caso di ottaedro o cubo li tratto nello stesso modo, cioè come un ottaedro
		// ottaedro
		if((p==3 && q==4) || (p==4 && q==3))
		{
			mesh.NumCell0Ds = 6;
			mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(mesh.NumCell0Ds, 3);
			mesh.Cell0DsCoordinates <<
				0,0,1,
				1,0,0,
				0,1,0,
				-1,0,0,
				0,-1,0,
				0,0,-1;	
				
		}
		
		// nel caso di icosaedro o dodecaedro li tratto nello stesso modo, cioè come un icosaedro
		//icosaedro
		if((p==3 && q==5) || (p==5 && q==3))
		{
			mesh.NumCell0Ds = 12;
			mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(mesh.NumCell0Ds, 3);
			mesh.Cell0DsCoordinates <<
				0,1,phi,
				0,-1,phi,
				-phi,0,1,
				-1,phi,0,
				1,phi,0,
				phi,0,1,
				1,-phi,0,
				phi,0,-1,
				0,1,-phi,
				-phi,0,-1,
				0,-1,-phi,
				-1,-phi,0;	
				
			mesh.Cell0DsCoordinates /= sqrt(1+phi*phi);
		}
		
		
	}
	/*
	bool BuildCell0Ds(PoliedralMesh& mesh, int p, int q, int b, int c)
	{
		mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
		
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
	}*/
	
	
	
	
	
}