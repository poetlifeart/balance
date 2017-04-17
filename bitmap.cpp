

#include "bitmap.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>



bitmap::bitmap(int w, int h)
    : width(w), height(h)
{
    // check to make sure we have a legal size
    if(w <= 0 || h <= 0) throw out_of_range("bitmap");
    
    // resize the array of lines to match the height
    lines.resize(h);
    
    // resize each line to match the width
    for(int y = 0; y < h; ++y) lines.at(y).resize(w);
}



void bitmap::save(const string& filename) const
{
    // open file in binary mode
    ofstream file(filename.c_str(), ios::binary);
    if(!file) {
        // construct an exception
        ostringstream s;
        s << "Could not open '" << filename << "' for writing.";
        throw s.str();
    }
    
    // write out the header
    file.put(0); // length of image ID field (we don't have one)
    file.put(0); // no color map
    file.put(2); // image type (pure uncompressed RGB data)
    file.put(0); // color map data...
    file.put(0);
    file.put(0);
    file.put(0);
    file.put(0);
    file.put(0); // X origin...
    file.put(0);
    file.put(0); // Y origin...
    file.put(0);
    file.put(width & 0xFF); // width...
    file.put((width >> 8) & 0xFF);
    file.put(height & 0xFF); // height...
    file.put((height >> 8) & 0xFF);
    file.put(24); // bits per pixel
    file.put(0); // no attributes, no interleaving, origin is bottom left
    
    // write out each of the lines
    for(int y = 0; y < height; ++y) {
        const vector<int>& line = lines[y];
        for(int x = 0; x < width; ++x) {
            int pixel = line[x];
            
            file.put((pixel >> 16) & 0xFF);
            file.put((pixel >> 8) & 0xFF);
            file.put(pixel & 0xFF);
        }
    }
}


