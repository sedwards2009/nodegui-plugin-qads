import { QFrame, QFrameSignals, QIcon, QPoint, QSize, TextElideMode, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';
import { CDockAreaWidget } from './CDockAreaWidget';
import { CDockWidget } from './CDockWidget';


export class CDockWidgetTab extends QFrame<CDockWidgetTabSignals> {

  dockAreaWidget(): CDockAreaWidget {
    return wrapperCache.getWrapper(this.native.dockAreaWidget()) as CDockAreaWidget;
  }

  dockWidget(): CDockWidget {
    return wrapperCache.getWrapper(this.native.dockWidget()) as CDockWidget;
  }

  isActiveTab(): boolean {
    return this.native.isActiveTab();
  }

  setActiveTab(active: boolean): void {
    this.native.setActiveTab(active);
  }

  setIcon(icon: QIcon): void {
    this.native.setIcon(icon.native);
  }

  icon(): QIcon {
    return new QIcon(this.native.icon());
  }

  text(): string {
    return this.native.text();
  }

  setText(title: string): void {
    this.native.setText(title);
  }

  isTitleElided(): boolean {
    return this.native.isTitleElided();
  }

  isClosable(): boolean {
    return this.native.isClosable();
  }

  setElideMode(mode: TextElideMode): void {
    this.native.setElideMode(mode);
  }

  updateStyle(): void {
    this.native.updateStyle();
  }

  iconSize(): QSize {
    return new QSize(this.native.iconSize());
  }

  setIconSize(Size: QSize): void {
    this.native.setIconSize(Size);
  }
}

wrapperCache.registerWrapper('CDockWidgetTabWrap', CDockWidgetTab);

export interface CDockWidgetTabSignals extends QFrameSignals {
  activeTabChanged: () => void;
  clicked: () => void;
  closeRequested: () => void;
  closeOtherTabsRequested: () => void;
  moved: (GlobalPos: QPoint) => void;
  elidedChanged: (elided: boolean) => void;
}

export enum DockWidgetTabFeature {
  DockWidgetTabContextMenu = 0x1,///< Show context menu
  DockWidgetTabTitle = 0x2,///< Show the tab label text
  DefaultDockWidgetTabFeatures = DockWidgetTabContextMenu | DockWidgetTabTitle,
  NoDockWidgetTabFeatures = 0x0
}
