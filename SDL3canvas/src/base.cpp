#include "include/defines.hpp"

bool show_demo_window = false;
ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
ImVec4 pointColor = ImVec4(0, 1, 0, 1.00f);
ImVec4 treeColor = ImVec4(0, 1, 0, 1.00f);
float pointSize = 3;
bool hideGui = false;
bool showQuadtree = true;
bool showPoints = true;
Point<float> queryLocation = {100,100};
float querySize = 100;

std::vector<FCircle> pts;
Quadtree<float> qt({0, 0}, {1280, 720});

void drawCanvas(SDL_Renderer* renderer){
  SDL_SetRenderDrawColorFloat(renderer, clear_color.x, clear_color.y, clear_color.z, clear_color.w);
  SDL_RenderClear(renderer);
  
  SDL_SetRenderDrawColorFloat(renderer, pointColor.x, pointColor.y, pointColor.z, pointColor.w);
  if(showPoints)
    for(const auto &c:pts)
      c.render(renderer);
  
  SDL_SetRenderDrawColorFloat(renderer, treeColor.x, treeColor.y, treeColor.z, treeColor.w);
  if(showQuadtree)
    qt.render(renderer);
  
  SDL_SetRenderDrawColorFloat(renderer, 1, 0, 0, 1);
  float qs2 = querySize/2;
  SDL_FRect r = {queryLocation.x-qs2, queryLocation.y-qs2, querySize, querySize};
  SDL_RenderRect(renderer, &r);
  std::vector<Point<float>> q = qt.query(
    {queryLocation.x-qs2, queryLocation.y-qs2},
    {queryLocation.x+qs2, queryLocation.y+qs2}
  );
  for(const auto &c:q)
    FCircle{c.x, c.y, pointSize}.render(renderer);

}

void pollEvent(SDL_Event event, ImGuiIO io){
  if(event.type == SDL_EVENT_KEY_DOWN)
    if( event.key.key == SDLK_H ){
      hideGui = !hideGui;
    }
  
  if(io.WantCaptureKeyboard || io.WantCaptureMouse)
    return;

  if(event.type == SDL_EVENT_MOUSE_BUTTON_DOWN){
    if(event.button.button == SDL_BUTTON_LEFT){
      pts.push_back( FCircle(event.motion.x, event.motion.y, pointSize) );
      qt.insert({event.motion.x, event.motion.y});
    }
    if(event.button.button == SDL_BUTTON_RIGHT){
      queryLocation.x = event.motion.x;
      queryLocation.y = event.motion.y;
    }
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
  ImGui::Checkbox("Show points", &showPoints);
  ImGui::Checkbox("Show quadtree", &showQuadtree);

  // ImGui::SliderFloat("point size", &pointSize, 1.0f, 10.0f);
  ImGui::SliderFloat("query size", &querySize, 100.0f, 600.0f);
  ImGui::ColorEdit3("Point color", (float*)&pointColor); // Edit 3 floats representing a color
  ImGui::ColorEdit3("Tree color", (float*)&treeColor); // Edit 3 floats representing a color
  ImGui::ColorEdit3("Clear color", (float*)&clear_color); // Edit 3 floats representing a color

  if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
    counter++;
  ImGui::SameLine();
  ImGui::Text("counter = %d", counter);

  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  ImGui::End();
}
