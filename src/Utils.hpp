#pragma once
#include <iostream>
#include "PolyhedralMesh.hpp"


namespace PolyhedralLibrary
{
	void BuildPolyhedron(PolyhedralMesh& mesh, int p, int q);
	void Triangulation_I(PolyhedralMesh& mesh, int b, int c);
}