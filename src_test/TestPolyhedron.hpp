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
		unsigned int F_total = 208;	// numero nuovi lati + lati iniziali
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
	
	// test su lati irrealizzabili nella mesh ottenuta con Triangulation_I (origine coincide con fine)
	TEST(PolyhedralMeshTest, OriginEqualsEnd)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		bool repeated = false;
		for(unsigned int j=0; j<mesh.NumCell1Ds; j++)
		{
			if(mesh.Cell1DsExtrema(j,0) == mesh.Cell1DsExtrema(j,1))
			{
				repeated = true;
				break;
			}
		}
		
		ASSERT_EQ(repeated, false);
	}
	
	
	// test su lati irrealizzabili nel duale (origine coincide con fine)
	TEST(PolyhedralMeshTest, OriginEqualsEnd_Duale)
	{
		PolyhedralMesh mesh;
		PolyhedralMesh dual;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		Dual(mesh, dual, 12, 8);
		bool repeated = false;
		for(unsigned int j=0; j<dual.NumCell1Ds; j++)
		{
			if(dual.Cell1DsExtrema(j,0) == dual.Cell1DsExtrema(j,1))
			{
				repeated = true;
				break;
			}
		}
		
		ASSERT_EQ(repeated, false);
	}
	
	
	/*
	// test sulla coerenza dei segmenti e dei vertici dello shortest path
	TEST(PolyhedronMeshTest, ControlloShortestPath)
	{
		PolyhedralMesh mesh;
		BuildPolyhedron(mesh, 3, 4);
		Triangulation_I(mesh, 3, 4, 5, 0);
		ShortestPath(mesh, 0, 42, 12);
		bool ok = true;
		unsigned int NumVertices = 0;
		unsigned int n_lati = 0;
		for(unsigned int i=0;i<mesh.NumCell0Ds;i++)
		{
			if(mesh.VerticesInShortestPath[i]==1)
			n_vertici++;
		}
		for(unsigned int k=0;k<mesh.NumCell1Ds;k++)
		{
			if(mesh.EdgesInShortestPath[k]==1)
			n_lati++;
		}
		if(n_vertici!=(n_lati+1))
		Corretto = false;
		vector<bool> trovato;
		trovato.reserve(n_vertici);
		if(Corretto==true)
		{
			for(unsigned int i=0;i<mesh.NumCell0Ds;i++)//ciclo su tutti vertici
			{
				if(mesh.VerticesInShortestPath[i]==1)//cerco solo quelli in shortestpath
				{
					for(unsigned int k=0;k<mesh.NumCell1Ds;k++)//ciclo su lati
					{
						if(mesh.EdgesInShortestPath[k]==1)//cerco solo quelli in shortestpath
						{
							if(mesh.Cell1DsExtrema(0,k)==i || mesh.Cell1DsExtrema(1,k)==i)//controllo se vertice è in un estremo
								trovato.push_back(true);
						}
					}
				}
			}
		}
		if(trovato.size()!=(2*n_vertici-2))
			Corretto=false;
		
		ASSERT_EQ(Corretto,true);

	}*/
	
}