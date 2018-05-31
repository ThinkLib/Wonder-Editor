open AssetTreeNodeType;

open AssetNodeType;

type assetRecord = {
  assetTreeRoot: option(assetTreeNodeType),
  index: int,
  currentNodeId: option(int),
  nodeMap: WonderCommonlib.SparseMapService.t(nodeResultType)
};