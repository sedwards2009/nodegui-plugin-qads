import { checkIfNativeElement, NativeElement, QAbstractButton, QAbstractButtonSignals, QFrame, QFrameSignals, QWidget, QWidgetSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';
import { CDockAreaTabBar } from './CDockAreaTabBar';
import { CDockAreaWidget } from './CDockAreaWidget';
import { TitleBarButton } from './adsGlobals';


export class CDockAreaTitleBar extends QFrame<CDockAreaTitleBarSignals> {

  constructor(arg?: CDockAreaWidget | NativeElement) {
    let native: NativeElement;
    if (checkIfNativeElement(arg)) {
        native = arg as NativeElement;
    } else if (arg != null) {
        const parent = arg as CDockAreaWidget;
        native = new addon.CDockAreaTitleBar(parent.native);
    }
    super(native);
  }

  // CLASS: CDockAreaTitleBar
    // ads::CElidingLabel* autoHideTitleLabel();

  insertWidget(index: number, widget: QWidget): void {
    this.native.insertWidget(index, widget.native);
  }

  indexOf(widget: QWidget): number {
    return this.native.indexOf(widget.native);
  }

  tabBar(): CDockAreaTabBar {
    return wrapperCache.getWrapper(this.native.tabBar()) as CDockAreaTabBar;
  }

  button(which: TitleBarButton): QAbstractButton<QAbstractButtonSignals> {
    const abstractButton = this.native.button(which);
    return wrapperCache.getWrapper(abstractButton) as QAbstractButton<QAbstractButtonSignals>;
  }

  updateDockWidgetActionsButtons(): void {
    this.native.updateDockWidgetActionsButtons();
  }

  titleBarButtonToolTip(button: TitleBarButton): string {
    return this.native.titleBarButtonToolTip(button);
  }
}

wrapperCache.registerWrapper('CDockAreaTitleBarWrap', CDockAreaTitleBar);

export interface CDockAreaTitleBarSignals extends QFrameSignals {
	tabBarClicked: (index: number) => void;
}
