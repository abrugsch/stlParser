# stlParser
A simple parser of binary .stl 3D files to .txt representations.

**NOTE** 
stlParser MUST be compiled with a structure alignment of 1 or 2 bytes (default is often 4 bytes) otherwise strange and interesting things may happen. In all likelyhood nothing bad will happen, but SIZEOF may report the size of the STL_DATA structure incorrectly which will throw off the alignment with the .stl internal structure

usage:

    stlparser <path/to/filename>.stl

output:

    <path/to/filename>.txt
    
    
The parser will output a textfile with the same name (but .txt extension) containing a list of all the triangles represented in the .stl

    Triangle 3
    Normal i: 0
    Normal j: -1
    Normal k: 0
    Vert 1 x: 2.11832
    Vert 1 y: 0.002
    Vert 1 z: 0
    Vert 2 x: 7.88168
    Vert 2 y: 0.002
    Vert 2 z: 0
    Vert 3 x: 4.9902
    Vert 3 y: 0.002
    Vert 3 z: 5.76394
    Attribute count: 3967

at the end of the file it will also generate a list of just the individual vertexes in x,y,z space. This may be of use for creating meshes for use in simple environments such as Pico-8

    Vertex 0:0,2,0
    Vertex 1:10,2,0
    Vertex 2:2.11832,0.002,0
    Vertex 3:2.11832,3.998,0
    Vertex 4:4.983,2,10.001
    Vertex 5:4.9902,0.002,5.76394
    Vertex 6:4.9902,3.998,5.76394
    Vertex 7:7.88168,0.002,0
    Vertex 8:7.88168,3.998,0

