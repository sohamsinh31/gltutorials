#include <stdio.h>
#include "iostream"
#include <stdlib.h>
#include "../include/GLFW/glfw3.h"
#include "./video_reader.hpp""
#include "./glfww.h"

GLFWwindow* window;
VideoReaderState vr_state;
using namespace std;
const int ALIGNMENT = 128;
int frame_width;
int frame_height;
uint8_t* frame_data;

int LoadVideo(){
    GLuint tex_handle;
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    //glfwMaximizeWindow(window);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // Set up orphographic projection
    int window_width, window_height;
    glfwGetFramebufferSize(window, &window_width, &window_height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    float aspect = window_width / window_height;
    cout<<"Width:"<<window_width<<" Height:"<<window_height<<" Aspect:"<<aspect<<"\n";
    glViewport(0, 0, window_width, window_height);
    glOrtho(window_width/8, (window_width), window_height, window_height/5, 1.0, -1.0);
    glMatrixMode(GL_MODELVIEW);
    // Read a new frame and load it into texture
    int64_t pts;
    if (!video_reader_read_frame(&vr_state, frame_data, &pts)) {
        printf("Couldn't load video frame\n");
        return 1;
    }
    static bool first_frame = true;
    if (first_frame) {
        glfwSetTime(0.0);
        first_frame = false;
    }
    double pt_in_seconds = pts * (double)vr_state.time_base.num / (double)vr_state.time_base.den;
    while (pt_in_seconds > glfwGetTime()) {
        glfwWaitEventsTimeout(pt_in_seconds - glfwGetTime());
    }
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, frame_width, frame_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, frame_data);
    // Render whatever you want
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glBegin(GL_QUADS);
    glTexCoord2d(0,0); glVertex2i(window_width/8, window_height/5);
    glTexCoord2d(1,0); glVertex2i( window_width, window_height/5);
    glTexCoord2d(1,1); glVertex2i( window_width,  window_height);
    glTexCoord2d(0,1); glVertex2i(window_width/8,  window_height);
    glEnd();
    glDisable(GL_TEXTURE_2D);
    glfwSwapBuffers(window);
    glfwPollEvents();
}

int main(int argc, const char** argv) {
    if (!glfwInit()) {
        printf("Couldn't init GLFW\n");
        return 1;
    }
    GLFWmonitor* MyMonitor =  glfwGetPrimaryMonitor(); // The primary monitor.. Later Occulus?..
    const GLFWvidmode* mode = glfwGetVideoMode(MyMonitor);
    window = glfwCreateWindow(800,600,"Astravarse",NULL,NULL);
    //window=glfwCreateWindow(glfwGetVideoMode(glfwGetPrimaryMonitor())->width,glfwGetVideoMode(glfwGetPrimaryMonitor())->height, "AstraVerse",glfwGetPrimaryMonitor(), nullptr);
    if (!window) {
        printf("Couldn't open window\n");
        return 1;
    }
    if (!video_reader_open(&vr_state, "/media/soham/win10/Users/lenov/Videos/logov.mp4")) {
        printf("Couldn't open video file (make sure you set a video file that exists)\n");
        return 1;
    }
    glfwMakeContextCurrent(window);
    // Generate texture
    // Allocate frame buffer
    //int ALIGNMENT = 128;
    frame_width = vr_state.width;
    frame_height = vr_state.height;
    //uint8_t* frame_data;
    if (posix_memalign((void**)&frame_data, ALIGNMENT, frame_width * frame_height * 4) != 0) {
        printf("Couldn't allocate frame buffer\n");
        return 1;
    }
    while (!glfwWindowShouldClose(window)) {
        LoadVideo();
    }
    video_reader_close(&vr_state);
    return 0;
}