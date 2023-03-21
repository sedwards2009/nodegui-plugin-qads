#include "cdockcontainerwidget_wrap.h"
#include "DockContainerWidget.h"
#include "DockManager.h"


Napi::FunctionReference CDockContainerWidgetWrap::constructor;

Napi::Object CDockContainerWidgetWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockContainerWidget";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {
       QFRAME_WRAPPED_METHODS_EXPORT_DEFINE(CDockContainerWidgetWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockContainerWidget, CDockContainerWidgetWrap);
  return exports;
}

ads::CDockContainerWidget* CDockContainerWidgetWrap::getInternalInstance() { return this->instance; }

CDockContainerWidgetWrap::~CDockContainerWidgetWrap() { extrautils::safeDelete(this->instance); }

CDockContainerWidgetWrap::CDockContainerWidgetWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CDockContainerWidgetWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 1) {
    if (info[0].IsExternal()) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<ads::CDockContainerWidget>>().Data();
    } else {

      Napi::Object dockManagerObject = info[0].As<Napi::Object>();
      NodeWidgetWrap* dockManagerObjectWrap =
          Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockManagerObject);
      ads::CDockManager *dockManager = qobject_cast<ads::CDockManager*>(dockManagerObjectWrap->getInternalInstance());

      Napi::Object parentObject = info[1].As<Napi::Object>();
      NodeWidgetWrap* parentWidgetWrap =
          Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(parentObject);
      QWidget *parentWidget = parentWidgetWrap->getInternalInstance();

      this->instance = new NCDockContainerWidget(dockManager, parentWidget);
    }
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CDockContainerWidgetWrap: Wrong number of arguments to constructor")
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
