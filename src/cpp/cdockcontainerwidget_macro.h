#include <QPoint>
#include <QList>
#include "QtWidgets/QFrame/qframe_macro.h"


#define CDOCKCONTAINERWIDGET_WRAPPED_METHODS_DECLARATION                    \
  QFRAME_WRAPPED_METHODS_DECLARATION                                        \
  Napi::Value dumpLayout(const Napi::CallbackInfo& info) {                  \
    Napi::Env env = info.Env();                                             \
    this->instance->dumpLayout();                                           \
    return env.Null();                                                      \
  }                                                                         \
  Napi::Value features(const Napi::CallbackInfo& info) {                    \
    Napi::Env env = info.Env();                                             \
    auto features = this->instance->features();                             \
    return Napi::Number::New(env, features);                                \
  }                                                                         \
  Napi::Value isFloating(const Napi::CallbackInfo& info) {                  \
    Napi::Env env = info.Env();                                             \
    bool result = this->instance->isFloating();                             \
    return Napi::Boolean::New(env, result);                                 \
  }                                                                         \
  Napi::Value zOrderIndex(const Napi::CallbackInfo& info) {                 \
    Napi::Env env = info.Env();                                             \
    int result = this->instance->zOrderIndex();                             \
    return Napi::Number::New(env, result);                                  \
  }                                                                         \
  Napi::Value hasTopLevelDockWidget(const Napi::CallbackInfo& info) {       \
    Napi::Env env = info.Env();                                             \
    bool result = this->instance->hasTopLevelDockWidget();                  \
    return Napi::Boolean::New(env, result);                                 \
  }                                                                         \
  Napi::Value dockAreaCount(const Napi::CallbackInfo& info) {               \
    Napi::Env env = info.Env();                                             \
    int result = this->instance->dockAreaCount();                           \
    return Napi::Number::New(env, result);                                  \
  }                                                                         \
  Napi::Value visibleDockAreaCount(const Napi::CallbackInfo& info) {        \
    Napi::Env env = info.Env();                                             \
    int result = this->instance->visibleDockAreaCount();                    \
    return Napi::Number::New(env, result);                                  \
  }                                                                         \
  Napi::Value addDockWidget(const Napi::CallbackInfo& info) {               \
    Napi::Env env = info.Env();                                             \
    int area = info[0].As<Napi::Number>().Int32Value();                     \
    Napi::Object dockObjectNapi = info[1].As<Napi::Object>();               \
    NodeWidgetWrap* dockWidgetWrap =                                        \
      Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockObjectNapi);             \
    QObject* dockObject = dockWidgetWrap->getInternalInstance();            \
    ads::CDockWidget* dockWidget =                                          \
      qobject_cast<ads::CDockWidget*>(dockObject);                          \
                                                                            \
    ads::CDockAreaWidget* dockAreaWidget = nullptr;                         \
    if ( ! info[2].IsNull()) {                                              \
      Napi::Object dockAreaObjectNapi = info[2].As<Napi::Object>();         \
      NodeWidgetWrap* dockAreaWidgetWrap =                                  \
        Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockAreaObjectNapi);       \
      QObject* dockAreaObject = dockAreaWidgetWrap->getInternalInstance();  \
      dockAreaWidget = qobject_cast<ads::CDockAreaWidget*>(dockAreaObject); \
    }                                                                       \
                                                                            \
    int index = info[3].As<Napi::Number>().Int32Value();                    \
    ads::CDockAreaWidget* dockAreaWidgetResult =                            \
      this->instance->addDockWidget(static_cast<ads::DockWidgetArea>(area), \
        dockWidget, dockAreaWidget, index);                                 \
                                                                            \
    if (dockAreaWidgetResult) {                                             \
      return WrapperCache::instance.getWrapper(env,                         \
        static_cast<QObject*>(dockAreaWidgetResult));                       \
    } else {                                                                \
      return env.Null();                                                    \
    }                                                                       \
  }                                                                         \
  Napi::Value removeDockWidget(const Napi::CallbackInfo& info) {            \
    Napi::Env env = info.Env();                                             \
    Napi::Object dockObjectNapi = info[0].As<Napi::Object>();               \
    NodeWidgetWrap* dockWidgetWrap =                                        \
      Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockObjectNapi);             \
    QObject* dockObject = dockWidgetWrap->getInternalInstance();            \
    ads::CDockWidget* dockWidget =                                          \
      qobject_cast<ads::CDockWidget*>(dockObject);                          \
    this->instance->removeDockWidget(dockWidget);                           \
    return env.Null();                                                      \
  }                                                                         \
  Napi::Value isInFrontOf(const Napi::CallbackInfo& info) {                 \
    Napi::Env env = info.Env();                                             \
    Napi::Object dockContainerWidgetNapi = info[1].As<Napi::Object>();      \
    NodeWidgetWrap* dockContainerWidgetWrap =                               \
      Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockContainerWidgetNapi);    \
    QObject* dockContainerWidgetObject =                                    \
      dockContainerWidgetWrap->getInternalInstance();                       \
    ads::CDockContainerWidget* dockContainerWidget =                        \
      qobject_cast<ads::CDockContainerWidget*>(dockContainerWidgetObject);  \
    bool result = this->instance->isInFrontOf(dockContainerWidget);         \
    return Napi::Boolean::New(env, result);                                 \
  }                                                                         \
  Napi::Value dockArea(const Napi::CallbackInfo& info) {                    \
    Napi::Env env = info.Env();                                             \
    int index = info[0].As<Napi::Number>().Int32Value();                    \
    ads::CDockAreaWidget* dockAreaWidgetResult =                            \
      this->instance->dockArea(index);                                      \
    if (dockAreaWidgetResult) {                                             \
      return WrapperCache::instance.getWrapper(env,                         \
        static_cast<QObject*>(dockAreaWidgetResult));                       \
    } else {                                                                \
      return env.Null();                                                    \
    }                                                                       \
  }                                                                         \
  Napi::Value dockAreaAt(const Napi::CallbackInfo& info) {                  \
    Napi::Env env = info.Env();                                             \
    QPoint* point =                                                         \
        Napi::ObjectWrap<QPointWrap>::Unwrap(info[0].As<Napi::Object>())    \
            ->getInternalInstance();                                        \
    ads::CDockAreaWidget* dockAreaWidgetResult =                            \
      this->instance->dockAreaAt(*point);                                   \
    if (dockAreaWidgetResult) {                                             \
      return WrapperCache::instance.getWrapper(env,                         \
        static_cast<QObject*>(dockAreaWidgetResult));                       \
    } else {                                                                \
      return env.Null();                                                    \
    }                                                                       \
  }                                                                         \
  Napi::Value closeOtherAreas(const Napi::CallbackInfo& info) {             \
    Napi::Env env = info.Env();                                             \
    ads::CDockAreaWidget* dockAreaWidget = nullptr;                         \
    if ( ! info[0].IsNull()) {                                              \
      Napi::Object dockAreaObjectNapi = info[0].As<Napi::Object>();         \
      NodeWidgetWrap* dockAreaWidgetWrap =                                  \
        Napi::ObjectWrap<NodeWidgetWrap>::Unwrap(dockAreaObjectNapi);       \
      QObject* dockAreaObject = dockAreaWidgetWrap->getInternalInstance();  \
      dockAreaWidget = qobject_cast<ads::CDockAreaWidget*>(dockAreaObject); \
    }                                                                       \
    this->instance->closeOtherAreas(dockAreaWidget);                        \
    return env.Null();                                                      \
  }                                                                         \
  Napi::Value openedDockAreas(const Napi::CallbackInfo& info) {             \
    Napi::Env env = info.Env();                                             \
    QList<ads::CDockAreaWidget*> list = this->instance->openedDockAreas();  \
    Napi::Array resultArrayNapi = Napi::Array::New(env, list.size());       \
    for (int i = 0; i < list.size(); i++) {                                 \
      resultArrayNapi[i] =                                                  \
          WrapperCache::instance.getWrapper(env, list[i]);                  \
    }                                                                       \
    return resultArrayNapi;                                                 \
  }


#define CDOCKCONTAINERWIDGET_WRAPPED_METHODS_EXPORT_DEFINE(WidgetWrapName)        \
  QFRAME_WRAPPED_METHODS_EXPORT_DEFINE(WidgetWrapName)                            \
                                                                                  \
  InstanceMethod("dumpLayout", &WidgetWrapName::dumpLayout),                      \
  InstanceMethod("features", &WidgetWrapName::features),                          \
  InstanceMethod("isFloating", &WidgetWrapName::isFloating),                      \
  InstanceMethod("zOrderIndex", &WidgetWrapName::zOrderIndex),                    \
  InstanceMethod("hasTopLevelDockWidget", &WidgetWrapName::hasTopLevelDockWidget),\
  InstanceMethod("dockAreaCount", &WidgetWrapName::dockAreaCount),                \
  InstanceMethod("visibleDockAreaCount", &WidgetWrapName::visibleDockAreaCount),  \
  InstanceMethod("addDockWidget", &WidgetWrapName::addDockWidget),                \
  InstanceMethod("removeDockWidget", &WidgetWrapName::removeDockWidget),          \
  InstanceMethod("isInFrontOf", &WidgetWrapName::isInFrontOf),                    \
  InstanceMethod("dockArea", &WidgetWrapName::dockArea),                          \
  InstanceMethod("dockAreaAt", &WidgetWrapName::dockAreaAt),                      \
  InstanceMethod("closeOtherAreas", &WidgetWrapName::closeOtherAreas),            \
  InstanceMethod("openedDockAreas", &WidgetWrapName::openedDockAreas),

  // ads::CFloatingDockContainer* floatingWidget() const;
