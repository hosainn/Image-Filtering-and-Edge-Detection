
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include<math.h>

using namespace std;

struct pixel{
   unsigned char R;
   unsigned char G;
   unsigned char B;

}ImData[1000][1000];
int height;
int width;
int Max=0;
int Min=255;

struct pixe{
   int R;
   int G;
   int B;

}newdata[1000][1000];


int im[1000][1000];
int salt[1000][1000];
int amplitude[1000][1000];
int phase[1000][1000];
int nonmaximum[1000][1000];
int high_threshold[1000][1000];
int low_threshold[1000][1000];





void orginal()
{
glBegin(GL_POINTS);
 int x=0;
 int y=0;
 float i,j;
float p=255.000;
float fr,fg,fb;
for( i=0.0;i<float(height/100.00);i+=0.01){
   y=30;
   for(j=0.0;j<float(width/100.00);j+=0.01){
   int b=newdata[x][y].B;
   int g=newdata[x][y].G;
   int r=newdata[x][y].R;
    fr=r/p;
    fg=g/p;
    fb=b/p;
   //printf("%d ,",(int)ImData[x][y].R);
glColor3f(fr,fg,fb);
glVertex2f(j-3.0,i-3.0);
y++;
}
x++;
}

glEnd();
}


void monogram()
{
glBegin(GL_POINTS);
 int x=0;
 int y=0;
 float i,j;
float p=255.000;
float fr,fg,fb;
for( i=0.0;i<float(height/100.00);i+=0.01){
   y=30;
   for(j=0.0;j<float(width/100.00);j+=0.01){
   int b=newdata[x][y].B;
   int g=newdata[x][y].G;
   int r=newdata[x][y].R;
   int av=(b+g+r)/3;
    im[x][y]=av;
    fr=av/p;
    fg=av/p;
    fb=av/p;
   //printf("%d ,",(int)ImData[x][y].R);
glColor3f(fr,fg,fb);
glVertex2f(j-3.0,i-3.0);
y++;
}
x++;
}

glEnd();
}

void Gaussian(){
int new_height=height-1;
int new_width=width-1;
int x,y;
int dy,dx;

for(x=1;x<new_height;x++){
   for(y=1;y<new_width;y++){
       salt[x][y]=((4*im[x][y]+2*im[x][y+1]+2*im[x][y-1]+2*im[x+1][y]+im[x+1][y+1]+im[x+1][y-1]+2*im[x-1][y]+im[x-1][y+1]+im[x-1][y-1])/16);

   }

}
glBegin(GL_POINTS);
  x=1;
  y=1;
 float i,j;
float p=255.000;
float fr,fg,fb;
for( i=0.0;i<float(height/100.00);i+=0.01){
   y=30;
   for(j=0.0;j<float(width/100.00);j+=0.01){
   int b=salt[x][y];
   int g=salt[x][y];
   int r=salt[x][y];
   int av=(b+g+r)/3;


    fr=av/p;
    fg=av/p;
    fb=av/p;

glColor3f(fr,fg,fb);
glVertex2f(j-3.0,i-3.0);
y++;
}
x++;
}

glEnd();


}

void Sobel(){
int new_height=height-1;
int new_width=width-1;
int x,y;
int dy,dx;
for(x=1;x<new_height;x++){
   for(y=1;y<new_width;y++){
      dx=((salt[x+1][y+1] +2*salt[x+1][y]+salt[x+1][y-1])-(salt[x-1][y+1]+2*salt[x-1][y]+salt[x-1][y-1]))/8;
	  dy=(((salt[x+1][y+1]+2*salt[x][y+1]+salt[x-1][y+1])-(salt[x+1][y-1]+2*salt[x][y-1]+salt[x-1][y-1]))/8);
	  amplitude[x][y]=sqrt((dx*dx)+(dy*dy));
      if(dx>0&&dy>0&&(abs(dx)>abs(dy)))
        phase[x][y]=0;
      else if(dx>0&&dy>0&&(abs(dx)<abs(dy)))
            phase[x][y]=45;

      else if(dx>0&&dy<0&&(abs(dx)<abs(dy)))
            phase[x][y]=90;

      else if(dx<0&&dy>0&&(abs(dx)>abs(dy)))
            phase[x][y]=135;
      else if(dx<0&&dy<0&&(abs(dx)>abs(dy)))
            phase[x][y]=180;

      else if(dx<0&&dy<0&&(abs(dx)<abs(dy)))
            phase[x][y]=225;
      else if(dx>0&&dy<0&&(abs(dx)<abs(dy)))
            phase[x][y]=270;
      else if(dx>0&&dy<0&&(abs(dx)>abs(dy)))
            phase[x][y]=315;

   }

}
glBegin(GL_POINTS);
  x=1;
  y=1;
 float i,j;
float p=255.000;
float fr,fg,fb;
for( i=0.0;i<float(height/100.00);i+=0.01){
   y=30;
   for(j=0.0;j<float(width/100.00);j+=0.01){
   int b=amplitude[x][y];
   int g=amplitude[x][y];
   int r=amplitude[x][y];
   int av=(b+g+r)/3;


    fr=av/p;
    //if (fr>0.040) fr=1.00;


glColor3f(fr,fr,fr);
glVertex2f(j-3.0,i-3.0);
y++;
}
x++;
}

glEnd();


}



void Nonmaximum(){
 int new_height=height-1;
int new_width=width-1;
int x,y;
int dy,dx;
for(x=1;x<new_height;x++){
   for(y=1;y<new_width;y++){
      if(phase[x][y]==45){
        if((amplitude[x][y]<amplitude[x+1][y+1])||(amplitude[x][y]<amplitude[x-1][y-1]))
            nonmaximum[x][y]=0;
        else nonmaximum[x][y]=amplitude[x][y];
      }

      else  if(phase[x][y]==90){
        if((amplitude[x][y]<amplitude[x][y+1])||(amplitude[x][y]<amplitude[x][y-1]))
            nonmaximum[x][y]=0;
        else nonmaximum[x][y]=amplitude[x][y];
      }

        else  if(phase[x][y]==135){
        if((amplitude[x][y]<amplitude[x-1][y+1])||(amplitude[x][y]<amplitude[x+1][y-1]))
            nonmaximum[x][y]=0;
        else nonmaximum[x][y]=amplitude[x][y];
      }

        else  if(phase[x][y]==180){
        if((amplitude[x][y]<amplitude[x-1][y])||(amplitude[x][y]<amplitude[x+1][y]))
            nonmaximum[x][y]=0;
        else nonmaximum[x][y]=amplitude[x][y];
      }

        else  if(phase[x][y]==225){
        if((amplitude[x][y]<amplitude[x-1][y-1])||(amplitude[x][y]<amplitude[x+1][y+1]))
            nonmaximum[x][y]=0;
        else nonmaximum[x][y]=amplitude[x][y];
      }

        else  if(phase[x][y]==270){
        if((amplitude[x][y]<amplitude[x][y-1])||(amplitude[x][y]<amplitude[x][y+1]))
            nonmaximum[x][y]=0;
        else nonmaximum[x][y]=amplitude[x][y];
      }

        else  if(phase[x][y]==315){
        if((amplitude[x][y]<amplitude[x+1][y-1])||(amplitude[x][y]<amplitude[x-1][y+1]))
            nonmaximum[x][y]=0;
        else nonmaximum[x][y]=amplitude[x][y];
      }

        else  if(phase[x][y]==0){
        if((amplitude[x][y]<amplitude[x+1][y])||(amplitude[x][y]<amplitude[x-1][y]))
            nonmaximum[x][y]=0;
        else nonmaximum[x][y]=amplitude[x][y];
      }



   }

}
glBegin(GL_POINTS);
  x=1;
  y=1;
 float i,j;
float p=255.000;
float fr,fg,fb;
for( i=0.0;i<float(height/100.00);i+=0.01){
   y=30;
   for(j=0.0;j<float(width/100.00);j+=0.01){
   int b=nonmaximum[x][y];
   int g=nonmaximum[x][y];
   int r=nonmaximum[x][y];
   int av=(b+g+r)/3;


    fr=av/p;

    //if (fr>0.040) fr=1.00;


glColor3f(fr,fr,fr);
glVertex2f(j-3.0,i-3.0);
y++;
}
x++;
}

glEnd();


}


void High_threshold(){
int new_height=height-1;
int new_width=width-1;
int x,y;
int dy,dx;
for(x=1;x<new_height;x++){
   for(y=1;y<new_width;y++){
       if(nonmaximum[x][y]>25)
           high_threshold[x][y]=nonmaximum[x][y];
       else high_threshold[x][y]=0;



   }

}
glBegin(GL_POINTS);
  x=1;
  y=1;
 float i,j;
float p=255.000;
float fr,fg,fb;
for( i=0.0;i<float(height/100.00);i+=0.01){
   y=30;
   for(j=0.0;j<float(width/100.00);j+=0.01){
    int av=high_threshold[x][y];


    fr=av/p;
    //if (fr>0.040) fr=1.00;


glColor3f(fr,fr,fr);
glVertex2f(j-3.0,i-3.0);
y++;
}
x++;
}

glEnd();


}

void Low_threshold(){
int new_height=height-1;
int new_width=width-1;
int x,y;
int dy,dx;
for(x=1;x<new_height;x++){
   for(y=1;y<new_width;y++){


       if((nonmaximum[x][y]>10)&&(nonmaximum[x][y]<=25))
             low_threshold[x][y]=nonmaximum[x][y];
       else low_threshold[x][y]=0;


   }

}
glBegin(GL_POINTS);
  x=1;
  y=1;
 float i,j;
float p=255.000;
float fr,fg,fb;
for( i=0.0;i<float(height/100.00);i+=0.01){
   y=30;
   for(j=0.0;j<float(width/100.00);j+=0.01){
    int av=low_threshold[x][y];


    fr=av/p;
    //if (fr>0.040) fr=1.00;


glColor3f(fr,fr,fr);
glVertex2f(j-3.0,i-3.0);
y++;
}
x++;
}

glEnd();


}




void display1(void)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluOrtho2D(-3, 3, -3, 3);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glViewport(0, 0,512,512);
orginal();



glFlush();
glutSwapBuffers();
}


void display2(void)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluOrtho2D(-3, 3, -3, 3);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glViewport(0, 0,512,512);
monogram();


glFlush();
glutSwapBuffers();
}



void display3(void)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluOrtho2D(-3, 3, -3, 3);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glViewport(0, 0,512,512);
Gaussian();


glFlush();
glutSwapBuffers();
}


void display4(void)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluOrtho2D(-3, 3, -3, 3);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glViewport(0, 0,512,512);
Sobel();


glFlush();
glutSwapBuffers();
}



void display5(void)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluOrtho2D(-3, 3, -3, 3);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glViewport(0, 0,512,512);
Nonmaximum();


glFlush();
glutSwapBuffers();
}


void display6(void)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluOrtho2D(-3, 3, -3, 3);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glViewport(0, 0,512,512);
High_threshold();


glFlush();
glutSwapBuffers();
}




void display7(void)
{
glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
glMatrixMode( GL_PROJECTION );
glLoadIdentity();
gluOrtho2D(-3, 3, -3, 3);
glMatrixMode( GL_MODELVIEW );
glLoadIdentity();
glViewport(0, 0,512,512);
Low_threshold();


glFlush();
glutSwapBuffers();
}






int main (int argc, char **argv){
unsigned char bitmapheader[54];
char filename[30];

int bytevalue;
int index=0;
printf("Enter a BMP image for processing: ");
scanf("%s",filename);
FILE *file;
file=fopen(filename,"rb");
if(file!=NULL){
    do{
        bytevalue=fgetc(file);
       bitmapheader[index]=bytevalue;
        index++;
        //cout<<index<<"  :"<<bytevalue<<endl;

        if(index==54) break;

    }while(bytevalue!=EOF);

}else {
   for(int i=0;i<29;i++)
       bitmapheader[i]='\0';
}

int image_width = bitmapheader[20-1]*256 + bitmapheader[19-1];
int image_height=bitmapheader[24-1]*256 + bitmapheader[23-1];
int image_bits=bitmapheader[29-1];

  height=image_height;
  width=image_width;

int pad=(image_width*3+3) & (~3);

unsigned char *pix=(unsigned char*)malloc(pad);
int z=0,l=0;
for(int f=0;f<height;f++){
           fread(pix, sizeof(unsigned char), pad, file);
       z=0;
    for(int j=0;j<width*3;j=j+3){
        newdata[l][z].R=(int)pix[j+2];
        newdata[l][z].G=(int)pix[j+1];
        newdata[l][z].B=(int)pix[j];

        z++;
    }
    l++;

}


fclose(file);

glutInit(&argc, argv);
glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB| GLUT_DEPTH);
glutInitWindowPosition(100,100);
glutInitWindowSize(411,436);


int window_1,window_2,window_3,window_4,window_5,window_6,window_7,window_8,window_9,window_10;


window_7 = glutCreateWindow (argv[0]);
glutSetWindowTitle("Low_threshold");
glutDisplayFunc(display7);

window_6 = glutCreateWindow (argv[0]);
glutSetWindowTitle("High_threshold");
glutDisplayFunc(display6);


window_5 = glutCreateWindow (argv[0]);
glutSetWindowTitle("Nonmaximum");
glutDisplayFunc(display5);

window_4 = glutCreateWindow (argv[0]);
glutSetWindowTitle("soble");
glutDisplayFunc(display4);


window_3 = glutCreateWindow (argv[0]);
glutSetWindowTitle("Gaussian");
glutDisplayFunc(display3);

window_2 = glutCreateWindow (argv[0]);
glutSetWindowTitle("Monogram");
glutDisplayFunc(display2);


window_1 = glutCreateWindow (argv[0]);
glutSetWindowTitle("Orginal");
glutDisplayFunc(display1);














glutMainLoop();

return 0;
}
