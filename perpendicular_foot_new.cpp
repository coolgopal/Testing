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


CFCoord CalculatePtToLineCoord(const CFCoord &oCoord,
                              const CFCoord &oLineStartPt,
                              const CFCoord &oLineEndPt)
{
    double x4 = ((oLineStartPt.X * oLineStartPt.X * oCoord.X) 
    - (2 * oLineStartPt.X * oLineEndPt.X * oCoord.X)
    + (oLineEndPt.X * oLineEndPt.X * oCoord.X)
    + (oLineEndPt.X * (oLineStartPt.Y - oLineEndPt.Y) * (oLineStartPt.Y - oCoord.Y))
    - (oLineStartPt.X * (oLineStartPt.Y - oLineEndPt.Y) * (oLineEndPt.Y - oCoord.Y)))
    / (((oLineEndPt.X - oLineStartPt.X)*(oLineEndPt.X - oLineStartPt.X)) 
    + ((oLineEndPt.Y - oLineStartPt.Y)*(oLineEndPt.Y - oLineStartPt.Y)));

    double y4 = ((oLineEndPt.X - oLineStartPt.X)*((oCoord.X * (oLineEndPt.Y - oLineStartPt.Y))
    - (oLineStartPt.X * oLineEndPt.Y) + (oLineEndPt.X * oLineStartPt.Y))
    + ((oLineStartPt.Y - oLineEndPt.Y) * (oLineStartPt.Y - oLineEndPt.Y) * oCoord.Y))
    / (((oLineEndPt.X - oLineStartPt.X)*(oLineEndPt.X - oLineStartPt.X)) 
    + ((oLineEndPt.Y - oLineStartPt.Y)*(oLineEndPt.Y - oLineStartPt.Y)));
    
    return CFCoord(x4, y4);
}

int main()
{
    printf("new formula:\n");
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
new formula:
line segment: A(1,1), B(4,4)   point: C(1,4)   perpendicular foot: D(2.500000, 2.500000)
line segment: A(1,1), B(4,4)   point: C(2,3)   perpendicular foot: D(2.500000, 2.500000)
line segment: A(1,1), B(4,1)   point: C(2,4)   perpendicular foot: D(2.000000, 1.000000)
line segment: A(1,1), B(4,1)   point: C(4,1)   perpendicular foot: D(2.500000, 2.500000)
**/