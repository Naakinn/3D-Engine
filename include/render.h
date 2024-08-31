#define WIDTH 1000.0
#define HEIGHT 1000.0
#define PI 3.1415926

 
struct color { 
	int r, g, b, a; 
};

void prepRender(); 
void render(); 
void setColor(struct color color); 
