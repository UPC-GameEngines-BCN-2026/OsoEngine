#include "OsoEngine.h"
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "imgui.h"
#include "imgui_impl_sdl3.h"
#include "imgui_impl_opengl3.h"

using namespace std;

int main()
{
    glm::vec3 position(1.0f, 2.0f, 3.0f);

    std::cout << "OsoEngine iniciado\n";

    //Iniciar SDL 
    if (!SDL_Init(SDL_INIT_VIDEO))
    {
        std::cerr << "SDL_Init fail: "
            << SDL_GetError()
            << std::endl;

        return 1;
    }


    //Configurar OpenGL
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(
        SDL_GL_CONTEXT_PROFILE_MASK,
        SDL_GL_CONTEXT_PROFILE_CORE
    );
    SDL_Window* window = SDL_CreateWindow(
        "OsoEngine - OpenGL",
        1280,
        720,
        SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE
    );
    if (window == nullptr)
    {
        std::cerr << "SDL_CreateWindow fail: "
            << SDL_GetError()
            << std::endl;

        SDL_Quit();
        return 1;
    }
    SDL_GLContext glContext = SDL_GL_CreateContext(window);

    if (glContext == nullptr)
    {
        std::cerr << "SDL_GL_CreateContext failed: "
            << SDL_GetError()
            << std::endl;

        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }
    if (!gladLoadGLLoader(
        reinterpret_cast<GLADloadproc>(SDL_GL_GetProcAddress)))
    {
        std::cerr << "Failed to initialize GLAD"
            << std::endl;

        SDL_GL_DestroyContext(glContext);
        SDL_DestroyWindow(window);
        SDL_Quit();

        return 1;
    }

    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 460");


bool running = true;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x * 0.5f, io.DisplaySize.y));

        ImGui::Begin("MenuBarVentana", nullptr,
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_MenuBar);

        bool showAbout = false;
        if (showAbout)
        {
            ImGui::Begin("About OsoEngine", &showAbout);

            ImGui::Text("Oso");
            ImGui::Text("Version 0.1.0");
            ImGui::Text("Heavyweight 3D performance. Unrestricted creativity.");
            ImGui::Text("By: David Garcia, Oscar & Sofia");
            ImGui::Separator();

            ImGui::Text("Libraries used:");
            ImGui::BulletText("SDL3");
            ImGui::BulletText("GLAD");
            ImGui::BulletText("GLM");
            ImGui::BulletText("Dear ImGui");
            ImGui::Separator();

            ImGui::Text("License");
            ImGui::Text("MIT License");
            ImGui::Text("Copyright (c) 2026 David Garcia, Oscar & Sofia");
            ImGui::Text("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the 'Software'), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and /or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions : ");
            ImGui::Text("The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.");
            ImGui::Text("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.");

            ImGui::End();
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Salir"))
                {
                    running = false;
                }
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("View"))
            {
                ImGui::EndMenu();
            }
            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("GitHub Documentation"))
                {
                    SDL_OpenURL("https://github.com/UPC-GameEngines-BCN-2026/OsoEngine/docs");
                }
                if (ImGui::MenuItem("Report a Bug"))
                {
                    SDL_OpenURL("https://github.com/UPC-GameEngines-BCN-2026/OsoEngine/issues");
                }
                if (ImGui::MenuItem("Download Latest"))
                {
                    SDL_OpenURL("https://github.com/UPC-GameEngines-BCN-2026/OsoEngine/releases");
                }
                if (ImGui::MenuItem("About"))
                {
                    showAbout = true;
                }
                ImGui::EndMenu();
            }

            ImGui::EndMainMenuBar();
        }

        ImGui::Render();

        glClearColor(
            0.1f,
            0.1f,
            0.15f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);

        SDL_Delay(16);
    }

    // Cleanup

    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
