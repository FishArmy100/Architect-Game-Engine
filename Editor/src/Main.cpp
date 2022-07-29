#include "Architect.h"
#include "EditorLayer.h"
#include "RefLib/Registration/BasicSTDRegistration.h"
#include "RefLib/Registration/HelperRegistrationMacros.h"
#include "Serialization/YAMLSerializer.h"
#include "Serialization/Serializeable.h"
#include "Debug-System/Asserts.h"
#include "Entity-Component-System/Entity-Components/Basic-Components.h"

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
    std::string Name = "Bob";
};

struct Player : public EntityData
{
    std::string Team = "Red";
};

int main()
{
    std::cout << std::boolalpha << "\n" << RefLib::Type::Get("Architect::TransformComponent").has_value() << "\n";
    std::cout << std::boolalpha << "\n" << RefLib::Type::Get("Position").has_value() << "\n";

    Architect::Application* app = new EditorApp();
    app->Run(); 
} 

REFLIB_REGISTRATION
{
    REFLIB_BEGIN_CLASS(Position)
        REFLIB_CTOR()
        REFLIB_PROP_BASIC(X)
        REFLIB_PROP_BASIC(Y)
        REFLIB_PROP_BASIC(Z)
        REFLIB_ATTRIBUTE(Architect::Serializable{})
    REFLIB_END_CLASS()

    REFLIB_BEGIN_CLASS(EntityData)
        REFLIB_CTOR()
        REFLIB_PROP_BASIC(Health)
        REFLIB_PROP_BASIC(Pos)
        REFLIB_PROP_BASIC(Name)
        REFLIB_ATTRIBUTE(Architect::Serializable{})
    REFLIB_END_CLASS()

    REFLIB_BEGIN_CLASS(Player)
        REFLIB_CTOR()
        REFLIB_PROP_BASIC(Team)
        REFLIB_BASE_CLASS(EntityData)
        REFLIB_ATTRIBUTE(Architect::Serializable{})
    REFLIB_END_CLASS()
}