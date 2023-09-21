#include <math.h>
#include <windows.h>
#include <GL/glut.h>

float angle = 0.0f;
float posX = 0.0f, rotX = 0.0f;
float posY = 0.0f, rotY = 0.0f;
float posZ = 5.0f, rotZ = -1.0f;

float objectAngleX = 0.0f;			// sudut tranformasi obyek di sumbu X
float objectAngleY = 0.0f;			// sudut tranformasi obyek di sumbu Y
float objectAngleZ = 0.0f;			// sudut tranformasi obyek di sumbu Z

GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat mat_diffuse[] = { 0.8, 0.6, 0.4, 1.0 };
GLfloat mat_ambient[] = { 0.8, 0.6, 0.4, 1.0 };
GLfloat mat_shininess = 100.0;
GLfloat light_ambient[] = { 0.2, 0.2, 0.2, 1.0 };
GLfloat light_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
GLfloat light_specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat light_position1[] = { 1.5, 1.0, -2.0, 0.0 };
GLfloat light_position2[] = { 1.5, 1.0, 2.0, 0.0 };

int subdiv = 0;

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45, (GLfloat)w / (GLfloat)h, 1.0, 100.0);
	glMatrixMode(GL_MODELVIEW);
}

void drawTorus(int numc, int numt)
{
	int i, j, k;
	double s, t, x, y, z, twopi;

	twopi = 2 * 3.141592;

	for (i = 0; i < numc; i++)
	{
		glBegin(GL_QUAD_STRIP);
		for (j = 0; j <= numt; j++)
		{
			for (k = 1; k >= 0; k--)
			{
				s = (i + k) % numc + 0.5;
				t = j % numt;

				x = (1 + 0.1 * cos(s * twopi / numc)) * cos(t * twopi / numt);
				y = (1 + 0.1 * cos(s * twopi / numc)) * sin(t * twopi / numt);
				z = 0.1 * sin(s * twopi / numc);

				glNormal3f(x, y, z);
				glVertex3f(x, y, z);
			}
		}
		glEnd();
	}
}

void display()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(posX, posY, posZ, posX + rotX, posY + rotY, posZ + rotZ, 0.0f, 1.0f, 0.0f);

	drawTorus(5, subdiv);

	glutSwapBuffers();
}



void keyboard(int key, int x, int y){
	float fraction = 0.1f;
	switch (key){
	// masukkan perintah disini bila tombol kiri ditekan
	case GLUT_KEY_LEFT:
		// dalam hal ini perintah rotasi obyek ke kiri sebanyak 1 derajat
		objectAngleY -= 1.0f;
		glutPostRedisplay(); // update obyek
		break;
	// masukkan perintah disini bila tombol kanan ditekan
	case GLUT_KEY_RIGHT:
		// dalam hal ini perintah rotasi obyek ke kanan sebanyak 1 derajat
		objectAngleY += 1.0f;
		glutPostRedisplay(); // update obyek
		break;
	// masukkan perintah disini bila tombol atas ditekan
	case GLUT_KEY_UP:
		// dalam hal ini perintah rotasi obyek ke atas sebanyak 1 derajat
		objectAngleX -= 1.0f;
		glutPostRedisplay(); // update obyek
		break;
	// masukkan perintah disini bila tombol bawah ditekan
	case GLUT_KEY_DOWN:
		// dalam hal ini perintah rotasi obyek ke bawah sebanyak 1 derajat
		objectAngleX += 1.0f;
		glutPostRedisplay(); // update obyek
		break;
	// masukkan perintah disini bila tombol PgUp ditekan
	case GLUT_KEY_PAGE_UP:
		posX += rotX * fraction;
		posZ += rotZ * fraction;
		glutPostRedisplay(); // update obyek
		break;
	// masukkan perintah disini bila tombol PgDn ditekan
	case GLUT_KEY_PAGE_DOWN:
		posX -= rotX * fraction;
		posZ -= rotZ * fraction;
		glutPostRedisplay(); // update obyek
	case GLUT_KEY_F1:
		subdiv++; // lakukan subdivisi
		glutPostRedisplay(); // update obyek
		break;
	case GLUT_KEY_F2:
		subdiv--; // lakukan subdivisi
		glutPostRedisplay(); // update obyek
		break;
	}
	if (subdiv<0) subdiv = 0;
}
	void init(void){
	// inisialisasi warna latar belakang
	glClearColor(1.0, 1.0, 1.0, 0.0);
	glEnable(GL_DEPTH_TEST); // mengaktifkan depth buffer
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, 1.0, 1.0, 100.0);// set proyeksi ke perspektif
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// inisialisasi kamera pandang
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
	// inisialisasi pencahayaan
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialf(GL_LIGHT0, GL_SHININESS, mat_shininess);
	glMaterialf(GL_LIGHT1, GL_SHININESS, mat_shininess);
	glShadeModel(GL_SMOOTH); // aktifkan smooth shading
	glEnable(GL_LIGHTING); // aktifkan pencahayaan
	glEnable(GL_LIGHT0); // aktifkan sumber cahaya 0
	glEnable(GL_LIGHT1); // aktifkan sumber cahaya 1
}
int main(int argc, char** argv)
{
	// inisialisasi jendela OpenGL
	// GLUT_SINGLE berarti memakai single buffer
	// GLUT_DOUBLE berarti memakai double buffer
	// GLUT_RGB berarti mode tampilan yang dipakai RGB
	// GLUT_RGBA berarti mode tampilan yang dipakai RGBA
	// GLUT_DEPTH berarti memakai depth buffer
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	// set ukuran jendela tampilan
	glutInitWindowSize(480, 480);		// besarnya jendela dalam piksel dalam hal ini 480x480
	glutInitWindowPosition(100, 100);	// posisi jendela dilayar komputer dalam piksel
	// judul jendela (wajib diubah dengan informasi NAMA / NIM - JUDUL PRAKTIKUM masing-masing)
	glutCreateWindow("BINTI SHOLIKHAH / 2100018299 - POSTEST 9 PRAKTIKUM GRAFIKA KOMPUTER");
	// panggil fungsi init untuk inisialisasi awal
	init();
	// event handler untuk display, reshape dan keyboard
	glutDisplayFunc(display);   // display
	glutReshapeFunc(reshape);   // reshape
	glutSpecialFunc(keyboard);  // keyboard
	//glutTimerFunc(0, timer, 0); // aktifkan timer bila perlu
	// looping
	glutMainLoop();

	return 0;
}
