#include <tp_qt_utils/EventDebug.h>

#include "tp_utils/DebugUtils.h"

namespace tp_qt_utils
{

//##################################################################################################
EventDebug::EventDebug(QObject* watched)
{
  watched->installEventFilter(this);
}

//##################################################################################################
std::string EventDebug::eventTypeString(QEvent::Type type)
{
  switch(type)
  {
  case QEvent::None:                                     return "None";
  case QEvent::Timer:                                    return "Timer";
  case QEvent::MouseButtonPress:                         return "MouseButtonPress";
  case QEvent::MouseButtonRelease:                       return "MouseButtonRelease";
  case QEvent::MouseButtonDblClick:                      return "MouseButtonDblClick";
  case QEvent::MouseMove:                                return "MouseMove";
  case QEvent::KeyPress:                                 return "KeyPress";
  case QEvent::KeyRelease:                               return "KeyRelease";
  case QEvent::FocusIn:                                  return "FocusIn";
  case QEvent::FocusOut:                                 return "FocusOut";
#if QT_VERSION >= 0x050000
  case QEvent::FocusAboutToChange:                       return "FocusAboutToChange";
#endif
  case QEvent::Enter:                                    return "Enter";
  case QEvent::Leave:                                    return "Leave";
  case QEvent::Paint:                                    return "Paint";
  case QEvent::Move:                                     return "Move";
  case QEvent::Resize:                                   return "Resize";
  case QEvent::Create:                                   return "Create";
  case QEvent::Destroy:                                  return "Destroy";
  case QEvent::Show:                                     return "Show";
  case QEvent::Hide:                                     return "Hide";
  case QEvent::Close:                                    return "Close";
  case QEvent::Quit:                                     return "Quit";
  case QEvent::ParentChange:                             return "ParentChange";
  case QEvent::ParentAboutToChange:                      return "ParentAboutToChange";
  case QEvent::ThreadChange:                             return "ThreadChange";
  case QEvent::WindowActivate:                           return "WindowActivate";
  case QEvent::WindowDeactivate:                         return "WindowDeactivate";
  case QEvent::ShowToParent:                             return "ShowToParent";
  case QEvent::HideToParent:                             return "HideToParent";
  case QEvent::Wheel:                                    return "Wheel";
  case QEvent::WindowTitleChange:                        return "WindowTitleChange";
  case QEvent::WindowIconChange:                         return "WindowIconChange";
  case QEvent::ApplicationWindowIconChange:              return "ApplicationWindowIconChange";
  case QEvent::ApplicationFontChange:                    return "ApplicationFontChange";
  case QEvent::ApplicationLayoutDirectionChange:         return "ApplicationLayoutDirectionChange";
  case QEvent::ApplicationPaletteChange:                 return "ApplicationPaletteChange";
  case QEvent::PaletteChange:                            return "PaletteChange";
  case QEvent::Clipboard:                                return "Clipboard";
  case QEvent::Speech:                                   return "Speech";
  case QEvent::MetaCall:                                 return "MetaCall";
  case QEvent::SockAct:                                  return "SockAct";
  case QEvent::WinEventAct:                              return "WinEventAct";
  case QEvent::DeferredDelete:                           return "DeferredDelete";
  case QEvent::DragEnter:                                return "DragEnter";
  case QEvent::DragMove:                                 return "DragMove";
  case QEvent::DragLeave:                                return "DragLeave";
  case QEvent::Drop:                                     return "Drop";
  case QEvent::DragResponse:                             return "DragResponse";
  case QEvent::ChildAdded:                               return "ChildAdded";
  case QEvent::ChildPolished:                            return "ChildPolished";
  case QEvent::ChildRemoved:                             return "ChildRemoved";
  case QEvent::ShowWindowRequest:                        return "ShowWindowRequest";
  case QEvent::PolishRequest:                            return "PolishRequest";
  case QEvent::Polish:                                   return "Polish";
  case QEvent::LayoutRequest:                            return "LayoutRequest";
  case QEvent::UpdateRequest:                            return "UpdateRequest";
  case QEvent::UpdateLater:                              return "UpdateLater";
  case QEvent::EmbeddingControl:                         return "EmbeddingControl";
  case QEvent::ActivateControl:                          return "ActivateControl";
  case QEvent::DeactivateControl:                        return "DeactivateControl";
  case QEvent::ContextMenu:                              return "ContextMenu";
  case QEvent::InputMethod:                              return "InputMethod";
  case QEvent::TabletMove:                               return "TabletMove";
  case QEvent::LocaleChange:                             return "LocaleChange";
  case QEvent::LanguageChange:                           return "LanguageChange";
  case QEvent::LayoutDirectionChange:                    return "LayoutDirectionChange";
  case QEvent::Style:                                    return "Style";
  case QEvent::TabletPress:                              return "TabletPress";
  case QEvent::TabletRelease:                            return "TabletRelease";
  case QEvent::OkRequest:                                return "OkRequest";
  case QEvent::HelpRequest:                              return "HelpRequest";
  case QEvent::IconDrag:                                 return "IconDrag";
  case QEvent::FontChange:                               return "FontChange";
  case QEvent::EnabledChange:                            return "EnabledChange";
  case QEvent::ActivationChange:                         return "ActivationChange";
  case QEvent::StyleChange:                              return "StyleChange";
  case QEvent::IconTextChange:                           return "IconTextChange";
  case QEvent::ModifiedChange:                           return "ModifiedChange";
  case QEvent::MouseTrackingChange:                      return "MouseTrackingChange";
  case QEvent::WindowBlocked:                            return "WindowBlocked";
  case QEvent::WindowUnblocked:                          return "WindowUnblocked";
  case QEvent::WindowStateChange:                        return "WindowStateChange";
  case QEvent::ToolTip:                                  return "ToolTip";
  case QEvent::WhatsThis:                                return "WhatsThis";
  case QEvent::StatusTip:                                return "StatusTip";
  case QEvent::ActionChanged:                            return "ActionChanged";
  case QEvent::ActionAdded:                              return "ActionAdded";
  case QEvent::ActionRemoved:                            return "ActionRemoved";
  case QEvent::FileOpen:                                 return "FileOpen";
  case QEvent::Shortcut:                                 return "Shortcut";
  case QEvent::ShortcutOverride:                         return "ShortcutOverride";
  case QEvent::WhatsThisClicked:                         return "WhatsThisClicked";
  case QEvent::ToolBarChange:                            return "ToolBarChange";
    //    case QEvent::ApplicationActivate:                      return "ApplicationActivate";
    //    case QEvent::ApplicationActivated:                     return "ApplicationActivated";
    //    case QEvent::ApplicationDeactivate:                    return "ApplicationDeactivate";
    //    case QEvent::ApplicationDeactivated:                   return "ApplicationDeactivated";
  case QEvent::QueryWhatsThis:                           return "QueryWhatsThis";
  case QEvent::EnterWhatsThisMode:                       return "EnterWhatsThisMode";
  case QEvent::LeaveWhatsThisMode:                       return "LeaveWhatsThisMode";
  case QEvent::ZOrderChange:                             return "ZOrderChange";
  case QEvent::HoverEnter:                               return "HoverEnter";
  case QEvent::HoverLeave:                               return "HoverLeave";
  case QEvent::HoverMove:                                return "HoverMove";
#ifdef QT_KEYPAD_NAVIGATION
  case QEvent::EnterEditFocus:                           return "EnterEditFocus";
  case QEvent::LeaveEditFocus:                           return "LeaveEditFocus";
#endif
  case QEvent::AcceptDropsChange:                        return "AcceptDropsChange";
  case QEvent::ZeroTimerEvent:                           return "ZeroTimerEvent";
  case QEvent::GraphicsSceneMouseMove:                   return "GraphicsSceneMouseMove";
  case QEvent::GraphicsSceneMousePress:                  return "GraphicsSceneMousePress";
  case QEvent::GraphicsSceneMouseRelease:                return "GraphicsSceneMouseRelease";
  case QEvent::GraphicsSceneMouseDoubleClick:            return "GraphicsSceneMouseDoubleClick";
  case QEvent::GraphicsSceneContextMenu:                 return "GraphicsSceneContextMenu";
  case QEvent::GraphicsSceneHoverEnter:                  return "GraphicsSceneHoverEnter";
  case QEvent::GraphicsSceneHoverMove:                   return "GraphicsSceneHoverMove";
  case QEvent::GraphicsSceneHoverLeave:                  return "GraphicsSceneHoverLeave";
  case QEvent::GraphicsSceneHelp:                        return "GraphicsSceneHelp";
  case QEvent::GraphicsSceneDragEnter:                   return "GraphicsSceneDragEnter";
  case QEvent::GraphicsSceneDragMove:                    return "GraphicsSceneDragMove";
  case QEvent::GraphicsSceneDragLeave:                   return "GraphicsSceneDragLeave";
  case QEvent::GraphicsSceneDrop:                        return "GraphicsSceneDrop";
  case QEvent::GraphicsSceneWheel:                       return "GraphicsSceneWheel";
  case QEvent::KeyboardLayoutChange:                     return "KeyboardLayoutChange";
  case QEvent::DynamicPropertyChange:                    return "DynamicPropertyChange";
  case QEvent::TabletEnterProximity:                     return "TabletEnterProximity";
  case QEvent::TabletLeaveProximity:                     return "TabletLeaveProximity";
  case QEvent::NonClientAreaMouseMove:                   return "NonClientAreaMouseMove";
  case QEvent::NonClientAreaMouseButtonPress:            return "NonClientAreaMouseButtonPress";
  case QEvent::NonClientAreaMouseButtonRelease:          return "NonClientAreaMouseButtonRelease";
  case QEvent::NonClientAreaMouseButtonDblClick:         return "NonClientAreaMouseButtonDblClick";
  case QEvent::MacSizeChange:                            return "MacSizeChange";
  case QEvent::ContentsRectChange:                       return "ContentsRectChange";
  case QEvent::MacGLWindowChange:                        return "MacGLWindowChange";
  case QEvent::FutureCallOut:                            return "FutureCallOut";
  case QEvent::GraphicsSceneResize:                      return "GraphicsSceneResize";
  case QEvent::GraphicsSceneMove:                        return "GraphicsSceneMove";
  case QEvent::CursorChange:                             return "CursorChange";
  case QEvent::ToolTipChange:                            return "ToolTipChange";
  case QEvent::NetworkReplyUpdated:                      return "NetworkReplyUpdated";
  case QEvent::GrabMouse:                                return "GrabMouse";
  case QEvent::UngrabMouse:                              return "UngrabMouse";
  case QEvent::GrabKeyboard:                             return "GrabKeyboard";
  case QEvent::UngrabKeyboard:                           return "UngrabKeyboard";
  case QEvent::MacGLClearDrawable:                       return "MacGLClearDrawable";
  case QEvent::StateMachineSignal:                       return "StateMachineSignal";
  case QEvent::StateMachineWrapped:                      return "StateMachineWrapped";
  case QEvent::TouchBegin:                               return "TouchBegin";
  case QEvent::TouchUpdate:                              return "TouchUpdate";
  case QEvent::TouchEnd:                                 return "TouchEnd";
#ifndef QT_NO_GESTURES
  case QEvent::NativeGesture:                            return "NativeGesture";
#endif
  case QEvent::RequestSoftwareInputPanel:                return "RequestSoftwareInputPanel";
  case QEvent::CloseSoftwareInputPanel:                  return "CloseSoftwareInputPanel";
  case QEvent::WinIdChange:                              return "WinIdChange";
#ifndef QT_NO_GESTURES
  case QEvent::Gesture:                                  return "Gesture";
  case QEvent::GestureOverride:                          return "GestureOverride";
#endif
#if QT_VERSION >= 0x050000
  case QEvent::ScrollPrepare:                            return "ScrollPrepare";
  case QEvent::Scroll:                                   return "Scroll";
  case QEvent::Expose:                                   return "Expose";
  case QEvent::InputMethodQuery:                         return "InputMethodQuery";
  case QEvent::OrientationChange:                        return "OrientationChange";
  case QEvent::TouchCancel:                              return "TouchCancel";
  case QEvent::ThemeChange:                              return "ThemeChange";
  case QEvent::SockClose:                                return "SockClose";
  case QEvent::PlatformPanel:                            return "PlatformPanel";
  case QEvent::StyleAnimationUpdate:                     return "StyleAnimationUpdate";
  case QEvent::ApplicationStateChange:                   return "ApplicationStateChange";
  case QEvent::WindowChangeInternal:                     return "WindowChangeInternal";
#endif
  default:
    if(type>=QEvent::User && type<=QEvent::MaxUser)
      return "User";
  }
  return std::string("Unknown: ") + QString::number(type).toStdString();
}

//##################################################################################################
bool EventDebug::eventFilter(QObject* watched, QEvent* event)
{
  tpWarning() << watched << eventTypeString(event->type());
  return false;
}

}
