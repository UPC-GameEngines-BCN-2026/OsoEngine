#include "OsoEngine.h"
#include <SDL3/SDL.h>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <imgui.h>
#include <imgui_impl_sdl3.h>
#include <imgui_impl_opengl3.h>


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

    //Initalize imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;


    ImGui_ImplSDL3_InitForOpenGL(window, glContext);
    ImGui::StyleColorsDark();

    ImGui_ImplOpenGL3_Init("#version 460");


    //Main loop
    bool running = true;
    bool showConfig = true;
    bool showAbout = false;

    while (running)
    {
        SDL_Event event;

        while (SDL_PollEvent(&event))
        {
            // Pass events to ImGui
            ImGui_ImplSDL3_ProcessEvent(&event);

            if (event.type == SDL_EVENT_QUIT)
            {
                running = false;
            }
        }
        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        // Create a  menu bar
        if (ImGui::BeginMainMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Exit"))
                {
                    running = false;
                }

                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("View"))
            {
                ImGui::MenuItem("Configuration", nullptr, &showConfig);


                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Help"))
            {
                if (ImGui::MenuItem("Github Documentation"))
                {
                    SDL_OpenURL("https://github.com/UPC-GameEngines-BCN-2026/OsoEngine/wiki");
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
        if (showConfig)
        {
            ImGui::Begin("Configuration", &showConfig);

            if (ImGui::CollapsingHeader("Application"))
            {
                ImGui::Text("OsoEngine");
                ImGui::Text("Version 0.1.0");
            }

            if (ImGui::CollapsingHeader("Window"))
            {
                ImGui::Text("Width: 1280");
                ImGui::Text("Height: 720");
            }

            if (ImGui::CollapsingHeader("Hardware Info"))
            {
                ImGui::Text("Hardware information");
            }

            ImGui::End();
        }
        if (showAbout)
        {
            ImGui::Begin("About OsoEngine", &showAbout);

            ImGui::Text("OsoEngine");
            ImGui::Text("Version 0.1.0");

            ImGui::Separator();

            ImGui::Text("Team:");
            ImGui::BulletText("Sofia Liles");
            ImGui::BulletText("Oscar Escofet");
            ImGui::BulletText("David Castro");

            ImGui::Separator();

            ImGui::Text("Libraries:");
            ImGui::BulletText("SDL3");
            ImGui::BulletText("GLAD");
            ImGui::BulletText("GLM");
            ImGui::BulletText("ImGui");


            ImGui::Separator();

            ImGui::Text("License");
            ImGui::Text("MIT License");

            ImGui::End();
        }
        glClearColor(
            0.1f,
            0.1f,
            0.15f,
            1.0f
        );

        glClear(GL_COLOR_BUFFER_BIT);

        // Render ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(window);

        SDL_Delay(16);
    }


    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DestroyContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}