import { QFrame, QFrameSignals, QPoint, wrapperCache } from '@nodegui/nodegui';
import { DockWidgetArea } from './adsGlobals';
import { CDockAreaWidget } from './CDockAreaWidget';
import { CDockWidget } from './CDockWidget';


export class CDockContainerWidget<Signals extends CDockContainerWidgetSignals=CDockContainerWidgetSignals> extends QFrame<Signals> {

  dumpLayout(): void {
    this.native.dumpLayout();
  }

  isFloating(): boolean {
    return this.native.isFloating();
  }

  features(): number {
    return this.native.features();
  }

  zOrderIndex(): number {
    return this.native.zOrderIndex();
  }

  hasTopLevelDockWidget(): boolean {
    return this.native.hasTopLevelDockWidget();
  }

  dockAreaCount(): number {
    return this.native.dockAreaCount();
  }

  visibleDockAreaCount(): number {
    return this.native.visibleDockAreaCount();
  }

  addDockWidget(area: DockWidgetArea, dockWidget: CDockWidget, dockAreaWidget: CDockAreaWidget = null,
      index = -1): CDockAreaWidget {
    return wrapperCache.getWrapper(this.native.addDockWidget(
      area,
      dockWidget.native,
      dockAreaWidget == null ? null : dockAreaWidget.native,
      index)) as CDockAreaWidget;
  }

  removeDockWidget(dockWidget: CDockWidget): void {
    this.native.removeDockWidget(dockWidget);
  }

  isInFrontOf(other: CDockContainerWidget): boolean {
    return this.native.isInFrontOf(other.native);
  }

  dockArea(index: number): CDockAreaWidget {
    return wrapperCache.getWrapper(this.native.dockArea(index)) as CDockAreaWidget;
  }

  dockAreaAt(globalPos: QPoint): CDockAreaWidget {
    return wrapperCache.getWrapper(this.native.dockAreaAt(globalPos)) as CDockAreaWidget;
  }

  closeOtherAreas(keepOpenArea: CDockAreaWidget): void {
    this.native.closeOtherAreas(keepOpenArea.native);
  }

  openedDockAreas(): CDockAreaWidget[] {
    return this.native.openedDockAreas().map((area: any) => wrapperCache.getWrapper(area));
  }
}

wrapperCache.registerWrapper('CDockContainerWidgetWrap', CDockContainerWidget);

export interface CDockContainerWidgetSignals extends QFrameSignals {
  // dockAreasAdded: () => void;
  // dockAreasRemoved: () => void;
  // dockAreaViewToggled: (dockArea: CDockAreaWidget, open: boolean) => void;
}
