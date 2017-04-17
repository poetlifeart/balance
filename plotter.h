
#include<string>
#include <vector>
using namespace std;

// forward declare some classes we will use
class bitmap;



class plotter {
private:
    bitmap* b;
    vector<int> colors;

public:

    plotter(int w, int h);
    
   
    ~plotter();
       
    

    void plot( double x, double y, double w, double h, double direction, double depth, string stg) const;
};
