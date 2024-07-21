#include "include/defines.hpp"

bool show_demo_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
ImVec4 pointColor = ImVec4(0, 1, 0, 1.00f);
ImVec4 treeColor = ImVec4(0, 1, 0, 1.00f);
float pointSize = 3;
bool hideGui = false;

std::vector<FCircle> pts;
Quadtree<float> qt({0, 0}, {1280, 720});

void drawCanvas(SDL_Renderer* renderer){
  SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColorFloat(renderer, pointColor.x, pointColor.y, pointColor.z, pointColor.w);
  for(const auto &c:pts)
    c.render(renderer);
  SDL_SetRenderDrawColorFloat(renderer, treeColor.x, treeColor.y, treeColor.z, treeColor.w);
  qt.render(renderer);
}

void pollEvent(SDL_Event event, ImGuiIO io){
  if(event.type == SDL_EVENT_KEY_DOWN)
    if( event.key.key == SDLK_H ){
      hideGui = !hideGui;
    }

  if(io.WantCaptureKeyboard || io.WantCaptureMouse)
    return;

  if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
    pts.push_back( FCircle(event.motion.x, event.motion.y, pointSize) );
    qt.insert({event.motion.x, event.motion.y});
  }
}

void drawGui(ImGuiIO io){
  static float f = 0.0f;
  static int counter = 0;

  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  if(hideGui)
    return;

  ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

  ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
  ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

  // ImGui::SliderFloat("point size", &pointSize, 1.0f, 10.0f);
  ImGui::ColorEdit3("point color", (float*)&pointColor); // Edit 3 floats representing a color
  ImGui::ColorEdit3("tree color", (float*)&treeColor); // Edit 3 floats representing a color
  ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

  if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
    counter++;
  ImGui::SameLine();
  ImGui::Text("counter = %d", counter);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  ImGui::End();
}
