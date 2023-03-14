import { QFrame, QFrameSignals, wrapperCache } from '@nodegui/nodegui';
// import addon from './addon';


export class CDockContainerWidget<Signals extends CDockContainerWidgetSignals> extends QFrame<Signals> {

}

wrapperCache.registerWrapper('CDockContainerWidgetWrap', CDockContainerWidget);

export interface CDockContainerWidgetSignals extends QFrameSignals {

}
