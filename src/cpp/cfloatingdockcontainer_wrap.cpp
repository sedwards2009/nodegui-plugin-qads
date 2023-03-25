#include "cfloatingdockcontainer_wrap.h"


Napi::FunctionReference CFloatingDockContainerWrap::constructor;

Napi::Object CFloatingDockContainerWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CFloatingDockContainer";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {
      //  InstanceMethod("setFeature", &CFloatingDockContainerWrap::setFeature),
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
