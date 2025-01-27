#ifndef __render_h_
#define __render_h_

#include <stdbool.h>

void vertexSpec();
void shaderSpec(const char* vertex, const char* fragment);
void preDraw(bool culling);
void draw();
void getInfo();

#endif
