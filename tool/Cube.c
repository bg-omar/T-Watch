const LuI::RawVertex3D CubeVertex[8] = { {-31.514444,-31.514444,-31.514444}, {-31.514444,-31.514444,31.514444}, {-31.514444,31.514444,-31.514444}, {-31.514444,31.514444,31.514444}, {31.514444,-31.514444,-31.514444}, {31.514444,-31.514444,31.514444}, {31.514444,31.514444,-31.514444}, {31.514444,31.514444,31.514444},  };
const LuI::RawFace3D CubeFace[12] = { {0x07E0,false,{1,2,0,},},{0xFFE0,false,{3,6,2,},},{0x001F,false,{7,4,6,},},{0xFFFF,false,{5,0,4,},},{0xF860,false,{6,0,2,},},{0xF800,false,{3,5,7,},},{0x07E0,false,{1,3,2,},},{0xFFE0,false,{3,7,6,},},{0x001F,false,{7,5,4,},},{0xFFFF,false,{5,1,0,},},{0xF860,false,{6,4,0,},},{0xF800,false,{3,1,5,},},};
const LuI::RawNormal3D CubeNormal[12] = { {-1.000000,0.000000,0.000000,},{0.000000,1.000000,-0.000000,},{1.000000,0.000000,-0.000000,},{0.000000,-1.000000,0.000000,},{0.000000,0.000000,-1.000000,},{0.000000,0.000000,1.000000,},{-1.000000,0.000000,0.000000,},{0.000000,1.000000,-0.000000,},{1.000000,0.000000,0.000000,},{0.000000,-1.000000,0.000000,},{0.000000,0.000000,-1.000000,},{0.000000,-0.000000,1.000000,},};
const LuI::Mesh3DDescriptor CubeMesh = {8,12,CubeVertex,CubeFace,CubeNormal};