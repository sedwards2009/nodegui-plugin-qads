#include "cdockareatitlebar_wrap.h"
#include "DockAreaWidget.h"
#include "DockAreaTabBar.h"

Napi::FunctionReference CDockAreaTitleBarWrap::constructor;

Napi::Object CDockAreaTitleBarWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockAreaTitleBar";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("insertWidget", &CDockAreaTitleBarWrap::insertWidget),
       InstanceMethod("indexOf", &CDockAreaTitleBarWrap::indexOf),
       InstanceMethod("tabBar", &CDockAreaTitleBarWrap::tabBar),
       QFRAME_WRAPPED_METHODS_EXPORT_DEFINE(CDockAreaTitleBarWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockAreaTitleBar, CDockAreaTitleBarWrap);
  return exports;
}

ads::CDockAreaTitleBar* CDockAreaTitleBarWrap::getInternalInstance() { return this->instance; }

CDockAreaTitleBarWrap::~CDockAreaTitleBarWrap() { extrautils::safeDelete(this->instance); }

CDockAreaTitleBarWrap::CDockAreaTitleBarWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CDockAreaTitleBarWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 1) {
    if (info[0].IsExternal()) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<ads::CDockAreaTitleBar>>().Data();
    } else {

      Napi::Object parentObject = info[0].As<Napi::Object>();
      NodeWidgetWrap* parentWidgetWrap =
          Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);

      QWidget *widget = parentWidgetWrap->getInternalInstance();
      ads::CDockAreaWidget*areaWidget = qobject_cast<ads::CDockAreaWidget*>(static_cast<QObject*>(widget));

      this->instance = new NCDockAreaTitleBar(areaWidget);
    }
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CDockAreaTitleBarWrap: Wrong number of arguments to constructor")
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

Napi::Value CDockAreaTitleBarWrap::insertWidget(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int index = info[0].As<Napi::Number>().Int32Value();
  Napi::Object widgetWidgetObject = info[1].As<Napi::Object>();
    NodeWidgetWrap* widgetWidgetWrap =
        Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(widgetWidgetObject);
    QWidget *widget = widgetWidgetWrap->getInternalInstance();
  this->instance->insertWidget(index, widget);
  return env.Null();
}

Napi::Value CDockAreaTitleBarWrap::indexOf(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  Napi::Object widgetWidgetObject = info[0].As<Napi::Object>();
    NodeWidgetWrap* widgetWidgetWrap =
        Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(widgetWidgetObject);
    QWidget *widget = widgetWidgetWrap->getInternalInstance();
  int result = this->instance->indexOf(widget);
  return Napi::Number::New(env, result);
}

Napi::Value CDockAreaTitleBarWrap::tabBar(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QObject *widget = this->instance->tabBar();
  if (widget) {
    return WrapperCache::instance.getWrapper(env, widget);
  } else {
    return env.Null();
  }
}
