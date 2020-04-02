    #version 140

    uniform mat4 PVMmatrix;
    in vec3 position;
    in vec3 color;
    smooth out vec4 vertColor;

    void main() {
	    gl_Position = PVMmatrix * vec4(position, 1.0);
	    vertColor = vec4(color, 1.0);
    }