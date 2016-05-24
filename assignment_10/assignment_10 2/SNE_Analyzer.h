

#ifndef SNE_Analyzer_H
#define SNE_Analyzer_H

#include "StarNearEarth.h"
#include "FHsparseMat.h"
#include <cmath>

class SNE_Analyzer: public StarNearEarth
{
private:
   const double PI = 3.1415926535897;
   double x, y, z;

public:
   void calcCartCoords();
   double getX() { return x; }
   double getY() { return y; }
   double getZ() { return z; }
   string coordToString();
   SNE_Analyzer & operator=( const StarNearEarth &sne );
};

void SNE_Analyzer::calcCartCoords()
{
   double ly, raRAD, decRAD;

   ly = 3.262/getParallaxMean();
   raRAD = getRAsc() * (PI/180);
   decRAD = getDec() * (PI/180);

   x = ly * cos(decRAD) * cos(raRAD);
   y = ly * cos(decRAD) * sin(raRAD);
   z = ly * sin(decRAD);

}
string SNE_Analyzer::coordToString()
{
   string xString,yString,zString, coord;
   xString = to_string(x);
   yString = to_string(y);
   zString = to_string(z);
   return coord = "x: " + xString + "; y: " + yString + "; z: " + zString;
}

SNE_Analyzer & SNE_Analyzer::operator=( const StarNearEarth &sne )
{

   setRank(sne.getRank());
   setNameCns(sne.getNameCns());
   setNumComponents(sne.getNumComponents());
   setNameLhs(sne.getNameLhs());
   setRAsc(sne.getRAsc());
   setDec(sne.getDec());
   setPropMotionMag(sne.getPropMotionMag());
   setPropMotionDir(sne.getPropMotionDir());
   setParallaxMean(sne.getParallaxMean());
   setParallaxVariance(sne.getParallaxVariance());
   setWhiteDwarfFlag(sne.getWhiteDwarfFlag());
   setSpectralType(sne.getSpectralType());
   setMagApparent(sne.getMagApparent());
   setMagAbsolute(sne.getMagAbsolute());
   setMass(sne.getMass());
   setNotes(sne.getNotes());
   setNameCommon(sne.getNameCommon());
   calcCartCoords();

   return *this;
}

#endif