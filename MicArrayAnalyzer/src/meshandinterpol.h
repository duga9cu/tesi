/**********************************************************************
                      
   Mic Array Analyzer

   meshandinterpol.h
   
   A Meshing and Bi-linear interpolation library!

   Luca Novarini

**********************************************************************/
#ifndef __MESH_AND_INTERPOL_H__
#define __MESH_AND_INTERPOL_H__

#include <math.h>
#include <vector>
#include "del_interface.h"

class TriangularMesh
   {
   private:
      int x[3],y[3];    //Vertexes coords.   
      int mic[3];       //Mic number @ each vertex
      double det,A,B,C; //Linear interpolation coeffs
      bool bCoeffs;     //false = det, A, B & C not yet defined.
      int Sign(int x1, int y1, int x2, int y2, int xvalue, int yvalue)
         {
         //This functions return 0 if p lies on the intercepting line between a and b,
         //-1 if p is under the line, +1 if over. (Algorithm based on the equation of a
         //line passing by 2 points)
         double value = xvalue*(y1-y2) - yvalue*(x1-x2) + x1*y2 - y1*x2;
         if (abs(value) < 1e-6) return 0; //TOLL = 1e-6
         else 
            {
            if (value > 0) return 1;
            else return -1;
            }
         }
   public:
      int PointTest(int xvalue, int yvalue)  //Returns -1 if the point is outside, 0 in it's onside and +1 if it's inside the triangle.
         {
         int s1,s2,s3;
         s1 = Sign(x[0],y[0],x[1],y[1],x[2],y[2]) * Sign(x[0],y[0],x[1],y[1],xvalue,yvalue);
         s2 = Sign(x[1],y[1],x[2],y[2],x[0],y[0]) * Sign(x[1],y[1],x[2],y[2],xvalue,yvalue);
         s3 = Sign(x[2],y[2],x[0],y[0],x[1],y[1]) * Sign(x[2],y[2],x[0],y[0],xvalue,yvalue);
         if ((s1 < 0)||(s2 < 0)||(s3 < 0)) return -1;
         else
            {
            if ((s1 > 0)&&(s2 > 0)&&(s3 > 0)) return +1;
            else return 0;
            }
         }
      int GetVertexX(int vertex) { if ((vertex < 3)&&(vertex >= 0)) { return x[vertex]; } else return 0; }
      int GetVertexY(int vertex) { if ((vertex < 3)&&(vertex >= 0)) { return y[vertex]; } else return 0; }
      double GetInterpolatedValue(int xvalue, int yvalue) { if (bCoeffs) { return A*xvalue + B*yvalue + C; } else return 0; }
      int GetMicAtVertex(int vertex) { if ((vertex < 3)&&(vertex >= 0)) { return mic[vertex]; } else return 0; }
      bool AreCoeffsSet() { return bCoeffs; }
      bool DeleteCoeffs() { return (bCoeffs = false); }
      bool SetLevelsAtVertexes(double z[3])
         {
         //Computing interpolation coeffs
#ifdef __AUDEBUG__
//         for (int k = 0; k < 3; k++)
//            {
//            printf("TriangleMesh Class: Setting levels on vert (%d;%d), Mic[%d], Level = %f\n",x[k],y[k],mic[k],z[k]);
//            fflush(stdout);
//            }
#endif
         det = x[0]*(y[1]-y[2]) - x[1]*(y[0]-y[2]) + x[2]*(y[0]-y[1]);
         A = (z[0]*(y[1]-y[2]) + z[1]*(y[2]-y[0]) + z[2]*(y[0]-y[1])) / det;
         B = (z[0]*(x[2]-x[1]) + z[1]*(x[0]-x[2]) + z[2]*(x[1]-x[0])) / det;
         C = (z[0]*(x[1]*y[2]-x[2]*y[1]) + z[1]*(x[2]*y[0]-x[0]*y[2]) + z[2]*(x[0]*y[1]-x[1]*y[0])) / det;
         bCoeffs = true;
         return true;
         }
      TriangularMesh(int xvalue[3], int yvalue[3], int micnum[3])
         {
         //Storing vertexes positions and mic #
         for (int i=0;i<3;i++) { x[i] = xvalue[i]; y[i] = yvalue[i]; mic[i] = micnum[i]; }
         bCoeffs = false;
         }
   };

#endif
