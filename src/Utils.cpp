#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace PolyhedralLibrary
{
	void BuildPolyhedron(PolyhedralMesh& mesh, int p, int q)
	{	
		const double phi = (1+sqrt(5))/2; 
		// tetraedro
		if(p==3 && q==3)
		{

			mesh.NumCell0Ds = 4;
			mesh.Cell0DsId.resize(mesh.NumCell0Ds);

			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++)
			{
				mesh.Cell0DsId[i] = i;
			}

			mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(mesh.NumCell0Ds, 3);
			mesh.Cell0DsCoordinates <<
				1,1,1,
				-1,-1,1,
				-1,1,-1,
				1,-1,-1;	
				
			mesh.Cell0DsCoordinates /= sqrt(3);

			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++)
				mesh.Cell0DsMarker[1].push_back(mesh.Cell0DsId[i]);

			for(int i = 0; i < mesh.NumCell0Ds; i++)
				cout << mesh.Cell0DsMarker[1][i] << endl;


			//cell1Ds

			mesh.NumCell1Ds = 6;
			mesh.Cell1DsId.resize(mesh.NumCell1Ds);

			for(unsigned int i = 0; i < mesh.NumCell1Ds; i++)
			{
				mesh.Cell1DsId[i] = i;
			}
			mesh.Cell1DsExtrema = Eigen::MatrixXi::Zero(mesh.NumCell1Ds, 2);
			mesh.Cell1DsExtrema << 
			0, 1,
			0, 2,
			0, 3,
			1, 2, 
			1, 3,
			2, 3;

			//Cell2Ds
			mesh.NumCell2Ds = 4;

			mesh.Cell2DsId.resize(mesh.NumCell2Ds);
			for(unsigned int i = 0; i < mesh.NumCell2Ds; i++)
			{
				mesh.Cell2DsId[i] = i;
			}

			mesh.Cell2DsVertices.resize(mesh.NumCell2Ds);
			mesh.Cell2DsVertices[0] = {0, 1, 2};
			mesh.Cell2DsVertices[1] = {0, 3, 1};
			mesh.Cell2DsVertices[2] = {0, 2, 3};
			mesh.Cell2DsVertices[3] = {1, 3, 2};

			mesh.Cell2DsEdges.resize(mesh.NumCell2Ds);
			mesh.Cell2DsEdges[0]    = {0, 3, 1};
			mesh.Cell2DsEdges[1]    = {2, 4, 0};
			mesh.Cell2DsEdges[2]    = {1, 5, 2};
			mesh.Cell2DsEdges[3]    = {4, 5, 3};
					

			

		}

		
		
		// nel caso di ottaedro o cubo li tratto nello stesso modo, cioè come un ottaedro
		// ottaedro
		if((p==3 && q==4) || (p==4 && q==3))
		{
			mesh.NumCell0Ds = 6;
			mesh.Cell0DsId.resize(mesh.NumCell0Ds);

			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++)
			{
				mesh.Cell0DsId[i] = i;
			}

			mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(mesh.NumCell0Ds, 3);
			mesh.Cell0DsCoordinates <<
				0,0,1,
				1,0,0,
				0,1,0,
				-1,0,0,
				0,-1,0,
				0,0,-1;	
			
			// ce
			
			mesh.NumCell1Ds = 12;
			mesh.Cell1DsId.resize(mesh.NumCell1Ds);

			for(unsigned int i = 0; i < mesh.NumCell1Ds; i++)
			{
				mesh.Cell1DsId[i] = i;
			}

			mesh.Cell1DsExtrema = Eigen::MatrixXi::Zero(mesh.NumCell1Ds,2);
			mesh.Cell1DsExtrema << 
			0, 1,
			0, 2,
			0, 3,
			0, 4,
			5, 1,
			5, 2,
			5, 3,
			5, 4,
			1, 2,
			2, 3,
			3, 4,
			4, 1;

			//Cell2Ds
			mesh.NumCell2Ds = 8;

			mesh.Cell2DsId.resize(mesh.NumCell2Ds);
			for(unsigned int i = 0; i < mesh.NumCell2Ds; i++)
			{
				mesh.Cell2DsId[i] = i;
			}
				
			mesh.Cell2DsVertices.resize(mesh.NumCell2Ds);
			mesh.Cell2DsVertices[0] = {0,1,2};  
			mesh.Cell2DsVertices[1] = {0,2,3};  
			mesh.Cell2DsVertices[2] = {0,3,4};  
			mesh.Cell2DsVertices[3] = {0,4,1};  
			mesh.Cell2DsVertices[4] = {5,2,1};
			mesh.Cell2DsVertices[5] = {5,3,2};  
			mesh.Cell2DsVertices[6] = {5,4,3};  
			mesh.Cell2DsVertices[7] = {5,1,4};  

			mesh.Cell2DsEdges.resize(mesh.NumCell2Ds);
			mesh.Cell2DsEdges[0] = {0, 8, 1};
			mesh.Cell2DsEdges[1] = {1, 9, 2};
			mesh.Cell2DsEdges[2] = {2,10, 3};
			mesh.Cell2DsEdges[3] = {3,11, 0};
			mesh.Cell2DsEdges[4] = {5, 8, 4};
			mesh.Cell2DsEdges[5] = {6, 9, 5};
			mesh.Cell2DsEdges[6] = {7,10, 6};
			mesh.Cell2DsEdges[7] = {4,11, 7};


		}
		
		// nel caso di icosaedro o dodecaedro li tratto nello stesso modo, cioè come un icosaedro
		//icosaedro
		if((p==3 && q==5) || (p==5 && q==3))
		{
			mesh.NumCell0Ds = 12;
			mesh.Cell0DsId.resize(mesh.NumCell0Ds);

			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++)
			{
				mesh.Cell0DsId[i] = i;
			}

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

			// cell1Ds

			mesh.NumCell1Ds = 30;
			mesh.Cell1DsId.resize(mesh.NumCell1Ds);

			for(unsigned int i = 0; i < mesh.NumCell1Ds; i++)
			{
				mesh.Cell1DsId[i] = i;
			}

			mesh.Cell1DsExtrema = Eigen::MatrixXi::Zero(mesh.NumCell1Ds,2);
			mesh.Cell1DsExtrema << 
			0,  1,
			0,  2,
			0,  4,
			0,  5,
			1,  2,
			1,  6,
			1,  5,
			2,  3,
			2,  9,
			3,  4,
			3,  9,
			3,  8,
			4,  8,
			4,  5,
			5,  7,
			6,  7,
			6, 10,
			6,  1,
			7, 10,
			7,  5,
			8,  9,
			8, 11,
			9, 11,
			10, 11,
			10,  6,
			11,  2,
			11,  3,
			10,  7,
			8,  4;

			//Cell2Ds
			mesh.NumCell2Ds = 20;

			mesh.Cell2DsId.resize(mesh.NumCell2Ds);
			for(unsigned int i = 0; i < mesh.NumCell2Ds; i++)
			{
				mesh.Cell2DsId[i] = i;
			}
			
			mesh.Cell2DsVertices.resize(mesh.NumCell2Ds);
			mesh.Cell2DsVertices[0] = {0, 1, 2};
			mesh.Cell2DsVertices[1] = {0, 2, 3};
			mesh.Cell2DsVertices[2] = {0, 3, 4};
			mesh.Cell2DsVertices[3] = {0, 4, 5};
			mesh.Cell2DsVertices[4] = {0, 5, 1};
			mesh.Cell2DsVertices[5] = {1, 6, 2};
			mesh.Cell2DsVertices[6] = {2, 6, 9};
			mesh.Cell2DsVertices[7] = {2, 9, 3};
			mesh.Cell2DsVertices[8] = {3, 9, 8};
			mesh.Cell2DsVertices[9] = {3, 8, 4};
			mesh.Cell2DsVertices[10] = {4, 8, 5};
			mesh.Cell2DsVertices[11] = {5, 8, 7};
			mesh.Cell2DsVertices[12] = {5, 7, 1};
			mesh.Cell2DsVertices[13] = {1, 7, 6};
			mesh.Cell2DsVertices[14] = {6,10, 9};
			mesh.Cell2DsVertices[15] = {9,10,11};
			mesh.Cell2DsVertices[16] = {9,11, 3};
			mesh.Cell2DsVertices[17] = {11,8, 3};
			mesh.Cell2DsVertices[18] = {11,10,8};
			mesh.Cell2DsVertices[19] = {10, 7,8};

			
			mesh.Cell2DsEdges.resize(mesh.NumCell2Ds);
			mesh.Cell2DsEdges[0] = {0, 4, 1};
			mesh.Cell2DsEdges[1] = {1, 7,11};
			mesh.Cell2DsEdges[2] = {11, 9, 2};
			mesh.Cell2DsEdges[3] = {2,13, 3};
			mesh.Cell2DsEdges[4] = {3, 6, 0};
			mesh.Cell2DsEdges[5] = {5,17, 4};
			mesh.Cell2DsEdges[6] = {5,16, 8};
			mesh.Cell2DsEdges[7] = {8,10, 7};
			mesh.Cell2DsEdges[8] = {10,20,11};
			mesh.Cell2DsEdges[9] = {11,12, 9};
			mesh.Cell2DsEdges[10] = {12,28,13};
			mesh.Cell2DsEdges[11] = {28,19,14};
			mesh.Cell2DsEdges[12] = {14,15, 6};
			mesh.Cell2DsEdges[13] = {15,18, 5};
			mesh.Cell2DsEdges[14] = {16,24,22};
			mesh.Cell2DsEdges[15] = {24,23,22};
			mesh.Cell2DsEdges[16] = {22,26,10};
			mesh.Cell2DsEdges[17] = {21,11,26};
			mesh.Cell2DsEdges[18] = {23,27,21};
			mesh.Cell2DsEdges[19] = {27,18,19};


		}
		
		
	}
	/*
	bool BuildCell0Ds(PoliedralMesh& mesh, int p, int q, int b, int c)
	{
		mesh.Cell0DsId.reserve(mesh.NumCell0Ds);
		
		mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(3, mesh.NumCell0Ds);
		
	}*/
	
	
	
	
	
}