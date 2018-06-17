open AssetTreeNodeType;

open FileType;

open AssetNodeType;

type state = {
  inputValue: string,
  originalName: string,
  postfix: string,
};

type action =
  | Blur
  | Change(string);

module Method = {
  let change = event => {
    let inputVal = ReactDOMRe.domElementToObj(
                     ReactEventRe.Form.target(event),
                   )##value;
    Change(inputVal);
  };
  let blur = _event => Blur;
  let triggerBlur = (dispatchFunc, value, nodeId) => {
    let editorState = StateEditorService.getState();

    editorState
    |> AssetNodeMapEditorService.unsafeGetNodeMap
    |> WonderCommonlib.SparseMapService.unsafeGet(nodeId)
    |> AssetTreeNodeUtils.renameNodeResult(value)
    |> AssetNodeMapEditorService.setResult(nodeId, _, editorState)
    |> StateEditorService.setState
    |> ignore;
    dispatchFunc(AppStore.ReLoad);
  };

  let buildFolderComponent = (state, send, nodeId) =>
    <div className="">
      <h1> (DomHelper.textEl("Folder")) </h1>
      <hr />
      <span className=""> (DomHelper.textEl("name:")) </span>
      <input
        className="input-component float-input"
        _type="text"
        value=state.inputValue
        disabled=(
          AssetUtils.isIdEqual(
            AssetTreeRootEditorService.getRootTreeNodeId
            |> StateLogicService.getEditorState,
            nodeId,
          )
        )
        onChange=(_e => send(change(_e)))
        onBlur=(_e => send(blur(_e)))
      />
    </div>;

  let buildTextureComponent = (state, send, textureId) =>
    <div className="">
      <h1> (DomHelper.textEl("Texture")) </h1>
      <hr />
      <div className="">
        <span className=""> (DomHelper.textEl("name:")) </span>
        <input
          className="input-component float-input"
          _type="text"
          value=state.inputValue
          onChange=(_e => send(change(_e)))
          onBlur=(_e => send(blur(_e)))
        />
      </div>
      <div className="">
        <span className=""> (DomHelper.textEl("Wrap S Mode:")) </span>
        <input
          className="input-component float-input"
          _type="text"
          value=state.inputValue
          onChange=(_e => send(change(_e)))
          onBlur=(_e => send(blur(_e)))
        />
      </div>
      <div className="">
        <span className=""> (DomHelper.textEl("Wrap T Mode:")) </span>
        <input
          className="input-component float-input"
          _type="text"
          value=state.inputValue
          onChange=(_e => send(change(_e)))
          onBlur=(_e => send(blur(_e)))
        />
      </div>
      <div className="">
        <span className=""> (DomHelper.textEl("Filter Mag Mode:")) </span>
        <input
          className="input-component float-input"
          _type="text"
          value=state.inputValue
          onChange=(_e => send(change(_e)))
          onBlur=(_e => send(blur(_e)))
        />
      </div>
      <div className="">
        <span className=""> (DomHelper.textEl("Filter Min Mode:")) </span>
        <input
          className="input-component float-input"
          _type="text"
          value=state.inputValue
          onChange=(_e => send(change(_e)))
          onBlur=(_e => send(blur(_e)))
        />
      </div>
    </div>;

  let buildJsonComponent = (state, send, nodeResult) =>
    <div>
      <h1> (DomHelper.textEl("Json")) </h1>
      <hr />
      <span className=""> (DomHelper.textEl("name:")) </span>
      <input
        className="input-component float-input"
        _type="text"
        value=state.inputValue
        onChange=(_e => send(change(_e)))
        onBlur=(_e => send(blur(_e)))
      />
      <p>
        (DomHelper.textEl(nodeResult.result |> OptionService.unsafeGet))
      </p>
    </div>;

  let showFolderInfo =
      (nodeResult, nodeId, {state, send}: ReasonReact.self('a, 'b, 'c)) =>
    switch (nodeResult.type_) {
    | Folder => buildFolderComponent(state, send, nodeId)
    | Texture =>
      buildTextureComponent(
        state,
        send,
        nodeResult.result |> OptionService.unsafeGet |> int_of_string,
      )
    | Json => buildJsonComponent(state, send, nodeResult)
    | _ =>
      WonderLog.Log.fatal(
        WonderLog.Log.buildFatalMessage(
          ~title="showFolderInfo",
          ~description={j|the type:$nodeResult not exist|j},
        ),
      )
    };
};

let component = ReasonReact.reducerComponent("AssetTreeInspector");

let reducer = (dispatchFunc, nodeId, action) =>
  switch (action) {
  | Change(value) => (
      state => ReasonReact.Update({...state, inputValue: value})
    )
  | Blur => (
      state =>
        switch (state.inputValue) {
        | "" => ReasonReact.Update({...state, inputValue: state.originalName})
        | value =>
          ReasonReactUtils.updateWithSideEffects(
            {...state, originalName: value}, _state =>
            Method.triggerBlur(dispatchFunc, value ++ state.postfix, nodeId)
          )
        }
    )
  };

let render = (nodeResult, nodeId, self) =>
  <article key="AssetTreeInspector" className="wonder-inspector-assetTree">
    (Method.showFolderInfo(nodeResult, nodeId, self))
  </article>;

let make =
    (
      ~store: AppStore.appState,
      ~dispatchFunc,
      ~nodeId,
      ~nodeResult,
      _children,
    ) => {
  ...component,
  initialState: () => {
    let (fileName, postfix) = FileNameUtils.handleFileName(nodeResult.name);
    {inputValue: fileName, originalName: fileName, postfix};
  },
  reducer: reducer(dispatchFunc, nodeId),
  render: self => render(nodeResult, nodeId, self),
};