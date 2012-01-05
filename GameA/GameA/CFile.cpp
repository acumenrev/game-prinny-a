#include "CFile.h"
/************************************************************************/
/*                           Read file                                  */
/************************************************************************/
void ReadFile(CQuadTree* quadTree, char* fileName)
{
	FILE* f;
	f = fopen(fileName,"r+");
	rewind(f);
	if(f)
	{
		char base[10000];
		fgets(base,10000,f);
		// 48 = '0'
		int width = (base[0] - 48)*100 + (base[1] - 48)*10 + (base[2] - 48);
		fgets(base,10000,f);
		int height = (base[0] - 48)*100 + (base[1] - 48)*10 + (base[2] - 48);
		// Multiplying with SizeTile cuz' need to suit with each unit
		quadTree->m_root->m_rect.bottom = height*SizeTile;
		quadTree->m_root->m_rect.right = width*SizeTile;
		int row = 0;
		int column = 0;
		while(!feof(f))
		{
			fgets(base,10000,f);
			while(base[column])
			{
				if(base[column] > UNIT_BLANK) // '0'
				{
					if(base[column] == UNIT_BEGIN) // '3'
					{
						quadTree->m_fX = column * SizeTile;
						quadTree->m_fY = row * SizeTile;
					}
					else
					{
						quadTree->AddObject(new CCObject(column*SizeTile,row*SizeTile,base[column]));
					}
				}
				column++;
			}
			row++;
			column = 0;
		}
		fclose(f);
	}
}
/************************************************************************/
/*                           Save file                                  */
/************************************************************************/
void SaveFile(int currentMap, float fX, float fY)
{
	FILE* f;
	f = fopen("Save.txt","r+");
	fputc(currentMap,f);
	fputc(fX/SizeTile,f);
	fputc(fY/SizeTile,f);
	fclose(f);
}
/************************************************************************/
/*                           Read saved file                            */
/************************************************************************/
void ReadSavedFile(int& currentMap, float& fX, float& fY)
{
	FILE* f;
	f = fopen("Save.txt","r+");
	currentMap = fgetc(f);
	fX = fgetc(f)*SizeTile;
	fY = fgetc(f)*SizeTile;
	fclose(f);
}