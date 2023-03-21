import { checkIfNativeElement, NativeElement, QFrame, QFrameSignals, wrapperCache } from '@nodegui/nodegui';
import { CDockAreaWidget } from './CDockAreaWidget';
// import addon from './addon';


export class CDockContainerWidget<Signals extends CDockContainerWidgetSignals=CDockContainerWidgetSignals> extends QFrame<Signals> {
}

wrapperCache.registerWrapper('CDockContainerWidgetWrap', CDockContainerWidget);

export interface CDockContainerWidgetSignals extends QFrameSignals {
	// dockAreasAdded: () => void;
	// dockAreasRemoved: () => void;
	// dockAreaViewToggled: (dockArea: CDockAreaWidget, open: boolean) => void;
}
