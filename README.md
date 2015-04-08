# todengine
Realtime 3D game/visualization engine, framework, toolkit, library and tool for Tool-Oriented Development paradigm, written in C++, scriptable through Python, Lua and Ruby. Supports D3D for rendering, runs under Windows.

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
  /code
    /external
      /irrlicht
        /include
        /lib
        ...
      /wxWidgets
        /include
        ...
  

## 
