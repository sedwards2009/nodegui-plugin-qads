import { checkIfNativeElement, NativeElement, QAbstractButton, QAbstractButtonSignals, QFrame, QFrameSignals, QRect, QWidget, QWidgetSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';
import { CDockAreaTitleBar } from './CDockAreaTitleBar';
import { DockWidgetArea, TitleBarButton } from './adsGlobals';
import { CDockManager } from './CDockManager';
import { CDockContainerWidget } from './CDockContainerWidget';
import { CDockWidget } from './CDockWidget';


export class CDockAreaWidget extends QFrame<CDockAreaWidgetSignals> {

  constructor(titleOrNative: string | NativeElement, arg?: QWidget<QWidgetSignals>) {
    let native: NativeElement;
    if (checkIfNativeElement(titleOrNative)) {
        native = titleOrNative as NativeElement;
    } else {
      const title: string = titleOrNative;
      if (arg != null) {
          const parent = arg as QWidget;
          native = new addon.CDockAreaWidget(title, parent.native);
      } else {
          native = new addon.CDockAreaWidget(title);
      }
    }
    super(native);
  }

  setAllowedAreas(areas: DockWidgetArea): void {
    this.native.setAllowedAreas(areas);
  }

  titleBar(): CDockAreaTitleBar {
    return wrapperCache.getWrapper(this.native.titleBar()) as CDockAreaTitleBar;
  }

  dockManager(): CDockManager {
    return wrapperCache.getWrapper(this.native.titleBar()) as CDockManager;
  }

  dockContainer(): CDockContainerWidget {
    return wrapperCache.getWrapper(this.native.titleBar()) as CDockContainerWidget;
  }

  titleBarGeometry(): QRect {
    return new QRect(this.native.titleBarGeometry());
  }

  contentAreaGeometry(): QRect {
    return new QRect(this.native.contentAreaGeometry());
  }

  dockWidgetsCount(): number {
    return this.native.dockWidgetsCount();
  }

  openDockWidgetsCount(): number {
    return this.native.openDockWidgetsCount();
  }

  currentIndex(): number {
    return this.native.currentIndex();
  }

  indexOfFirstOpenDockWidget(): number {
    return this.native.indexOfFirstOpenDockWidget();
  }

  setCurrentIndex(index: number): void {
    this.native.setCurrentIndex(index);
  }

  closeArea(): void {
    this.native.closeArea();
  }

  closeOtherAreas(): void {
    this.native.closeOtherAreas();
  }

  isCentralWidgetArea(): boolean {
    return this.native.isCentralWidgetArea();
  }

  dockWidgets(): CDockAreaWidget[] {
    return this.native.dockWidgets().map((area: any) => wrapperCache.getWrapper(area));
  }

  openedDockWidgets(): CDockWidget[] {
    return this.native.openedDockWidgets().map((area: any) => wrapperCache.getWrapper(area));
  }

  dockWidget(index: number): CDockWidget {
    return wrapperCache.getWrapper(this.native.dockWidget(index)) as CDockWidget;
  }

  currentDockWidget(): CDockWidget {
    return wrapperCache.getWrapper(this.native.currentDockWidget()) as CDockWidget;
  }

  setCurrentDockWidget(dockWidget: CDockWidget): void {
    this.native.setCurrentDockWidget(dockWidget.native);
  }

  features(): number /* DockWidgetFeatures */ {
    return this.native.features();
  }

  allowedAreas(): number /* DockWidgetAreas */ {
    return this.native.allowedAreas();
  }

  dockAreaFlags(): number /* DockAreaFlags */ {
    return this.native.dockAreaFlags();
  }

  titleBarButton(which: TitleBarButton): QAbstractButton<QAbstractButtonSignals> {
    return wrapperCache.getWrapper(this.native.titleBarButton(which)) as QAbstractButton<QAbstractButtonSignals>;
  }

  setDockAreaFlag(flag: eDockAreaFlag, on: boolean): void {
    this.native.setDockAreaFlag(flag, on);
  }

  // CLASS: CDockAreaWidget
  // TODO: 	ads::CDockWidget::DockWidgetFeatures features(ads::eBitwiseOperator Mode = ads::BitwiseAnd) const;
}

wrapperCache.registerWrapper('CDockAreaWidgetWrap', CDockAreaWidget);

export interface CDockAreaWidgetSignals extends QFrameSignals {
  tabBarClicked: (index: number) => void;
  currentChanging: (index: number) => void;
  currentChanged: (index: number) => void;
  viewToggled: (open: boolean) => void;
}

export enum eDockAreaFlag {
  HideSingleWidgetTitleBar = 0x0001,
  DefaultFlags = 0x0000
}
