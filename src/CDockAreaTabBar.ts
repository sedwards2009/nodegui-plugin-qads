import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';
import { CDockAreaWidget } from './CDockAreaWidget';
import { CDockWidgetTab } from './CDockWidgetTab';


export class CDockAreaTabBar extends QFrame<CDockAreaTabBarSignals> {

  constructor(arg?: CDockAreaWidget | NativeElement) {
    let native: NativeElement;
    if (checkIfNativeElement(arg)) {
        native = arg as NativeElement;
    } else if (arg != null) {
        const parent = arg as CDockAreaWidget;
        native = new addon.CDockAreaTabBar(parent.native);
    }
    super(native);
  }

// CLASS: CDockAreaTabBar
// void insertTab(int index, ads::CDockWidgetTab* Tab);
// void removeTab(ads::CDockWidgetTab* tab);

  currentTab(): CDockWidgetTab {
    return wrapperCache.getWrapper(this.native.currentTab()) as CDockWidgetTab;
  }

  tab(index: number): CDockWidgetTab {
    return wrapperCache.getWrapper(this.native.tab(index)) as CDockWidgetTab;
  }

  count(): number {
    return this.native.count();
  }

  currentIndex(): number {
    return this.native.currentIndex();
  }

  isTabOpen(index: number): boolean {
    return this.native.isTabOpen(index);
  }

  elidedChanged(elided: boolean): void {
    this.native.elidedChanged(elided);
  }

  setCurrentIndex(index: number): void {
    this.native.setCurrentIndex(index);
  }

  closeTab(index: number): void {
    this.native.closeTab(index);
  }
}

wrapperCache.registerWrapper('CDockAreaTabBarWrap', CDockAreaTabBar);

export interface CDockAreaTabBarSignals extends QFrameSignals {
	currentChanging: (index: number) => void;
	currentChanged: (index: number) => void;
	tabBarClicked: (index: number) => void;
	tabCloseRequested: (index: number) => void;
	tabClosed: (index: number) => void;
	tabOpened: (index: number) => void;
	tabMoved: (from: number, to: number) => void;
	removingTab: (index: number) => void;
	tabInserted: (index: number) => void;
}
