#include "cdockareawidget_wrap.h"
#include "cdockcontainerwidget_wrap.h"
#include "cdockmanager_wrap.h"
#include "DockAreaTitleBar.h"

Napi::FunctionReference CDockAreaWidgetWrap::constructor;

Napi::Object CDockAreaWidgetWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockAreaWidget";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {InstanceMethod("setAllowedAreas", &CDockAreaWidgetWrap::setAllowedAreas),
      InstanceMethod("titleBar", &CDockAreaWidgetWrap::titleBar),
       QFRAME_WRAPPED_METHODS_EXPORT_DEFINE(CDockAreaWidgetWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockAreaWidget, CDockAreaWidgetWrap);
  return exports;
}

ads::CDockAreaWidget* CDockAreaWidgetWrap::getInternalInstance() { return this->instance; }

CDockAreaWidgetWrap::~CDockAreaWidgetWrap() { extrautils::safeDelete(this->instance); }

CDockAreaWidgetWrap::CDockAreaWidgetWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CDockAreaWidgetWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 1) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<ads::CDockAreaWidget>>().Data();
  } else if (argCount == 2) {
    // --- Construct a new instance and pass a parent
    Napi::Object dockManagerObject = info[0].As<Napi::Object>();
    CDockManagerWrap* dockManagerWrap =
        Napi::ObjectWrap<CDockManagerWrap>::Unwrap(dockManagerObject);

    Napi::Object parentObject = info[1].As<Napi::Object>();
    CDockContainerWidgetWrap* parentWidgetWrap =
        Napi::ObjectWrap<CDockContainerWidgetWrap>::Unwrap(parentObject);

    this->instance = new NCDockAreaWidget(dockManagerWrap->getInternalInstance(),
                                          parentWidgetWrap->getInternalInstance());
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CDockAreaWidgetWrap: Wrong number of arguments to constructor")
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

Napi::Value CDockAreaWidgetWrap::setAllowedAreas(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  int areas = info[0].As<Napi::Number>().Int32Value();
  this->instance->setAllowedAreas(static_cast<ads::DockWidgetAreas>(areas));
  return env.Null();
}

Napi::Value CDockAreaWidgetWrap::titleBar(const Napi::CallbackInfo& info) {
  Napi::Env env = info.Env();
  QObject* widget = this->instance->titleBar();
  if (widget) {
    return WrapperCache::instance.getWrapper(env, widget);
  } else {
    return env.Null();
  }
}
