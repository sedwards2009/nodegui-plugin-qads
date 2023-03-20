import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, wrapperCache } from '@nodegui/nodegui';
import addon from './addon';
import { CDockAreaWidget } from './CDockAreaWidget';


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
