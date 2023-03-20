#include "cdockareatabbar_wrap.h"
#include "DockAreaWidget.h"


Napi::FunctionReference CDockAreaTabBarWrap::constructor;

Napi::Object CDockAreaTabBarWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockAreaTabBar";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {QFRAME_WRAPPED_METHODS_EXPORT_DEFINE(CDockAreaTabBarWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockAreaTabBar, CDockAreaTabBarWrap);
  return exports;
}

ads::CDockAreaTabBar* CDockAreaTabBarWrap::getInternalInstance() { return this->instance; }

CDockAreaTabBarWrap::~CDockAreaTabBarWrap() { extrautils::safeDelete(this->instance); }

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
