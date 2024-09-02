#define WIDTH 1000.0f
#define HEIGHT 1000.0f

 
struct color { 
	int r, g, b, a; 
};

void preRender(); 
void render(); 
void setColor(struct color color); 
