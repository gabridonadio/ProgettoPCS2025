#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

namespace PolyhedralLibrary
{
	void BuildPolyhedron(PolyhedralMesh& mesh, int p, int q)
	{	
		const double phi = (1.0+sqrt(5.0))/2.0; 
		// tetraedro
		if(p==3 && q==3)
		{
			//Cell0Ds
			mesh.NumCell0Ds = 4;
			
			mesh.Cell0DsId.resize(mesh.NumCell0Ds); //Salvataggio degli ID
			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++)
				mesh.Cell0DsId[i] = i;
			
			mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(mesh.NumCell0Ds, 3); 	//Salvataggio delle coordinate

			mesh.Cell0DsCoordinates <<
				1, 1, 1,
			   -1,-1, 1,
			   -1, 1,-1,
				1,-1,-1;	
				
			mesh.Cell0DsCoordinates /= sqrt(3);

			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++)  //Salvataggio dei marker
				mesh.Cell0DsMarker[1].push_back(mesh.Cell0DsId[i]);

			//for(int i = 0; i < mesh.NumCell0Ds; i++)
				//cout << mesh.Cell0DsMarker[1][i] << endl;

			//cell1Ds
			mesh.NumCell1Ds = 6;
			
			mesh.Cell1DsId.resize(mesh.NumCell1Ds); //Salvataggio degli ID
			for(unsigned int i = 0; i < mesh.NumCell1Ds; i++)
				mesh.Cell1DsId[i] = i;

			mesh.Cell1DsExtrema = Eigen::MatrixXi::Zero(mesh.NumCell1Ds, 2); //Salvataggio degli estremi dei lati
			mesh.Cell1DsExtrema << 
				0, 1,
				0, 2,
				0, 3,
				1, 2, 
				1, 3,
				2, 3;

			//Cell2Ds
			mesh.NumCell2Ds = 4;

			mesh.Cell2DsId.resize(mesh.NumCell2Ds); //Salvataggio degli ID
			for(unsigned int i = 0; i < mesh.NumCell2Ds; i++)
				mesh.Cell2DsId[i] = i;

			mesh.Cell2DsVertices.resize(mesh.NumCell2Ds); //Salvataggio dei vertici di ogni faccia
			mesh.Cell2DsVertices[0] = {0, 1, 2};
			mesh.Cell2DsVertices[1] = {0, 3, 1};
			mesh.Cell2DsVertices[2] = {0, 2, 3};
			mesh.Cell2DsVertices[3] = {1, 3, 2};

			mesh.Cell2DsEdges.resize(mesh.NumCell2Ds); //Salvataggio dei lati di ogni faccia
			mesh.Cell2DsEdges[0] = {0, 3, 1};
			mesh.Cell2DsEdges[1] = {2, 4, 0};
			mesh.Cell2DsEdges[2] = {1, 5, 2};
			mesh.Cell2DsEdges[3] = {4, 5, 3};
					
			for(unsigned int i = 0; i < mesh.NumCell2Ds; i++) //Salvataggio dei marker
				mesh.Cell2DsMarker[1].push_back(mesh.Cell2DsId[i]);
		}

		// nel caso di ottaedro o cubo li tratto nello stesso modo, cioè come un ottaedro
		// ottaedro
		if((p==3 && q==4) || (p==4 && q==3))
		{
			//Cell0Ds
			mesh.NumCell0Ds = 6;

			mesh.Cell0DsId.resize(mesh.NumCell0Ds);	//Salvataggio degli ID
			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++)
				mesh.Cell0DsId[i] = i;

			mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(mesh.NumCell0Ds, 3); //Salvataggio delle coordinate
			mesh.Cell0DsCoordinates <<
				0, 0, 1,
				1, 0, 0,
				0, 1, 0,
			   -1, 0, 0,
				0,-1, 0,
				0, 0,-1;	

			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++) //Salvataggio dei marker
				mesh.Cell0DsMarker[1].push_back(mesh.Cell0DsId[i]);
			
			//Cell1Ds
			mesh.NumCell1Ds = 12;

			mesh.Cell1DsId.resize(mesh.NumCell1Ds); //Salvataggio degli ID
			for(unsigned int i = 0; i < mesh.NumCell1Ds; i++)
				mesh.Cell1DsId[i] = i;

			mesh.Cell1DsExtrema = Eigen::MatrixXi::Zero(mesh.NumCell1Ds,2); //Salvataggio degli estremi dei lati
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

			mesh.Cell2DsId.resize(mesh.NumCell2Ds); //Salvataggio degli ID
			for(unsigned int i = 0; i < mesh.NumCell2Ds; i++)
				mesh.Cell2DsId[i] = i;
				
			mesh.Cell2DsVertices.resize(mesh.NumCell2Ds); //Salvataggio dei vertici di ogni faccia
			mesh.Cell2DsVertices[0] = {0,1,2};  
			mesh.Cell2DsVertices[1] = {0,2,3};  
			mesh.Cell2DsVertices[2] = {0,3,4};  
			mesh.Cell2DsVertices[3] = {0,4,1};  
			mesh.Cell2DsVertices[4] = {5,2,1};
			mesh.Cell2DsVertices[5] = {5,3,2};  
			mesh.Cell2DsVertices[6] = {5,4,3};  
			mesh.Cell2DsVertices[7] = {5,1,4};  

			mesh.Cell2DsEdges.resize(mesh.NumCell2Ds); //Salvataggio dei lati di ogni faccia
			mesh.Cell2DsEdges[0] = {0, 8, 1};
			mesh.Cell2DsEdges[1] = {1, 9, 2};
			mesh.Cell2DsEdges[2] = {2,10, 3};
			mesh.Cell2DsEdges[3] = {3,11, 0};
			mesh.Cell2DsEdges[4] = {5, 8, 4};
			mesh.Cell2DsEdges[5] = {6, 9, 5};
			mesh.Cell2DsEdges[6] = {7,10, 6};
			mesh.Cell2DsEdges[7] = {4,11, 7};

			for(unsigned int i = 0; i < mesh.NumCell2Ds; i++)
				mesh.Cell2DsMarker[1].push_back(mesh.Cell2DsId[i]);
		}
		
		// nel caso di icosaedro o dodecaedro li tratto nello stesso modo, cioè come un icosaedro
		//icosaedro
		if((p==3 && q==5) || (p==5 && q==3))
		{
			//Cell0Ds
			mesh.NumCell0Ds = 12;

			mesh.Cell0DsId.resize(mesh.NumCell0Ds);	//Salvataggio degli ID
			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++)
				mesh.Cell0DsId[i] = i;

			mesh.Cell0DsCoordinates = Eigen::MatrixXd::Zero(mesh.NumCell0Ds, 3); //Salvataggio delle coordinate
			mesh.Cell0DsCoordinates <<
				 0,  1,  phi,  
				 0, -1,  phi,  
				-phi, 0,   1,  
				-1,  phi, 0,   
				 1,  phi, 0,   
				 phi, 0,   1,  
				 1, -phi, 0,   
				 phi, 0,  -1,  
				 0,   1, -phi, 
				-phi, 0,  -1,  
				 0,  -1, -phi, 
				-1, -phi, 0; 
				
			mesh.Cell0DsCoordinates /= sqrt(1+phi*phi);

			for(unsigned int i = 0; i < mesh.NumCell0Ds; i++) //Salvataggio dei marker
				mesh.Cell0DsMarker[1].push_back(mesh.Cell0DsId[i]);

			// cell1Ds
			mesh.NumCell1Ds = 30;

			mesh.Cell1DsId.resize(mesh.NumCell1Ds); //Salvataggio degli ID
			for(unsigned int i = 0; i < mesh.NumCell1Ds; i++)
				mesh.Cell1DsId[i] = i;

			mesh.Cell1DsExtrema = Eigen::MatrixXi::Zero(mesh.NumCell1Ds,2); //Salvataggio degli estremi dei lati
			mesh.Cell1DsExtrema << 
			0, 1,   
			0, 2,   
			0, 3,   
			0, 4,   
			0, 5,   
			1, 2,   
			1, 5,   
			1, 6,   
			1,11,   
			2, 3,   
			2, 9,   
			2,11,   
			3, 4,   
			3, 8,   
			3, 9,   
			4, 5,   
			4, 8,   
			4, 7,   
			5, 6,   
			5, 7,   
			6,10,   
			6, 7,   
			7, 8,   
			7,10,   
			8, 9,   
			8,10,   
			9,10,   
			9,11,   
			11, 6,   
			11,10;

			//Cell2Ds
			mesh.NumCell2Ds = 20;

			mesh.Cell2DsId.resize(mesh.NumCell2Ds); //Salvataggio degli ID
			for(unsigned int i = 0; i < mesh.NumCell2Ds; i++)
				mesh.Cell2DsId[i] = i;
			
			mesh.Cell2DsVertices.resize(mesh.NumCell2Ds); //Salvataggio dei vertici di ogni faccia
			mesh.Cell2DsVertices[0] = {0, 1, 2};
			mesh.Cell2DsVertices[1] = {0, 2, 3};
			mesh.Cell2DsVertices[2] = {0, 3, 4};
			mesh.Cell2DsVertices[3] = {0, 4, 5};
			mesh.Cell2DsVertices[4] = {0, 5, 1};
			mesh.Cell2DsVertices[5] = {1, 5, 6};
			mesh.Cell2DsVertices[6] = {1, 6, 11};
			mesh.Cell2DsVertices[7] = {2, 1, 11};
			mesh.Cell2DsVertices[8] = {2, 11, 9};
			mesh.Cell2DsVertices[9] = {3, 2, 9};
			mesh.Cell2DsVertices[10] = {3, 9, 8};
			mesh.Cell2DsVertices[11] = {3, 8, 4};
			mesh.Cell2DsVertices[12] = {4, 8, 7};
			mesh.Cell2DsVertices[13] = {4, 7, 5};
			mesh.Cell2DsVertices[14] = {5,7, 6};
			mesh.Cell2DsVertices[15] = {6,7,10};
			mesh.Cell2DsVertices[16] = {6,10, 11};
			mesh.Cell2DsVertices[17] = {7,10, 8};
			mesh.Cell2DsVertices[18] = {8,10,9};
			mesh.Cell2DsVertices[19] = {9, 10,11};


			mesh.Cell2DsEdges.resize(mesh.NumCell2Ds); //Salvataggio dei lati di ogni faccia
			mesh.Cell2DsEdges[0] = {0, 5, 1};
			mesh.Cell2DsEdges[1] = {1, 9,2};
			mesh.Cell2DsEdges[2] = {2, 12, 3};
			mesh.Cell2DsEdges[3] = {3,15, 4};
			mesh.Cell2DsEdges[4] = {4, 6, 0};
			mesh.Cell2DsEdges[5] = {6,18, 7};
			mesh.Cell2DsEdges[6] = {7,28, 8};
			mesh.Cell2DsEdges[7] = {5, 8, 11};
			mesh.Cell2DsEdges[8] = {11,27,10};
			mesh.Cell2DsEdges[9] = {9,10, 14};
			mesh.Cell2DsEdges[10] = {14,24,13};
			mesh.Cell2DsEdges[11] = {13,16,12};
			mesh.Cell2DsEdges[12] = {16,22, 17};
			mesh.Cell2DsEdges[13] = {17,19, 15};
			mesh.Cell2DsEdges[14] = {19,21,18};
			mesh.Cell2DsEdges[15] = {21,23,20};
			mesh.Cell2DsEdges[16] = {20,29,28};
			mesh.Cell2DsEdges[17] = {23,25,22};
			mesh.Cell2DsEdges[18] = {25,26,24};
			mesh.Cell2DsEdges[19] = {26,29,27};

			for(unsigned int i = 0; i < mesh.NumCell2Ds; i++) //Salvataggio dei marker
				mesh.Cell2DsMarker[1].push_back(mesh.Cell2DsId[i]);
		}
	}
	
	// Suppongo di aver già controllato che uno tra b e c sia uguale a 0 e l'altro >= 1
	// Triangolazione caso b = 0 oppure c = 0
	void Triangulation_I(PolyhedralMesh& mesh, const int p, const int q, const int b, const int c)
	{
		unsigned int T = b*b + b*c + c*c;
		unsigned int V;
		unsigned int E;
		unsigned int F;
		
		if(p==3 && q==3)
		{
			V = 2*T + 2;
			E = 6*T;
			F = 4*T;
			
		}
		
		if((p==3 && q==4)||(p==4 && q==3))
		{
			V = 4*T + 2;
			E = 12*T;
			F = 8*T;
		}
		
		if((p==3 && q==5)||(p==5 && q==3))
		{
			V = 10*T + 2;
			E = 30*T;
			F = 20*T;
		}
		
		mesh.Cell0DsId.reserve(V);
		mesh.Cell1DsId.reserve(10000);
		mesh.Cell2DsId.reserve(F+F/T);
		
		mesh.Cell0DsCoordinates.conservativeResize(V, Eigen::NoChange);
		mesh.Cell1DsExtrema.conservativeResize(10000, Eigen::NoChange);
		
		mesh.Cell2DsVertices.reserve(F+F/T);
		mesh.Cell2DsEdges.reserve(F+F/T);
		

		// salvare gli ID dei vertici che escono dalla suddivisione dei lati principali
		array<vector<unsigned int>, 3> id_vertices_suddivisione;
		for (auto& vec : id_vertices_suddivisione) {
			vec.resize(b-1);
		}
		
		map<unsigned int, vector<unsigned int>> vertices_per_face;
		unsigned int n = mesh.NumCell0Ds;
		unsigned int m = mesh.NumCell1Ds;	// usato nella triangolazione
		unsigned int f = mesh.NumCell2Ds;	// usato nella triangolazione
		
		//vector<unsigned int> v;

		//mesh.Cell1DsMarker[3] = v;
	

		for(unsigned int face = 0; face < mesh.NumCell2Ds; face++)
		{
			// salvare le 3 direzioni del triangolo
			Eigen::Matrix3d matrix_edges;
			
			// puzza
			for (auto& vec : id_vertices_suddivisione) {
				vec.clear();
			}
			for (auto& vec : id_vertices_suddivisione) {
			vec.resize(b-1);
			}
			vertices_per_face.clear();

			
			for(unsigned int vertex = 0; vertex < 3; vertex++)
			{
				// Controllo che il lato non sia ancora stato diviso
				// Controllo che esista la chiave 2 per i lati già divisi
				/*key = 2;
				// Se c'è la key allora entra nell'if
				if (auto mesh.Cell1DsMarker.find(key) != mesh.Cell1DsMarker.end()) {
					
					// Cerco il lato di ID Cell2DsEdges[face][vertex] nella lista associata al marker key
					auto iter_2DMark = find(mesh.Cell1DsMarker[key].begin(), mesh.Cell1DsMarker[key].end(), mesh.Cell2DsEdges[face][vertex]);

					if (iter_2DMark == mesh.Cell1DsMarker[key].end()) {
						// Nella lista associata al marker key non c'è il lato cercato, cioè il lato non è ancora stato diviso
						*/
						// DIVIDO IL LATO
						unsigned int vertex_origin_ID = mesh.Cell2DsVertices[face][vertex];
						unsigned int vertex_end_ID = mesh.Cell2DsVertices[face][(vertex+1)%3];
						
						double x_origin = mesh.Cell0DsCoordinates(vertex_origin_ID, 0);
						double y_origin = mesh.Cell0DsCoordinates(vertex_origin_ID, 1);
						double z_origin = mesh.Cell0DsCoordinates(vertex_origin_ID, 2);
						
						double x_end = mesh.Cell0DsCoordinates(vertex_end_ID, 0);
						double y_end = mesh.Cell0DsCoordinates(vertex_end_ID, 1);
						double z_end = mesh.Cell0DsCoordinates(vertex_end_ID, 2); 
						
						Eigen::Vector3d vector_edge;
						vector_edge << x_end - x_origin,
									   y_end - y_origin, 
									   z_end - z_origin;
						vector_edge /= b; // vettore direzione normalizzato
						matrix_edges.row(vertex) = vector_edge;
						// Creo i punti della triangolazione sui lati principali
						// Cerco il lato di ID Cell2DsEdges[face][vertex] nel vettore associato al marker 2
						auto iter_2DMark = find(mesh.Cell1DsMarker[2].begin(), mesh.Cell1DsMarker[2].end(), mesh.Cell2DsEdges[face][vertex]);
						// iter_2DMark != mesh.Cell1DsMarker[2].end()
						if (iter_2DMark != mesh.Cell1DsMarker[2].end()){
							for(unsigned int i = 1; i < b; i++) 
							{
								//cout << "vertex" << vertex << endl;
								double x_sudd = x_origin + vector_edge(0)*i;
								double y_sudd = y_origin + vector_edge(1)*i;
								double z_sudd = z_origin + vector_edge(2)*i;
								
								bool found = false;
								unsigned int ind = 0;
								
								// recupero gli id dei vertici della suddivisone dei lati principali
								unsigned int id_found;
								while(not found){
									if(abs(mesh.Cell0DsCoordinates(ind,0)-x_sudd) < 1e-12 && abs(mesh.Cell0DsCoordinates(ind,1)-y_sudd) < 1e-12 && abs(mesh.Cell0DsCoordinates(ind,2)-z_sudd) < 1e-12) {
										id_found = mesh.Cell0DsId[ind];
										found = true;
									}
									ind++;
								}
								id_vertices_suddivisione[vertex][i-1] = id_found;
							}
								
						}
						else{
							for(unsigned int i = 1; i < b; i++) 
							{
								mesh.Cell0DsCoordinates(n, 0) = x_origin + vector_edge(0)*i;
								mesh.Cell0DsCoordinates(n, 1) = y_origin + vector_edge(1)*i;
								mesh.Cell0DsCoordinates(n, 2) = z_origin + vector_edge(2)*i;
								mesh.Cell0DsId.push_back(n);
								id_vertices_suddivisione[vertex][i-1] = n;
								n++;
							}
							mesh.Cell1DsMarker[2].push_back(mesh.Cell2DsEdges[face][vertex]);
						}
						
							
							
						
						
					//}
				//}

			}
			
			// popolo il livello 0 della mappa con tutti i vertici della faccia
			vertices_per_face[0].reserve(b+1);
			vertices_per_face[0].push_back(mesh.Cell2DsVertices[face][0]);
			for(const auto& iter : id_vertices_suddivisione[0]) {
				vertices_per_face[0].push_back(iter);
			}
			vertices_per_face[0].push_back(mesh.Cell2DsVertices[face][1]);
			
			// trovo i vertici interni della triangolazione
			// itero sull'altezza 
			for(unsigned int j = 0; j < b-1 ; j++)
			{
				vertices_per_face[j+1].reserve(b-j);
				vertices_per_face[j+1].push_back(id_vertices_suddivisione[2][b-2-j]);
				// itero sulle righe
				for(unsigned int k = b-2-j; k > 0; k--)
				{
					mesh.Cell0DsCoordinates(n, 0) = mesh.Cell0DsCoordinates(id_vertices_suddivisione[1][j], 0) - matrix_edges(0, 0)*k;
					mesh.Cell0DsCoordinates(n, 1) = mesh.Cell0DsCoordinates(id_vertices_suddivisione[1][j], 1) - matrix_edges(0, 1)*k;
					mesh.Cell0DsCoordinates(n, 2) = mesh.Cell0DsCoordinates(id_vertices_suddivisione[1][j], 2) - matrix_edges(0, 2)*k;
					mesh.Cell0DsId.push_back(n);
					vertices_per_face[j+1].push_back(n);
					n++;
				}
				
				vertices_per_face[j+1].push_back(id_vertices_suddivisione[1][j]);
			}
			
			vertices_per_face[b].reserve(1);
			vertices_per_face[b].push_back(mesh.Cell2DsVertices[face][2]);
			
			// creazione lati e facce triangolazione
			// itero sulla base
			for(unsigned int j = 0; j < b; j++)
			{
				// itero sull'altezza
				for(unsigned int liv = 0; liv < b-j; liv++)
				{
					unsigned int vert_0 = vertices_per_face[liv][j];
					unsigned int vert_1 = vertices_per_face[liv][j+1];
					unsigned int vert_2 = vertices_per_face[liv+1][j];
					
					// memorizzazione lati
					// creazione lato 0
					//cout << "passo " << j << " lato 0" << endl;
					mesh.Cell1DsExtrema(m, 0) = vert_0;
					mesh.Cell1DsExtrema(m, 1) = vert_1;
					unsigned int edge_0 = m;
					
					if(liv == 0)
					{
						bool found = false;
						for(auto& iter : mesh.Cell1DsMarker[3])
						{
							// cerchiamo se esiste il lato con estremi vert_0 e vert_1 tra quelli con marker 3
							if((mesh.Cell1DsExtrema(iter, 0) == vert_0 && mesh.Cell1DsExtrema(iter, 1) == vert_1)||(mesh.Cell1DsExtrema(iter, 0) == vert_1 && mesh.Cell1DsExtrema(iter, 1) == vert_0))
							{
								edge_0 = iter;
								found = true;
					//			cout << iter << endl;
							}
						}
						
						if(found == false)
						{
							mesh.Cell1DsMarker[3].push_back(m);
							mesh.Cell1DsId.push_back(edge_0);
					//		cout << m << endl;
							m++;
						}
					}
					else
					{
						mesh.Cell1DsId.push_back(edge_0);
					//	cout << m << endl;
						m++;
					}
					
					//cout << "passo " << j << " lato 1" << endl;
					// creazione lato 1
					mesh.Cell1DsExtrema(m, 0) = vert_1;
					mesh.Cell1DsExtrema(m, 1) = vert_2;
					unsigned int edge_1 = m;
					mesh.Cell1DsId.push_back(edge_1);
					if(j == b-1)
					{
						bool found = false;
						for(auto& iter : mesh.Cell1DsMarker[3])
						{
							// cerchiamo se esiste il lato con estremi vert_0 e vert_1 tra quelli con marker 3
							if((mesh.Cell1DsExtrema(iter, 0) == vert_1 && mesh.Cell1DsExtrema(iter, 1) == vert_2)||(mesh.Cell1DsExtrema(iter, 0) == vert_2 && mesh.Cell1DsExtrema(iter, 1) == vert_1))
							{
								edge_1 = iter;
								found = true;
					//			cout << iter << endl;
							}
						}
						if(not found)
						{
							mesh.Cell1DsMarker[3].push_back(m);
							mesh.Cell1DsId.push_back(edge_1);
					//		cout << m << endl;
							m++;

						}
					}
					else
					{
						mesh.Cell1DsId.push_back(edge_1);
					//	cout << m << endl;
						m++;
					}
					
					// creazione lato 2
					//cout << "passo " << j << " lato 2" << endl;
					mesh.Cell1DsExtrema(m, 0) = vert_2;
					mesh.Cell1DsExtrema(m, 1) = vert_0;
					unsigned int edge_2 = m;
					mesh.Cell1DsId.push_back(edge_2);
					if(j == 0)
					{
						bool found = false;
						for(auto& iter : mesh.Cell1DsMarker[3])
						{
							// cerchiamo se esiste il lato con estremi vert_0 e vert_1 tra quelli con marker 3
							if((mesh.Cell1DsExtrema(iter, 0) == vert_2 && mesh.Cell1DsExtrema(iter, 1) == vert_0)||(mesh.Cell1DsExtrema(iter, 0) == vert_0 && mesh.Cell1DsExtrema(iter, 1) == vert_2))
							{
								edge_2 = iter;
								found = true;
					//			cout << iter << endl;
							}
						}
						
						if(not found)
						{
							mesh.Cell1DsMarker[3].push_back(m);
							mesh.Cell1DsId.push_back(edge_2);
					//		cout << m << endl;
							m++;
						}
					}
					else
					{
						mesh.Cell1DsId.push_back(edge_2);
					//	cout << m << endl;
						m++;
					}
					
					// memorizzazione faccia con lati appena creati
					mesh.Cell2DsVertices[f] = {vert_0, vert_1, vert_2};
					mesh.Cell2DsEdges[f] = {edge_0, edge_1, edge_2};
					mesh.Cell2DsId.push_back(f);
					f++;
					
				}
			}
			
			
			// numero lati triangolazione: 3b(b+1)/2
			//triangolazione seconda parte
			for(unsigned int j = 0; j < b; j++)
			{
				// itero sull'altezza
				for(unsigned int liv = 0; liv < b-j-1; liv++)
				{
					unsigned int vert_0c = vertices_per_face[liv][j+1];
					unsigned int vert_1c = vertices_per_face[liv+1][j];
					unsigned int vert_2c = vertices_per_face[liv+1][j+1];
					
					unsigned int edge_0c;
					unsigned int edge_1c;
					unsigned int edge_2c;
					
					// memorizzazione lati
					for(unsigned int i = 0; i < m; i++)
					{
						if((mesh.Cell1DsExtrema(i,0)==vert_0c && mesh.Cell1DsExtrema(i,1)==vert_1c)||(mesh.Cell1DsExtrema(i,0)==vert_1c && mesh.Cell1DsExtrema(i,1)==vert_0c))
							edge_0c = i;
						else if((mesh.Cell1DsExtrema(i,0)==vert_1c && mesh.Cell1DsExtrema(i,1)==vert_2c)||(mesh.Cell1DsExtrema(i,0)==vert_2c && mesh.Cell1DsExtrema(i,1)==vert_1c))
							edge_1c = i;
						else if((mesh.Cell1DsExtrema(i,0)==vert_2c && mesh.Cell1DsExtrema(i,1)==vert_0c)||(mesh.Cell1DsExtrema(i,0)==vert_0c && mesh.Cell1DsExtrema(i,1)==vert_2c))
							edge_2c = i;
					}
					
					// memorizzazione faccia con lati appena creati
					mesh.Cell2DsVertices[f] = {vert_0c, vert_1c, vert_2c};
					mesh.Cell2DsEdges[f] = {edge_0c, edge_1c, edge_2c};
					mesh.Cell2DsId.push_back(f);
					f++;
					
					
				}
			}
			
			/*for(unsigned int i = 0; i < 3; i++) {
				cout << "id_vertices " << i << " " << endl;
				for(unsigned int j = 0; j < b-1; j++)
					cout << id_vertices_suddivisione[i][j] << ", " << endl; 
			}*/
			
			
			/*for(unsigned int i =0; i < b+1; i++){
				cout << "vertices_per face " << i << " " << endl;
				for(unsigned int j = 0; j <b+1-i; j++)
					cout << vertices_per_face[i][j] << ", " << endl; 
			}*/
			
		}
		cout << "n: " << n << endl;
		cout << "m: " << m << endl;
		cout << "f: " << f << endl;
		mesh.NumCell0Ds = n;
		mesh.NumCell1Ds = m;
		mesh.NumCell2Ds = f;
	}
}