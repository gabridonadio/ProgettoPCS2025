#pragma once
#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;


namespace PolyhedralLibrary {
	struct PolyhedralMesh
	{
		unsigned int NumCell0Ds;
		unsigned int NumCell1Ds;
		unsigned int NumCell2Ds;
		
		vector<unsigned int> Cell0DsId;
		vector<unsigned int> Cell1DsId;
		vector<unsigned int> Cell2DsId;
		vector<unsigned int> Cell3DsId = {0};
		
		map<unsigned int,vector<unsigned int>> Cell0DsMarker;
		map<unsigned int,vector<unsigned int>> Cell1DsMarker;
		map<unsigned int,vector<unsigned int>> Cell2DsMarker;
		
		MatrixXd Cell0DsCoordinates;
		MatrixXi Cell1DsExtrema;
		vector<vector<unsigned int>> Cell2DsVertices;
		vector<vector<unsigned int>> Cell2DsEdges;
		
		
		vector<double> VerticesShortestPath;
		vector<double> EdgesShortestPath;
	};
}