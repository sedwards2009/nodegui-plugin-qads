#include "cdocksplitter_wrap.h"
#include "cdockwidget_wrap.h"
#include "cdockcontainerwidget_wrap.h"
#include "cdockmanager_wrap.h"
#include "DockAreaTitleBar.h"

Napi::FunctionReference CDockSplitterWrap::constructor;

Napi::Object CDockSplitterWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "CDockSplitter";
  Napi::Function func = DefineClass(
      env, CLASSNAME,
      {
        QSPLITTER_WRAPPED_METHODS_EXPORT_DEFINE(CDockSplitterWrap)});
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  QOBJECT_REGISTER_WRAPPER(ads::CDockSplitter, CDockSplitterWrap);
  return exports;
}

ads::CDockSplitter* CDockSplitterWrap::getInternalInstance() { return this->instance; }

CDockSplitterWrap::~CDockSplitterWrap() { }

CDockSplitterWrap::CDockSplitterWrap(const Napi::CallbackInfo& info)
    : Napi::ObjectWrap<CDockSplitterWrap>(info) {
  Napi::Env env = info.Env();
  size_t argCount = info.Length();
  if (argCount == 1) {
      // --- Wrap a given C++ instance
      this->instance = info[0].As<Napi::External<ads::CDockSplitter>>().Data();
  } else {
    Napi::TypeError::New(
        env, "NodeGui: CDockSplitterWrap: Wrong number of arguments to constructor")
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
