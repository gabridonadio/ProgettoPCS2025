#pragma once
#include <iostream>
#include "PolyhedralMesh.hpp"


namespace PolyhedralLibrary
{
	void BuildPolyhedron(PolyhedralMesh& mesh, int p, int q);
	void Triangulation_I(PolyhedralMesh& mesh, const int p, const int q, const int b, const int c);
}