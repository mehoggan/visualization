#include "com/visualization/log_helpers.h"

namespace com
{
  namespace visualization
  {
    std::stringstream &operator<<(std::stringstream &ss,
      const QEvent &event)
    {
      ss << "isAccepted = " << event.isAccepted() << " type = ";

      switch (event.type()) {
      case QEvent::None: {
        ss << "QEvent::None";
      }
        break;
      case QEvent::ActionAdded: {
        ss << "QEvent::ActionAdded";
      }
        break;
      case QEvent::ActionChanged: {
        ss << "QEvent::ActionChanged";
      }
        break;
      case QEvent::ActionRemoved: {
        ss << "QEvent::ActionRemoved";
      }
        break;
      case QEvent::ActivationChange: {
        ss << "QEvent::ActivationChange";
      }
        break;
      case QEvent::ApplicationActivate: {
        ss << "QEvent::ApplicationActivate";
      }
        break;
      case QEvent::ApplicationDeactivate: {
        ss << "QEvent::ApplicationDeactivate";
      }
        break;
      case QEvent::ApplicationFontChange: {
        ss << "QEvent::ApplicationFontChange";
      }
        break;
      case QEvent::ApplicationLayoutDirectionChange: {
        ss << "QEvent::ApplicationLayoutDirectionChange";
      }
        break;
      case QEvent::ApplicationPaletteChange: {
        ss << "QEvent::ApplicationPaletteChange";
      }
        break;
      case QEvent::ApplicationStateChange: {
        ss << "QEvent::ApplicationStateChange";
      }
        break;
      case QEvent::ApplicationWindowIconChange: {
        ss << "QEvent::ApplicationWindowIconChange";
      }
        break;
      case QEvent::ChildAdded: {
        ss << "QEvent::ChildAdded";
      }
        break;
      case QEvent::ChildPolished: {
        ss << "QEvent::ChildPolished";
      }
        break;
      case QEvent::ChildRemoved: {
        ss << "QEvent::ChildRemoved";
      }
        break;
      case QEvent::Clipboard: {
        ss << "QEvent::Clipboard";
      }
        break;
      case QEvent::Close: {
        ss << "QEvent::Close";
      }
        break;
      case QEvent::CloseSoftwareInputPanel: {
        ss << "QEvent::CloseSoftwareInputPanel";
      }
        break;
      case QEvent::ContentsRectChange: {
        ss << "QEvent::ContentsRectChange";
      }
        break;
      case QEvent::ContextMenu: {
        ss << "QEvent::ContextMenu";
      }
        break;
      case QEvent::Create: {
        ss << "QEvent::Create";
      }
        break;
      case QEvent::CursorChange: {
        ss << "QEvent::CursorChange";
      }
        break;
      case QEvent::DeferredDelete: {
        ss << "QEvent::DeferredDelete";
      }
        break;
      case QEvent::Destroy: {
        ss << "QEvent::Destroy";
      }
        break;
      case QEvent::DragEnter: {
        ss << "QEvent::DragEnter";
      }
        break;
      case QEvent::DragLeave: {
        ss << "QEvent::DragLeave";
      }
        break;
      case QEvent::DragMove: {
        ss << "QEvent::DragMove";
      }
        break;
      case QEvent::DragResponse: {
        ss << "QEvent::DragResponse";
      }
        break;
      case QEvent::Drop: {
        ss << "QEvent::Drop";
      }
        break;
      case QEvent::DynamicPropertyChange: {
        ss << "QEvent::DynamicPropertyChange";
      }
        break;
      case QEvent::EnabledChange: {
        ss << "QEvent::EnabledChange";
      }
        break;
      case QEvent::Enter: {
        ss << "QEvent::Enter";
      }
        break;
      case QEvent::EnterWhatsThisMode: {
        ss << "QEvent::EnterWhatsThisMode";
      }
        break;
      case QEvent::Expose: {
        ss << "QEvent::Expose";
      }
        break;
      case QEvent::FileOpen: {
        ss << "QEvent::FileOpen";
      }
        break;
      case QEvent::FocusIn: {
        ss << "QEvent::FocusIn";
      }
        break;
      case QEvent::FocusOut: {
        ss << "QEvent::FocusOut";
      }
        break;
      case QEvent::FocusAboutToChange: {
        ss << "QEvent::FocusAboutToChange";
      }
        break;
      case QEvent::FontChange: {
        ss << "QEvent::FontChange";
      }
        break;
      case QEvent::Gesture: {
        ss << "QEvent::Gesture";
      }
        break;
      case QEvent::GestureOverride: {
        ss << "QEvent::GestureOverride";
      }
        break;
      case QEvent::GrabKeyboard: {
        ss << "QEvent::GrabKeyboard";
      }
        break;
      case QEvent::GrabMouse: {
        ss << "QEvent::GrabMouse";
      }
        break;
      case QEvent::GraphicsSceneContextMenu: {
        ss << "QEvent::GraphicsSceneContextMenu";
      }
        break;
      case QEvent::GraphicsSceneDragEnter: {
        ss << "QEvent::GraphicsSceneDragEnter";
      }
        break;
      case QEvent::GraphicsSceneDragLeave: {
        ss << "QEvent::GraphicsSceneDragLeave";
      }
        break;
      case QEvent::GraphicsSceneDragMove: {
        ss << "QEvent::GraphicsSceneDragMove";
      }
        break;
      case QEvent::GraphicsSceneDrop: {
        ss << "QEvent::GraphicsSceneDrop";
      }
        break;
      case QEvent::GraphicsSceneHelp: {
        ss << "QEvent::GraphicsSceneHelp";
      }
        break;
      case QEvent::GraphicsSceneHoverEnter: {
        ss << "QEvent::GraphicsSceneHoverEnter";
      }
        break;
      case QEvent::GraphicsSceneHoverLeave: {
        ss << "QEvent::GraphicsSceneHoverLeave";
      }
        break;
      case QEvent::GraphicsSceneHoverMove: {
        ss << "QEvent::GraphicsSceneHoverMove";
      }
        break;
      case QEvent::GraphicsSceneMouseDoubleClick: {
        ss << "QEvent::GraphicsSceneMouseDoubleClick";
      }
        break;
      case QEvent::GraphicsSceneMouseMove: {
        ss << "QEvent::GraphicsSceneMouseMove";
      }
        break;
      case QEvent::GraphicsSceneMousePress: {
        ss << "QEvent::GraphicsSceneMousePress";
      }
        break;
      case QEvent::GraphicsSceneMouseRelease: {
        ss << "QEvent::GraphicsSceneMouseRelease";
      }
        break;
      case QEvent::GraphicsSceneMove: {
        ss << "QEvent::GraphicsSceneMove";
      }
        break;
      case QEvent::GraphicsSceneResize: {
        ss << "QEvent::GraphicsSceneResize";
      }
        break;
      case QEvent::GraphicsSceneWheel: {
        ss << "QEvent::GraphicsSceneWheel";
      }
        break;
      case QEvent::Hide: {
        ss << "QEvent::Hide";
      }
        break;
      case QEvent::HideToParent: {
        ss << "QEvent::HideToParent";
      }
        break;
      case QEvent::HoverEnter: {
        ss << "QEvent::HoverEnter";
      }
        break;
      case QEvent::HoverLeave: {
        ss << "QEvent::HoverLeave";
      }
        break;
      case QEvent::HoverMove: {
        ss << "QEvent::HoverMove";
      }
        break;
      case QEvent::IconDrag: {
        ss << "QEvent::IconDrag";
      }
        break;
      case QEvent::IconTextChange: {
        ss << "QEvent::IconTextChange";
      }
        break;
      case QEvent::InputMethod: {
        ss << "QEvent::InputMethod";
      }
        break;
      case QEvent::InputMethodQuery: {
        ss << "QEvent::InputMethodQuery";
      }
        break;
      case QEvent::KeyboardLayoutChange: {
        ss << "QEvent::KeyboardLayoutChange";
      }
        break;
      case QEvent::KeyPress: {
        ss << "QEvent::KeyPress";
      }
        break;
      case QEvent::KeyRelease: {
        ss << "QEvent::KeyRelease";
      }
        break;
      case QEvent::LanguageChange: {
        ss << "QEvent::LanguageChange";
      }
        break;
      case QEvent::LayoutDirectionChange: {
        ss << "QEvent::LayoutDirectionChange";
      }
        break;
      case QEvent::LayoutRequest: {
        ss << "QEvent::LayoutRequest";
      }
        break;
      case QEvent::Leave: {
        ss << "QEvent::Leave";
      }
        break;
      case QEvent::LeaveWhatsThisMode: {
        ss << "QEvent::LeaveWhatsThisMode";
      }
        break;
      case QEvent::LocaleChange: {
        ss << "QEvent::LocaleChange";
      }
        break;
      case QEvent::NonClientAreaMouseButtonDblClick: {
        ss << "QEvent::NonClientAreaMouseButtonDblClick";
      }
        break;
      case QEvent::NonClientAreaMouseButtonPress: {
        ss << "QEvent::NonClientAreaMouseButtonPress";
      }
        break;
      case QEvent::NonClientAreaMouseButtonRelease: {
        ss << "QEvent::NonClientAreaMouseButtonRelease";
      }
        break;
      case QEvent::NonClientAreaMouseMove: {
        ss << "QEvent::NonClientAreaMouseMove";
      }
        break;
      case QEvent::MacSizeChange: {
        ss << "QEvent::MacSizeChange";
      }
        break;
      case QEvent::MetaCall: {
        ss << "QEvent::MetaCall";
      }
        break;
      case QEvent::ModifiedChange: {
        ss << "QEvent::ModifiedChange";
      }
        break;
      case QEvent::MouseButtonDblClick: {
        ss << "QEvent::MouseButtonDblClick";
      }
        break;
      case QEvent::MouseButtonPress: {
        ss << "QEvent::MouseButtonPress";
      }
        break;
      case QEvent::MouseButtonRelease: {
        ss << "QEvent::MouseButtonRelease";
      }
        break;
      case QEvent::MouseMove: {
        ss << "QEvent::MouseMove";
      }
        break;
      case QEvent::MouseTrackingChange: {
        ss << "QEvent::MouseTrackingChange";
      }
        break;
      case QEvent::Move: {
        ss << "QEvent::Move";
      }
        break;
      case QEvent::NativeGesture: {
        ss << "QEvent::NativeGesture";
      }
        break;
      case QEvent::OrientationChange: {
        ss << "QEvent::OrientationChange";
      }
        break;
      case QEvent::Paint: {
        ss << "QEvent::Paint";
      }
        break;
      case QEvent::PaletteChange: {
        ss << "QEvent::PaletteChange";
      }
        break;
      case QEvent::ParentAboutToChange: {
        ss << "QEvent::ParentAboutToChange";
      }
        break;
      case QEvent::ParentChange: {
        ss << "QEvent::ParentChange";
      }
        break;
      case QEvent::PlatformPanel: {
        ss << "QEvent::PlatformPanel";
      }
        break;
      case QEvent::PlatformSurface: {
        ss << "QEvent::PlatformSurface";
      }
        break;
      case QEvent::Polish: {
        ss << "QEvent::Polish";
      }
        break;
      case QEvent::PolishRequest: {
        ss << "QEvent::PolishRequest";
      }
        break;
      case QEvent::QueryWhatsThis: {
        ss << "QEvent::QueryWhatsThis";
      }
        break;
      case QEvent::Quit: {
        ss << "QEvent::Quit";
      }
        break;
      case QEvent::ReadOnlyChange: {
        ss << "QEvent::ReadOnlyChange";
      }
        break;
      case QEvent::RequestSoftwareInputPanel: {
        ss << "QEvent::RequestSoftwareInputPanel";
      }
        break;
      case QEvent::Resize: {
        ss << "QEvent::Resize";
      }
        break;
      case QEvent::ScrollPrepare: {
        ss << "QEvent::ScrollPrepare";
      }
        break;
      case QEvent::Scroll: {
        ss << "QEvent::Scroll";
      }
        break;
      case QEvent::Shortcut: {
        ss << "QEvent::Shortcut";
      }
        break;
      case QEvent::ShortcutOverride: {
        ss << "QEvent::ShortcutOverride";
      }
        break;
      case QEvent::Show: {
        ss << "QEvent::Show";
      }
        break;
      case QEvent::ShowWindowRequest: {
        ss << "QEvent::ShowWindowRequest";
      }
        break;
      case QEvent::ShowToParent: {
        ss << "QEvent::ShowToParent";
      }
        break;
      case QEvent::SockAct: {
        ss << "QEvent::SockAct";
      }
        break;
      case QEvent::Speech: {
        ss << "QEvent::Speech";
      }
        break;
      case QEvent::StateMachineSignal: {
        ss << "QEvent::StateMachineSignal";
      }
        break;
      case QEvent::StateMachineWrapped: {
        ss << "QEvent::StateMachineWrapped";
      }
        break;
      case QEvent::StatusTip: {
        ss << "QEvent::StatusTip";
      }
        break;
      case QEvent::StyleChange: {
        ss << "QEvent::StyleChange";
      }
        break;
      case QEvent::TabletMove: {
        ss << "QEvent::TabletMove";
      }
        break;
      case QEvent::TabletPress: {
        ss << "QEvent::TabletPress";
      }
        break;
      case QEvent::TabletRelease: {
        ss << "QEvent::TabletRelease";
      }
        break;
      case QEvent::TabletEnterProximity: {
        ss << "QEvent::TabletEnterProximity";
      }
        break;
      case QEvent::TabletLeaveProximity: {
        ss << "QEvent::TabletLeaveProximity";
      }
        break;
      case QEvent::ThreadChange: {
        ss << "QEvent::ThreadChange";
      }
        break;
      case QEvent::Timer: {
        ss << "QEvent::Timer";
      }
        break;
      case QEvent::ToolBarChange: {
        ss << "QEvent::ToolBarChange";
      }
        break;
      case QEvent::ToolTip: {
        ss << "QEvent::ToolTip";
      }
        break;
      case QEvent::ToolTipChange: {
        ss << "QEvent::ToolTipChange";
      }
        break;
      case QEvent::TouchBegin: {
        ss << "QEvent::TouchBegin";
      }
        break;
      case QEvent::TouchCancel: {
        ss << "QEvent::TouchCancel";
      }
        break;
      case QEvent::TouchEnd: {
        ss << "QEvent::TouchEnd";
      }
        break;
      case QEvent::TouchUpdate: {
        ss << "QEvent::TouchUpdate";
      }
        break;
      case QEvent::UngrabKeyboard: {
        ss << "QEvent::UngrabKeyboard";
      }
        break;
      case QEvent::UngrabMouse: {
        ss << "QEvent::UngrabMouse";
      }
        break;
      case QEvent::UpdateLater: {
        ss << "QEvent::UpdateLater";
      }
        break;
      case QEvent::UpdateRequest: {
        ss << "QEvent::UpdateRequest";
      }
        break;
      case QEvent::WhatsThis: {
        ss << "QEvent::WhatsThis";
      }
        break;
      case QEvent::WhatsThisClicked: {
        ss << "QEvent::WhatsThisClicked";
      }
        break;
      case QEvent::Wheel: {
        ss << "QEvent::Wheel";
      }
        break;
      case QEvent::WinEventAct: {
        ss << "QEvent::WinEventAct";
      }
        break;
      case QEvent::WindowActivate: {
        ss << "QEvent::WindowActivate";
      }
        break;
      case QEvent::WindowBlocked: {
        ss << "QEvent::WindowBlocked";
      }
        break;
      case QEvent::WindowDeactivate: {
        ss << "QEvent::WindowDeactivate";
      }
        break;
      case QEvent::WindowIconChange: {
        ss << "QEvent::WindowIconChange";
      }
        break;
      case QEvent::WindowStateChange: {
        ss << "QEvent::WindowStateChange";
      }
        break;
      case QEvent::WindowTitleChange: {
        ss << "QEvent::WindowTitleChange";
      }
        break;
      case QEvent::WindowUnblocked: {
        ss << "QEvent::WindowUnblocked";
      }
        break;
      case QEvent::WinIdChange: {
        ss << "QEvent::WinIdChange";
      }
        break;
      case QEvent::ZOrderChange: {
        ss << "QEvent::ZOrderChange";
      }
        break;
      default: {
        ss << event.type();
      }
        break;
      }

      return ss;
    }

    std::stringstream &operator<<(std::stringstream &ss,
      const QKeyEvent &event)
    {
      ss << (*dynamic_cast<const QEvent *>(&event));
      ss << " count = " << event.count();
      ss << " isAutoRepeat = " << ((event.isAutoRepeat()) ? "true" : "false");
      ss << " key = " << event.key();
      ss << " modifiers = ";
      switch (event.modifiers()) {
      case Qt::NoModifier: {
        ss << "Qt::NoModifier";
      }
        break;
      case Qt::ShiftModifier: {
        ss << "QtShiftModifier";
      }
        break;
      case Qt::ControlModifier: {
        ss << "Qt::ControlModifier";
      }
        break;
      case Qt::AltModifier: {
        ss << "Qt::AltModifier";
      }
        break;
      case Qt::MetaModifier: {
        ss << "Qt::MetaModifier";
      }
        break;
      case Qt::KeypadModifier: {
        ss << "Qt::KeypadModifier";
      }
        break;
      case Qt::GroupSwitchModifier: {
        ss << "Qt::GroupSwitchModifier";
      }
        break;
      default: {
      }
        break;
      }
      ss << " nativeModifiers = " << event.nativeModifiers();
      ss << " nativeScanCode = " << event.nativeScanCode();
      ss << " nativeVirtualKey = " << event.nativeVirtualKey();
      ss << " text = " << event.text().toStdString();

      return ss;
    }

    std::stringstream &operator<<(std::stringstream &ss,
      const QMouseEvent &event)
    {
      ss << (*dynamic_cast<const QEvent *>(&event));
      ss << " button = ";
      switch (event.button()) {
      case Qt::NoButton: {
        ss << "Qt::NoButton";
      }
        break;
      case Qt::AllButtons: {
        ss << "Qt::AllButtons";
      }
        break;
      case Qt::LeftButton: {
        ss << "Qt::LeftButton";
      }
        break;
      case Qt::RightButton: {
        ss << "Qt::RightButton";
      }
        break;
      case Qt::MiddleButton: {
        ss << "Qt::MiddleButton";
      }
        break;
      case Qt::BackButton: {
        ss << "Qt::BackButton";
      }
        break;
      case Qt::ForwardButton: {
        ss << "Qt::ForwardButton";
      }
        break;
      case Qt::TaskButton: {
        ss << "Qt::TaskButton";
      }
        break;
      case Qt::ExtraButton4: {
        ss << "Qt::ExtraButton4";
      }
        break;
      case Qt::ExtraButton5: {
        ss << "Qt::ExtraButton5";
      }
        break;
      case Qt::ExtraButton6: {
        ss << "Qt::ExtraButton6";
      }
        break;
      case Qt::ExtraButton7: {
        ss << "Qt::ExtraButton7";
      }
        break;
      case Qt::ExtraButton8: {
        ss << "Qt::ExtraButton8";
      }
        break;
      case Qt::ExtraButton9: {
        ss << "Qt::ExtraButton9";
      }
        break;
      case Qt::ExtraButton10: {
        ss << "Qt::ExtraButton10";
      }
        break;
      case Qt::ExtraButton11: {
        ss << "Qt::ExtraButton11";
      }
        break;
      case Qt::ExtraButton12: {
        ss << "Qt::ExtraButton12";
      }
        break;
      case Qt::ExtraButton13: {
        ss << "Qt::ExtraButton13";
      }
        break;
      case Qt::ExtraButton14: {
        ss << "Qt::ExtraButton14";
      }
        break;
      case Qt::ExtraButton15: {
        ss << "Qt::ExtraButton15";
      }
        break;
      case Qt::ExtraButton16: {
        ss << "Qt::ExtraButton16";
      }
        break;
      case Qt::ExtraButton17: {
        ss << "Qt::ExtraButton17";
      }
        break;
      case Qt::ExtraButton18: {
        ss << "Qt::ExtraButton18";
      }
        break;
      case Qt::ExtraButton19: {
        ss << "Qt::ExtraButton19";
      }
        break;
      case Qt::ExtraButton20: {
        ss << "Qt::ExtraButton20";
      }
        break;
      case Qt::ExtraButton21: {
        ss << "Qt::ExtraButton21";
      }
        break;
      case Qt::ExtraButton22: {
        ss << "Qt::ExtraButton22";
      }
        break;
      case Qt::ExtraButton23: {
        ss << "Qt::ExtraButton23";
      }
        break;
      case Qt::ExtraButton24: {
        ss << "Qt::ExtraButton24";
      }
        break;
      default: {
        ss << event.button();
      }
        break;
      }
      ss << " buttons = " << event.buttons();
      ss << " flags = ";
      switch (event.flags()) {
      case Qt::MouseEventCreatedDoubleClick: {
        ss << "Qt::MouseEventCreatedDoubleClick";
      }
        break;
      default: {
        ss << event.flags();
      }
      }
      ss << " globalPos = " << event.globalPos().x() << ", "
        << event.globalPos().y();
      ss << " localPos = " << event.localPos().x() << ", "
        << event.localPos().y();
      ss << " pos = " << event.pos().x() << ", " << event.pos().y();
      ss << " screenPos = " << event.screenPos().x() << ", "
        << event.screenPos().y();
      ss << " source = ";
      switch (event.source()) {
      case Qt::MouseEventNotSynthesized: {
        ss << "Qt::MouseEventNotSynthesized";
      }
        break;
      case Qt::MouseEventSynthesizedBySystem: {
        ss << "Qt::MouseEventSynthesizedBySystem";
      }
        break;
      default: {
        ss << event.source();
      }
        break;
      }
      ss << " windowPos = " << event.windowPos().x() << ", "
        << event.windowPos().y();
      ss << " x = " << event.x() << ", y = " << event.y();

      return ss;
    }

    std::stringstream &operator<<(std::stringstream &ss,
      const QMoveEvent &event)
    {
      ss << (*dynamic_cast<const QEvent *>(&event));
      ss << " oldPos = " << event.oldPos().x() << ", " << event.oldPos().y();
      ss << " pos = " << event.pos().x() << ", " << event.pos().y();
      return ss;
    }

    std::stringstream &operator<<(std::stringstream &ss,
      const QPaintEvent &event)
    {
      ss << (*dynamic_cast<const QEvent *>(&event));
      ss << " rect = "
        << "(x = " << event.rect().x() << ", y = "
        << event.rect().y() << " width = " << event.rect().width()
        << " height = " << event.rect().height() << ")";

      return ss;
    }

    std::stringstream &operator<<(std::stringstream &ss,
      const QResizeEvent &event)
    {
      ss << (*dynamic_cast<const QEvent *>(&event));
      ss << " oldSize = "
        << "(" << "width = " << event.oldSize().width()
        << " height = " << event.oldSize().height() << ")";
      ss << " size = "
        << "(" << "width = " << event.size().width()
        << " height = " << event.size().height() << ")";
      return ss;
    }

    std::stringstream &operator<<(std::stringstream &ss,
      const QShowEvent &event)
    {
      ss << (*dynamic_cast<const QEvent *>(&event));

      return ss;
    }

    std::stringstream &operator<<(std::stringstream &ss,
      const QWheelEvent &event)
    {
      ss << (*dynamic_cast<const QEvent *>(&event));
      ss << " angleDelta = " << event.angleDelta().x() << ", "
        << event.angleDelta().y();
      ss << " buttons = " << event.buttons();
      ss << " globalPos = " << event.globalPos().x() << ", "
        << event.globalPos().y();
      ss << " globalPosF = " << event.globalPosF().x() << ", "
        << event.globalPosF().y();
      ss << " phase = ";
      switch (event.phase()) {
      case Qt::ScrollBegin: {
        ss << "Qt::ScrollBegin";
      }
        break;
      case Qt::ScrollUpdate: {
        ss << "Qt::ScrollUpdate";
      }
        break;
      case Qt::ScrollEnd: {
        ss << "Qt::ScrollEnd";
      }
        break;
      default: {
        ss << event.phase();
      }
        break;
      }
      ss << " pixelDelta = " << event.pixelDelta().x() << ", "
        << event.pixelDelta().y();
      ss << " pos = " << event.pos().x() << ", " << event.pos().y();
      ss << " posF = " << event.posF().x() << ", " << event.posF().y();
      ss << " source = ";
      switch (event.source()) {
      case Qt::MouseEventNotSynthesized: {
        ss << "Qt::MouseEventNotSynthesized";
      }
        break;
      case Qt::MouseEventSynthesizedBySystem: {
        ss << "Qt::MouseEventSynthesizedBySystem";
      }
        break;
      case Qt::MouseEventSynthesizedByQt: {
        ss << "Qt::MouseEventSynthesizedByQt";
      }
        break;
      default: {
        ss << event.source();
      }
        break;
      }
      ss << " x = " << event.x() << ", y = " << event.y();

      return ss;
    }
  }
}
