#include "Architect.h"
#include "EditorLayer.h"

class EditorApp : public Architect::Application
{
public:
    EditorApp() : Application("Editor App")
    {
        PushLayer(new Editor::EditorLayer());
    }
};

int main()
{
    Architect::Application* app = new EditorApp();
    app->Run();
}