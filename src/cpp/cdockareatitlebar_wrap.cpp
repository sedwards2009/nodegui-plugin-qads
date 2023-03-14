#include "cdockareatitlebar_wrap.h"
#include "DockAreaWidget.h"


Napi::FunctionReference CDockAreaTitleBarWrap::constructor;

Napi::Object CDockAreaTitleBarWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockAreaTitleBar";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {
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
