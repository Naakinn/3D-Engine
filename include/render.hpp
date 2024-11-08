#ifndef __render_h_
#define __render_h_

void vertexSpec(); 
void shaderSpec(const char* vertex, const char* fragment); 
void preDraw(bool culling = true);
void draw();
void getInfo(); 

#endif
