#include "cdockareatabbar_wrap.h"
#include "DockAreaWidget.h"
#include "DockWidgetTab.h"


Napi::FunctionReference CDockAreaTabBarWrap::constructor;

Napi::Object CDockAreaTabBarWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockAreaTabBar";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      { InstanceMethod("count", &CDockAreaTabBarWrap::count),
        InstanceMethod("currentIndex", &CDockAreaTabBarWrap::currentIndex),
        InstanceMethod("isTabOpen", &CDockAreaTabBarWrap::isTabOpen),
        InstanceMethod("elidedChanged", &CDockAreaTabBarWrap::elidedChanged),
        InstanceMethod("setCurrentIndex", &CDockAreaTabBarWrap::setCurrentIndex),
        InstanceMethod("closeTab", &CDockAreaTabBarWrap::closeTab),
        InstanceMethod("currentTab", &CDockAreaTabBarWrap::currentTab),
        InstanceMethod("tab", &CDockAreaTabBarWrap::tab),
        QSCROLLAREA_WRAPPED_METHODS_EXPORT_DEFINE(CDockAreaTabBarWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockAreaTabBar, CDockAreaTabBarWrap);
  return exports;
}

ads::CDockAreaTabBar* CDockAreaTabBarWrap::getInternalInstance() { return this->instance; }

CDockAreaTabBarWrap::~CDockAreaTabBarWrap() { }

CDockAreaTabBarWrap::CDockAreaTabBarWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CDockAreaTabBarWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 1) {
    if (info[0].IsExternal()) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<ads::CDockAreaTabBar>>().Data();
    } else {

      Napi::Object parentObject = info[0].As<Napi::Object>();
      NodeWidgetWrap* parentWidgetWrap = Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);

      QWidget *widget = parentWidgetWrap->getInternalInstance();
      ads::CDockAreaWidget*areaWidget = qobject_cast<ads::CDockAreaWidget*>(static_cast<QObject*>(widget));

      this->instance = new NCDockAreaTabBar(areaWidget);
    }
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CDockAreaTabBarWrap: Wrong number of arguments to constructor")
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

Napi::Value CDockAreaTabBarWrap::count(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int result = this->instance->count();
  return Napi::Number::New(env, result);
}

Napi::Value CDockAreaTabBarWrap::currentIndex(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int result = this->instance->currentIndex();
  return Napi::Number::New(env, result);
}

Napi::Value CDockAreaTabBarWrap::isTabOpen(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int index = info[0].As<Napi::Number>().Int32Value();
  bool result = this->instance->isTabOpen(index);
  return Napi::Boolean::New(env, result);
}

Napi::Value CDockAreaTabBarWrap::elidedChanged(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  bool elided = info[0].As<Napi::Boolean>().Value();
  this->instance->elidedChanged(elided);
  return env.Null();
}

Napi::Value CDockAreaTabBarWrap::setCurrentIndex(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int index = info[0].As<Napi::Number>().Int32Value();
  this->instance->setCurrentIndex(index);
  return env.Null();
}

Napi::Value CDockAreaTabBarWrap::closeTab(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int index = info[0].As<Napi::Number>().Int32Value();
  this->instance->closeTab(index);
  return env.Null();
}

Napi::Value CDockAreaTabBarWrap::currentTab(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  ads::CDockWidgetTab* tab = this->instance->currentTab();
  if (tab) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(tab));
  } else {
    return env.Null();
  }
}

Napi::Value CDockAreaTabBarWrap::tab(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int index = info[0].As<Napi::Number>().Int32Value();
  ads::CDockWidgetTab* tab = this->instance->tab(index);
  if (tab) {
    return WrapperCache::instance.getWrapper(env, static_cast<QObject*>(tab));
  } else {
    return env.Null();
  }
}
