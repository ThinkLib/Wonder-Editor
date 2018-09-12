open Wonder_jest;

open Expect;

open Expect.Operators;

open Sinon;

open MainEditorTransform;

let _ =
  describe("MainEditor CameraProjection", () => {
    let sandbox = getSandboxDefaultVal();
    beforeEach(() => {
      sandbox := createSandbox();

      MainEditorSceneTool.initState(~sandbox, ());
    });
    afterEach(() => restoreSandbox(refJsObjToSandbox(sandbox^)));

    describe("test set currentSceneTreeNode to be camera", () => {
      beforeEach(() =>
        MainEditorSceneTool.createDefaultScene(
          sandbox,
          MainEditorSceneTool.setSceneFirstCameraToBeCurrentSceneTreeNode,
        )
      );
      describe("test cameraProjection's attribute set in engine", () => {
        describe("test change CameraProjection near", () =>
          test("test change near should set into engine", () => {
            let currentGameObjectPerspectiveCamera =
              GameObjectTool.getCurrentGameObjectPerspectiveCamera();
            let value = 10.1;

            let nearDomIndex =
              MainEditorCameraProjectionTool.getNearDomIndex();

            MainEditorCameraProjectionTool.triggerPerspectiveCameraChangeAndBlurEvent(
              nearDomIndex,
              value,
            );

            StateEngineService.unsafeGetState()
            |> PerspectiveCameraProjectionEngineService.getPerspectiveCameraNear(
                 currentGameObjectPerspectiveCamera,
               )
            |. FloatService.truncateFloatValue(5)
            |> expect == value;
          })
        );

        describe("test change CameraProjection far", () =>
          test("test change far should set into engine", () => {
            let currentGameObjectPerspectiveCamera =
              GameObjectTool.getCurrentGameObjectPerspectiveCamera();
            let value = 120.1123;

            let farDomIndex = MainEditorCameraProjectionTool.getFarDomIndex();

            MainEditorCameraProjectionTool.triggerPerspectiveCameraChangeAndBlurEvent(
              farDomIndex,
              value,
            );

            StateEngineService.unsafeGetState()
            |> PerspectiveCameraProjectionEngineService.getPerspectiveCameraFar(
                 currentGameObjectPerspectiveCamera,
               )
            |. FloatService.truncateFloatValue(5)
            |> expect == value;
          })
        );

        /* describe("test change CameraProjection aspect", () =>
             test("test change aspect should set into engine", () => {
               let currentGameObjectPerspectiveCamera =
                 GameObjectTool.getCurrentGameObjectPerspectiveCamera();
               let value = 320.123;

               let aspectDomIndex =
                 MainEditorCameraProjectionTool.getAspectDomIndex();

               MainEditorCameraProjectionTool.triggerPerspectiveCameraChangeAndBlurEvent(
                 aspectDomIndex,
                 value,
               );

               (
                 StateEngineService.unsafeGetState()
                 |> PerspectiveCameraProjectionEngineService.getPerspectiveCameraAspect(
                      DiffComponentTool.getEditEngineComponent(
                        DiffType.PerspectiveCamera,
                        currentGameObjectPerspectiveCamera,
                      ),
                    )
                 |. FloatService.truncateFloatValue(5),
                 StateEngineService.unsafeGetState();
                 |> PerspectiveCameraProjectionEngineService.getPerspectiveCameraAspect(
                      currentGameObjectPerspectiveCamera,
                    )
                 |. FloatService.truncateFloatValue(5),
               )
               |> expect == (value, value);
             })
           ); */
        describe("test change CameraProjection fovy", () =>
          test("test change fovy should set into engine", () => {
            let currentGameObjectPerspectiveCamera =
              GameObjectTool.getCurrentGameObjectPerspectiveCamera();
            let value = 32.123;

            let fovyDomIndex =
              MainEditorCameraProjectionTool.getFovyDomIndex();

            MainEditorCameraProjectionTool.triggerPerspectiveCameraChangeAndBlurEvent(
              fovyDomIndex,
              value,
            );

            StateEngineService.unsafeGetState()
            |> PerspectiveCameraProjectionEngineService.getPerspectiveCameraFovy(
                 currentGameObjectPerspectiveCamera,
               )
            |. FloatService.truncateFloatValue(5)
            |> expect == value;
          })
        );
      });
    });
  });