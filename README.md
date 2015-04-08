# todengine
TodEngine 은 3D엔진입니다. C++로 작성되어 있고, 게임을 제작하는데 필요한 Third-party 라이브러리 및 스크립트 언더(Python, Lua)를 통합하며, WorldEditor 를 포함하고 있습니다.
TodEngine 은 Tool-Oriented Development 라는 패러다임을 구현하기 위해 제작되었습니다. 개념은 Tool과 게임을 통합으로 개발한다는 개념입니다.
요즘은 Unity 나 UnrealEngine 같이 Editor로만 개발하는 환경이 되었습니다. 하지만 웬지 저런 에디터 위에서 개발하는 것은 골수 C++유저인 분들은 거부감이 들수도 있다는 생각을 갖고 있습니다. ^^; 약간 구식일지도 모르겠지만 C++상에서 간편하게 사용할 수도 있는 3D엔진을 지향합니다.

# Installation
## 준비물
 - VisualStudio 2013 for Desktop
 - wxWidget : https://www.wxwidgets.org/
 - Python : https://www.python.org/ 에서 2.7 버전 다운
 - LuaJIT : http://luajit.org/
 - irrlicht 3D 엔진 : http://irrlicht.sourceforge.net/

## 설치
 - wxWidget, irrlicht 를 code/external 에 설치(또는 복사)
 - wxWidgets 은 code/external/wxWidgets/build/msw/wx_vc12.sln 를 VS2013 으로 로딩하여 Debug/Release 모드 컴파일
 - irrlicht 는 미리 컴파일된 lib, dll 이 존재
 - 다음과 같은 형태가 되어야함
  - /code
    - /external
      - /irrlicht
        - /include
        - /lib
        - ...
      - /wxWidgets
        - /include
        - ...
  

## Tool-Oriented Development
'툴을 개발하면서 게임을 개발한다.' 는 개념에서 출발합니다. 게임 프로그래밍을 해보면 툴을 개발하여 생산성을 가속시키고 싶을때가 많습니다. 예를들면 플레이어가 발사한 미사일의 궤적을 에디팅 하고 싶을때 우리는 급하면 하드코딩하거나 조금더 발전시키면 data-driven 개발하곤 합니다. 특히 하드코딩은 C++같은 환경에서는 컴파일과정을 거치기 때문에 우리의 시간을 좀먹습니다. Unity 엔진을 사용해보신분들은 아시겠지만 Script Component를 추가하면 해당 기능을 스크립트로 구현하며 Editor에서 해당 내용을 곧바로 볼수 있는 기능이 있습니다. TodEngine도 비슷한 기능을 구현하는 것입니다.
하지만 TodEngine 은 Unity의 해당 기능을 C++또는 Python, Lua 로 접근 할 수 있다는 장점을 가지고 있습니다. (C++ 프로그래머에게만 해당되는 이야기겠죠? ^_^)

## Nebula & SceneGraph & Nodes
TodEngine 도 여타 3D엔진처럼 Scene Graph 와 유사한 Node 조합 형태를 갖고 있습니다.
아시는분이 있을지 모르겠지만 RadonLabs 에서 nebula 라는 엔진을 개발하여 오픈소스로 공개했습니다. nubula 엔진은 굉장히 아름다운 엔진 구조를 가지고 있어서 저는 그 엔진에게서 영감을 많이 받았습니다.

## Reflection
Nebula 에서느 제가 발전시키고 다듬은 기능은 최신 언어들에서 지원하는 Reflection 아키텍쳐를 C++에서 근접하게 구현한 것입니다. 
Reflection 은 객체의 속성 및 메서드를 실시간에 조회 및 엑세스 할 수 있는 기능을 제공하는 아키텍쳐입니다. 
TodEngine 에서는 Reflection 을 Editor에서 적극 활용하여 Unity 의 Inspector 와 유사한 기능을 제공합니다.
Unity 와 다른점은 C++을 사용한다는 것이지요. ^_^
C++ 에서 다음과 같은 코드를 사용할 수 있습니다.

auto node1 = Kernel::instance()->create("Node");
//property 조회
auto hp_prop = node1->findProperty("hp");
hp_prop->fromString(node1, "10");



## Scripting
TodEngine 에서는 2개의 스크립트 언어를 지원합니다. Python 과 Lua 입니다.
Python 은 대단히 방대한 양의 라이브러리를 갖고 있습니다. 이는 Tool-Oriented Dev 에서 빠른 툴 개발을 할 때 유용합니다.
Lua 는 굉장히 빠른 스크립트 언어입니다. 근래(?)에 Lua는 LuaJIT이 나오면서 더 빨라졌습니다. 우리는 LuaJIT을 사용하여 Swift따위를 배우지 않아도 빠른 프로토타이핑 및 게임 개발을 할 수 있습니다. 단... Lua를 배워야 겠네요? ㅜ_ㅜ

