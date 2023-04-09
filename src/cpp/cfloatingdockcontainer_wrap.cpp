#include "cfloatingdockcontainer_wrap.h"
#include "cdockwidget_wrap.h"
#include "cdockcontainerwidget_wrap.h"


Napi::FunctionReference CFloatingDockContainerWrap::constructor;

Napi::Object CFloatingDockContainerWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CFloatingDockContainer";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {
       InstanceMethod("dockContainer", &CFloatingDockContainerWrap::dockContainer),
       InstanceMethod("isClosable", &CFloatingDockContainerWrap::isClosable),
       InstanceMethod("hasTopLevelDockWidget", &CFloatingDockContainerWrap::hasTopLevelDockWidget),
       InstanceMethod("topLevelDockWidget", &CFloatingDockContainerWrap::topLevelDockWidget),
       InstanceMethod("dockWidgets", &CFloatingDockContainerWrap::dockWidgets),
       QWIDGET_WRAPPED_METHODS_EXPORT_DEFINE(CFloatingDockContainerWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CFloatingDockContainer, CFloatingDockContainerWrap);
  return exports;
}

ads::CFloatingDockContainer* CFloatingDockContainerWrap::getInternalInstance() { return this->instance; }

CFloatingDockContainerWrap::~CFloatingDockContainerWrap() { extrautils::safeDelete(this->instance); }

CFloatingDockContainerWrap::CFloatingDockContainerWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CFloatingDockContainerWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 1) {
    if (info[0].IsExternal()) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<ads::CFloatingDockContainer>>().Data();
    }
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CFloatingDockContainerWrap: Wrong number of arguments to constructor")
        .ThrowAsJavaScriptException();
  }

  // YogaWidget* yogaWidget =
  //     dynamic_cast<YogaWidget*>(this->getInternalInstance());
  // if (yogaWidget) {
  //   auto flexNode = yogaWidget->getFlexNode();
  //   YGNodeSetNodeType(flexNode, YGNodeType::YGNodeTypeText);
  // }
  this->rawData =
      extrautils::configureQWidget(this->getInternalInstance(), true);
}

Napi::Value CFloatingDockContainerWrap::dockContainer(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockContainerWidget* dockContainer = this->instance->dockContainer();
  if (dockContainer) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockContainer));
  } else {
    return env.Null();
  }
}

Napi::Value CFloatingDockContainerWrap::isClosable(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->isClosable();
  return Napi::Boolean::New(env, result);
}

Napi::Value CFloatingDockContainerWrap::hasTopLevelDockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool result = this->instance->hasTopLevelDockWidget();
  return Napi::Boolean::New(env, result);
}

Napi::Value CFloatingDockContainerWrap::topLevelDockWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockWidget* dockWidgetResult = this->instance->topLevelDockWidget();
  if (dockWidgetResult) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(dockWidgetResult));
  } else {
    return env.Null();
  }
}

Napi::Value CFloatingDockContainerWrap::dockWidgets(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    QList<ads::CDockWidget*> list = this->instance->dockWidgets();
    Napi::Array resultArrayNapi = Napi::Array::New(env, list.size());
    for (int i = 0; i < list.size(); i++) {
      resultArrayNapi[i] =
          WrapperCache::instance.getWrapper(env, list[i]);
    }
    return resultArrayNapi;
}
