#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <random>

static void glfw_error_callback(int error, const char* description);

static void DrawRectangle(float x, float y, float width, float height) 
{
    glBegin(GL_QUADS);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width, y + height);
    glVertex2f(x, y + height);
    glEnd();
}

static bool isSorted(std::vector<int>& list)
{
    for (int i = 0; i < list.size() - 1; i++)
        if (list[i] > list[i + 1])
            return false;

    return true;
}

static void bubbleSortOneStep(int i, std::vector<int>& list)
{
    int currentValue = 0;
    int nextValue = 0;

    if (list[i] > list[i + 1])
    {
        currentValue = list[i];
        nextValue = list[i + 1];

        list[i] = nextValue;
        list[i + 1] = currentValue;
    }
}

int main()
{
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit())
        return 1;

    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Sorting Algorithm Visualizer", nullptr, nullptr);
    if (window == nullptr)
    {
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);

    std::vector<int> list = {};

    std::random_device random_device;
    std::default_random_engine generator(random_device());
    std::uniform_int_distribution<> distribution(1, 100);

    int i = 0;
    int sortType = 0;

    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();

        if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
        {
            ImGui_ImplGlfw_Sleep(10);
            continue;
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        {
            static int length = 0;

            ImGui::Begin("Menu");

            if (ImGui::Button("Generate List"))
            {
                list = {};
                if (length > 1 && length <= 200)
                {
                    for (int i = 0; i < length; i++)
                    {
                        list.push_back(distribution(generator));
                    }
                }
            }

            ImGui::InputInt("Length", &length);
            ImGui::Text("Must be between 2 and 200");

            if (ImGui::Button("Bubble Sort"))
            {
                i = 0;
                sortType = 1;
            }

            ImGui::End();
        }
        ImGui::Render();

        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (list.size() > 1)
        {
            switch (sortType)
            {
            case 1:
                if (!isSorted(list))
                {
                    if (i < list.size() - 1)
                    {
                        bubbleSortOneStep(i, list);
                        i++;
                    }
                    else
                    {
                        i = 0;
                    }
                }
                else
                {
                    sortType = 0;
                }
            }
        }

        if (list.size() > 0)
        {
            for (int x = 0; x < list.size(); x++)
            {
                if (x == i)
                {
                    glColor3f(0.0f, 1.0f, 0.0f);
                }
                else
                {
                    glColor3f(1.0f, 1.0f, 1.0f);
                }
                
                DrawRectangle(-1.0f + (x * 2.0f / list.size()), -1.0f, 1.0f / list.size(), list[x] / 100.0f);
            }
        }

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

static void glfw_error_callback(int error, const char* description)
{
    std::cerr << "GLFW Error " << error << ": " << description << std::endl;
}