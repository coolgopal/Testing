/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <stdio.h>
#include <math.h>

#define TWO_PI    (2.0f * M_PI)

class CCoordBasic
{
public:
	CCoordBasic(int X_, int Y_): X(X_), Y(Y_) { };
    int X;
    int Y;
};

class CCoord : public CCoordBasic
{
public:
    CCoord();  //default constructor
    CCoord(int p_lX, int p_lY); //constructor
    CCoord(int p_lID, int p_lX, int p_lY);

    void SetID(int p_lID);
    int GetID() const;
private:
    int ID;
};

class CFCoord
{
public:
    double X;
    double Y;
    CFCoord();  //default constructor
    CFCoord(double p_fX, double p_fY): ID(-1), X(p_fX), Y(p_fY){}; //constructor
    CFCoord(int p_lID, double p_fX, double p_fY);

    void SetID(int p_lID);
    int GetID() const;

private:
    int ID;
};

double CalculateDistance(const CFCoord &oCoord1, const CFCoord &oCoord2)
{
	double sqrRt_Dist = std::sqrt(std::pow(double(oCoord1.X - oCoord2.X), 2) + std::pow(double(oCoord1.Y - oCoord2.Y), 2));
    return sqrRt_Dist;
}

double CalculateAngleOfGrad(const CFCoord &oVectorCoord)
{
    return std::atan2(double(oVectorCoord.Y), double(oVectorCoord.X));
}

double CalculateAngleBtwnTwoLines(const CFCoord &oIntersectPt,
                                  const CFCoord &oLine1EndPt,
                                  const CFCoord &oLine2EndPt)
{
    if (!(oIntersectPt.X - oLine1EndPt.X) || !(oIntersectPt.X - oLine2EndPt.X))
//TODO: assert(0);
        return 0;

    //calculates the angle of the lines using intersect as the origin
    //hence offset the end points to the new origin
    double dAngle1 = CalculateAngleOfGrad(CFCoord(oLine1EndPt.X - oIntersectPt.X,
                                              oLine1EndPt.Y - oIntersectPt.Y));
    double dAngle2 = CalculateAngleOfGrad(CFCoord(oLine2EndPt.X - oIntersectPt.X,
                                              oLine2EndPt.Y - oIntersectPt.Y));

    double dAngleDiff = dAngle2 - dAngle1;  //with ref to angle 1
    //printf("angle2=%f, angle1=%f\n", dAngle2, dAngle1);

    //return only smaller of the angle if the angle is more than pi or less than
    //-pi
    if (dAngleDiff < -M_PI)
        dAngleDiff += TWO_PI;
    else if (dAngleDiff > M_PI)
        dAngleDiff = dAngleDiff - TWO_PI;

    return dAngleDiff;
}


CFCoord CalculatePtToLineCoord(const CFCoord &oCoord,
                              const CFCoord &oLineStartPt,
                              const CFCoord &oLineEndPt)
{
    double lLineXDiff = oLineEndPt.X - oLineStartPt.X;
    double lLineYDiff = oLineEndPt.Y - oLineStartPt.Y;
    //printf("lLineXDiff=%f\n", lLineXDiff);
    //printf("lLineYDiff=%f\n", lLineYDiff);

    //calculates the dot product
    double dDotProduct = (double(oCoord.X - oLineStartPt.X) * lLineXDiff) +
                         (double(oCoord.Y - oLineStartPt.Y) * lLineYDiff);

    if (dDotProduct < 0)  //point is beyond the LineStartPt
        return oLineStartPt;
    else //calculation is to determine whether the line is within the line segment
    {
        dDotProduct = (double(oLineEndPt.X - oCoord.X) * lLineXDiff) +
                      (double(oLineEndPt.Y - oCoord.Y) * lLineYDiff);

        if (dDotProduct < 0)  //line is beyond LineEndPt
            return oLineEndPt;
    }

    //if the code reaches here, the coord is within segment, so can calculate
    //the foot of perpendicular
    double dAngle = CalculateAngleBtwnTwoLines(oLineStartPt, oLineEndPt, oCoord);
    //printf("angle=%f\n", dAngle);

    //calculates the dist from the line start pt to the end pt and the pt
    double dLineDist = CalculateDistance(oLineStartPt, oLineEndPt);
    double dLineToPtDist = CalculateDistance(oLineStartPt, oCoord);

    //calculates the dist from the line start to the foot of perpendicular
    //using cos formula cos(-Q) = cos Q
    double dLineToFootDist = std::cos(dAngle) * dLineToPtDist;
    //printf("dLineDist=%f, dLineToPtDist=%f, dLineToFootDist=%f\n", dLineDist, dLineToPtDist, dLineToFootDist);
    
    //locate and return the exact pt on the line using parameter
    return CFCoord((oLineStartPt.X + lLineXDiff * (dLineToFootDist / dLineDist)),
                   (oLineStartPt.Y + lLineYDiff * (dLineToFootDist / dLineDist)));
}

int main()
{
    printf("legacy formula:\n");
    CFCoord perpendicular_foot = CalculatePtToLineCoord(CFCoord(1,4), CFCoord(1,1), CFCoord(4,4));
    printf("line segment: A(1,1), B(4,4)   point: C(1,4)   ");
    printf("perpendicular foot: D(%f, %f)\n", perpendicular_foot.X, perpendicular_foot.Y);
    CFCoord perpendicular_foot2 = CalculatePtToLineCoord(CFCoord(2,3), CFCoord(1,1), CFCoord(4,4));
    printf("line segment: A(1,1), B(4,4)   point: C(2,3)   ");
    printf("perpendicular foot: D(%f, %f)\n", perpendicular_foot2.X, perpendicular_foot2.Y);
    CFCoord perpendicular_foot3 = CalculatePtToLineCoord(CFCoord(2,4), CFCoord(1,1), CFCoord(4,1));
    printf("line segment: A(1,1), B(4,1)   point: C(2,4)   ");
    printf("perpendicular foot: D(%f, %f)\n", perpendicular_foot3.X, perpendicular_foot3.Y);
    CFCoord perpendicular_foot4 = CalculatePtToLineCoord(CFCoord(4,1), CFCoord(1,1), CFCoord(4,4));
    printf("line segment: A(1,1), B(4,1)   point: C(4,1)   ");
    printf("perpendicular foot: D(%f, %f)\n", perpendicular_foot4.X, perpendicular_foot4.Y);

    return 0;
}

/**
legacy formula:
line segment: A(1,1), B(4,4)   point: C(1,4)   perpendicular foot: D(3.121320, 3.121320)
line segment: A(1,1), B(4,4)   point: C(2,3)   perpendicular foot: D(2.500000, 2.500000)
line segment: A(1,1), B(4,1)   point: C(2,4)   perpendicular foot: D(2.000000, 1.000000)
line segment: A(1,1), B(4,1)   point: C(4,1)   perpendicular foot: D(2.500000, 2.500000)
**/