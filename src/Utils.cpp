#include "Utils.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_set>
#include <iomanip>

using namespace std;


namespace PolyhedralLibrary
{
	void BuildPolyhedron(PolyhedralMesh& mesh, const int p, const int q)
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
	void Triangulation_I(PolyhedralMesh& mesh, const int p, const int q, int b, int c)
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
		
		if(b!=1)
		{
			mesh.Cell0DsId.reserve(V);
			mesh.Cell1DsId.reserve(E+E/T);
			mesh.Cell2DsId.reserve(F+F/T);
			
			mesh.Cell0DsCoordinates.conservativeResize(V, Eigen::NoChange);
			mesh.Cell1DsExtrema.conservativeResize(E+E/T, Eigen::NoChange);
			
			mesh.Cell2DsVertices.reserve(F+F/T);
			mesh.Cell2DsEdges.reserve(F+F/T);
		}
		
		b = max(b,c);
		

		// salvare gli ID dei vertici che escono dalla suddivisione dei lati principali
		array<vector<unsigned int>, 3> id_vertices_suddivisione;
		if(b > 1)
		{
			for (auto& vec : id_vertices_suddivisione) {
				vec.resize(b-1);
			}
		}
		
		map<unsigned int, vector<unsigned int>> vertices_per_face;
		unsigned int n = mesh.NumCell0Ds;
		unsigned int m = mesh.NumCell1Ds;	// usato nella triangolazione
		unsigned int f = mesh.NumCell2Ds;	// usato nella triangolazione
		
		//vector<unsigned int> v;

		//mesh.Cell1DsMarker[3] = v;
	

		for(unsigned int face = 0; face < mesh.NumCell2Ds; face++)
		{
			if(b==1)
				continue;
			
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
						
						if(not found)
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
					if(liv == b-j-1)
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
	
	void Dual(PolyhedralMesh& mesh, PolyhedralMesh& dual, const unsigned int E_initial, const unsigned int F_initial)
	{
		// memorizziamo le informazioni del duale
		dual.NumCell0Ds = mesh.NumCell2Ds-F_initial;
		dual.NumCell1Ds = mesh.NumCell1Ds-E_initial;
		dual.NumCell2Ds = mesh.NumCell0Ds;
		unsigned int n = 0;
		unsigned int m = 0;
		unsigned int f = 0;
		
		dual.Cell0DsId.reserve(dual.NumCell0Ds);
		dual.Cell0DsCoordinates.resize(dual.NumCell0Ds, 3);
		
		dual.Cell1DsId.reserve(dual.NumCell1Ds);
		dual.Cell1DsExtrema.resize(dual.NumCell1Ds, 2);
		cout << dual.Cell1DsExtrema.size() << endl;
		
		dual.Cell2DsId.reserve(dual.NumCell2Ds);
		dual.Cell2DsEdges.resize(dual.NumCell2Ds);
		dual.Cell2DsVertices.resize(dual.NumCell2Ds);
		
		
		// creiamo un numero di vertici pari al numero di facce di mesh (escluse quelle principali)
		for(unsigned int face = F_initial; face < mesh.NumCell2Ds; face++)
		{
			// prendiamo le righe di Cell2DsVertices a partire dalla F_initial 
			// e troviamo le coordinate del baricento a partire dai vertici di ogni faccia
			double x_vertex = 0;
			double y_vertex = 0;
			double z_vertex = 0;
			unsigned int num = 0;
			for(const auto& vertex: mesh.Cell2DsVertices[face])
			{
				num++;
				x_vertex += mesh.Cell0DsCoordinates(vertex,0);
				y_vertex += mesh.Cell0DsCoordinates(vertex,1);
				z_vertex += mesh.Cell0DsCoordinates(vertex,2);
			}
			dual.Cell0DsCoordinates(face-F_initial, 0) = x_vertex/num;
			dual.Cell0DsCoordinates(face-F_initial, 1) = y_vertex/num;
			dual.Cell0DsCoordinates(face-F_initial, 2) = z_vertex/num;
			// al primo Id corrisponde il vertice creato a partire dalla prima faccia
			dual.Cell0DsId.push_back(face-F_initial);
		}
		
		// creiamo struttura di vicinato delle facce per sapere quali vertici collegare
		// per ogni faccia, se questa ha un lato in comune con un'altra, allora sono vicine
		
		// chiave: Id_vertice, valori: Id_facce adiacenti
		map<unsigned int, vector<unsigned int>> neighborhood_faces; 
		for(unsigned int vertex = 0; vertex < mesh.NumCell0Ds; vertex++)
		{
			vector<unsigned int> neighbors;
			neighbors.reserve(6); // massima valenza dei vertici è 6
			/*const auto& key_edges = mesh.Cell2DsEdges[face];
			unordered_set<unsigned int> to_be_found = {key_edges[0], key_edges[1], key_edges[2]};*/
			// cerchiamo facce con vertex
			
			for(unsigned int face_ad = F_initial; face_ad < mesh.NumCell2Ds; face_ad++)
			{
				/*if(face_ad == face)
					continue;*/
				
				/*if(neighbors.size() == 3)
					break;*/
				
				const auto& iter_face = mesh.Cell2DsVertices[face_ad];
				
				// per ogni faccia itero sui vertici per vedere se c'è il vertice vertex
				
				/*
				// LAMBDA FUNCTION
				auto iter_edges = find_if(iter_face.begin(), iter_face.end(), [&](int id_edge) {
				return to_be_found.count(id_edge) > 0;
				});
				if(iter_edges!=iter_face.end())
				{
					neighbors.push_back(face_ad);
				}*/
				
				auto iter_vertices = find(iter_face.begin(), iter_face.end(), vertex);
				if(iter_vertices!=iter_face.end())
				{
					neighbors.push_back(face_ad);
				}
			}
			
			neighborhood_faces[vertex] = neighbors;
		}
		
		
		for(unsigned int vertex = 0; vertex < mesh.NumCell0Ds; vertex++)
		{
			unsigned int iter_face = neighborhood_faces[vertex][0];
			vector<unsigned int> vertices;
			vector<unsigned int> edges;
			vertices.reserve(neighborhood_faces[vertex].size());
			edges.reserve(neighborhood_faces[vertex].size());
			vertices.push_back(iter_face-F_initial);
			
			dual.Cell2DsId.push_back(f);
			f++;
			unsigned int new_face_ad;
			
			int id_past = -1;
			for(unsigned int face = 0; face < neighborhood_faces[vertex].size(); face++)
			{
				//cout << "face " << face << endl;
				
				vector<unsigned int> edges_face = mesh.Cell2DsEdges[iter_face];
				//cout << "iterface " << iter_face << endl;
				
				bool found = false;
				for(const auto& iter_face_ad: neighborhood_faces[vertex])
				{
					if(found)
						break;
					//cout<< "iter_face_ad " << iter_face_ad << endl;
					if(iter_face_ad == iter_face || iter_face_ad == id_past)
						continue;
					//cout << "hey" << endl;
					
					vector<unsigned int> edges_face_ad = mesh.Cell2DsEdges[iter_face_ad];
					
					for(const auto& it: edges_face_ad)
					{
						
						auto iter_edges = find(edges_face.begin(), edges_face.end(), it);
						if(iter_edges!=edges_face.end())
						{
							found = true;
							new_face_ad = iter_face_ad;
							if(face < neighborhood_faces[vertex].size()-1)
								vertices.push_back(new_face_ad-F_initial);
							//cout << new_face_ad-F_initial << endl;
							
						}
					}
				}
					
					
					
				bool find = false;
				unsigned int edge_0 = m;
				unsigned int vert_0 = iter_face-F_initial;
				cout << "vert_0 " << vert_0 << endl;
				unsigned int vert_1 = new_face_ad-F_initial;
				cout << "vert_1 " << vert_1 << endl;
				cout<< "iter "<<endl;
				for(unsigned int iter = 0; iter < dual.Cell1DsId.size(); iter++)
				{
					cout  << iter << endl;
					/*cout << "Extrema "<< endl;
					for(unsigned int i = 0; i < dual.Cell1DsExtrema.size()/2; i++)
					{
						cout << dual.Cell1DsExtrema(i, 0) << " " << dual.Cell1DsExtrema(i,1) << endl;
					}*/
					// cerchiamo se esiste il lato con estremi vert_0 e vert_1 tra quelli con marker 3
					if((dual.Cell1DsExtrema(iter, 0) == vert_0 && dual.Cell1DsExtrema(iter , 1) == vert_1)||(dual.Cell1DsExtrema(iter, 0) == vert_1 && dual.Cell1DsExtrema(iter, 1) == vert_0))
					{
						edge_0 = dual.Cell1DsId[iter];
						find = true;
						break;
					}
				}
				
				if(not find) //aggiunto controllo su m
				{
					dual.Cell1DsId.push_back(edge_0);
					// baricentro di faccia iter_face è iter_face-F_initial
					dual.Cell1DsExtrema(m, 0) = vert_0; //Accesso più sicuro rispetto a quello con le "<<" di Eigen
					dual.Cell1DsExtrema(m, 1) = vert_1;
					cout << vertex << endl;
					cout << "m " << m <<endl;
					edge_0 = m;
					m++;
				}
				
				edges.push_back(edge_0);
					
				
				id_past = iter_face;
				iter_face = new_face_ad;
				
			}
			
			dual.Cell2DsVertices[vertex] = vertices;
			dual.Cell2DsEdges[vertex] = edges;
			cout << "vertices" << endl;
			for(const auto& it: vertices)
				cout<< it << " ";
			cout << endl;
			cout << "edges" <<endl;
			for(const auto& it: edges)
				cout<< it << " ";
			cout << endl;
		}
		
		
		
		
		for(unsigned int i = 0; i<mesh.NumCell0Ds; i++)
		{
			cout << "faccia "  << i << endl;
			for(unsigned int j = 0; j< neighborhood_faces[i].size(); j++)
				cout << neighborhood_faces[i][j] << " ";
			cout << endl;
		}
		
		
	}


	void ExportMesh(PolyhedralMesh& mesh, string basePath) 
	{
    // Export Cell0Ds
    ofstream cell0DsFile(basePath + "Cell0Ds.txt");
    if (!cell0DsFile.is_open()) 
	{
        cerr << "Error opening Cell0Ds.txt" << endl;
        return;
    }
    cell0DsFile << "Id;X;Y;Z" << endl;
    for (unsigned int i = 0; i < mesh.NumCell0Ds; i++) 
	{
        cell0DsFile << mesh.Cell0DsId[i] << ";"
                    << fixed << setprecision(12) << mesh.Cell0DsCoordinates(i, 0) << ";"
                    << mesh.Cell0DsCoordinates(i, 1) << ";"
                    << mesh.Cell0DsCoordinates(i, 2) << endl;
    }
    cell0DsFile.close();

    // Export Cell1Ds
    ofstream cell1DsFile(basePath + "Cell1Ds.txt");
    if (!cell1DsFile.is_open()) 
	{
        cerr << "Error opening Cell1Ds.txt" << endl;
        return;
    }
    cell1DsFile << "Id;Origin;End" << endl;
    for (unsigned int i = 0; i < mesh.NumCell1Ds; i++) 
	{
        cell1DsFile << mesh.Cell1DsId[i] << ";"
                    << mesh.Cell1DsExtrema(i, 0) << ";"
                    << mesh.Cell1DsExtrema(i, 1) << endl;
    }
    cell1DsFile.close();

    // Export Cell2Ds
    ofstream cell2DsFile(basePath + "Cell2Ds.txt");
    if (!cell2DsFile.is_open()) 
	{
        cerr << "Error opening Cell2Ds.txt" << endl;
        return;
    }
    cell2DsFile << "Id;NumVertices;Vertices;NumEdges;Edges" << endl;
    for (unsigned int i = 0; i < mesh.NumCell2Ds; i++) 
	{
        cell2DsFile << mesh.Cell2DsId[i] << ";"
                    << mesh.Cell2DsVertices[i].size() << ";";
        // Vertici
        for (size_t j = 0; j < mesh.Cell2DsVertices[i].size(); j++) 
		{
            cell2DsFile << mesh.Cell2DsVertices[i][j];
            if (j != mesh.Cell2DsVertices[i].size() - 1)
                cell2DsFile << ",";
        }
        cell2DsFile << ";"
                    << mesh.Cell2DsEdges[i].size() << ";";
        // Lati
        for (size_t j = 0; j < mesh.Cell2DsEdges[i].size(); j++) 
		{
            cell2DsFile << mesh.Cell2DsEdges[i][j];
            if (j != mesh.Cell2DsEdges[i].size() - 1)
                cell2DsFile << ",";
        }
        cell2DsFile << endl;
    }
    cell2DsFile.close();

    // Export Cell3Ds
    ofstream cell3DsFile(basePath + "Cell3Ds.txt");
    if (!cell3DsFile.is_open()) 
	{
        cerr << "Error opening Cell3Ds.txt" << endl;
        return;
    }
    cell3DsFile << "Id;NumVertices;Vertices;NumEdges;Edges;NumFaces;Faces" << endl;
	cell3DsFile << 1 << ";";
	// Vertici
	cell3DsFile << mesh.NumCell0Ds << ";";
	for(size_t j = 0; j < mesh.NumCell0Ds; j++)
	{
		cell3DsFile << mesh.Cell0DsId[j];
		if(j != mesh.NumCell0Ds-1) 
			cell3DsFile << ",";
	}
	cell3DsFile << ";";
	// Lati
	cell3DsFile << mesh.NumCell1Ds << ";";
	// DA SISTEMARE, CI SONO DUPLICATI NEGLI EDGES, A PARTIRE DA 13
	for(size_t j = 0; j < mesh.NumCell1Ds; j++)
	{
		cell3DsFile << mesh.Cell1DsId[j];
		cout << mesh.Cell1DsId[j] << endl;
		if(j != mesh.NumCell1Ds - 1) 
			cell3DsFile << ",";
	}
	cell3DsFile << ";";
	// Facce
	cell3DsFile << mesh.NumCell2Ds << ";";
	for(size_t j = 0; j < mesh.NumCell2Ds; j++)
	{
		cell3DsFile << mesh.Cell2DsId[j];
		if(j != mesh.NumCell2Ds - 1)
			cell3DsFile << ",";
	} 
	cell3DsFile<< ";";
    cell3DsFile.close();
	}
}