#define _CRTDBG_MAP_ALLOC
#define VC_EXTRALEAN
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <assert.h>
#include <stdlib.h>
#include <crtdbg.h>
#include <thread>
#include <list>
#include <algorithm>
#include "todcore/kernel.h"
#include "todcore/ref.h"
#include "todcore/object.h"
#include "todcore/singletonmgr.h"
#include "todcore/node.h"
#include "todcore/method.h"
#include "todcore/methodbinder.h"
#include "todcore/property.h"
#include "todcore/simplepropertybinder.h"
#include "todcore/enumpropertybinder.h"
#include "todcore/module.h"
#include "todcore/tokenizer.h"
#include "todcore/serializer.h"


using namespace tod;




class Fighter : public Derive<Fighter, Object>
{
public:
    enum StaticEnum
    {
        ENUM_1,
        ENUM_2,
        ENUM_3,

        ENUM_MAX,
    };

public:
    Fighter()
    {
        this->dynamicEnum.push_back("enum_1");
        this->dynamicEnum.push_back("enum_2");
        this->dynamicEnum.push_back("enum_3");
    }

    int attack(int damage)
    {
        return damage * 2;
    }

    void setHp(int hp)
    {
        this->hp = hp;
    }

    int getHp()
    {
        return this->hp;
    }

    void setVisible(bool e)
    {
        this->visible = e;
    }

    bool isVisible()
    {
        return this->visible;
    }

    void setRatio(float r)
    {
        this->ratio = r;
    }

    float getRatio()
    {
        return this->ratio;
    }

    void setName(const String& s)
    {
        this->name = s;
    }

    const String& getName()
    {
        return this->name;
    }

    const String& getTestText()
    {
        return this->name;
    }

    typedef std::vector<String> DynamicEnum;
    DynamicEnum dynamicEnum;
    int enumValue;
    const DynamicEnum& getDynamicEnumList()
    {
        return this->dynamicEnum;
    }
    void setEnumValue(int value)
    {
        this->enumValue = value;
    }
    int getEnumValue()
    {
        return this->enumValue;
    }

    static void bindMethod()
    {
        BIND_METHOD(i_attack_i, { params.out().set<int>(0, self->attack(params.in().get<int>(0))); });
    }

    static void bindProperty()
    {
        BIND_PROPERTY(bool, visible, setVisible, isVisible, { return true; });
        BIND_PROPERTY(int, hp, setHp, getHp, { return 0; });
        BIND_PROPERTY(float, ratio, setRatio, getRatio, { return 1; });
        BIND_PROPERTY(const String&, name, setName, getName, { static String d; return d; });
        BIND_ENUM_PROPERTY(int, dynamic_enum, getDynamicEnumList, setEnumValue, getEnumValue, { return 0; });
    }

private:
    bool visible;
    int hp;
    float ratio;
    String name;
};

class Gladiator : public Derive<Gladiator, Fighter>
{
public:
    int critical_attack(int damage)
    {
        return damage * 2;
    }

    static void bindMethod()
    {
        BIND_METHOD(i_critical_attack_i, { params.out().set<int>(0, self->critical_attack(params.in().get<int>(0))); });
    }
};


class Archive
{
public:
};

class FileArchive : public Archive
{

};

template <typename TYPE>
class Value
{
public:
    Value(const TYPE& value) :data(value) {}

    bool save(Archive& archive)
    {
    }

private:
    TYPE data;
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    typedef Value<int> int32;
    int32 test_int = 10;
    
    // 1. �� Value �� save ��� �Լ��� �ִ� ���
    // 2. FileStream �� �����, �ű⿡ Value<typename TYPE> �� �ִ� ���
    // 3. �ΰ��� ���� ���. �ֳĸ�, FileStream �Ǵ� 


	return 0;


    //_CrtSetBreakAlloc(10223);
    _CrtDumpMemoryLeaks();
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    _CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);

    VariableBinder<String>::null_instance();

    type_id a = TypeId<String>::id();
    type_id a2 = TypeId<const String&>::id();

    int b = sizeof(String);
    int b2 =sizeof(const String&);

    const char* c1 = typeid(String).raw_name();
    const char* c2 = typeid(const String&).raw_name();

    //test Object & Ref class
    Ref<Object> o1 = new Object();
    Object* o2 = o1.get();
    assert(o1->getRefCount() == 2);
    Ref<Object> o3 = o1;
    Ref<Object> o5(o1); //copy contructor
    assert(o1->getRefCount() == 4);
    assert(o1 == o2);
    assert(o1 == o3);
    assert(o1.release() == 3);
    assert(o3.release() == 2);
    o5 = new Object(); //copy assignment
    
    std::list<Ref<Object>> l;
    l.push_back(Ref<Object>(o5)); //move constructor
    l.clear();
    assert(o5->getRefCount() == 2);

    //test AutoReleasePool
    Object* o4 = new Object();


    //test Node hierarchy
    Node* n1 = new Node();
    n1->setName(S("1"));
    Node* n2 = new Node();
    n2->setName(S("1"));
    Node* n3 = new Node();
    n3->addChild(n1);
    n3->addChild(n2);
    n3->removeChildrenByName(S("1"));
    assert(n3->getNumChildren() == 0);


    //test reflection
    Type* fighter_type = Fighter::get_type();
    Fighter* f = dynamic_cast<Fighter*>(fighter_type->create());
    Type* fighter_base_type = fighter_type->getBaseType();;

    Type* gladiator_type = Gladiator::get_type();
    Gladiator* gladiator_obj = dynamic_cast<Gladiator*>(gladiator_type->create());
    Type* gladiator_base_type = gladiator_type->getBaseType();
    assert(gladiator_type->getName() == S("Gladiator"));

    size_t object_size = sizeof(Object);
    object_size = sizeof(Gladiator);

    //register custom class
    Module module(S("test"));
    module.addType<Fighter>();
    module.addType<Gladiator>();
    Object* new_fighter_obj = module.createInstance(S("Fighter"));
    assert(new_fighter_obj->getType() == Fighter::get_type());
    
    //method invokation
    Object* self = new_fighter_obj;
    Method* attack_method = self->getType()->findMethod(S("attack"));
    attack_method->getParams().in().set<int>(0, 2);
    attack_method->invoke(self);
    assert(attack_method->getParams().out().get<int>(0) == 4);

    //tokenizer test
    Tokenizer tok1(S("/sys/test/ttt"), S('/'));
    assert(tok1.size() == 3);
    assert(tok1[0] == S("sys"));
    assert(tok1[1] == S("test"));
    assert(tok1[2] == S("ttt"));

    Tokenizer tok2(S("/sys/test/ttt/"), S('/'));
    assert(tok2.size() == 3);
    assert(tok2[0] == S("sys"));
    assert(tok2[1] == S("test"));
    assert(tok2[2] == S("ttt"));

    tok2.tokenize(S("///sys/test///ttt///"), S('/'));
    assert(tok2.size() == 3);
    assert(tok2[0] == S("sys"));
    assert(tok2[1] == S("test"));
    assert(tok2[2] == S("ttt"));

    //property set/get
    Property* hp_prop = self->getType()->findProperty(S("hp"));
    hp_prop->fromString(self, S("10"));
    String hp_prop_str;
    hp_prop->toString(self, hp_prop_str);
    assert(hp_prop_str == S("10"));

    Property* visible_prop = self->getType()->findProperty(S("visible"));
    visible_prop->fromString(self, S("true"));
    String visible_prop_str;
    visible_prop->toString(self, visible_prop_str);
    assert(visible_prop_str == S("true"));

    Property* ratio_prop = self->getType()->findProperty(S("ratio"));
    ratio_prop->fromString(self, S("1.11"));
    String ratio_prop_str;
    ratio_prop->toString(self, ratio_prop_str);
    assert(ratio_prop_str == S("1.110000"));

    Property* name_prop = self->getType()->findProperty(S("name"));
    name_prop->fromString(self, S("test_name"));
    String name_prop_str;
    name_prop->toString(self, name_prop_str);
    assert(name_prop_str == S("test_name"));


    //superclass property access
    Property* name_prop2 = gladiator_obj->getType()->findProperty(S("name"));
    name_prop2->fromString(self, S("gladiator_obj"));    
    name_prop->toString(self, name_prop_str);
    assert(name_prop_str == S("gladiator_obj"));

    //kernel bootstrap
    Kernel::instance();
    Node* n4 = Kernel::instance()->create(S("Node"), "/sys/test");
    assert(n4->getName() == S("test"));
    Node* n5 = Kernel::instance()->find(S("/sys/../sys/test"));
    assert(n5->getName() == S("test"));

    SimpleProperty<const char*>* ppp = dynamic_cast<SimpleProperty<const char*>*>(n4->getType()->findProperty(S("test_text")));

    Serializer s;
    String serialized_str;
    assert(s.serialize(n4->getParent(), Serializer::PARSER_JSONCPP, serialized_str));
    Node* n6 = s.deserialize(Serializer::PARSER_JSONCPP, serialized_str);
    assert(n6);



    /*
    Method ������ ���̵��
    1. Method �� �񵿱�call �� �� �ֵ��� ����� ���? ajax ó�� =..
    2. Method call �Ҷ� C++11 �� lamda fuction �� �̿��غ���. -> �����带 ������� �ʾƵ�, cocos2d ó�� CallFunc ����� ����� ����� ���ʵڿ� ���� �̷��� ���� �� �ְڴ�.
    3. python �� ����� ����� �Ķ���� ����� ������.
    
    Module ������ ���̵��
    1. �ڵ����� Type�� Module�� ����ϴ� ����� ������? �� class Fighter : public Derive.. �ϴ� ���� ���
    2. ��ü �����Ҷ� module_name.class_name �̷��԰� ������? �� class_name �� ġ�°� ������?
        = ����. �ֳĸ� ���� �����Ҷ� module_name���� ����ϰ� �������� ���ڳ�. Ŭ������ ���� �װڴµ�.
        �۰� ���� ���� �̸��� Ŭ������ �ٸ� ����� ���� interface�� �����ϸ� ���� ���� ȿ���� ����.


    4. Tokenizer ���̵��
        - iteration �Ҷ� �Ѳ����� token�� �� ���⺸�� ���ʴ�� ���� ���� �������̴�.
        - operator [] �� random ���ٽ� ���ʺ��� ���� ���µ�, �ش� index������ ���� ���� �������̴�.
        - ���� �����ص��� ����, �ش� token�� �߰��ؼ� �׳� �Ѱ��ָ� ���?
            - operator [] ���ٽ� �ش� index���� �����Ѵ����� token ���� �ٷ� ����
            - �޸� ��뷮�� �ٰ�, std::vector �� �ȳ־ �Ǵϱ� ������嵵 �پ���.
            - ��, �����ٽ� ������尡 �����.
            ->>> �Ľ��ص���, �ƴϸ� �׳� �Ѱ����� ����ڰ� �����ϵ��� �����ȴ�.

    5. �� ���̵��.
        - Unity3D ó�� Executer �� ���Ӱ� ó������ �����ϰų� �߰����� �����ϰų� �� �� �־�� ��
        - ��������߿� pause �� �����Ǿ����
        - Unity3D �� Unreal ó��.. ������ ������ �ǽð����� ��ũ�� ����Ǿ�� ��. <- �̷��� Executer �� ����Ǿ����� ���Ϸκ��� �����͸� �о ����
        - ������ static structure �� runtime structure �� ������ �ٸ��� �� �� �־�� �� -> ����������� �ٽ� ��� NOH�� �����ؼ� ����� �� �־����
        - JNI �� �̿��ϸ� �̰� java�� ���� ������ ���൵ �� �� �ְڴ�! ������ ���� ��� ����~
        
        ���θ޴�
        ���ڽ�
            - ���彺������, �ͷ���, �Ĺ�
            - ������Ʈ��
            - ī�޶�
            - �޽� ������
            - ����ƽ �޽� ���
        ����Ʈ
            - run game in-viewport
            - draw mode
                - wire frame
                - except lighting
                - inlucde lighting
                - lighting only
                - detail lighting 
                - lighting complexcity
                - texture only
                - texture density
                - shader complexcity
                - game mode
            - �������� gizmo�� �Ѱ� ����
            - ��Ŭ���� �ø�, �ø��� ������
                - �𸮾󿡵��Ϳ��� �θ� ����Ʈ, �ڽĺ���Ʈ �����̾����� �̰� �� ������Ⱑ �����. �� ��Ŭ���� �ø��� ��带 ����°� �� ������.
        StatusBar
                - Console input
                - ������ �ν����� ����
                - translation snap, ratation angle snap
                - �ڵ����� ���
        Search
            - ����
            - NOH ���� Ÿ�Ե�� search
        - todeditor ���� node�� �ϳ��� ���۵ɰ��̴�. �׷��� todpython���� �ش� ��带 �����ϰ� ���� ������ �����Ѱ��̴�.
        - �׷� wxwidget���� roburst �ϰ� �ۼ��ϰ�, �ʿ��ϴٸ� todpython ���� ���������� �������� �Ǿ����� �Ѵ�.
        - �׸��� ��.. �� todeditoer.exe�� �־ ����.
        - Inspector�� ���� �����ϰ� ������̴�.
        - lua �� python ���� AOP������ �����Ǵ��� ã�ƺ���, �����Ǹ� [inspectable] �̷� �� �ؼ�.. ��ũ��Ʈ�� inspectable�� ������ ��������� ���ٵ�.
        - ������ C++������ BIND_PROPERTY�� �װ��� �����ߴµ�, ��ũ��Ʈ������ �����ؼ� inpector���� �� �����Ǿ����� ���ٴ�.
        - �׷���� ���������� �ش� ��ü�� ��� ����Ǵ����� ����������Ѵ�.
    */

    /*
        1. ��ũ��Ʈ���� property ����?
        2. �پ��� property ����
            - angel
            - vector2/3/4
            - texture
            - image
            - range
            - random
            - file
            - font
            - rect
            - list
         3. timeline �� ����?
         4. auto refresh : �������� �׸��� ����
         5. category ���� ����
         6. ���� base �� ���� node�� �ߺ� ���õǾ��� ��� ó��
        */

    
    return 0;
}