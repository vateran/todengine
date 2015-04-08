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
    
    // 1. 걍 Value 에 save 라는 함수가 있는 방법
    // 2. FileStream 을 만들고, 거기에 Value<typename TYPE> 을 넣는 방법
    // 3. 두개를 섞는 방법. 왜냐면, FileStream 또는 


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
    Method 제작중 아이디어
    1. Method 를 비동기call 할 수 있도록 만들면 어떨까? ajax 처럼 =..
    2. Method call 할때 C++11 의 lamda fuction 을 이용해보자. -> 쓰레드를 사용하지 않아도, cocos2d 처럼 CallFunc 비슷한 기능을 만들어 몇초뒤에 실행 이런거 만들 수 있겠다.
    3. python 과 비슷한 방식의 파라메터 사용을 만들어보자.
    
    Module 제작중 아이디어
    1. 자동으로 Type을 Module에 등록하는 방법은 없을까? 걍 class Fighter : public Derive.. 하는 순간 등록
    2. 객체 생성할때 module_name.class_name 이렇게가 나을까? 걍 class_name 만 치는게 나을까?
        = 후자. 왜냐면 실제 개발할때 module_name따위 기억하고 싶을리가 없자나. 클래스도 많아 죽겠는데.
        글고 만약 같은 이름의 클래스로 다른 모듈이 같은 interface로 제공하면 버전 업된 효과도 난다.


    4. Tokenizer 아이디어
        - iteration 할때 한꺼번에 token을 다 떼기보다 차례대로 떼는 편이 경제적이다.
        - operator [] 로 random 접근시 앞쪽부터 떼긴 떼는데, 해당 index까지만 떼는 편이 경제적이다.
        - 떼서 보관해두지 말고, 해당 token을 발견해서 그냥 넘겨주면 어떨까?
            - operator [] 접근시 해당 index까지 증가한다음에 token 떼서 바로 리턴
            - 메모리 사용량도 줄고, std::vector 에 안넣어도 되니까 오버헤드도 줄어든다.
            - 단, 재접근시 오버헤드가 생긴다.
            ->>> 파싱해둘지, 아니면 그냥 넘겨줄지 사용자가 결정하도록 만들면된다.

    5. 툴 아이디어.
        - Unity3D 처럼 Executer 가 새롭게 처음부터 시작하거나 중간부터 시작하거나 할 수 있어야 함
        - 실행과정중에 pause 가 지원되어야함
        - Unity3D 나 Unreal 처럼.. 변경한 내용이 실시간으로 디스크로 저장되어야 함. <- 이래야 Executer 가 실행되었을때 파일로부터 데이터를 읽어서 실행
        - 게임의 static structure 랑 runtime structure 랑 구조를 다르게 할 수 있어야 함 -> 실행시점에서 다시 모든 NOH를 구성해서 진행될 수 있어야함
        - JNI 를 이용하면 이거 java로 만들어서 웹에서 실행도 될 수 있겠다! ㅎㅎㅎ 요즘 기술 좋넹~
        
        메인메뉴
        툴박스
            - 랜드스케이프, 터레인, 식물
            - 지오메트리
            - 카메라
            - 메시 페인팅
            - 스태틱 메시 모드
        뷰포트
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
            - 에디터의 gizmo들 켜고 끄기
            - 오클루젼 컬링, 컬링된 옵젝들
                - 언리얼에디터에선 부모 뷰포트, 자식뷰포트 개념이었지만 이거 쫌 개념잡기가 힘들다. 걍 오클루젼 컬링뷰 모드를 만드는게 더 낫겠음.
        StatusBar
                - Console input
                - 간단한 인스펙터 역할
                - translation snap, ratation angle snap
                - 자동저장 기능
        Search
            - 에셋
            - NOH 내의 타입들로 search
        - todeditor 역시 node의 하나로 제작될것이다. 그래서 todpython에서 해당 노드를 생성하고 띄우면 조립도 가능한것이다.
        - 그럼 wxwidget으로 roburst 하게 작성하고, 필요하다면 todpython 에서 조립가능한 수준으로 되었으면 한다.
        - 그리고 머.. 걍 todeditoer.exe가 있어도 좋고.
        - Inspector를 아주 강력하게 만들것이다.
        - lua 나 python 에서 AOP같은게 지원되는지 찾아보고, 지원되면 [inspectable] 이런 거 해서.. 스크립트가 inspectable한 변수를 만들었으면 좋겟따.
        - 이전엔 C++에서만 BIND_PROPERTY로 그것이 가능했는데, 스크립트에서도 가능해서 inpector에서 막 설정되었으면 좋겟다.
        - 그럴라믄 수정했을때 해당 객체가 어떻게 저장되는지를 지정해줘야한다.
    */

    /*
        1. 스크립트에서 property 노출?
        2. 다양한 property 편집
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
         3. timeline 과 통합?
         4. auto refresh : 편집중인 항목은 제외
         5. category 별로 정리
         6. 같은 base 를 갖는 node가 중복 선택되었을 경우 처리
        */

    
    return 0;
}