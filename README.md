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


