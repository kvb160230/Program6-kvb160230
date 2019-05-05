/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Krishna Boreda
 * Email:  kvb160230@utdallas.edu
 */

#include <iostream>
#include <stdint.h>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <stdio.h>
#include "cdk.h"
//#include "binHeader.h"

#define MATRIX_WIDTH 5
#define MATRIX_HEIGHT 3
#define BOX_WIDTH 20
#define MATRIX_NAME_STRING "Binary File Contents"

using namespace std;

/*
 * Records in the file have a fixed length buffer
 * that will hold a C‐Style string. This is the
 * size of the fixed length buffer.
 */
const int maxRecordStringLength = 25;

class BinaryFileRecord
{
    public:
       uint8_t strLength;
       char   stringBuffer[maxRecordStringLength];
};

class BinaryFileHeader
{
public:  
  uint32_t magicNumber;         /* Should be 0xFEEDFACE */
       uint32_t versionNumber;
       uint64_t numRecords;
};

int main()
{
  // uint32_t magicNumber = 0XFEEDFACE;

  WINDOW*window;
  CDKSCREEN*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char *rowTitles[MATRIX_HEIGHT+1] = {"R0", "a", "b", "c"};
  const char *columnTitles[MATRIX_WIDTH+1] = {"C0", "a", "b", "c", "d", "e"};
  int boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
   */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT,
			  MATRIX_NAME_STRING, (char **) columnTitles, (char **) rowTitles, boxWidths,
			  boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);
  
  stringstream binStream;
  BinaryFileRecord *myRecord = new BinaryFileRecord();
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  //   myRecord->strLength = 127.4567;
   //  int counter;
  //  ofstream binOutfile ("binaryTestFile.bin", ios::out | ios::binary);
 
 ifstream binInfile ("cs3377.bin", ios::in | ios::binary);
 if(!binInfile)
   {
     cout<<"Cannot open!"<<endl;
   }

 
 binInfile.read((char *) myHeader, sizeof(BinaryFileHeader));

 binStream<<"0x"<< uppercase<<hex<<myHeader->magicNumber;
 string str = "Magic: " + binStream.str();
 setCDKMatrixCell(myMatrix, 1, 1, str.c_str());
 binStream.str(std::string());

 binStream << dec << myHeader->versionNumber;
 str = "Version: " +  binStream.str();
 setCDKMatrixCell(myMatrix, 1, 2, str.c_str());
 binStream.str(std::string());

 binStream<<myHeader->numRecords;
 str = "numRecords: " +  binStream.str();
 setCDKMatrixCell(myMatrix, 1, 3, str.c_str());
 binStream.str(std::string());

 int i = 0;
 int col = 2; 
 int len = 0;
 
 while(i<= myHeader->numRecords)
   {
     binInfile.read((char*) myRecord, sizeof(BinaryFileRecord));
     binStream << myRecord-> stringBuffer;
     str = binStream.str();
     setCDKMatrixCell(myMatrix, col, 2, str.c_str());
     binStream.str(std::string());

     len = myRecord -> strLength;
     binStream << len;
     str = "strlen: " +  binStream.str();
     setCDKMatrixCell(myMatrix, col, 1, str.c_str());
     binStream.str(std::string());
     i++;
     col++;
   }
 
  binInfile.close();



  /*
   * Dipslay a message
   */
  // setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  sleep (10);


  // Cleanup screen
  endCDK();
}
