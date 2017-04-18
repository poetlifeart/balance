#include "plotter.h"
#include "bitmap.h"
#include <thread>
#include <iostream>


// quick function to make a pixel given constituent colors
inline int make_rgb(int r, int g, int b)
{
    return (b << 16) | (g << 8) | r;
}



plotter::plotter(int w, int h)
    : b(new bitmap(w, h))
{
    // choose some colors
    colors.reserve(1000); // for efficiency's sake
    
    // fade from blue to purple
    for(int j = 0; j < 256; j += 16) colors.push_back(make_rgb(j, 0, 255));
    // fade from purple to red
    for(int k = 0; k < 256; k += 16) colors.push_back(make_rgb(255, 0, 255 - k));
    // fade from red to yellow
    for(int f = 0; f < 256; f += 16) colors.push_back(make_rgb(255, f, 0));
    
    // last color is black
    colors.push_back(0);
}

plotter::~plotter()
{
    delete b;
}






void plotter::plot( double x, double y, double w, double h, double direction, double depth, string stg) const
{
    string filename = stg+"tree.tga";

    
    
    
    for(int col = 0; col < b->width/(h*depth); ++col) 
     
       	double Y =y-col;
 
    for(int r =0; r <30 ; ++r) {
 
         double X =x+(direction*col+r);
        
         
          int    esc = 5  ;    
            
         if (col > b->width/(h*depth)*0.90 ) esc=20;
         this->b->putpixel(X, Y, colors[esc]);
            
        }
        
    }

    b->save(filename);
       cout << endl;    
   
}

    
    
 
