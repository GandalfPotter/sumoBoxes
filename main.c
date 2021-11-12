#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <GLFW/glfw3.h>

//vars
float bgR=200.0f;
float bgG=0.0f;
float bgB=200.0f;

float tfSpeed=0.001f;

float triTfX=0.0f;
float triTfY=0.0f;
float dtriTfX=0.0f;
float dtriTfY=0.0f;
float triPosX=-0.8f;
float triPosY=0.0f;

float triTfX2=0.0f;
float triTfY2=0.0f;
float dtriTfX2=0.0f;
float dtriTfY2=0.0f;
float triPosX2=0.8f;
float triPosY2=0.0f;



int wrapAround=0;

//input function
static void key_callback(GLFWwindow*window, int key, int scancode, int action, int mods)
{

if(key==GLFW_KEY_ESCAPE && action==GLFW_PRESS)
{
glfwSetWindowShouldClose(window, GLFW_TRUE);
}

//reset tri pos (not used rn)
/*
if(key==GLFW_KEY_LEFT_CONTROL && action==GLFW_PRESS)
{
triTfX=0.0f;
triTfY=0.0f;
}
*/

//toggle wraparound (not used rn)
/*
if(key==GLFW_KEY_M)
{
wrapAround=1;
}
if(key==GLFW_KEY_N)
{
wrapAround=0;
}
*/

//player 1 movex
if(key==GLFW_KEY_D)
{
triTfX+=tfSpeed;
}
if(key==GLFW_KEY_A)
{
triTfX-=(tfSpeed);
}

//player 1 movey
if(key==GLFW_KEY_W)
{
triTfY+=tfSpeed;
}
if(key==GLFW_KEY_S)
{
triTfY-=tfSpeed;
}

//player 2 movex
if(key==GLFW_KEY_RIGHT)
{
triTfX2+=tfSpeed;
}
if(key==GLFW_KEY_LEFT)
{
triTfX2-=(tfSpeed);
}

//player 2 movey
if(key==GLFW_KEY_UP)
{
triTfY2+=tfSpeed;
}
if(key==GLFW_KEY_DOWN)
{
triTfY2-=tfSpeed;
}

}

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

void resetPlayers()
{
triPosX=-0.8f;
triTfX=0.0f;
triPosY=-0.0f;
triTfY=0.0f;
triPosX2=0.8;
triTfX2=0.0f;
triPosY2=-0.0f;
triTfY2=0.0f;
}

int main(void)
{

if(!glfwInit())
{
printf("glfw was unable to initialize    TOT\n");
}
else{printf("glfw was successfully initialized!    :D\n");}


GLFWwindow* window = glfwCreateWindow(640, 480, "among us in real life", NULL, NULL);
glfwSetKeyCallback(window,key_callback);

if(!window)
{
printf("the window couldnt be created    TOT\n");
return -1;
}
else
{
printf("the window was successfully created!    :D\n");
}

glfwMakeContextCurrent(window);

glfwSwapInterval(1);

int width, height;
glfwGetFramebufferSize(window, &width, &height);
glViewport(0,0,width,height);
glClearColor(0.0f,0.0f,0.0f,0.0f);

printf("app is running nice and good    :D\n");

printf("----------\nsumo boxing!\n\n");
printf("rules:\ntry to knock the other player into the edge of the screen\n\n");
printf("controls:\n[W,A,S,D] for player 1 movement\narrow keys for player 2 movement\n[ESC] quit\n\n");
printf("bugs:\nyou must spam the key to move without stopping\n\n");
printf("have fun!\n\n");

while(!glfwWindowShouldClose(window))
{
//input & calc
glfwPollEvents();

//calculate player 1
if(triPosX>=0.92f || triPosX <= -0.92f)
{
if(bgR>0.0f)
{
//resetPlayers();
//bgR-=50.0f;
resetPlayers();
bgR=255.0f;
bgB=255.0f;
glClearColor(0,0,0.2,0);
}
else
{
resetPlayers();
bgR=255.0f;
bgB=255.0f;
glClearColor(0,0,0.2,0);
}
}
if(triPosY>=0.92f || triPosY <= -0.92f)
{
if(bgR>0.0f)
{
//resetPlayers();
//bgR-=50.0f;
resetPlayers();
bgR=255.0f;
bgB=255.0f;
glClearColor(0,0,0.2,0);
}
else
{
resetPlayers();
bgR=255.0f;
bgB=255.0f;
glClearColor(0,0,0.2,0);
}
}

//calculate player interaction with eachother
if(triPosX>triPosX2-0.12f&&triPosX<triPosX2+0.12f)
{
if(triPosY>triPosY2-0.2f&&triPosY<triPosY2+0.2f)
{
dtriTfX=triTfX2;
dtriTfX2=triTfX;
triTfX=dtriTfX;
triTfX2=dtriTfX2;

dtriTfY=triTfY2;
dtriTfY2=triTfY;
triTfY=dtriTfY;
triTfY2=dtriTfY2;
}
}

//still calculate player 1
triPosX+=triTfX;
triPosY+=triTfY;

triTfX-=0.005f*triTfX;
triTfY-=0.005f*triTfY;

//calculate player 2
if(triPosX2>=0.92f || triPosX2 <= -0.92f)
{
if(bgB>0.0f)
{
//resetPlayers();
//bgB-=50.0f;
resetPlayers();
bgR=255.0f;
bgB=255.0f;
glClearColor(0.2,0,0,0);
}
else
{
resetPlayers();
bgR=255.0f;
bgB=255.0f;
glClearColor(0.2,0,0,0);
}
}
if(triPosY2>=0.92f || triPosY2 <= -0.92f)
{
if(bgB>0.0f)
{
//resetPlayers();
//bgB-=50.0f;
resetPlayers();
bgR=255.0f;
bgB=255.0f;
glClearColor(0.2,0,0,0);
}
else
{
resetPlayers();
bgR=255.0f;
bgB=255.0f;
glClearColor(0.2,0,0,0);
}
}

triPosX2+=triTfX2;
triPosY2+=triTfY2;

triTfX2-=0.005f*triTfX2;
triTfY2-=0.005f*triTfY2;


//render
glClear(GL_COLOR_BUFFER_BIT);

//draw player 1
glBegin(GL_QUADS);
glColor4f(255,0,0,0);
glVertex2f(-0.06f+triPosX,-0.1f+triPosY);
glColor4f(255,0,0,0);
glVertex2f(-0.06f+triPosX,0.1f+triPosY);
glColor4f(255,0,0,0);
glVertex2f(0.06f+triPosX,0.1f+triPosY);
glColor4f(255,0,0,0);
glVertex2f(0.06f+triPosX,-0.1f+triPosY);
glEnd();

//draw player 2
glBegin(GL_QUADS);
glColor4f(0,0,255,0);
glVertex2f(-0.06f+triPosX2,-0.1f+triPosY2);
glColor4f(0,0,255,0);
glVertex2f(-0.06f+triPosX2,0.1f+triPosY2);
glColor4f(0,0,255,0);
glVertex2f(0.06f+triPosX2,0.1f+triPosY2);
glColor4f(0,0,255,0);
glVertex2f(0.06f+triPosX2,-0.1f+triPosY2);
glEnd();


glfwSwapBuffers(window);
//other 
//60 fps is 16.6666666667
msleep(16.6666666667);

}

glfwDestroyWindow(window);
glfwTerminate();
printf("program terminated successfully\n");
return 0;

}
