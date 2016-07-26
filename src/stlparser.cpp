// stlparser.cpp : Defines the entry point for the console application.
//

//#include "stdafx.h"
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <map>

typedef struct STL_DATA {
	float ni;
	float nj;
	float nk;
	float v1x;
	float v1y;
	float v1z;
	float v2x;
	float v2y;
	float v2z;
	float v3x;
	float v3y;
	float v3z;
	short attCnt;
}STL_DATA;

int main(int argc, char* argv[])
{
	switch (argc)
	{
	case 1:
		std::cout << "Supply a .stl filename" << std::endl;
		break;
	case 2:
	{
		//the main use case
		FILE *pStl;
		fopen_s(&pStl, argv[1], "rb");
		if (pStl == NULL)
		{
			std::cout << "File does not exist" << std::endl;
		}
		else
		{
			//check it's an stl
			std::string strIn = argv[1];
			size_t pos = strIn.find(".stl");
			if (pos == std::string::npos)
			{
				//not an stl file
				std::cout << "Supply a .stl filename" << std::endl;
			}
			else
			{
				//make the .txt out file name
				std::string strOut;
				strOut = strIn;
				strOut.replace(pos, 4, ".txt");
				std::ofstream ofOut(strOut , std::ofstream::out|std::ofstream::trunc);
				

				//read header
				unsigned char * pBuf[80];
				fread(pBuf, 1, 80, pStl);
				//write the header to the output file
				ofOut << "Header" <<std::endl;
				std::string strTmp = (char*)pBuf;
				ofOut << strTmp << std::endl;

				//get the count of objects
				uint32_t nNumObj;
				fread(&nNumObj, 4, 1, pStl);
				//nNumObj = *((uint32_t *)pBuf);
				ofOut << "Triangles:" << std::endl;
				STL_DATA Data;
				int siz = sizeof(STL_DATA);
				std::map<std::string, bool> vertexMap;
				
				for (unsigned int i = 0; i < nNumObj; ++i)
				{
					fread(&Data, sizeof(STL_DATA), 1, pStl);
					//pData = (STL_DATA*)pBuf;
					std::stringstream v1;
					std::stringstream v2;
					std::stringstream v3;
					ofOut << std::endl << "Triangle " << i + 1 << std::endl;
					ofOut << "Normal i: " << Data.ni << std::endl;
					ofOut << "Normal j: " << Data.nj << std::endl;
					ofOut << "Normal k: " << Data.nk << std::endl;
					ofOut << "Vert 1 x: " << Data.v1x << std::endl;
					ofOut << "Vert 1 y: " << Data.v1y << std::endl;
					ofOut << "Vert 1 z: " << Data.v1z << std::endl;
					ofOut << "Vert 2 x: " << Data.v2x << std::endl;
					ofOut << "Vert 2 y: " << Data.v2y << std::endl;
					ofOut << "Vert 2 z: " << Data.v2z << std::endl;
					ofOut << "Vert 3 x: " << Data.v3x << std::endl;
					ofOut << "Vert 3 y: " << Data.v3y << std::endl;
					ofOut << "Vert 3 z: " << Data.v3z << std::endl;
					ofOut << "Attribute count: " << Data.attCnt << std::endl;
					v1 << Data.v1x << "," << Data.v1y << "," << Data.v1z;
					v2 << Data.v2x << "," << Data.v2y << "," << Data.v2z;
					v3 << Data.v3x << "," << Data.v3y << "," << Data.v3z;
					vertexMap[v1.str()] = true;
					vertexMap[v2.str()] = true;
					vertexMap[v3.str()] = true;
				}
				int vertexInd = 0;
				ofOut << std::endl;
				for (auto thing : vertexMap)
				{
					ofOut << "Vertex " << vertexInd++ << ":";
					ofOut << thing.first << std::endl;
				}
				//done
				ofOut.close();
				fclose(pStl);			
			}
			break;
		}
	}
	default:
		std::cout << "Too many arguments. Supply a .stl filename" << std::endl;
		break;
	}
    return 0;
}

