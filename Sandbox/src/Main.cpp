#include "Architect.h"

class SandboxApp : public Architect::Application
{
public:
    SandboxApp() : Application("Sandbox App")
    {
        PushLayer(new Architect::EditorLayer());
    }
};

int main()
{
    Architect::Application* app = new SandboxApp();
    app->Run();
}