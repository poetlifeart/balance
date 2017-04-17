

#include <vector>
#include <string>
using namespace std;



class bitmap {
private:
    vector<vector<int> > lines;
    
    // no copying or assignment
    bitmap(const bitmap&);
    bitmap& operator=(const bitmap&);

public:

    bitmap(int w, int h);
    
    int shift=10;
    
    /// Width of the bitmap, in pixels.
    const int width;
    
    /// Height of the bitmap, in pixels.
    const int height;
    
    

    inline int getpixel(int x, int y) const
    {
        // use checked at() function
        const vector<int>& line = lines.at(y);
        return line.at(x);
    }
    
    
    
    
    inline void putpixel(int x, int y, int pixel)
    {
        // use checked at() function
        vector<int>& line = lines.at(y);
        line.at(x) = pixel;
    }
    
    
    
   
    void save(const string& filename) const;
};


