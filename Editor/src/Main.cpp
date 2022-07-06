#include "Architect.h"
#include "EditorLayer.h"
#include "RefLib/Registration/BasicSTDRegistration.h"
#include "RefLib/Registration/HelperRegistrationMacros.h"
#include "Serialization/YAMLSerializer.h"
#include "Serialization/Serializeable.h"

class EditorApp : public Architect::Application
{
public:
    EditorApp() : Application("Editor App")
    {
        PushLayer(new Editor::EditorLayer());
    }
};

struct Position
{
    float X = 0;
    float Y = 0;
    float Z = 0;
};

struct EntityData
{
    float Health = 10.0f;
    Position Pos;
    //std::string Name = "Nate";
};


int main()
{
    Architect::YAMLSerializer s;
    s.Serialize(EntityData());

    Architect::Application* app = new EditorApp(); 
    app->Run(); 
}

REFLIB_REGISTRATION
{
    REFLIB_BEGIN_CLASS(Position)
        REFLIB_PROP_BASIC(X)
        REFLIB_PROP_BASIC(Y)
        REFLIB_PROP_BASIC(Z)
        REFLIB_ATTRIBUTE(Architect::Serializable{})
    REFLIB_END_CLASS()

    REFLIB_BEGIN_CLASS(EntityData)
        REFLIB_PROP_BASIC(Health)
        REFLIB_PROP_BASIC(Pos)
        //REFLIB_PROP_BASIC(Name)
        REFLIB_ATTRIBUTE(Architect::Serializable{})
    REFLIB_END_CLASS()
}