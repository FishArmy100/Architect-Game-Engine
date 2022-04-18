#include "Architect.h"
#include "EditorLayer.h"
#include "Reflection/Reflection.h"

class EditorApp : public Architect::Application
{
public:
    EditorApp() : Application("Editor App")
    {
        PushLayer(new Editor::EditorLayer());
    }
};

class Test
{
public:
    Test() {}
    Test(int hello, int goodbye) {}
    int value{};
    int Add(int x, int y) { return x + y; }

    enum class TestEnum
    {
        One,
        Two
    };

    ARC_ENABLE_CLASS_REFLECTION()
};

struct Attribute
{
    int Data;

    Attribute(int val) : Data(val) {}
};

enum class E_Alignment
{
    AlignLeft = 0x0001,
    AlignRight = 0x0002,
    AlignHCenter = 0x0004,
    AlignJustify = 0x0008
};

int main()
{
    ARC_USE_REFLECTION;

    std::cout << IndexArrayRange(rttr::type::get<E_Alignment>().get_enumeration().get_names(), 1)->to_string() << "\n";

    Architect::Application* app = new EditorApp();
    app->Run();
}

ARC_REGISTER_GLOBAL_ENUM_CLASS(
    E_Alignment,
    ARC_GLOBAL_ENUM_VAL(AlignLeft),
    ARC_GLOBAL_ENUM_VAL(AlignRight),
    ARC_GLOBAL_ENUM_VAL(AlignHCenter),
    ARC_GLOBAL_ENUM_VAL(AlignJustify)
)

ARC_USE_REFLECTION;

ARC_BEGIN_REGISTER_CLASS(Test)
    ARC_REGISTER_CONSTRUCTOR(AccessLevel::Public).enumeration<Test::TestEnum>("TestEnum")
    ARC_REGISTER_CONSTRUCTOR(AccessLevel::Public, int, int)
    ARC_REGISTER_PROPERTY(AccessLevel::Public, value)(ARC_ATTRIB(Attribute(99)))
    ARC_REGISTER_FUNCTION(AccessLevel::Public, int(int, int), Add)(ARC_PARAM_NAMES("int a", "int b"))

ARC_END_REGISTER_CLASS;