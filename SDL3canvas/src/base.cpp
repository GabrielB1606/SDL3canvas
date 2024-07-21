#include "include/defines.hpp"

bool show_demo_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

std::vector<FCircle> pts;
Quadtree<float> qt({0, 0}, {1280, 720});

void drawCanvas(SDL_Renderer* renderer){
  SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0xff, 0, 0xff);
  for(const auto &c:pts)
    c.render(renderer);
  qt.render(renderer);
}

void pollEvent(SDL_Event event){
  if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
    pts.push_back( FCircle(event.motion.x, event.motion.y, 3) );
    qt.insert({event.motion.x, event.motion.y});
  }
}

void drawGui(ImGuiIO io){
  static float f = 0.0f;
  static int counter = 0;

  if (show_demo_window)
    ImGui::ShowDemoWindow(&show_demo_window);

  ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

  ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
  ImGui::Checkbox("Demo Window", &show_demo_window);      // Edit bools storing our window open/close state

  ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
  ImGui::ColorEdit3("clear color", (float*)&clear_color); // Edit 3 floats representing a color

  if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
      counter++;
  ImGui::SameLine();
  ImGui::Text("counter = %d", counter);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  ImGui::End();
}
