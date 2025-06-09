#pragma once
#include <iostream>
#include "PolyhedralMesh.hpp"


namespace PolyhedralLibrary
{
	void BuildPolyhedron(PolyhedralMesh& mesh, const int p, const int q);
	void Triangulation_I(PolyhedralMesh& mesh, const int p, const int q, int b, int c);
	void Dual(PolyhedralMesh& mesh, PolyhedralMesh& dual, const unsigned int E_initial, const unsigned int F_initial);
	void SphereProjection(PolyhedralMesh& mesh);
	void ExportMesh(PolyhedralMesh& mesh, string basePath);
	void ShortestPath(PolyhedralMesh& mesh, const int id_origin, const int id_end, const unsigned int E_initial);
}