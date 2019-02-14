type retainedProps = {isEngineStart: bool};

module Method = {
  let _getCanvasParentSize = parent => (
    parent##offsetWidth,
    parent##offsetHeight,
  );

  /* let _setAllAspectsWhoseAspectBasedOnCanvasSize = engineState =>
     GameObjectComponentEngineService.getAllPerspectiveCameraProjectionComponents(
       engineState,
     ); */

  let _updateViewRect = (canvasWidth, canvasHeight) =>
    StateEditorService.setState(
      StateEditorService.getState()
      |> SceneViewEditorService.updateViewRect((
           0,
           0,
           canvasWidth / 2,
           canvasHeight,
         ))
      |> GameViewEditorService.updateViewRect((
           canvasWidth / 2,
           0,
           canvasWidth / 2,
           canvasHeight,
         )),
    );

  let resizeCanvasAndViewPort = () => {
    let (width, height) =
      DomHelper.getElementById("canvasParent")
      |> DomHelperType.convertDomElementToJsObj
      |> _getCanvasParentSize;

    DomHelper.getElementById("canvas")
    |> DomHelperType.convertDomElementToJsObj
    |> ScreenEngineService.setScreenSize((width, height, width, height))
    |> ignore;

    DeviceManagerEngineService.getGl(StateEngineService.unsafeGetState())
    |> Js.Option.isSome ?
      {
        _updateViewRect(width, height) |> ignore;

        StateEngineService.unsafeGetState()
        |> PerspectiveCameraProjectionEngineService.markAllPerspectiveCameraProjectionsDirty
        |> DeviceManagerEngineService.setViewport((0, 0, width, height))
        |> DirectorEngineService.loopBody(0.)
        |> StateEngineService.setState
        |> ignore;
      } :
      ();
  };

  let buildStartedRunWebglComponent = () =>
    SceneUtils.isSceneHaveNoActiveCamera() ?
      switch (
        GameViewEditorService.getViewRect(StateEditorService.getState())
      ) {
      | None => ReasonReact.null
      | Some(_) =>
        <div className="gameViewNoCamera">
          <span className="gameViewNoCamera-text">
            (DomHelper.textEl("No Camera !"))
          </span>
        </div>
      } :
      ReasonReact.null;

  let dragWDB = MainEditorDragWDBEventHandler.MakeEventHandler.pushUndoStackWithNoCopyEngineState;
};

let component = ReasonReact.statelessComponentWithRetainedProps("MainEditor");

let _buildNotStartElement = (uiState, dispatchFunc) =>
  <article key="mainEditor" className="wonder-mainEditor-component">
    <div key="leftComponent" className="left-component">
      <div className="top-widget">
        <div id="canvasParent" key="webglParent" className="webgl-parent">
          <Canvas
            key="webgl"
            domId="canvas"
            dragWDB=(Method.dragWDB((uiState, dispatchFunc), ()))
            isWDBAssetFile=WDBNodeAssetEditorService.isWDBAssetFile
          />
        </div>
      </div>
      <div className="bottom-widget" />
    </div>
    <div key="rightComponent" className="right-component" />
  </article>;

let _buildStartedElement = (uiState, dispatchFunc) =>
  <article key="mainEditor" className="wonder-mainEditor-component">
    <div key="leftComponent" className="left-component">
      <div className="top-widget">
        <MainEditorLeftComponents uiState dispatchFunc />
        <div id="canvasParent" key="webglParent" className="webgl-parent">
          (Method.buildStartedRunWebglComponent())
          <Canvas
            key="webgl"
            domId="canvas"
            dragWDB=(Method.dragWDB((uiState, dispatchFunc), ()))
            isWDBAssetFile=WDBNodeAssetEditorService.isWDBAssetFile
          />
        </div>
      </div>
      <div className="bottom-widget">
        <MainEditorBottomComponents uiState dispatchFunc />
      </div>
    </div>
    <div key="rightComponent" className="right-component">
      <div className="inline-component inspector-parent">
        <MainEditorInspector
          uiState
          dispatchFunc
          addableComponentConfig=(
            GameObjectAllComponentParseUtils.getGameObjectAllComponentConfig()
          )
        />
      </div>
    </div>
  </article>;

let render = (uiState: AppStore.appState, dispatchFunc, _self) =>
  uiState.isEditorAndEngineStart ?
    _buildStartedElement(uiState, dispatchFunc) :
    _buildNotStartElement(uiState, dispatchFunc);

let make = (~uiState: AppStore.appState, ~dispatchFunc, _children) => {
  ...component,
  retainedProps: {
    isEngineStart: uiState.isEditorAndEngineStart,
  },
  didUpdate:
    ({oldSelf, newSelf}: ReasonReact.oldNewSelf('a, retainedProps, 'c)) =>
    uiState.isEditorAndEngineStart
    && oldSelf.retainedProps != newSelf.retainedProps ?
      Method.resizeCanvasAndViewPort() : (),
  didMount: _self => {
    Js.Promise.(
      MainUtils.start()
      |> then_(_ => {
           (
             editorState =>
               editorState
               |> TreeAssetEditorService.createTree
               |> StateEditorService.setState
           )
           |> StateLogicService.getAndSetEditorState;

           dispatchFunc(AppStore.StartEngineAction) |> resolve;
         })
      |> ignore
    );

    EventHelper.onresize(Method.resizeCanvasAndViewPort);
  },
  render: self => render(uiState, dispatchFunc, self),
};