#pragma once

#include <iostream>
#include <vector>

#include <gtest/gtest.h>
#include "Utils.hpp"

namespace PolyhedralLibrary
{
	// test per la correttezza dei poliedri creati con BuildPolyhedron
	TEST(PolyhedralMeshTest, NoRepeatedVerticesPerFace)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		bool repeated = false;
		unsigned int n=0;
		for(unsigned int i=0; i<mesh.NumCell0Ds; i++)
		{
			if(not repeated)
			{
				for(unsigned int j=0; j<mesh.NumCell2Ds; j++)
				{
					if(not repeated)
					{
						n = 0;
						for(unsigned int k=0; k<3; k++)
						{
							if(mesh.Cell2DsVertices[j][k]==i)
								n++;
							if(n > 1)
								repeated = true;
						}
					}
					else
						break;
				}
			}
			else
				break;
		}
		
		ASSERT_EQ(repeated, false);
		
	}
	
	TEST(PolyhedralMeshTest, NoRepeatedEdgesPerFace)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		bool repeated = false;
		unsigned int n=0;
		for(unsigned int i=0; i<mesh.NumCell1Ds; i++)
		{
			if(not repeated)
			{
				for(unsigned int j=0; j<mesh.NumCell2Ds; j++)
				{
					if(not repeated)
					{
						n = 0;
						for(unsigned int k=0; k<3; k++)
						{
							if(mesh.Cell2DsEdges[j][k]==i)
								n++;
							if(n > 1)
								repeated = true;
						}
					}
					else
						break;
				}
			}
			else
				break;
		}
		
		ASSERT_EQ(repeated, false);
		
	}
	
	// test per la correttezza dei poliedri che derivano da Triangulation_I
	TEST(PolyhedralMeshTest, NoRepeatedVerticesPerFace_Triangulation)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		bool repeated = false;
		unsigned int n;
		for(unsigned int i=0; i<mesh.NumCell0Ds; i++)
		{
			if(not repeated)
			{
				for(unsigned int j=0; j<mesh.NumCell2Ds; j++)
				{
					if(not repeated)
					{
						n = 0;
						for(unsigned int k=0; k<3; k++)
						{
							if(mesh.Cell2DsVertices[j][k]==i)
								n++;
							if(n > 1)
								repeated = true;
						}
					}
					else
						break;
				}
			}
			else
				break;
		}
		
		ASSERT_EQ(repeated, false);
		
	}
	
	TEST(PolyhedralMeshTest, NoRepeatedEdgesPerFace_Triangulation)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		bool repeated = false;
		unsigned int n;
		for(unsigned int i=0; i<mesh.NumCell1Ds; i++)
		{
			if(not repeated)
			{
				for(unsigned int j=0; j<mesh.NumCell2Ds; j++)
				{
					if(not repeated)
					{
						n = 0;
						for(unsigned int k=0; k<3; k++)
						{
							if(mesh.Cell2DsEdges[j][k]==i)
								n++;
							if(n > 1)
								repeated = true;
						}
					}
					else
						break;
				}
			}
			else
				break;
		}
		
		ASSERT_EQ(repeated, false);
		
	}

	// test sul numero di vertici, lati e facce della mesh che deriva da Triangulation_I
	TEST(PolyhedralMeshTest, NumVertices_Triangulation)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		bool ok = true;
		unsigned int V_total = 102;
		if(mesh.Cell0DsId.size() != V_total)
			ok = false;
		else if(mesh.NumCell0Ds != V_total)
			ok = false;
		
		ASSERT_EQ(ok, true);
	}

	TEST(PolyhedralMeshTest, NumEdges_Triangulation)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		bool ok = true;
		unsigned int E_total = 312;	// numero nuovi lati + lati iniziali
		if(mesh.Cell1DsId.size() != E_total)
			ok = false;
		else if(mesh.NumCell1Ds != E_total)
			ok = false;
		
		ASSERT_EQ(ok, true);
	}

	TEST(PolyhedralMeshTest, NumFaces_Triangulation)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		bool ok = true;
		unsigned int F_total = 208;	// numero nuove facce + facce iniziali
		if(mesh.Cell2DsId.size() != F_total)
			ok = false;
		else if(mesh.NumCell2Ds != F_total)
			ok = false;
		
		ASSERT_EQ(ok, true);
	}
	
	// test sulla valenza dei vertici della mesh ottenuta con Triangulation_I
	TEST(PolyhedralMeshTest, ValenceVertices)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		unsigned int E_initial = 12;
		// numero vertici con valenza 4
		unsigned int NumLowValence_Teo = 6; 
		// numero vertici con valenza 6
		unsigned int NumHighValence_Teo = 96; 
		
		// numero vertici nella mesh con valenze 4 e 6
		unsigned int NumLowValence = 0;
		unsigned int NumHighValence = 0;
		
		unsigned int NumPerVertex = 0;
		
		for(unsigned int i = 0; i<mesh.NumCell0Ds; i++)
		{
			NumPerVertex = 0;
			for(unsigned int j=E_initial; j<mesh.NumCell1Ds; j++)
			{
				if(mesh.Cell1DsExtrema(j,0)==i || mesh.Cell1DsExtrema(j,1)==i)
					NumPerVertex++;
			}
			
			if(NumPerVertex == 4)
				NumLowValence++;
			else if(NumPerVertex == 6)
				NumHighValence++;
		}
		
		ASSERT_EQ(NumLowValence, NumLowValence_Teo);
		ASSERT_EQ(NumHighValence, NumHighValence_Teo);
	}
	
	// test per il controllo dei punti sulla sfera della mesh
	TEST(PolyhedralMeshTest, NormalizedVertices)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		SphereProjection(mesh);
		bool ok = true;
		
		double x = 0;
		double y = 0;
		double z = 0;
		
		double norma = 0;
		
		for(unsigned int i=0; i<mesh.NumCell0Ds; i++)
		{
			x = mesh.Cell0DsCoordinates(i,0);
			y = mesh.Cell0DsCoordinates(i,1);
			z = mesh.Cell0DsCoordinates(i,2);
			
			norma = sqrt(x*x+y*y+z*z);
			if(abs(norma-1.0) > 1e-12)
			{
				ok = false;
				break;
			}
		}
		
		ASSERT_EQ(ok, true);
	}
	
	// test sulla coerenza dei segmenti e dei vertici dello shortest path
	TEST(PolyhedralMeshTest, CheckShortestPath)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		unsigned int E_initial = 12;
		ShortestPath(mesh, 0, 42, E_initial);
		bool ok = true;
		unsigned int NumVertices = 0;
		unsigned int NumEdges = 0;
		vector<unsigned int> vertices;
		vector<unsigned int> edges;
		vertices.reserve(mesh.NumCell0Ds);
		edges.reserve(mesh.NumCell0Ds); // ci dovranno essere vertices.size() - 1 edges
		for(unsigned int i=0; i<mesh.NumCell0Ds; i++)
		{
			if(mesh.VerticesShortestPath[i]==1)
			{
				NumVertices++;
				vertices.push_back(i);
			}
		}
		for(unsigned int j=0; j<mesh.NumCell1Ds-E_initial; j++)
		{
			if(mesh.EdgesShortestPath[j]==1)
			{
				NumEdges++;
				edges.push_back(j+E_initial);
			}
		}
		if(NumVertices!=(NumEdges+1))
			ok = false;
		
		// se è già falso da prima, inutile fare altri controlli
		if(ok)
		{
			for(const auto& vertex: vertices)
			{
				if(ok)
				{
					unsigned int count = 0;
					
					// verifichiamo in quanti lati di edges compare l'estremo vertex
					for(const auto& edge: edges)
					{
						if(mesh.Cell1DsExtrema(edge, 0) == vertex || mesh.Cell1DsExtrema(edge, 1) == vertex)
							count++;
					}
					
					if(count < 1 && (vertex == 0 || vertex == 42))
						ok = false;
					else if(count < 2 && (vertex != 0 && vertex != 42))
						ok = false;
				}
			}
		}
		
		ASSERT_EQ(ok,true);
	}
}